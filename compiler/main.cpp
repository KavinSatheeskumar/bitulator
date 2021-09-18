#include <string>
#include <iostream>
#include <sstream>
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {

    std::string input = argv[1]; //
    //remove useless whitespace
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    std::vector<Tokens> tmp = getchars(input);
    parse(tmp);
}; 