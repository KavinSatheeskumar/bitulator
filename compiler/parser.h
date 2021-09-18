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

struct braExp
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
        braExp *braExpr;
        literal *lit;
    };
    expressions type;
};

void deleteExp(exp *exp);
void toJson(std::stringstream &buffer, const exp *exp);
exp* parse(std::vector<Tokens> tokens);
void search(exp *cur);