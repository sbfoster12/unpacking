#ifndef PARSER_HH
#define PARSER_HH

#include <iostream>
#include <string>
#include <vector>

namespace parsers {

    class Parser {
        
    public:
        
        //Constructor
        Parser();

        //Destructor
        virtual ~Parser();

        //Set methods
        void SetWords(std::vector<uint64_t> words);

        //Get methods
        uint64_t GetSize() const;
        uint64_t GetWord(size_t iWord) const;

    private:
        std::string className_ = "Parser";

    protected:
        std::vector<uint64_t> words_;
    };
}

#endif // PARSER_HH