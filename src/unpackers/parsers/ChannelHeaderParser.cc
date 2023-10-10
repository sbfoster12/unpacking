#include "ChannelHeaderParser.hh"

using namespace parsers;

ChannelHeaderParser::ChannelHeaderParser() : Parser() {};

ChannelHeaderParser::~ChannelHeaderParser() {};

std::unique_ptr<dataProducts::ChannelHeader>
ChannelHeaderParser::NewDataProduct(unsigned int crateNum
                                    ,unsigned int amcNum) {
    return std::make_unique<dataProducts::ChannelHeader>(
                crateNum
                ,amcNum
                ,WaveformCount()
                ,WaveformGap()
                ,ChannelTag()
                ,TrigNum()
                ,FillType()
                ,WaveformLength()
                ,DDR3Address()
                ,!DataIntCheck()
            );
}

uint32_t ChannelHeaderParser::DDR3Address_1() const { return (GetWord(DDR3Address_1_WORD) >> DDR3Address_1_BIT) & DDR3Address_1_MASK; }
uint32_t ChannelHeaderParser::DDR3Address_2() const { return (GetWord(DDR3Address_2_WORD) >> DDR3Address_2_BIT) & DDR3Address_2_MASK; }
uint32_t ChannelHeaderParser::DDR3Address() const { return (DDR3Address_2() << 14) | DDR3Address_1(); }
uint32_t ChannelHeaderParser::WaveformCount() const { return (GetWord(WaveformCount_WORD) >> WaveformCount_BIT) & WaveformCount_MASK; }
uint32_t ChannelHeaderParser::WaveformGap() const { return (GetWord(WaveformGap_WORD) >> WaveformGap_BIT) & WaveformGap_MASK; }
uint32_t ChannelHeaderParser::ChannelTag() const { return (GetWord(ChannelTag_WORD) >> ChannelTag_BIT) & ChannelTag_MASK; }
uint32_t ChannelHeaderParser::TrigNum() const { return (GetWord(TrigNum_WORD) >> TrigNum_BIT) & TrigNum_MASK; }
uint32_t ChannelHeaderParser::FillType() const { return (GetWord(RCH_FillType_WORD) >> RCH_FillType_BIT) & RCH_FillType_MASK; }
uint32_t ChannelHeaderParser::WaveformLength() const { return (GetWord(WaveformLength_WORD) >> WaveformLength_BIT) & WaveformLength_MASK; }
uint32_t ChannelHeaderParser::DataIntCheck() const { return (GetTrailerWord(DataIntCheck_WORD) >> DataIntCheck_BIT) & DataIntCheck_MASK; }

std::ostringstream ChannelHeaderParser::Stream() {
    std::ostringstream oss;
    oss << "\t\t---> Entering Channel #" << ChannelTag() << std::endl;
    oss << "\t\tFillType: " << FillType() << std::endl;
    oss << "\t\tWaveformGap: " << WaveformGap() << std::endl;
    oss << "\t\tWaveformCount: " << WaveformCount() << std::endl;
    oss << "\t\tWaveformLength: " << WaveformLength() << std::endl;
    oss << "\t\tTrigNum: " << TrigNum() << std::endl;
    oss << "\t\tDDR3Address: 0x" << std::hex << DDR3Address() << std::dec << std::endl;
    return oss;
}

void ChannelHeaderParser::Print() {
    std::cout << this->Stream().str();
}