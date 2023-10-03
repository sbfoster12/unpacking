#ifndef CRBANKUNPACKER_HH
#define CRBANKUNPACKER_HH

//Custom
#include "unpackers/utils/Logger.hh"
#include "unpackers/BankUnpacker.hh"
#include "unpackers/WFD5Unpacker.hh"
#include "unpackers/FC7Unpacker.hh"

namespace unpackers {

    class CRBankUnpacker : public BankUnpacker {
        
    public:
        
        //Constructor
        CRBankUnpacker();

        //Destructor
        ~CRBankUnpacker();

        // Virtual function to unpack the event
        void UnpackBank(TMEvent* event, const std::string& bankName) override;    

    private:
        //class name
        const std::string className_;

    protected:
    };

}

#endif // CRBANKUNPACKER_HH