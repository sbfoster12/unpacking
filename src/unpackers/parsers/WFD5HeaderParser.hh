#ifndef WFD5HEADERPARSER_HH
#define WFD5HEADERPARSER_HH

//Custom
#include "unpackers/parsers/Parser.hh"
#include "dataProducts/WFD5Header.hh"

// Bit locations and masks for AMCPayload format:
#define AMCNo_WORD 0
#define AMCNo_BIT 56
#define AMCNo_MASK 0xf
#define DataLength_WORD 0
#define DataLength_BIT 0
#define DataLength_MASK 0xfffff
#define ChannelsEnabled_WORD 1 
#define ChannelsEnabled_BIT 59
#define ChannelsEnabled_MASK 0x1f
#define BoardType_WORD 1 
#define BoardType_BIT 13 
#define BoardType_MASK 0x7
#define WFD5_BT 1
#define FC7_BT 2
#define Endianness_WORD 1
#define Endianness_BIT 58
#define Endianness_MASK 0x1
#define EMPTYEVENT_WORD 1  
#define EMPTYEVENT_BIT 53
#define EMPTYEVENT_MASK 0x1

namespace parsers {

    class WFD5HeaderParser : public Parser {
        
    public:
        
        //Constructor
        WFD5HeaderParser();

        //Destructor
        ~WFD5HeaderParser();

        //Method to make the data product
        dataProducts::WFD5Header CreateDataProduct();

        //Get methods
        uint32_t        AMCNo() const ;
        uint32_t        DataLength() const ;
        unsigned int    NumEnabledChannels() const ;
        uint32_t        BoardType() const ;
        std::string     BoardTypeString()const ;
        uint32_t        Endianness() const ;
        bool            EmptyEvent() const ;

    private:
        const std::string className_ = "WFD5HeaderParser";

    };
}

#endif // WFD5HEADERPARSER_HH