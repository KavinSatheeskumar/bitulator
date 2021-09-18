#include <string>
#include <iostream>
#include <sstream>
#include "lexer.h"
#include "parser.h"

std::string parse(std::vector<Tokens> tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << tokens[i].type << tokens[i].value;
    }
}