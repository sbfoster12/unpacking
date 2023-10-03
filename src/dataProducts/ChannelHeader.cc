#include "ChannelHeader.hh"

using namespace dataProducts;

ChannelHeader::ChannelHeader()
    : DataProduct(),
    crateNum(0),
    amcNum(0),
    waveformCount(0),
    waveformGap(0),
    channelTag(0),
    triggerNum(0),
    fillType(0),
    waveformLength(0),
    DDR3Address(0),
    passedIntegrityCheck(false)
{};

ChannelHeader::~ChannelHeader() {};

void ChannelHeader::Print() const {
    std::ostringstream oss;
    oss << std::endl;
    oss << "ChannelHeader:" << std::endl;
    oss << "    crateNum: " << crateNum << std::endl;
    oss << "    amcNum: " << amcNum << std::endl;
    oss << "    waveformCount: " << waveformCount << std::endl;
    oss << "    waveformGap: " << waveformGap << std::endl;
    oss << "    channelTag: " << channelTag << std::endl;
    oss << "    triggerNum: " << triggerNum << std::endl;
    oss << "    fillType: " << fillType << std::endl;
    oss << "    waveformLength: " << waveformLength << std::endl;
    oss << "    DDR3Address: " << DDR3Address << std::endl;
    oss << "    passedIntegrityCheck: " << (passedIntegrityCheck ? "true" : "false") << std::endl;
    std::cout << oss.str();
}