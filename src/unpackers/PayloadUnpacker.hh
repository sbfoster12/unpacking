#ifndef PAYLOADUNPACKER_HH
#define PAYLOADUNPACKER_HH

//Standard
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <bitset>
#include <map>

//Custom
#include "unpackers/CollectionsHolder.hh"
#include "dataProducts/DataProduct.hh"

namespace unpackers {

    class PayloadUnpacker : public CollectionsHolder {
        
    public:
        
        //Constructor
        PayloadUnpacker();

        //Destructor
        virtual ~PayloadUnpacker();

        virtual void Unpack(const uint64_t* words, unsigned int& wordNum) = 0;

        void SetCrateNum(int crateNum);
        void SetEventNum(int eventNum);

    private:
        const std::string className_ = "PayloadUnpacker";

    protected:
        int crateNum_;
        int eventNum_;

    };
}

#endif // PAYLOADUNPACKER_HH