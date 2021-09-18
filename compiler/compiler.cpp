#include "lexer.h"
#include "parser.h"

std::string ans;

exp test; 
std::stack<std::string> svalues;
std::stack<double> dvalues;  

void search(exp *cur) {

    if(cur->type == Lit) {
        svalues.push(cur->lit->lit);
        dvalues.push(std::stod(cur->lit->lit)); 
        return; 
    }

    else if(cur->type == bracket) {
        return search(cur->braExpr->Exp); 
    }   

    else if(cur->type == binary) {
        search(cur->binExpr->lExp);
        search(cur->binExpr->rExp); 
        
        std::string s1 = svalues.top(); svalues.pop(); 
        std::string s2 = svalues.top(); svalues.pop();

        double d1 = dvalues.top(); dvalues.pop();  
        double d2 = dvalues.top(); dvalues.pop();
        
        svalues.push(std::to_string(d1+d2)); dvalues.push(d1+d2); 
    
        std::string tmp = "";
        switch(cur->binExpr->op) {
            case '+': 
                tmp = "ADD";
                break; 
            case '-': 
                tmp = "MINUS";
                break; 
            case '*': 
                tmp = "MULTI";
                break; 
            case '/': 
                tmp = "DIVIDE";
                break; 
            case '^': 
                tmp = "EXPR"; 
                break; 
        }
        ans += tmp + " " + s1 + " " + s2 + "," + '\n'; 
        return;
    }
}

std::string returnSOutput() {
    ans.pop_back(); 
    return ans; 
}

double returnDOutput() {
    return dvalues.top(); 
}