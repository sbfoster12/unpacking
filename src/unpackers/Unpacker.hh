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

        std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<dataProducts::DataProduct>>>>
        GetCollections();

        // This template function returns a std::vector<std::shared_ptr<T>>
        // extracted from the collectionPtrs map. The map stores the vector of
        // base DataProduct pointers, so we have to individually cast 
        // each back to its original derived class
        template <typename T>
        std::vector<std::shared_ptr<T>> GetCollection(std::string collectionName) {
            //Get the collection of base pointers
            auto colBasePtr = basePtrCol[collectionName];
            std::cout << colBasePtr->size() << std::endl;
            //Create collection of derive pointers
            std::vector<std::shared_ptr<T>> derivedPtrCol;
            //Loop over base pointers and cast to derived
            //Exit if casting fails
            //Return collection of derived pointers
            for (const auto& basePtr : *colBasePtr) {
                auto derivedPtr = std::dynamic_pointer_cast<T>(basePtr);
                if (derivedPtr != nullptr) {
                    derivedPtrCol.push_back(derivedPtr);
                } else {
                    std::cerr << "Collection could not be found with";
                    std::cout << "the provided template" << std::endl;
                    exit(1);
                }
            }
            return derivedPtrCol;
        }

        void ClearCollections();

    private:
        //class name
        const std::string className_;

    protected:

        //collections
        std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<dataProducts::DataProduct>>>> basePtrCol;


    };

}

#endif // _HH