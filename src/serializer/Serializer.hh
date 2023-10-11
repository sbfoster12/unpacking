#ifndef SERIALIZER_HH
#define SERIALIZER_HH

//Standard
#include <iostream>
#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <nlohmann/json.hpp>

//Custom
#include "dataProducts/Waveform.hh"

namespace unpackers {

    class Serializer {
        
    public:
        
        //Constructor
        Serializer(std::string inputFile);

        //Destructor
        ~Serializer();

        void LoadChannelMapping();

        void SetRun(int run);
        void SetSubRun(int subRun);
        void SetEvent(int event);
        void SetWaveforms(const dataProducts::WaveformCollection& inputWaveforms);

        std::string GetString() const;

    private:

        std::string inputFile_;

        int run_;
        int subRun_;
        int event_;

        std::map<std::string,int> nDetectorsMap_; //number of detectors for each detector type
        std::map<std::tuple<int,int,int>,std::pair<std::string,int>> detectorMap_; // (crateNum,amcNum,channelTag) -> (detector name, index)

        std::map<std::string,std::vector<std::vector<short>>> traces_; //map to collection of traces for each detector

    protected:


    };
}

#endif //SERIALIZERR_HH