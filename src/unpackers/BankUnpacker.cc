#include "BankUnpacker.hh"

using namespace unpackers;

BankUnpacker::BankUnpacker() :
    className_("BankUnpacker")
{}

BankUnpacker::~BankUnpacker() {};

void BankUnpacker::UpdateEventNum(int eventNum) {
    for (auto & unpacker : unpackers_) { 
        unpacker.second->SetEventNum(eventNum);
    }
}

void BankUnpacker::UpdateCrateNum(int crateNum) {
    for (auto & unpacker : unpackers_) { 
        unpacker.second->SetCrateNum(crateNum);
    }
}