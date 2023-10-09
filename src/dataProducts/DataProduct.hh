#ifndef DATAPRODUCT_HH  
#define DATAPRODUCT_HH

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include <TH1.h>
#include <TObject.h>

namespace dataProducts {

    class DataProduct : public TObject {

        public:
            DataProduct();

            //Destructor
            virtual ~DataProduct();

            virtual void PrintMembers() const;

            ClassDef(DataProduct,1)
    };

    typedef std::vector<DataProduct> DataProductCollection;
    typedef std::vector<std::shared_ptr<DataProduct>> DataProductPtrCollection;

}

#endif // DATAPRODUCT_HH