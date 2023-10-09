#ifndef _HH
#define _HH

//Standard
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

//Custom
#include "dataProducts/DataProduct.hh"

namespace unpackers {

    class Unpacker {
        
    public:
        
        //Constructor
        Unpacker();

        //Destructor
        virtual ~Unpacker();

        std::map<std::string,std::shared_ptr<dataProducts::DataProductPtrCollection>>
        GetCollections();

        // This template function returns a std::vector<T>
        // extracted from the collectionPtrs map. That map stores the vector of
        // base DataProduct pointers, so we have to individually cast 
        // each back to its original derived class. Here we return a vector
        // of the objects (no pointers)
        // The dynamic cast to T must be valid or else an empty vector is returned
        template <typename T>
        std::vector<T> GetCollection(std::string collectionName) {
            //Get the collection of base pointers
            auto colBasePtr = basePtrCol_[collectionName];
            //Create dervied object (not pointer) collection
            std::vector<T> derivedCol;
            //Loop over references to base pointers and cast to derived
            //Exit if casting fails
            //Return collection of derived objects (not pointers)
            //These derived objects are copies - is this okay?
            for (const auto& basePtr : *colBasePtr) {
                if (auto derivedPtr = dynamic_cast<T*>(basePtr.get())) {
                    derivedCol.push_back(*derivedPtr);
                } else {
                    std::cerr << "Collection could not be found with the provided template.\n"
                        << "Returning an empty vector\n";
                    return {};
                }
            }
            return derivedCol;
        }

        void ClearCollections();

    private:
        //class name
        const std::string className_;

    protected:

        //collections
        std::map<std::string,std::shared_ptr<dataProducts::DataProductPtrCollection>> basePtrCol_;


    };

}

#endif // _HH