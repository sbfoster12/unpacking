#include "WFD5HeaderParser.hh"

using namespace parsers;

WFD5HeaderParser::WFD5HeaderParser() : Parser() {};

WFD5HeaderParser::~WFD5HeaderParser() {};

dataProducts::WFD5Header WFD5HeaderParser::CreateDataProduct() {
    
    //create the data product
    auto WFD5header = dataProducts::WFD5Header();
    
    //fill it
    WFD5header.amcNum = this->AMCNo();

    //return it
    return WFD5header;
}

//Get methods
uint32_t WFD5HeaderParser::AMCNo() const { return (GetWord(AMCNo_WORD) >> AMCNo_BIT) & AMCNo_MASK; }

uint32_t WFD5HeaderParser::DataLength() const {return (GetWord(DataLength_WORD) >> DataLength_BIT) & DataLength_MASK;}

unsigned int WFD5HeaderParser::NumEnabledChannels() const { 
    // the number of enabled channels is equal to the number of 1's
    // in the binary representation of nChannelsBits
    unsigned int nChannelsBits =(GetWord(ChannelsEnabled_WORD) >> ChannelsEnabled_BIT) & ChannelsEnabled_MASK;
    unsigned int nEnabledChannels = 0;
    for (; nChannelsBits > 0; nChannelsBits >>= 1) {
        nEnabledChannels += nChannelsBits & 0x1;
    }
  return nEnabledChannels;
}

uint32_t WFD5HeaderParser::BoardType() const {return (GetWord(BoardType_WORD) >> BoardType_BIT) & BoardType_MASK; }

std::string WFD5HeaderParser::BoardTypeString() const {
    auto boardType = this->BoardType();
    if (boardType == WFD5_BT) {
        return "WFD5";
    } else if (boardType == FC7_BT) {
        return "FC7";
    } else {
        std::cerr << "Error: the board type doesn't match a WFD5 or an FC7\n"
        << "Location: WFD5HeaderParser::BoardTypeString\n"
        << "Details: the board type found was " << boardType << std::endl;
        exit(1);
    }
}

uint32_t WFD5HeaderParser::Endianness() const { return (GetWord(Endianness_WORD) >> Endianness_BIT) & Endianness_MASK; }

bool WFD5HeaderParser::EmptyEvent() const { return (GetWord(EMPTYEVENT_WORD) >> EMPTYEVENT_BIT) & EMPTYEVENT_MASK; }
