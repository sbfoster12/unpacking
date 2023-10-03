#ifndef WFD5UNPACKER_HH
#define WFD5UNPACKER_HH

//Custom
#include "dataProducts/WFD5Header.hh"
#include "dataProducts/Waveform.hh"

#include "unpackers/utils/Logger.hh"
#include "unpackers/PayloadUnpacker.hh"
#include "unpackers/UnpackerHelpers.hh"
#include "unpackers/parsers/WFD5HeaderParser.hh"
#include "unpackers/parsers/ChannelHeaderParser.hh"
#include "unpackers/parsers/WaveformHeaderParser.hh"
#include "unpackers/parsers/WaveformParser.hh"

namespace unpackers {

    class WFD5Unpacker : public PayloadUnpacker {
        
    public:
        
        //Constructor
        WFD5Unpacker();

        //Destructor
        ~WFD5Unpacker();

        void Unpack(const uint64_t* words, unsigned int& wordNum) override;

        void RegisterDataProducts(std::map<std::string,std::shared_ptr<dataProducts::DataProductPtrCollection>>& basePtrCol) override;

        //Collections
        std::shared_ptr<dataProducts::DataProductPtrCollection> WFD5HeaderPtrCol_;
        std::shared_ptr<dataProducts::DataProductPtrCollection> waveformPtrCol_;

    private:
        const std::string className_ = "WFD5Unpacker";

        //Parsers
        std::unique_ptr<parsers::WFD5HeaderParser> WFD5HeaderParser_;
        std::unique_ptr<parsers::ChannelHeaderParser> ChannelHeaderParser_;
        std::unique_ptr<parsers::WaveformHeaderParser> WaveformHeaderParser_;
        std::unique_ptr<parsers::WaveformParser> WaveformParser_;
    };
}

#endif // WFD5UNPACKER_HH