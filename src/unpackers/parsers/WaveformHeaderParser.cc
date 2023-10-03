#include "WaveformHeaderParser.hh"

using namespace parsers;

WaveformHeaderParser::WaveformHeaderParser() : Parser() {};

WaveformHeaderParser::~WaveformHeaderParser() {};

dataProducts::WaveformHeader WaveformHeaderParser::CreateDataProduct() {
    
    //create the data product
    auto WaveformHeader = dataProducts::WaveformHeader();
    
    //fill it

    //return it
    return WaveformHeader;
}

//Get methods

uint32_t WaveformHeaderParser::WaveformLength() const { return (GetWord(RWF_WaveformLength_WORD) >> RWF_WaveformLength_BIT) & RWF_WaveformLength_MASK; }