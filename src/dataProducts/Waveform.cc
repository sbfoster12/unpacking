#include "Waveform.hh"

using namespace dataProducts;

Waveform::Waveform()
    : DataProduct(),
    crateNum(0),
    amcNum(0), 
    channelTag(0),
    eventNum(0),
    length(0),
    pedestalLevel(0),
    trace({})
{}

Waveform::Waveform(int crateNumArg
    ,int amcNumArg
    ,int channelTagArg
    ,int eventNumArg
    ,unsigned int lengthArg
    ,int pedestalLevelArg
    ,std::vector<short> traceArg
    ) : DataProduct()
    ,crateNum(crateNumArg)
    ,amcNum(amcNumArg)
    ,channelTag(channelTagArg)
    ,eventNum(eventNumArg)
    ,length(lengthArg)
    ,pedestalLevel(pedestalLevelArg)
    ,trace(traceArg)
{}

Waveform::~Waveform() {}

void Waveform::Show() const {
    std::ostringstream oss;
    oss << std::endl;
    oss << "Waveform:" << std::endl;
    oss << "    crateNum: " << crateNum << std::endl;
    oss << "    amcSlot: " << amcNum << std::endl;
    oss << "    channelTag: " << channelTag << std::endl;
    oss << "    eventNum: " << eventNum << std::endl;
    oss << "    pedestalLevel: " << pedestalLevel << std::endl;
    oss << "    trace.size(): " << trace.size() << std::endl;
    oss << "        trace: ";
    for (const auto & sample : trace) {
        oss << sample << ", ";
    }
    std::cout << std::endl; << oss.str();
}