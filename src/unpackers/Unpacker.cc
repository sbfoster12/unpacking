#include "Unpacker.hh"

using namespace unpackers;

Unpacker::Unpacker()
    : className_("Unpacker")
{}

Unpacker::~Unpacker() {}

std::map<std::string,std::shared_ptr<dataProducts::DataProductPtrCollection>>
Unpacker::GetCollections() {
    return basePtrCol;
}

void Unpacker::ClearCollections() {
    //loop over each collection and clear
    for (auto& col : basePtrCol) { col.second->clear();}
}