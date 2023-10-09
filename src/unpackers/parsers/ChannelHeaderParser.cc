#include "ChannelHeaderParser.hh"

using namespace parsers;

ChannelHeaderParser::ChannelHeaderParser() : Parser() {};

ChannelHeaderParser::~ChannelHeaderParser() {};

std::unique_ptr<dataProducts::ChannelHeader> ChannelHeaderParser::NewDataProduct() {
    return std::make_unique<dataProducts::ChannelHeader>();
}

//Get methods

uint32_t ChannelHeaderParser::WaveformCount() const { return (GetWord(WaveformCount_WORD) >> WaveformCount_BIT) & WaveformCount_MASK;}

uint32_t ChannelHeaderParser::ChannelTag() const { return (GetWord(ChannelTag_WORD) >> ChannelTag_BIT) & ChannelTag_MASK; }

void ChannelHeaderParser::Print() {
}