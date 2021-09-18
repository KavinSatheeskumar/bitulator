#include <string>
#include <iostream>
#include <sstream>

class binExp;
class brackets;
class literal;

enum expressions
{
    Lit,
    binary,
    bracket
};

class exp
{
public:
    union
    {
        binExp *binExpr;
        brackets *braExpr;
        literal *lit;
    };
    expressions type;

    exp(binExp *expr) { exp::binExpr = expr, exp::type = binary; }
    exp(brackets *expr) { exp::braExpr = expr, exp::type = bracket; }
    exp(literal *expr) { exp::lit = expr, exp::type = Lit; }
    ~exp()
    {
        switch (exp::type)
        {
        case binary:
            delete exp::binExpr->lExp;
            delete exp::binExpr->rExp;
            delete exp::binExpr;
            break;

        case Lit:
            delete exp::lit->lit;
            delete exp::lit;
            break;

        case bracket:
            delete exp::braExpr->Exp;
            delete exp::braExpr;
            break;
        }
    }
    void toJson(std::stringstream &buffer) {
        switch (exp::type)
        {
        case binary:
            exp::binExpr->toJson(buffer);
            break;
        case Lit:
            exp::lit->toJson(buffer);
            break;
        case bracket:
            exp::braExpr->toJson(buffer);
            break;
        }
    };
};

class binExp
{
public:
    char op;
    exp *lExp;
    exp *rExp;
    void toJson(std::stringstream &buffer)
    {
        buffer << '{' << std::endl;
        buffer << '\'' << op << "\': {" << std::endl;
        buffer << "\t\'left\': ";
        lExp->toJson(buffer);
        buffer << "," << std::endl;
        buffer << "\t\'right\': ";
        rExp->toJson(buffer);
        buffer << "," << std::endl;
        buffer << '\t}' << std::endl;
        buffer << '}' << std::endl;
    }
};

class brackets
{
public:
    exp *Exp;
    void toJson(std::stringstream &buffer)
    {
        buffer << "{\n \'brackets\': ";
        brackets::Exp->toJson(buffer);
        buffer << '}' << std::endl;
    }
};

class brackets
{
public:
    exp *Exp;
    void toJson(std::stringstream &buffer)
    {
        buffer << "{\n \'brackets\': ";
        brackets::Exp->toJson(buffer);
        buffer << '}' << std::endl;
    }
};

class literal
{
public:
    std::string *lit;
    void toJson(std::stringstream &buffer)
    {
        buffer << "{\n \'literal\': ";
        buffer << lit;
        buffer << '}' << std::endl;
    }
};