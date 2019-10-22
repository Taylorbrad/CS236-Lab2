#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <string>
#include <stack>
#include "Token.h"
#include "Rule.h"
#include "Predicate.h"
using namespace std;
// syn
class DatalogProgram
{
    public:
    DatalogProgram(stack <Token> tokensFromScanner);
    string toString();
    void parse();
    
    stack <Token> tokenStack;
    stack <string> testStack;
    
    
    private:
    bool isFactString = false;
    bool isFromExpression = false;
    int domainSize = 0;
    stack <Predicate> schemes;
    stack <Predicate> facts;
    stack <Rule> rules;
    stack <Predicate> queries;
    string domain[100];
    stack <Predicate> reversePredicates;
    stack <Rule> reverseRules;
    stack <string> reverseStrings;
    
    Predicate currentPredicate;
    Predicate headPredicate;
    Rule currentRule;
    string headString;
    string currentString;
    string expression;
    stack <string> toMakePredicate;
    stack <string> emptyStringStack;
    stack <Predicate> emptyPredicateStack;
    stack <Predicate> toMakeRule;
    string emptyString;
    
    bool isTypeExpected(stack <TokenType> expectedTypes);
    bool isTypeExpectedOrdered(stack <TokenType> expectedTypesInOrder);
    void setPredicateStart();
    bool isDuplicateStringInDomain(string inString);
    void addToDomainAplhabetically(string);
    void stringArraySort();
    
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
#endif