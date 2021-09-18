#include "lexer.h"
bool isValid = true; 
bool bracketErr = false; 
bool cErr = false; bool charErr = false; bool numErr = false;
bool validation(std::vector<Tokens> result) {
    int n = result.size();
    int opcnt[n]; int ncnt[n]; std::unordered_map<int, int> matchbrackets;
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

    if(isValid) return true; 
    else {

        return false; 
    } 
}

std::string replaceall(std::string s) {
    std::string t = "--";
    size_t index = 0;
    while (true) {
        index = s.find("--", index);
        if (index == std::string::npos) break;
        s.replace(index, 2, "+");
        index += 1;
    }
    return s; 
}

std::string timbit(std::string s) {
    std::string t = "$"; 
    srand(time(NULL));
    std::vector<std::string> operators = {"+", "-", "*", "/", "^"}; 
    size_t index = 0;
    while (true) {
        index = s.find("$", index);
        if (index == std::string::npos) break;
        int id = rand()%5; 
        s.replace(index, 1, operators[id]);
        index += 1;
    }
    return s; 
}

std::vector<Tokens> getchars(std::string input) {  
    input = replaceall(input); 
    input = timbit(input); 
    std::vector<Tokens> result;  
    std::set<char> operators = {'+', '-', '*', '/', '^', '$'}; 
    std::set<char> allbrackets = {'(', ')'}; 
    bool hasDot = false; bool isDotLast = false; 
    bool isNumber = false; std::string tmp = ""; std::string convert = "";
    for(char c : input) {
        if(isNumber) {
            if(c == '.') {
                if(hasDot) {
                    numErr = true; 
                    isValid = false;
                    break;
                }
                tmp += c; 
                hasDot = true; 
                isDotLast = true; 
            }

            else if(c >= '0' && c <= '9') {
                if(isDotLast) isDotLast = false; 
                tmp += c; 
            }

            else if(operators.count(c)) {
                if(isDotLast) {
                    numErr = true;
                    isValid = false;
                    break; 
                }
                isNumber = false;
                isDotLast = false; 
                hasDot = false; 
                result.push_back({"Number", tmp});
                tmp = ""; 
                convert += c; 
                result.push_back({"Operator", convert}); 
                convert = ""; 
            }

            else if(allbrackets.count(c)) {
                if(isDotLast) {
                    numErr = true;
                    isValid = false;
                    break; 
                }
                isNumber = false;
                isDotLast = false; 
                hasDot = false; 
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
                break; 
            }
        }

        else {
            if(c == '.') {
                numErr = true; 
                isValid = false; 
                break; 
            }
            else if(c >= '0' && c <= '9') {
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
                break; 
            }
        }
    }   

    if(isNumber) {
        if(isDotLast) {
            numErr = true;
            isValid = false;
        }
        else result.push_back({"Number", tmp});
    }
    if(validation(result) && isValid) {
        std::cout << "Tokens:" << '\n'; 
        for(int i = 0; i<result.size(); i++) {
            if(i != result.size()-1) std::cout << result[i].type << " " << result[i].value << ",\n";
            else std::cout << result[i].type << " " << result[i].value;
        }
        return result; 
    }
    else {
        if(bracketErr) std::cerr << "Bracket Error" << '\n';
        if(cErr) std::cerr << "Format Error" << '\n'; 
        if(charErr) std::cerr << "Invalid Character" << '\n'; 
        if(numErr) std::cerr << "Number Error" << '\n'; 
        return {}; 
    }
}