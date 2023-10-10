#ifndef EVENTRUNPACKER_HH
#define EVENTRUNPACKER_HH

//Standard
#include <iostream>
#include <string>

//Custom
#include "unpackers/CollectionsHolder.hh"
#include "unpackers/BankUnpacker.hh"

#define CR_BANK_ID 0

namespace unpackers {

    class EventUnpacker : public CollectionsHolder {
        
    public:
        
        //Constructor
        EventUnpacker();

        //Destructor
        virtual ~EventUnpacker();

        // Virtual function to read the event
        virtual void UnpackEvent(TMEvent* event) = 0;

    private:
        //class name
        const std::string className_;

    protected:
        //bank unpackers
        std::map<int,std::unique_ptr<unpackers::BankUnpacker>> bankUnpackers_;

    };

}

#endif // EVENTRUNPACKER_HH