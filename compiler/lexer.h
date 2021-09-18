#ifndef _INDEX_H_
#define _INDEX_H_
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <cstring>

class binExp;
class brackets;

enum expressions
{
    integer,
    binary,
    bracket
};

class exp
{
    union
    {
        binExp *binExpr;
        brackets *braExpr;
        int *lit;
    };
    expressions type;

    public:
    exp(binExp *expr) { exp::binExpr = expr, exp::type = binary; }
    exp(brackets *expr) { exp::braExpr = expr, exp::type = bracket; }
    exp(int *expr) { exp::lit = expr, exp::type = integer; }
    ~exp()
    {
        switch (exp::type)
        {
        case binary:
            delete exp::binExpr;
            break;

        case integer:
            delete exp::lit;
            break;

        case bracket:
            delete exp::braExpr;
            break;
        }
    }
    std::string toJson(std::stringstream &buffer);
};

class binExp
{
    char op;
    exp lExp;
    exp rExp;

public:
    std::string toJson(std::stringstream &buffer)
    {
        buffer << '{' << std::endl;
        buffer << '\'' << op << "\': {" << std::endl;
        buffer << "\t\'left\': ";
        lExp.toJson(buffer);
        buffer << "," << std::endl;
        buffer << "\t\'right\': ";
        rExp.toJson(buffer);
        buffer << "," << std::endl;
        buffer << '\t}' << std::endl;
        buffer << '}' << std::endl;
    }
};

struct Tokens {
    std::string type, value; 
}; 

std::vector<Tokens> getchars(std::string input);
#endif