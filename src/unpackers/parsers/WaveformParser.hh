#ifndef WAVEFORMPARSER_HH
#define WAVEFORMPARSER_HH

//Custom
#include "unpackers/parsers/Parser.hh"
#include "dataProducts/Waveform.hh"

// Bit locations and masks for WFD5 waveform format:

namespace parsers {

    class WaveformParser : public Parser {
        
    public:
        
        //Constructor
        WaveformParser();

        //Destructor
        ~WaveformParser();

        //Method to make the data product
        dataProducts::Waveform CreateDataProduct();

        //Get methods
        std::vector<short> ADCData();

        uint16_t ADCData(int wordNum, int sampleNum);

        //Print method
        void Print() override;

    private:
        std::string className_ = "WaveformParser";

    };
}

#endif // WAVEFORMPARSER_HH