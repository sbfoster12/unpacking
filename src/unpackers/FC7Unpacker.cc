#include "FC7Unpacker.hh"

using namespace unpackers;

FC7Unpacker::FC7Unpacker() 
    : PayloadUnpacker()
    , FC7HeaderPtrCol_(std::make_shared<dataProducts::DataProductPtrCollection>())
    , FC7HeaderParser_(std::make_unique<parsers::FC7HeaderParser>())
{
    utils::LoggerHolder::getInstance()->InfoLogger << "We are constructing the FC7 unpacker." << std::endl;

};

FC7Unpacker::~FC7Unpacker() {};

void FC7Unpacker::Unpack(const uint64_t* words, unsigned int& wordNum) {
    utils::LoggerHolder::getInstance()->InfoLogger << " We are unpacking a FC7 payload." << std::endl;

    //First, we get the header, which is 3 64-bit words long
    auto header_words = GetXWords(words,wordNum,3,"bigendian");
    wordNum-=3;

    //Set the words in the parser
    FC7HeaderParser_->SetWords(header_words);

    //Get the data length
    int data_length = FC7HeaderParser_->DataLength();
    //std::cout << "data_length: " << data_length << std::endl;

    //Parse and create the data product
    auto FC7HeaderDataProduct = FC7HeaderParser_->CreateDataProduct();

    //TODO: Do more parsing...


    //Push back to the collection

    //Increment wordNum
    wordNum+=data_length;
};

void FC7Unpacker::RegisterDataProducts(std::map<std::string,std::shared_ptr<dataProducts::DataProductPtrCollection>>& basePtrCol) {
    
    std::string FC7HeaderLabel="FC7HeaderCollection";

    //check if the FC7Header collection is already registered
    auto it = basePtrCol.find(FC7HeaderLabel);

    if (it != basePtrCol.end()) {
        std::cerr << "Error: a dataProduct with this label has already been registered\n"
        << "Details: label = " << FC7HeaderLabel << std::endl;
        exit(1);
    } else {
        basePtrCol[FC7HeaderLabel] = FC7HeaderPtrCol_;
    }

}