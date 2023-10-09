#ifndef WAVEFORMHEADERPARSER_HH
#define WAVEFORMHEADERPARSER_HH

//Custom
#include "unpackers/parsers/Parser.hh"
#include "dataProducts/WaveformHeader.hh"

// Bit locations and masks for WFD5 channel format:
#define RWF_WaveformLength_WORD 0 
#define RWF_WaveformLength_BIT 0
#define RWF_WaveformLength_MASK 0x7fffff

namespace parsers {

    class WaveformHeaderParser : public Parser {
        
    public:
        
        //Constructor
        WaveformHeaderParser();

        //Destructor
        ~WaveformHeaderParser();

        //Method to make the data product
        dataProducts::WaveformHeader CreateDataProduct();

        //Get methods
        uint32_t WaveformLength() const ;

        //Print method
        void Print() override;

    private:
        const std::string className_ = "WaveformHeaderParser";

    };
}

#endif // WAVEFORMHEADERPARSER_HH