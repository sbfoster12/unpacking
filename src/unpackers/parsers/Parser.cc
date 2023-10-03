#include "Parser.hh"

using namespace parsers;

Parser::Parser()
    : words_({}) {}

Parser::~Parser() {}

void Parser::SetWords(std::vector<uint64_t> words) {
    words_=words; 
}

uint64_t Parser::GetSize() const { 
    uint64_t bankSize = words_.size();
    return bankSize;
}

uint64_t Parser::GetWord(size_t iWord) const {
    if (words_.size() == 0) {
        throw "words is empty!";
    }
    if (iWord > GetSize() - 1) {
        throw "words is shorter than requested length";
    }
    return words_.at(iWord);
}