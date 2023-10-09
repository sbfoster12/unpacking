#include "FC7HeaderParser.hh"

using namespace parsers;

FC7HeaderParser::FC7HeaderParser() : Parser() {};

FC7HeaderParser::~FC7HeaderParser() {};

dataProducts::FC7Header FC7HeaderParser::CreateDataProduct() {
    
    //create the data product
    auto FC7header = dataProducts::FC7Header();
    
    //fill it
    FC7header.amcNum = this->AMCNo();

    //return it
    return FC7header;
}

//Get methods
uint32_t FC7HeaderParser::AMCNo() const { return (GetWord(AMCNo_WORD) >> AMCNo_BIT) & AMCNo_MASK; }
uint32_t FC7HeaderParser::DataLength() const {return (GetWord(DataLength_WORD) >> DataLength_BIT) & DataLength_MASK;}
uint32_t FC7HeaderParser::BoardType() const {return (GetWord(BoardType_WORD) >> BoardType_BIT) & BoardType_MASK; }
std::string FC7HeaderParser::BoardTypeString() const {
    auto boardType = this->BoardType();
    if (boardType == WFD5_BT) {
        return "WFD5";
    } else if (boardType == FC7_BT) {
        return "FC7";
    } else {
        std::cerr << "Error: the board type doesn't match a WFD5 or an FC7\n"
        << "Location: FC7HeaderParser::BoardTypeString\n"
        << "Details: the board type found was " << boardType << std::endl;
        exit(1);
    }
}

void FC7HeaderParser::Print() {
}