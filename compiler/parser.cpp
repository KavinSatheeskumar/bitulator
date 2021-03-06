#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include "lexer.h"
#include "parser.h"

node *parse(std::vector<Tokens> tokens)
{
    if (tokens.empty()) return nullptr;
    node *expr = new node;
    std::string precedence = "-+*/^";
    for (char op : precedence)
    {
        int i = 0;
        int brackets = 0;
        for (Tokens token : tokens)
        {
            //std::cout << "operator: " << op << " token_type: " << token.type << " token_value: " << token.value << " brackets: " << brackets << std::endl;
            if (token.type == "Bracket")
            {
                if (token.value.at(0) == '(')
                {
                    brackets++;
                    //std::cout << "brackets++\n";
                }
                else
                {
                    brackets--;
                    //std::cout << "brackets--\n";
                }
            }
            if (token.type == "Operator" && token.value.at(0) == op && brackets == 0)
            {
                std::vector<Tokens> lExpVector, rExpVector;
                for (int j = 0; j < i; j++)
                    lExpVector.push_back(tokens[j]);
                for (int j = i + 1; j < tokens.size(); j++)
                    rExpVector.push_back(tokens[j]);
                expr->type = binary;
                expr->binExpr = new binExp;
                expr->binExpr->lExp = parse(lExpVector);
                expr->binExpr->rExp = parse(rExpVector);
                expr->binExpr->op = op;
                return expr;
            }
            i++;
        }
    }
    if (tokens[0].value.at(0) == '(')
    {
        expr->type = bracket;
        expr->braExpr = new braExp;
        std::vector<Tokens> expVector;
        for (int j = 1; j < tokens.size(); j++)
            expVector.push_back(tokens[j]);
        expr->braExpr->Exp = parse(expVector);
        return expr;
    }
    else
    {
        expr->type = Lit;
        expr->lit = new literal;
        expr->lit->lit = tokens[0].value;
        return expr;
    }
}

void deleteExp(node *expr)
{
    switch (expr->type)
    {
    case binary:
        deleteExp(expr->binExpr->lExp);
        deleteExp(expr->binExpr->rExp);
        delete expr->binExpr;
        break;

    case Lit:
        delete expr->lit;
        break;

    case bracket:
        deleteExp(expr->braExpr->Exp);
        delete expr->braExpr;
        break;
    }
}

void toJson(std::stringstream &buffer, const node *node)
{
    switch (node->type)
    {
    case binary:
        buffer << '{' << std::endl;
        buffer << '\'' << node->binExpr->op << "\': {" << std::endl;
        buffer << "\t\'left\': ";
        toJson(buffer, node->binExpr->lExp);
        buffer << "," << std::endl;
        buffer << "\t\'right\': ";
        toJson(buffer, node->binExpr->rExp);
        buffer << "," << std::endl;
        buffer << "\t}" << std::endl;
        buffer << '}' << std::endl;
        break;
    case Lit:
        buffer << "{\n \'literal\': ";
        buffer << node->lit->lit;
        buffer << '}' << std::endl;
        break;
    case bracket:
        buffer << "{\n \'brackets\': ";
        toJson(buffer, node->braExpr->Exp);
        buffer << '}' << std::endl;
        break;
    }
};
