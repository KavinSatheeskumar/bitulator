#include <bits/stdc++.h>

struct Tokens {
    std::string type, value; 
}; 

std::set<char> operators = {'+', '-', '*', '/', '^', '$'}; 
std::set<char> allbrackets = {'(', ')'}; 
std::vector<Tokens> result; 
std::unordered_map<int, int> matchbrackets; 

bool isValid = true; 
bool bracketErr = false; 
bool cErr = false; bool charErr = false; 
void getchars(std::string input) {  
    bool isNumber = false; std::string tmp = ""; std::string convert = "";
    for(char c : input) {
        if(isNumber) {
            if(c >= '0' && c <= '9') tmp += c; 

            else if(operators.count(c)) {
                isNumber = false;
                result.push_back({"Number", tmp});
                tmp = ""; 
                convert += c; 
                result.push_back({"Operator", convert}); 
                convert = ""; 
            }

            else if(allbrackets.count(c)) {
                isNumber = false;
                result.push_back({"Number", tmp});
                tmp = ""; 
                convert += c;
                result.push_back({"Bracket", convert});
                convert = ""; 
            }

            else {
                charErr = true; 
                isValid = false; 
                return; 
            }
        }
        else {
            if(c >= '0' && c <= '9') {
                tmp += c;
                isNumber = true; 
            }

            else if(operators.count(c)) {
                convert += c; 
                result.push_back({"Operator", convert}); 
                convert = ""; 
            }

            else if(allbrackets.count(c)) {
                convert += c;
                result.push_back({"Bracket", convert});
                convert = ""; 
            }

            else {
                charErr = true; 
                isValid = false; 
                return; 
            }
        }
    }   
    if(isNumber) result.push_back({"Number", tmp});
}


int main(int argc, char* argv[]) {

    std::string input = argv[1]; 
    //remove useless whitespace
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    getchars(input); 

    std::cout << input << '\n'; 


    int n = result.size();

    int opcnt[n]; int ncnt[n]; 
    memset(opcnt, 0, sizeof(opcnt)); 
    memset(ncnt, 0, sizeof(ncnt)); 

    std::string prevt = ""; std::stack<int> bids;  std::vector<int> bbids; 


    for(int i = 0; i<n; i++) {
        Tokens t = result[i]; 

        if(i) {
            ncnt[i] = ncnt[i-1]; 
            opcnt[i] = opcnt[i-1];
        }

        if(t.type == "Number") {
            ncnt[i]++; 
            if(t.type == prevt || prevt == "Bracket") {
                isValid = false; 
                cErr = true; 
                break; 
            }
        }

        else if(t.type == "Operator") {
            opcnt[i]++; 
            if(t.type == prevt) {
                isValid = false; 
                cErr = true; 
                break; 
            }
        }

        else {
            if(prevt == "Number") {
                cErr = true; 
                isValid = false; break; 
            }
            else if(prevt == "Bracket") {
                if(result[i-1].value != t.value) {
                    cErr = true; 
                    isValid = false; break; 
                }
            }
            if(t.value == "(") {
                bids.push(i); 
            }
            else {
                if(bids.empty()) {
                    bracketErr = true; 
                    isValid = false; break; 
                }
                bbids.push_back(i); 
                int tmp = bids.top(); bids.pop(); 
                matchbrackets[i] = tmp; 
            }
        }
    }

    if(bids.size()) { bracketErr = true; isValid = false; }
    if(!opcnt[n-1] || (opcnt[n-1] + 1 != ncnt[n-1])) { cErr = true; isValid = false; }

    for(int a : bbids) {
        int id = matchbrackets[a];
        
        if(id) {
            if((opcnt[a] - opcnt[id-1]) + 1 !=  (ncnt[a] - ncnt[id-1]) || !(opcnt[a] - opcnt[id-1])) { cErr = true; isValid = false; }
        }
        else {
            if(opcnt[a] + 1 != ncnt[a] || !(opcnt[a])) { cErr = true; isValid = false; }
        }
    }

    if(isValid) {
        std::cout << "Tokens:" << '\n'; 
        for(Tokens t : result) {
            std::cout << t.type << " " << t.value << '\n';  
        }
    }
    else {
        if(bracketErr) std::cout << "Bracket Error" << '\n';
        if(cErr) std::cout << "Format Error" << '\n'; 
        if(charErr) std::cout << "Invalid Character" << '\n'; 
    } 
}; 