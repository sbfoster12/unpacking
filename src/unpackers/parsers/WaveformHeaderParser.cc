#include "WaveformHeaderParser.hh"

using namespace parsers;

WaveformHeaderParser::WaveformHeaderParser() : Parser() {};

WaveformHeaderParser::~WaveformHeaderParser() {};

std::unique_ptr<dataProducts::WaveformHeader>
WaveformHeaderParser::NewDataProduct(unsigned int crateNum
                                    ,unsigned int amcNum) {
    return std::make_unique<dataProducts::WaveformHeader>(
                crateNum
                ,amcNum
                ,WaveformCount()
                ,WaveformGap()
                ,ChannelTag()
                ,WaveformIndex()
                ,FillType()
                ,WaveformLength()
                ,DDR3Address()
            );
}

//Get methods
uint32_t WaveformHeaderParser::WaveformCount() const { return (GetWord(RWF_WaveformCount_WORD) >> RWF_WaveformCount_BIT) & RWF_WaveformCount_MASK; }
uint32_t WaveformHeaderParser::DDR3Address() const { return (GetWord(RWF_DDR3Address_WORD) >> RWF_DDR3Address_BIT) & RWF_DDR3Address_MASK; }
uint32_t WaveformHeaderParser::FillType() const { return (GetWord(RWF_FillType_WORD) >> RWF_FillType_BIT) & RWF_FillType_MASK; }
uint32_t WaveformHeaderParser::WaveformLength() const { return (GetWord(RWF_WaveformLength_WORD) >> RWF_WaveformLength_BIT) & RWF_WaveformLength_MASK; }
uint32_t WaveformHeaderParser::ChannelTag() const { return (GetWord(RWF_ChannelTag_WORD) >> RWF_ChannelTag_BIT) & RWF_ChannelTag_MASK; }
uint32_t WaveformHeaderParser::WaveformGap() const { return (GetWord(RWF_WaveformGap_WORD) >> RWF_WaveformGap_BIT) & RWF_WaveformGap_MASK; }
uint32_t WaveformHeaderParser::WaveformIndex() const { return (GetWord(RWF_WaveformIndex_WORD) >> RWF_WaveformIndex_BIT) & RWF_WaveformIndex_MASK;}

void WaveformHeaderParser::Print() {
    std::cout << "\t\t\t---> WaveformIndex: " << WaveformIndex() << std::endl;
    std::cout << "\t\t\tFillType: " << FillType() << std::endl;
    std::cout << "\t\t\tWaveformGap: " << WaveformGap() << std::endl;
    std::cout << "\t\t\tWaveformCount: " << WaveformCount() << std::endl;
    std::cout << "\t\t\tWaveformLength: " << WaveformLength() << std::endl;
    std::cout << "\t\t\tChannelTag: " << ChannelTag() << std::endl;
    std::cout << "\t\t\tDDR3Address: 0x" << std::hex << DDR3Address() << std::dec << std::endl;
}