#include "BasicEventUnpacker.hh"

using namespace unpackers;

BasicEventUnpacker::BasicEventUnpacker()
    : EventUnpacker(), 
    className_("BasicEventUnpacker")
{
    utils::LoggerHolder::getInstance()->InfoLogger << "We are constructing the basic event unpacker." << std::endl;

    //Create the bank unpackers
    bankUnpackers_[0] = std::make_unique<CRBankUnpacker>();

    //Register the collections by looping over the
    //collections in the bankUnpackers
    //col0 is a map of labels -> shared ptr to the col
    auto col0 = bankUnpackers_[0]->GetCollections();
    for (const auto& col : col0) {
        //find if label already exists
        auto it = basePtrCol.find(col.first);
        if (it != basePtrCol.end()) {
            std::cerr << "Error: a dataProduct with this label has already been registered\n"
            << "Details: label = " << col.first << std::endl;
            exit(1);
        } else {
            basePtrCol[col.first] = col.second;
        }
    }
}

BasicEventUnpacker::~BasicEventUnpacker() {}

void BasicEventUnpacker::UnpackEvent(TMEvent* event) {

    //Clear previous event
    this->ClearCollections();

    utils::LoggerHolder::getInstance()->InfoLogger << "Unpacking with Event ID: " << event->event_id << " and SN: " << event->serial_number << std::endl;

    // Loop over all banks and read the CR banks
    // Can we parallelize this loop?
    event->FindAllBanks();
    for (const auto& bank : event->banks) {
        if (bank.name.substr(0, 2) == "CR") {
            bankUnpackers_[0]->UnpackBank(event, bank.name);
        }
    }
}