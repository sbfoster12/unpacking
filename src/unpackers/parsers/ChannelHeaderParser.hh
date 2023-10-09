#ifndef CHANNELHEADERPARSER_HH
#define CHANNELHEADERPARSER_HH

//Custom
#include "unpackers/parsers/Parser.hh"
#include "dataProducts/ChannelHeader.hh"

// Bit locations and masks for WFD5 channel format:
#define WaveformCount_WORD 0
#define WaveformCount_BIT 12
#define WaveformCount_MASK 0xfff
#define ChannelTag_WORD 0
#define ChannelTag_BIT 46
#define ChannelTag_MASK 0xfff

namespace parsers {

    class ChannelHeaderParser : public Parser {
        
    public:
        
        //Constructor
        ChannelHeaderParser();

        //Destructor
        ~ChannelHeaderParser();

        //Method to make the data product
        dataProducts::ChannelHeader CreateDataProduct();

        //Get methods
        uint32_t WaveformCount() const ;
        uint32_t ChannelTag() const ;

        //Print method
        void Print() override;

    private:
        const std::string className_ = "ChannelHeaderParser";

    };
}

#endif // CHANNELHEADERPARSER_HH