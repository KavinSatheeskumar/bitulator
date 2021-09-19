#include "lexer.h"
#include "parser.h"
#include "math.h"

std::string ans;

node test; 
std::stack<std::string> svalues;
std::stack<double> dvalues;  

void search(node *cur) {

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
        

    
        std::string tmp = "";
        switch(cur->binExpr->op) {
            case '+': 
                tmp = "ADD";
                svalues.push(std::to_string(d1+d2)); 
                dvalues.push(d1+d2); 
                break; 
            case '-': 
                tmp = "SUB";
                svalues.push(std::to_string(d1-d2)); 
                dvalues.push(d1-d2); 
                break; 
            case '*': 
                tmp = "MUL";
                svalues.push(std::to_string(d1*d2)); 
                dvalues.push(d1*d2); 
                break; 
            case '/': 
                tmp = "DIV";
                svalues.push(std::to_string(d1/d2)); 
                dvalues.push(d1/d2); 
                break; 
            case '^': 
                tmp = "EXP"; 
                svalues.push(std::to_string(pow(d1,d2))); 
                dvalues.push(pow(d1, d2)); 
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