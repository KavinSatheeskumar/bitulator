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
#include <time.h>  
struct Tokens {
    std::string type, value; 
}; 

std::vector<Tokens> getchars(std::string input);
#endif