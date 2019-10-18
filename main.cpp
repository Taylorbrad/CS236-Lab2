#include <iostream>
#include <fstream>
#include <cctype>
#include <stack>
#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"
using namespace std;
// no changes made 10/18/19
//OBJECTIVE 1: Write a parser (with recursive descent parsing form) that checks a token stream for syntax errors given the following grammar:

// void checkOperator();
// bool isTypeExpected(stack <TokenType> expectedCharacters);

int main(int, char* argv[])
{
    Scanner funScanner = Scanner(argv[1]);
	DatalogProgram funProgram = DatalogProgram(funScanner.tokenize());
	
	funProgram.parse();
}
//building functions from the bottom for maximum functionality during the coding process;
