#ifndef CHANNELHEADERPARSER_HH
#define CHANNELHEADERPARSER_HH

//Custom
#include "unpackers/parsers/Parser.hh"
#include "dataProducts/ChannelHeader.hh"

// Bit locations and masks for WFD5 channel format:
#define RiderCH_MAGIC_WORD 0
#define RiderWF_MAGIC_WORD 0
#define RiderCH_MAGIC_BIT 62
#define RiderWF_MAGIC_BIT 62
#define RiderCH_MAGIC_MASK 0x3
#define RiderWF_MAGIC_MASK 0x3
#define ChannelTag_WORD 0
#define ChannelTag_BIT 46
#define ChannelTag_MASK 0xfff
#define WaveformGap_WORD 0
#define WaveformGap_BIT 24
#define WaveformGap_MASK 0x3fffff
#define WaveformCount_WORD 0
#define WaveformCount_BIT 12
#define WaveformCount_MASK 0xfff
#define DDR3Address_2_WORD 0
#define DDR3Address_2_BIT 0
#define DDR3Address_2_MASK 0xfff
#define TrigNum_WORD 1
#define TrigNum_BIT 0
#define TrigNum_MASK 0xffffff
#define RCH_FillType_WORD 1
#define RCH_FillType_BIT 24
#define RCH_FillType_MASK 0x7
#define WaveformLength_WORD 1
#define WaveformLength_BIT 27
#define WaveformLength_MASK 0x7fffff
#define DDR3Address_1_WORD 1
#define DDR3Address_1_BIT 50
#define DDR3Address_1_MASK 0x3fff
#define ChannelChecksum1_BIT 0
#define ChannelChecksum1_MASK 0xffffffffffffffff
#define ChannelChecksum2_BIT 0
#define ChannelChecksum2_MASK 0xffffffffffffffff
#define DataIntCheck_WORD 2
#define DataIntCheck_BIT 32
#define DataIntCheck_MASK 0xffffffff
#define DataTransTime_BIT 0
#define DataTransTime_MASK 0xffffffff

namespace parsers {

    class ChannelHeaderParser : public Parser {
        
    public:
        
        //Constructor
        ChannelHeaderParser();

        //Destructor
        ~ChannelHeaderParser();

        //Method to make the data product
        std::unique_ptr<dataProducts::ChannelHeader>
        NewDataProduct(unsigned int crateNum
                    ,unsigned int amcNum);

        uint32_t DDR3Address_1() const;
        uint32_t DDR3Address_2() const;
        uint32_t DDR3Address() const;
        uint32_t WaveformCount() const;
        uint32_t WaveformGap() const;
        uint32_t ChannelTag() const;
        uint32_t TrigNum() const;
        uint32_t FillType() const;
        uint32_t WaveformLength() const;
        uint32_t DataIntCheck() const;

        //Print method
        std::ostringstream Stream() override;
        void Print() override;

    private:
        const std::string className_ = "ChannelHeaderParser";

    };
}

#endif // CHANNELHEADERPARSER_HH