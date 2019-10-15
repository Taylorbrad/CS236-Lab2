#pragma once //only compile this file once
#include <stack>
#include <iostream>
#include <fstream>
#include <cctype>
#include "Token.h"
using namespace std;
// syn
//Attempting to alter the scanner to return the stack of tokens, instead of cout-ing them. 10/8/19
class Scanner
{
    public:
        Scanner(string inFile);
        stack <Token> tokenize();
        
    private:
        stack <char> tokenTemp;
        ifstream inFile;
        string fileName;
};