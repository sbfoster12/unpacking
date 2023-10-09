#ifndef BANKUNPACKER_HH
#define BANKUNPACKER_HH

//Standard
#include <iostream>
#include <string>
#include <map>

//Custom
#include "midas/midasio.h"
#include "unpackers/Unpacker.hh"
#include "unpackers/PayloadUnpacker.hh"

namespace unpackers {

    class BankUnpacker : public Unpacker {
        
    public:
        
        //Constructor
        BankUnpacker();

        //Destructor
        virtual ~BankUnpacker();

        // Virtual function to read the event
        virtual void UnpackBank(TMEvent* event, const std::string& bankName) = 0;

        void UpdateEventNum(int eventNum);
        void UpdateCrateNum(int crateNum);

    private:
        //class name
        const std::string className_;

    protected:
        //unpackers
        std::map<int,std::unique_ptr<unpackers::PayloadUnpacker>> payloadUnpackers_;

    };
}

#endif // BANKUNPACKER_HH