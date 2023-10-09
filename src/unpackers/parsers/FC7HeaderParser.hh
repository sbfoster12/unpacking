#ifndef FC7HEADERPARSER_HH
#define FC7HEADERPARSER_HH

#include <iostream>
#include <string>
#include <vector>


#include "unpackers/parsers/Parser.hh"
#include "dataProducts/FC7Header.hh"

// Bit locations and masks for AMCPayload format:
#define AMCNo_WORD 0
#define AMCNo_BIT 56
#define AMCNo_MASK 0xf
#define DataLength_WORD 0
#define DataLength_BIT 0
#define DataLength_MASK 0xfffff
#define BoardType_WORD 1 
#define BoardType_BIT 13 
#define BoardType_MASK 0x7
#define WFD5_BT 1
#define FC7_BT 2

namespace parsers {

    class FC7HeaderParser : public Parser {
        
    public:
        
        //Constructor
        FC7HeaderParser();

        //Destructor
        ~FC7HeaderParser();

        //Method to make the data product
        dataProducts::FC7Header CreateDataProduct();

        //Get methods
        uint32_t            AMCNo() const ;
        uint32_t            DataLength() const ;
        uint32_t            BoardType() const ;
        std::string         BoardTypeString() const ;

        //Print method
        void Print() override;

    private:
        const std::string className_ = "FC7HeaderParser";

    };
}

#endif // FC7HEADERPARSER_HH