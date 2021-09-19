#include <string>
#include <iostream>
#include <sstream>

struct node;

struct binExp
{
    char op;
    node *lExp;
    node *rExp;
};

struct braExp
{
    node *Exp;
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

struct node
{
    union
    {
        binExp *binExpr;
        braExp *braExpr;
        literal *lit;
    };
    expressions type;
};

void deleteExp(node *node);
void toJson(std::stringstream &buffer, const node *node);
node* parse(std::vector<Tokens> tokens);
void search(node *cur);