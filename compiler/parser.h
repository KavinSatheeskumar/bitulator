#include <string>
#include <iostream>
#include <sstream>

struct exp;

struct binExp
{
    char op;
    exp *lExp;
    exp *rExp;
};

struct brackets
{
    exp *Exp;
};

struct literal
{
    std::string lit;
};

enum expressions
{
    Lit,
    binary,
    bracket
};

struct exp
{
    union
    {
        binExp *binExpr;
        brackets *braExpr;
        literal *lit;
    };
    expressions type;
};

void deleteExp(exp *exp);
void toJson(std::stringstream &buffer, const exp *exp);
exp* parse(std::vector<Tokens> tokens);
