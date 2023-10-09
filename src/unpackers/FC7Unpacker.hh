#ifndef FC7UNPACKER_HH
#define FC7UNPACKER_HH

//Custom
#include "unpackers/utils/Logger.hh"
#include "unpackers/PayloadUnpacker.hh"
#include "unpackers/UnpackerHelpers.hh"
#include "unpackers/parsers/FC7HeaderParser.hh"
#include "dataProducts/FC7Header.hh"

namespace unpackers {

    class FC7Unpacker : public PayloadUnpacker {
        
    public:
        
        //Constructor
        FC7Unpacker();

        //Destructor
        ~FC7Unpacker();

        void Unpack(const uint64_t* words, unsigned int& wordNum) override;

        //Collections
        std::shared_ptr<dataProducts::DataProductPtrCollection> FC7HeaderPtrCol_;

    private:
        const std::string className_ = "FC7Unpacker";

        //Parser
        std::unique_ptr<parsers::FC7HeaderParser> FC7HeaderParser_;


    };
}

#endif // FC7UNPACKER_HH