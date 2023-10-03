#include "WaveformParser.hh"

using namespace parsers;

WaveformParser::WaveformParser() : Parser() {};

WaveformParser::~WaveformParser() {};

dataProducts::Waveform WaveformParser::CreateDataProduct() {
    
    //create the data product
    auto waveform = dataProducts::Waveform();
    
    //fill it
    waveform.trace = this->ADCData();

    //std::cout << "        Trace size: " << waveform.trace.size() << std::endl;

    //return it
    return waveform;
}

//Get methods
std::vector<short> WaveformParser::ADCData() {
    //initialize output vector
    std::vector<short> trace = {};

    //loop over each words
    for (uint64_t& words : words_) {
        //cast to a short
        short* shortWords = (short*)&words;
        //insert into vector
        size_t wordsSize = sizeof(shortWords)/sizeof(short);
        trace.insert(trace.end(),shortWords, shortWords + wordsSize);
    } 
    return trace;    
}

uint16_t WaveformParser::ADCData(int wordNum, int sampleNum) {
    return (uint16_t)((GetWord(wordNum) >> sampleNum*16) & 0xffff); 
}
