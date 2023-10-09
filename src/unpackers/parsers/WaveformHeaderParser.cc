#include "WaveformHeaderParser.hh"

using namespace parsers;

WaveformHeaderParser::WaveformHeaderParser() : Parser() {};

WaveformHeaderParser::~WaveformHeaderParser() {};

std::unique_ptr<dataProducts::WaveformHeader> WaveformHeaderParser::NewDataProduct() {
    return std::make_unique<dataProducts::WaveformHeader>();
}

//Get methods

uint32_t WaveformHeaderParser::WaveformLength() const { return (GetWord(RWF_WaveformLength_WORD) >> RWF_WaveformLength_BIT) & RWF_WaveformLength_MASK; }

void WaveformHeaderParser::Print() {
}