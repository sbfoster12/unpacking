#include "ChannelHeaderParser.hh"

using namespace parsers;

ChannelHeaderParser::ChannelHeaderParser() : Parser() {};

ChannelHeaderParser::~ChannelHeaderParser() {};

dataProducts::ChannelHeader ChannelHeaderParser::CreateDataProduct() {
	
	//create the data product
	auto ChannelHeader = dataProducts::ChannelHeader();
	
	//fill it

	//return it
	return ChannelHeader;
}

//Get methods

uint32_t ChannelHeaderParser::WaveformCount() const { return (GetWord(WaveformCount_WORD) >> WaveformCount_BIT) & WaveformCount_MASK;}

uint32_t ChannelHeaderParser::ChannelTag() const { return (GetWord(ChannelTag_WORD) >> ChannelTag_BIT) & ChannelTag_MASK; }