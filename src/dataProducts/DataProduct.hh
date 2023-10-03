#ifndef DATAPRODUCT_HH  
#define DATAPRODUCT_HH

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <TObject.h>

namespace dataProducts {

    class DataProduct : public TObject {

        public:
            DataProduct();

            //Destructor
            virtual ~DataProduct();

            virtual void Print() const;

            ClassDef(DataProduct,1)
    };

    typedef std::vector<DataProduct> DataProductCollection;

}

#endif // DATAPRODUCT_HH