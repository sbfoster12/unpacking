#ifndef BASICEVENTUNPACKER_HH
#define BASICEVENTUNPACKER_HH

//Custom
#include "unpackers/utils/Logger.hh"
#include "unpackers/CRBankUnpacker.hh"
#include "unpackers/EventUnpacker.hh"

namespace unpackers {

    class BasicEventUnpacker : public EventUnpacker {
        
    public:
        
        //Constructor
        BasicEventUnpacker();

        //Destructor
        ~BasicEventUnpacker();

        void UnpackEvent(TMEvent* event) override;

    private:
        //class name
        const std::string className_;
        
    };

}

#endif // BASICEVENTUNPACKER_HH