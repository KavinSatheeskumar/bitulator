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

void deleteExp(exp *exp)
{
    switch (exp->type)
    {
    case binary:
        deleteExp(exp->binExpr->lExp);
        deleteExp(exp->binExpr->rExp);
        delete exp->binExpr;
        break;

    case Lit:
        delete exp->lit->lit;
        delete exp->lit;
        break;

    case bracket:
        deleteExp(exp->braExpr->Exp);
        delete exp->braExpr;
        break;
    }
}

void toJson(std::stringstream &buffer, const exp *exp)
{
    switch (exp->type)
    {
    case binary:
        buffer << '{' << std::endl;
        buffer << '\'' << exp->binExpr->op << "\': {" << std::endl;
        buffer << "\t\'left\': ";
        toJson(buffer, exp->binExpr->lExp);
        buffer << "," << std::endl;
        buffer << "\t\'right\': ";
        toJson(buffer, exp->binExpr->rExp);
        buffer << "," << std::endl;
        buffer << "\t}" << std::endl;
        buffer << '}' << std::endl;
        break;
    case Lit:
        buffer << "{\n \'literal\': ";
        buffer << exp->lit->lit;
        buffer << '}' << std::endl;
        break;
    case bracket:
        buffer << "{\n \'brackets\': ";
        toJson(buffer, exp->braExpr->Exp);
        buffer << '}' << std::endl;
        break;
    }
};
