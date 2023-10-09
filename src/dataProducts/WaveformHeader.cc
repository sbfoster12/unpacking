#include "WaveformHeader.hh"

using namespace dataProducts;

WaveformHeader::WaveformHeader()
    : DataProduct(),
    crateNum(0),
    amcNum(0),
    waveformCount(0),
    waveformGap(0),
    channelTag(0),
    waveformIndex(0),
    fillType(0),
    waveformLength(0),
    DDR3Address(0) {}

            
WaveformHeader::~WaveformHeader() {};

void WaveformHeader::PrintMembers() const {
    std::ostringstream oss;
    oss << std::endl;
    oss << "WaveformHeader: " << std::endl;
    oss << "    crateNum: " << crateNum << std::endl;
    oss << "    amcNum: " << amcNum << std::endl;
    oss << "    waveformCount: " << waveformCount << std::endl;
    oss << "    waveformGap: " << waveformGap << std::endl;
    oss << "    channelTag: " << channelTag << std::endl;
    oss << "    waveformIndex: " << waveformIndex << std::endl;
    oss << "    fillType: " << fillType << std::endl;
    oss << "    waveformLength: " << waveformLength << std::endl;
    oss << "    DDR3Address: " << DDR3Address << std::endl;
    std::cout << oss.str();
}