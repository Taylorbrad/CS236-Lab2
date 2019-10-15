#pragma once
#include <string>
#include <stack>
#include "Token.h"
using namespace std;
// syn
class DatalogProgram
{
    public:
    DatalogProgram(stack <Token> tokensFromScanner);
    string toString();
    void parse();
    
    stack <Token> tokenStack;
    
    private:
    bool isTypeExpected(stack <TokenType> expectedTypes);
    bool isTypeExpectedOrdered(stack <TokenType> expectedTypesInOrder);
    
    void checkDatalogProgram();
    
    void checkSchemeList();
    void checkFactList();
    void checkRuleList();
    void checkQueryList();
    
    void checkScheme();
    void checkFact();
    void checkRule();
    void checkQuery();
    
    void checkHeadPredicate();
    void checkPredicate();
    
    void checkPredicateList();
    void checkParameterList();
    void checkStringList();
    void checkIdList();
    
    void checkParameter();
    void checkExpression();
    void checkOperator();
    
    // bool parseFailFlag = false; //Initialized in non-failed state
    // vector<Predicate> schemes; dont need these yet
    // vector<Predicate> facts;
    // vector<Predicate> rules;
    // vector<Predicate> queries;
};