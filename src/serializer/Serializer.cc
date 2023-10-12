#include "Serializer.hh"

using namespace unpackers;

Serializer::Serializer() {}

Serializer::Serializer(std::string inputFile, int run, int subRun, int event) 
    : inputFile_(inputFile)
    ,run_(run)
    ,subRun_(subRun)
    ,event_(event)
{
    this->LoadChannelMapping();
}

Serializer::~Serializer() {}

void Serializer::SetRun(int run) { run_ = run; }
void Serializer::SetSubRun(int subRun) { subRun_ = subRun; }
void Serializer::SetEvent(int event) { event_ = event; }

std::string Serializer::GetString() const {
    nlohmann::json json_object = {
        {"run", run_}
        ,{"subRun", subRun_}
        ,{"event", event_}
    };

    std::cout << traces_.size() << std::endl;
    for (const auto& val : traces_) {
        json_object["n_"+val.first] = val.second.size();
        json_object["traces_"+val.first] = val.second;
    }
    return json_object.dump();
}

void Serializer::LoadChannelMapping() {
    boost::property_tree::ptree pt;

    if (!std::filesystem::exists(inputFile_)) {
        std::cerr << "Channel mapping file doesn't exist\n"
        << "File path = " << inputFile_ << "\n";
        exit(1);
    }

    try {
        boost::property_tree::read_json(inputFile_, pt);
    } catch (boost::property_tree::json_parser_error const &ex) {
        std::cerr << "Error parsing JSON: " << ex.what() << std::endl;
        exit(1);
    }

    for (const auto& detectorType : pt.get_child("detectors")) {
        for (const auto& detector : detectorType.second) {
            std::string detectorName = detector.second.get<std::string>("detectorName");
            int detectorNum = detector.second.get<int>("detectorNum");
            int crateNum = detector.second.get<int>("crateNum");
            int amcNum = detector.second.get<int>("amcSlotNum");
            int channelNum = detector.second.get<int>("channelNum");

            if (detectorMap_.find(std::make_tuple(crateNum,amcNum,channelNum)) == detectorMap_.end()) {
                detectorMap_[std::make_tuple(crateNum,amcNum,channelNum)] = std::make_pair(detectorName,detectorNum);
            } else {
                std::cerr << "Provided detector mapping has a duplicate entry for\n"
                << "crateNum=" << crateNum << ", amcNum=" << amcNum << ", channelNum=" << channelNum << "\n";
                exit(1); 
            }
        }
    }

    //set the sizes
    nDetectorsMap_["lyso"] = pt.get_child("detectors.lyso").size();
    nDetectorsMap_["nai"] = pt.get_child("detectors.nai").size();
    nDetectorsMap_["t0"] = pt.get_child("detectors.t0").size();
    nDetectorsMap_["hodo_x"] = pt.get_child("detectors.hodo_x").size();
    nDetectorsMap_["hodo_y"] = pt.get_child("detectors.hodo_y").size();

    // for (const auto& val : detectorMap_) {
    //     std::cout << "Detector Name: " << val.second.first << std::endl;
    //     std::cout << "Detector Number: " << val.second.second << std::endl;
    //     std::cout << "Crate Number: " << std::get<0>(val.first) << std::endl;
    //     std::cout << "AMC Slot Number: " << std::get<1>(val.first) << std::endl;
    //     std::cout << "Channel Number: " << std::get<2>(val.first) << std::endl;
    //     std::cout << std::endl;
    // }



}

void Serializer::SetWaveforms(const dataProducts::WaveformCollection& inputWaveforms) {
    for (const auto& val : nDetectorsMap_) {
        std::string detectorName = val.first;
        int nChannels = val.second;

        std::vector<std::vector<short>> outputTraces(nChannels);

        for (const auto& waveform : inputWaveforms) {
            auto pair = detectorMap_[std::make_tuple(waveform.crateNum,waveform.amcNum,waveform.channelTag)];
            if (pair.first == detectorName) {
                if ((size_t)pair.second <= outputTraces.size()) {
                    if (outputTraces[pair.second].size() == 0) {
                        outputTraces[pair.second] = waveform.trace;
                    } else {
                        std::cerr << "This detector number already has a trace\n";
                        exit(1);
                    }
                } else {
                    std::cerr << "The index for this detector is larger than the expected size\n";
                    exit(1);
                }
            }
        } // loop over waveforms

        //store these traces in the map
        traces_[detectorName] = std::move(outputTraces);
    } // loop over detectors
}
