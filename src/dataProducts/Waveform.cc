#include "Waveform.hh"

using namespace dataProducts;

Waveform::Waveform()
    : DataProduct(),
    crateNum(0),
    amcSlot(0), 
    channelTag(0),
    eventNum(0),
    length(0),
    pedestalLevel(0),
    trace()
{}
    
Waveform::~Waveform() {}

void Waveform::PrintMembers() const {
    std::ostringstream oss;
    oss << std::endl;
    oss << "Waveform:" << std::endl;
    oss << "    crateNum: " << crateNum << std::endl;
    oss << "    amcSlot: " << amcSlot << std::endl;
    oss << "    channelTag: " << channelTag << std::endl;
    oss << "    eventNum: " << eventNum << std::endl;
    oss << "    pedestalLevel: " << pedestalLevel << std::endl;
    oss << "    trace.size(): " << trace.size() << std::endl;
    std::cout << oss.str();
}