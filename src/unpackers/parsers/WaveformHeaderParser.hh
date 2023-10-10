#ifndef WAVEFORMHEADERPARSER_HH
#define WAVEFORMHEADERPARSER_HH

//Custom
#include "unpackers/parsers/Parser.hh"
#include "dataProducts/WaveformHeader.hh"

// Bit locations and masks for waveform header format:
#define RWF_MAGIC_WORD 0
#define RWF_MAGIC_BIT 62
#define RWF_MAGIC_MASK 0x3
#define RWF_WaveformCount_WORD 0
#define RWF_WaveformCount_BIT 52
#define RWF_WaveformCount_MASK 0xfff
#define RWF_DDR3Address_WORD 0
#define RWF_DDR3Address_BIT 26
#define RWF_DDR3Address_MASK 0x3ffffff
#define RWF_FillType_WORD 0
#define RWF_FillType_BIT 23
#define RWF_FillType_MASK 0x7
#define RWF_WaveformLength_WORD 0
#define RWF_WaveformLength_BIT 0
#define RWF_WaveformLength_MASK 0x7fffff
#define RWF_ChannelTag_WORD 1
#define RWF_ChannelTag_BIT 34
#define RWF_ChannelTag_MASK 0xfff
#define RWF_WaveformGap_WORD 1
#define RWF_WaveformGap_BIT 12
#define RWF_WaveformGap_MASK 0x3fffff
#define RWF_WaveformIndex_WORD 1
#define RWF_WaveformIndex_BIT 0
#define RWF_WaveformIndex_MASK 0xfff

namespace parsers {

    class WaveformHeaderParser : public Parser {
        
    public:
        
        //Constructor
        WaveformHeaderParser();

        //Destructor
        ~WaveformHeaderParser();

        //Method to make the data product
        std::unique_ptr<dataProducts::WaveformHeader>
        NewDataProduct(unsigned int crateNum
                    ,unsigned int amcNum); 

        //Get methods
        uint32_t WaveformCount() const;
        uint32_t DDR3Address() const;
        uint32_t FillType() const;
        uint32_t WaveformLength() const;
        uint32_t ChannelTag() const;
        uint32_t WaveformGap() const;
        uint32_t WaveformIndex() const;

        //Print method
        std::ostringstream Stream() override;
        void Print() override;

    private:
        const std::string className_ = "WaveformHeaderParser";

    };
}

#endif // WAVEFORMHEADERPARSER_HH