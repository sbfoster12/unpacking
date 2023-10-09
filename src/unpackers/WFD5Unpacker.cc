#include "WFD5Unpacker.hh"

using namespace unpackers;

WFD5Unpacker::WFD5Unpacker() 
    : PayloadUnpacker()
    , WFD5HeaderPtrCol_(std::make_shared<dataProducts::DataProductPtrCollection>())
    , waveformPtrCol_(std::make_shared<dataProducts::DataProductPtrCollection>())
    , WFD5HeaderParser_(std::make_unique<parsers::WFD5HeaderParser>())
    , ChannelHeaderParser_(std::make_unique<parsers::ChannelHeaderParser>())
    , WaveformHeaderParser_(std::make_unique<parsers::WaveformHeaderParser>())
    , WaveformParser_(std::make_unique<parsers::WaveformParser>())
{
    utils::LoggerHolder::getInstance()->InfoLogger << "We are constructing the WFD5 unpacker." << std::endl;
}

WFD5Unpacker::~WFD5Unpacker() {};

void WFD5Unpacker::Unpack(const uint64_t* words, unsigned int& wordNum) {
    utils::LoggerHolder::getInstance()->InfoLogger << " We are unpacking a WFD5 payload." << std::endl;

    //Store the starting word for comparison at the end
    unsigned int startWordNum = wordNum;

    /*
        First up is the AMC13+WFD5 header, which is 3 words long
    */

    auto amc_header_words = GetXWords(words,wordNum,3,"bigendian");

    //Set the words in the parser
    WFD5HeaderParser_->SetWords(amc_header_words);

    //Get the AMC slot num
    int amcSlot = WFD5HeaderParser_->AMCNo();

    //Get the data length
    int data_length = WFD5HeaderParser_->DataLength();

    //Get the number of enabled channels
    unsigned int enabled_channels = WFD5HeaderParser_->NumEnabledChannels();

    //Is the event empty?
    if (WFD5HeaderParser_->EmptyEvent()) {
        utils::LoggerHolder::getInstance()->InfoLogger << " This event is empty. Not unpacking." << std::endl;
        //increment the current word and exit
        wordNum+=data_length;
        return;
    }

    //Parse and create the data product
    WFD5HeaderPtrCol_->push_back(WFD5HeaderParser_->NewDataProduct(crateNum_));

    //WFD5HeaderParser_->Print();

    //Clear data from parser
    WFD5HeaderParser_->Clear();

    /*
        Now we loop over the channels
    */
    for (unsigned int iChannel = 0; iChannel < enabled_channels; ++iChannel)
    {
        //std::cout << "        Proceesing channel: " << iChannel << std::endl;
        /*
            Parse the Channel header, which is 2 64 bit words long
        */
        auto ch_header_words = GetXWords(words,wordNum,2,"bigendian");

        //Set the words in the parser
        ChannelHeaderParser_->SetWords(ch_header_words);

        //Get the channel tag
        uint32_t channelTag = ChannelHeaderParser_->ChannelTag();
        //std::cout << "        Channel tag: " << channelTag << std::endl;

        //Get the number of waveforms in this channel
        unsigned int waveform_count = ChannelHeaderParser_->WaveformCount();
        //std::cout << "        Waveform count: " << waveform_count << std::endl;

        ChannelHeaderParser_->Clear();

        /*
            Now we loop over each waveform
        */
        for (unsigned int iWaveform = 0; iWaveform < waveform_count; ++iWaveform)
        {
            //std::cout << "            Proceesing waveform: " << iWaveform << std::endl;
            /*
                Parse the Waveform header, which is 2 64 bit words long
            */
            auto wf_header_words = GetXWords(words,wordNum,2,"bigendian");

            //Set the words in the parser
            WaveformHeaderParser_->SetWords(wf_header_words);

            //Get the waveform length (number of 8 bit ADC samples = 2 64 bit words)
            uint32_t waveform_length = WaveformHeaderParser_->WaveformLength();
            //std::cout << "            waveformLength: " << waveform_length << std::endl;

            /*
                Now get the ADC data , which is waveform_length*2 64-bit words
            */
            auto adc_words = GetXWords(words,wordNum,waveform_length*2,"le");

            //Set the words in the parser
            WaveformParser_->SetWords(adc_words);

            //Create the data product
            auto waveformDataProduct = WaveformParser_->CreateDataProduct();
            auto waveformPtr = std::make_shared<dataProducts::Waveform>();
                waveformPtr->crateNum = crateNum_;
                waveformPtr->amcSlot = amcSlot;
                waveformPtr->channelTag = channelTag;
                waveformPtr->eventNum = eventNum_;
                waveformPtr->trace = waveformDataProduct.trace;
                waveformPtrCol_->push_back(std::move(waveformPtr));

            WaveformParser_->Clear();

        }

        //channel trailer
        wordNum+=3;
    }

    //Trailers
    wordNum+=1;

    //Check that we have processed exactly the data_length
    if ((wordNum - startWordNum) != data_length) {
        std::cerr << "Error: didn't parse entire data length\n"
        << "Location: WFD5Unpacker::Unpack(uint64_t* words, unsigned int& wordNum)\n"
        << "Details: the data length is " << data_length << ", but the number of parse words is " << wordNum - startWordNum << std::endl;
        exit(1);

    }
};

void WFD5Unpacker::RegisterDataProducts(std::map<std::string,std::shared_ptr<dataProducts::DataProductPtrCollection>>& basePtrCol) {
    std::string WFD5HeaderLabel="WFD5HeaderCollection";
    std::string WaveformLabel="WaveformCollection";

    //check if the WFD5Header collection is already registered
    auto it = basePtrCol.find(WFD5HeaderLabel);

    if (it != basePtrCol.end()) {
        std::cerr << "Error: a dataProduct with this label has already been registered\n"
        << "Details: label = " << WFD5HeaderLabel << std::endl;
        exit(1);
    } else {
        basePtrCol[WFD5HeaderLabel] = WFD5HeaderPtrCol_;
    }

    //check if the Waveform collection is already registered
    it = basePtrCol.find(WaveformLabel);

    if (it != basePtrCol.end()) {
        std::cerr << "Error: a dataProduct with this label has already been registered\n"
        << "Details: label = " << WaveformLabel << std::endl;
        exit(1);
    } else {
        basePtrCol[WaveformLabel] = waveformPtrCol_;
    }
}