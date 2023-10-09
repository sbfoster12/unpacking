#include "CRBankUnpacker.hh"

using namespace unpackers;

CRBankUnpacker::CRBankUnpacker() :
    BankUnpacker(),
    className_("CRBankUnpacker")
{
    utils::LoggerHolder::getInstance()->InfoLogger << "We are constructing the CR bank unpacker." << std::endl;

    //Initialize the unpackers
    payloadUnpackers_[1] = std::move(std::make_unique<unpackers::WFD5Unpacker>());
    payloadUnpackers_[2] = std::move(std::make_unique<unpackers::FC7Unpacker>());

    //Fill in map of collections
    payloadUnpackers_[1]->RegisterDataProducts(basePtrCol_);
    payloadUnpackers_[2]->RegisterDataProducts(basePtrCol_);
}

CRBankUnpacker::~CRBankUnpacker() {};

void CRBankUnpacker::UnpackBank(TMEvent* event, const std::string& bankName) {

    //Get the bank
    TMBank *bank = event->FindBank(bankName.c_str());

    //Update the unpackers event and crate numbers
    this->UpdateEventNum(event->serial_number);
    this->UpdateCrateNum(std::stoi(bank->name.substr(3, 4)));

    //Get total number of words (each word is 8 bytes) 
    unsigned int totalWords = bank->data_size/8;

    if (bank != NULL) {
        uint64_t* bankData = reinterpret_cast<uint64_t*>(event->GetBankData(bank));

        //keep track of which word we are parsing
        unsigned int wordNum = 0;

        //Loop over the payloads
        while (wordNum < totalWords) {
            //Determine what payload we are looking at
            unsigned int tmpNum = wordNum;
            auto tmpwords = unpackers::GetXWords(bankData,tmpNum,2,"bigendian");
            int payload_type = unpackers::ExtractBits(tmpwords[1],13,15);
            //int data_length = unpackers::ExtractBits(tmpwords[0],0,19);

            //Get the unpacker and unpack this payload
            payloadUnpackers_[payload_type]->Unpack(bankData,wordNum);
        }
    } else {
        utils::LoggerHolder::getInstance()->InfoLogger <<"  No CR bank in event ID: " <<  event->event_id << " SN: " << event->serial_number << std::endl;
    }
}