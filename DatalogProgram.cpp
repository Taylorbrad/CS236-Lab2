#include "DatalogProgram.h"
#include "Token.h"
// #include <bits/stdc++.h> 
#include <algorithm>
#include <string>
// syn
using namespace std;
//improvements to be done: 1. methodize toString more. 2. make TokenTypes private variables

// void checkOperator();
stack <Rule> reverseRuleStack(stack <Rule>);
stack <Predicate> reversePredicateStack(stack <Predicate>);
stack <string> reverseStringStack(stack <string>);


DatalogProgram::DatalogProgram(stack <Token> tokensFromScanner)
{
    this->tokenStack = tokensFromScanner;
}

string DatalogProgram::toString()
{
    string convertedString; //placeholder method

    convertedString = "Schemes(";
    convertedString += to_string(this->schemes.size());
    convertedString += "):\n";
    
    this->schemes = reversePredicateStack(this->schemes);
    while (!this->schemes.empty())
    {
        convertedString += "\t";
        convertedString += this->schemes.top().toString();
        convertedString += "\n";
        
        this->schemes.pop();
    }
    
    convertedString += "Facts(";
    convertedString += to_string(this->facts.size());
    convertedString += "):\n";
    
    this->facts = reversePredicateStack(this->facts);
    while (!this->facts.empty())
    {
        convertedString += "\t";
        convertedString += this->facts.top().toString();
        convertedString += ".\n";
        
        this->facts.pop();
    }
    
    convertedString += "Rules(";
    convertedString += to_string(this->rules.size());
    convertedString += "):\n";
    
    this->rules = reverseRuleStack(this->rules);
    while (!this->rules.empty())
    {
        convertedString += "\t";
        convertedString += this->rules.top().toString();
        convertedString += "\n";
        
        this->rules.pop();
    }
    
    convertedString += "Queries(";
    convertedString += to_string(this->queries.size());
    convertedString += "):\n";
    
    this->queries = reversePredicateStack(this->queries);
    while (!this->queries.empty())
    {
        convertedString += "\t";
        convertedString += this->queries.top().toString();
        convertedString += "?\n";
        
        this->queries.pop();
    }
    
    // int domainSize = sizeof(this->domain);
    
    convertedString += "Domain(";
    convertedString += to_string(this->domainSize);
    convertedString += "):\n";
    
    stringArraySort();
    while (this->domainSize > 0)
    {
        convertedString += "\t";
        convertedString += this->domain[this->domainSize - 1];
        convertedString += "\n";
        this->domainSize--;
    }
    // while (!this->domain.empty())
    // {
    //     convertedString += "\t";
    //     convertedString += this->domain.top(); //NEEDS TO BE SORTED GUY
    //     convertedString += "\n";
        
    //     this->domain.pop();
    // }
    
    return convertedString;
}
void DatalogProgram::parse()
{
    try
    {
        checkDatalogProgram();// this is what you will do eventually
        
        if (this->tokenStack.top().getTokenType() != EndOf)
        {
            // cout << this->tokenStack.top().tokenTypeToString();
            // cout << "fail here";
            throw tokenStack.top();
        }
        
        cout << "Success!\n";
        cout << toString();
    }
    catch (Token failToken)
    {
        cout << "Failure!\n  " << failToken.toString();
    }
    
    // if (!this->parseFailFlag)
    // {
    //     cout << "Success!\n" << "Insert Datalog program output here\n";
    // }
}
// void DatalogProgram::parseFail(Token failedToken)
// {
    // cout << "Failure!\n  " << failedToken.toString();
    // this->parseFailFlag = true; //this flag tells the methods that parse has failed due to a syntax error, so stop trying
// }
stack <Rule> reverseRuleStack(stack <Rule> inRuleStack)
{
    stack <Rule> outRuleStack;
    while (!inRuleStack.empty())
    {
        outRuleStack.push(inRuleStack.top());
        inRuleStack.pop();
    }
    return outRuleStack;
}
stack <Predicate> reversePredicateStack(stack <Predicate> inPredicateStack)
{
    stack <Predicate> outPredicateStack;
    while (!inPredicateStack.empty())
    {
        outPredicateStack.push(inPredicateStack.top());
        inPredicateStack.pop();
    }
    
    return outPredicateStack;
}
stack <string> reverseStringStack(stack <string> inStringStack)
{
    stack <string> outStringStack;
    while (!inStringStack.empty())
    {
        outStringStack.push(inStringStack.top());
        inStringStack.pop();
    }
    
    return outStringStack;
}
bool DatalogProgram::isDuplicateStringInDomain(string inString)
{
    int tempSize = this->domainSize;
    
    while (tempSize > 0)
    {
        if (inString == this->domain[tempSize - 1])
        {
            return true;
        }
        tempSize--;
    }
    return false;
}
void DatalogProgram::stringArraySort()
{
    sort(begin(this->domain), end(this->domain), greater<>());
}

string tokenTypeToString(TokenType inTokenType) //For debugging only
{
    switch(inTokenType)
    {
        case COMMA:
        {
            return "COMMA"; 
            break;
        }
        case PERIOD:
        {
            return "PERIOD"; 
            break;
        }
        case Q_MARK:
        {
            return "Q_MARK"; 
            break;
        }
        case LEFT_PAREN:
        {
            return "LEFT_PAREN"; 
            break;
        }
        case RIGHT_PAREN:
        {
            return "RIGHT_PAREN"; 
            break;
        }
        case COLON:
        {
            return "COLON"; 
            break;
        }
        case COLON_DASH:
        {
            return "COLON_DASH"; 
            break;
        }
        case MULTIPLY:
        {
            return "MULTIPLY"; 
            break;
        }
        case ADD:
        {
            return "ADD"; 
            break;
        }
        case SCHEMES:
        {
            return "SCHEMES"; 
            break;
        }
        case FACTS:
        {
            return "FACTS"; 
            break;
        }case RULES:
        {
            return "RULES"; 
            break;
        }
        case QUERIES:
        {
            return "QUERIES"; 
            break;
        }
        case ID:
        {
            return "ID"; 
            break;
        }
        case STRING:
        {
            return "STRING"; 
            break;
        }
        case COMMENT:
        {
            return "COMMENT"; 
            break;
        }
        case UNDEFINED:
        {
            return "UNDEFINED"; 
            break;
        }
        case EndOf:
        {
            return "EOF"; 
            break;
        }
    }
    return "Error";
}

bool DatalogProgram::isTypeExpected(stack <TokenType> typesThatItCouldBe) //possibly not the way to go, maybe do comparisons within methods. or do a stack of stack <TokenType>s
{
    // stack <TokenType> typeThatItShouldBe; //Obviously this method is all just a placeholder for now
    stack <TokenType> debugTypes = typesThatItCouldBe;
    
    while (!typesThatItCouldBe.empty())
    {
        // cout << "E" << tokenTypeToString(typesThatItCouldBe.top());
        if (this->tokenStack.top().getTokenType() == typesThatItCouldBe.top())
        {
            // cout << "true";
            return true;
        }
        typesThatItCouldBe.pop();
    }
    // cout << "false";
    while (!debugTypes.empty())//while loop for debugging purposes only, to see which types are failing
    {
        // cout << tokenTypeToString(debugTypes.top()); //this is where its not compiling, as shown in the debugger
        debugTypes.pop();
    }
    return false; //if while loop terminates without finding a match, return false
}
bool DatalogProgram::isTypeExpectedOrdered(stack <TokenType> typeToCompare)
{
    stack <Token> tokensCopy = this->tokenStack;
    
    while (!typeToCompare.empty())
    {
        
        if (tokensCopy.top().getTokenType() == typeToCompare.top())
        {
            tokensCopy.pop(); //changed so I dont pop the main tokenStack here
            typeToCompare.pop();
        }
        else
        {
            return false;
        }
    }
    return true;
}
void DatalogProgram::setPredicateStart()
{
    this->headString = tokenStack.top().tokenToString();
    this->tokenStack.pop();
    this->tokenStack.pop();
    // this->currentString = tokenStack.top().tokenToString();
    this->toMakePredicate.push(tokenStack.top().tokenToString());
    
    if (this->domainSize == 0 && isFactString)
    {
        this->domain[0] = tokenStack.top().tokenToString();
        // cout << "--->"  << this->domain[0] << "<--";
        this->domainSize++;
    }
    else if (!isDuplicateStringInDomain(tokenStack.top().tokenToString()) && isFactString)
    {
        this->domain[domainSize] = tokenStack.top().tokenToString();
        this->domainSize++;
    }
    
    this->tokenStack.pop();
}


//recursive descent below:
//
void DatalogProgram::checkDatalogProgram()
{
    stack <TokenType> orderOfTypes;
    stack <TokenType> firstType;
    stack <TokenType> secondType;
    
    stack <TokenType> secondOrder;
    stack <TokenType> thirdType;
    stack <TokenType> fourthType;
    
    stack <TokenType> thirdOrder;
    stack <TokenType> fifthType;
    stack <TokenType> sixthType;
    
    stack <TokenType> fourthOrder;
    stack <TokenType> seventhType;
    stack <TokenType> eighthType;
    
    TokenType schemes = SCHEMES;
    TokenType facts = FACTS;
    TokenType rules = RULES;
    TokenType queries = QUERIES;
    TokenType colon = COLON;
    
    orderOfTypes.push(colon);
    orderOfTypes.push(schemes);
    
    secondOrder.push(colon);
    secondOrder.push(facts);
    
    thirdOrder.push(colon);
    thirdOrder.push(rules);
    
    fourthOrder.push(colon);
    fourthOrder.push(queries);
    
    
    if (isTypeExpectedOrdered(orderOfTypes))
    {
        this->tokenStack.pop();
        this->tokenStack.pop();
        checkScheme();
        checkSchemeList();
    }
    else
    {
        throw this->tokenStack.top();//fail
    }
    
    if (isTypeExpectedOrdered(secondOrder))
    {
        this->tokenStack.pop();
        this->tokenStack.pop();
        checkFactList();
    }
    else
    {
        throw this->tokenStack.top();//fail
    }
    
    if (isTypeExpectedOrdered(thirdOrder))
    {
        this->tokenStack.pop();
        this->tokenStack.pop();
        checkRuleList();
    }
    else
    {
        throw this->tokenStack.top();//fail
    }
    
    if (isTypeExpectedOrdered(fourthOrder))
    {
        this->tokenStack.pop();
        this->tokenStack.pop();
        checkQuery();
        checkQueryList();
    }
    else
    {
        throw this->tokenStack.top();//fail
    }
}
void DatalogProgram::checkSchemeList()
{
    stack <TokenType> expectedType;
    stack <TokenType> followType;
    
    TokenType id = ID;
    TokenType facts = FACTS;
    
    expectedType.push(id);
    followType.push(facts);
    
    if (isTypeExpected(expectedType))
    {
        checkScheme();
        checkSchemeList();
    }
    else if (isTypeExpected(followType))
    {
        return;//return
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
}
void DatalogProgram::checkFactList()
{
    stack <TokenType> expectedType;
    stack <TokenType> followType;
    
    TokenType rules = RULES;
    TokenType id = ID;
    
    expectedType.push(id);
    followType.push(rules);
    
    if (isTypeExpected(expectedType)) //dont pop ID, checkFact will need it
    {
        checkFact();
        checkFactList();
    }
    else if (isTypeExpected(followType))
    {
        // this->tokenStack.pop();
        return; //return
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
}
void DatalogProgram::checkRuleList()
{
    stack <TokenType> expectedType;
    stack <TokenType> secondExpectedType;
    
    TokenType id = ID;
    TokenType queries = QUERIES;
    
    expectedType.push(id);
    secondExpectedType.push(queries);
    
    // cout << this->tokenStack.top().toString();
    if (isTypeExpected(expectedType))
    {
        // cout << "How many";
        checkRule();
        checkRuleList();
    }
    else if (isTypeExpected(secondExpectedType))
    {
        return;
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail
    }
}
void DatalogProgram::checkQueryList()
{
    stack <TokenType> expectedType;
    stack <TokenType> secondExpectedType;
    
    TokenType id = ID;
    TokenType eof = EndOf;
    
    expectedType.push(id);
    secondExpectedType.push(eof);
    
    if (isTypeExpected(expectedType))
    {
        checkQuery();
        checkQueryList();
    }
    else if (isTypeExpected(secondExpectedType))
    {
        return;
        //return
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
    
}

void DatalogProgram::checkScheme()
{
    stack <TokenType> orderOfTypes;
    stack <TokenType> secondExpectedType;
    
    TokenType id = ID;
    TokenType leftParen = LEFT_PAREN;
    TokenType rightParen = RIGHT_PAREN;
    
    orderOfTypes.push(id);
    orderOfTypes.push(leftParen);
    orderOfTypes.push(id);
    
    
    if (isTypeExpectedOrdered(orderOfTypes))
    {
        setPredicateStart();
        checkIdList();
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
    // this->schemes.push(this->currentPredicate);
    this->toMakePredicate = reverseStringStack(this->toMakePredicate);
    
    this->schemes.push(Predicate(this->headString, this->toMakePredicate));
    this->currentPredicate = Predicate(); //empty currentPredicate & other private vars for next go around
    this->currentString = this->emptyString;
    this->headString = this->emptyString;
    this->toMakePredicate = this->emptyStringStack;
    
    secondExpectedType.push(rightParen);
    
    if (isTypeExpected(secondExpectedType))
    {
        this->tokenStack.pop();
        return;
        //return
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
}
void DatalogProgram::checkFact()
{
    this->isFactString = true;
    stack <TokenType> orderOfTypes;
    stack <TokenType> secondOrder;
    
    TokenType period = PERIOD;
    TokenType id = ID;
    TokenType string = STRING;
    TokenType leftParen = LEFT_PAREN;
    TokenType rightParen = RIGHT_PAREN;
    
     //push ID first, so it is checked second
    orderOfTypes.push(string);
    orderOfTypes.push(leftParen);
    orderOfTypes.push(id);
    
    secondOrder.push(period);
    secondOrder.push(rightParen);
    
    if (isTypeExpectedOrdered(orderOfTypes))
    {
        setPredicateStart();
        // this->isFactString = false;
        
        // this->isFactString = false;
        checkStringList(); //RIGHT_PAREN is checked, but not popped at the end of this method
        // this->isFactString = true;
        this->isFactString = false;
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
    this->isFactString = false;
    
    this->toMakePredicate = reverseStringStack(this->toMakePredicate);
    
    this->facts.push(Predicate(this->headString, toMakePredicate));
    this->currentPredicate = Predicate(); //empty currentPredicate & other private vars for next go around
    this->currentString = this->emptyString;
    this->headString = this->emptyString;
    this->toMakePredicate = this->emptyStringStack;
    
    if (isTypeExpectedOrdered(secondOrder)) //if is RIGHT_PAREN, then PERIOD.
    {
        this->tokenStack.pop();
        this->tokenStack.pop();
        return; //return
    }
    else
    {
        throw this->tokenStack.top(); //fail
    }
    
}
void DatalogProgram::checkRule()
{
    checkHeadPredicate(); //You will have set this->headPredicate by the end of this function
    
    stack <TokenType> expectedType;
    stack <TokenType> secondType;
    
    TokenType colonDash = COLON_DASH;
    TokenType period = PERIOD;
    
    expectedType.push(colonDash);
    secondType.push(period);
    
    
    if (isTypeExpected(expectedType))
    {
        this->tokenStack.pop();
        checkPredicate();
        
        this->headString = this->emptyString;
        this->toMakePredicate = this->emptyStringStack;
        
        checkPredicateList();
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail
    }
    // currentRule = Rule(this->headPredicate, this->toMakeRule);
    
    
    // while (!this->toMakeRule.empty())
    // {
    //     this->reversePredicates.push(this->toMakeRule.top());
    //     this->toMakeRule.pop();
    // }
    
    this->toMakeRule = reversePredicateStack(this->toMakeRule);
    
    this->rules.push(Rule(this->headPredicate, this->toMakeRule));
    this->headString = this->emptyString;
    this->toMakePredicate = this->emptyStringStack;
    this->reversePredicates = this->emptyPredicateStack;
    this->toMakeRule = emptyPredicateStack;
    
    
    if (isTypeExpected(secondType))
    {
        this->tokenStack.pop();
        return;
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail
    }
}
void DatalogProgram::checkQuery()
{
    checkPredicate();
    
    stack <TokenType> expectedType;
    
    TokenType qMark = Q_MARK;
    
    expectedType.push(qMark);
    
    this->queries.push(Predicate(headString, toMakePredicate));
    
    this->toMakePredicate = this->emptyStringStack;
    
    if (isTypeExpected(expectedType))
    {
        this->tokenStack.pop();
        return;
    }
    else
    {
        throw this->tokenStack.top();//fail
    }
}


void DatalogProgram::checkHeadPredicate()
{
    // cout << "how many";
    stack <TokenType> orderOfTypes;
    stack <TokenType> secondType;
    
    TokenType id = ID;
    TokenType leftParen = LEFT_PAREN;
    TokenType rightParen = RIGHT_PAREN;
    
    orderOfTypes.push(id);
    orderOfTypes.push(leftParen);
    orderOfTypes.push(id);
    
    secondType.push(rightParen);
    
    if (isTypeExpectedOrdered(orderOfTypes))
    {
        setPredicateStart(); //You will have set headString by the end of this function
        checkIdList(); //you will have finished toMakePredicate by the end of this function
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail
    }
    this->toMakePredicate = reverseStringStack(this->toMakePredicate);
    
    this->headPredicate = Predicate(this->headString, this->toMakePredicate);
    this->headString = this->emptyString;
    this->toMakePredicate = this->emptyStringStack;
    
    if (isTypeExpected(secondType))
    {
        this->tokenStack.pop();
        return;
        // checkIdList();
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top();//fail
    }
}
void DatalogProgram::checkPredicate()
{
    stack <TokenType> orderOfTypes;
    stack <TokenType> secondType;
    
    TokenType id = ID;
    TokenType leftParen = LEFT_PAREN;
    TokenType rightParen = RIGHT_PAREN;
    
    orderOfTypes.push(leftParen);
    orderOfTypes.push(id);
    
    secondType.push(rightParen);
    
    if (isTypeExpectedOrdered(orderOfTypes))
    {
        this->headString = tokenStack.top().tokenToString();
        this->tokenStack.pop();
        this->tokenStack.pop();
        
        checkParameter();
        if (isFromExpression)
        {
            toMakePredicate.push(this->expression);
            this->expression = emptyString;
        }
        isFromExpression = false;
        checkParameterList();
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail
    }
    this->toMakePredicate = reverseStringStack(this->toMakePredicate);
    
    this->toMakeRule.push(Predicate(headString, toMakePredicate));
    //probably set things to empty I think here
    
    if (isTypeExpected(secondType))
    {
        this->tokenStack.pop();
        return;
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top();//fail
    }
}

void DatalogProgram::checkPredicateList()
{
    stack <TokenType> expectedType;
    stack <TokenType> followType;
    
    TokenType comma = COMMA;
    TokenType period = PERIOD;
    
    expectedType.push(comma);
    followType.push(period);
    
    if (isTypeExpected(expectedType))
    {
        this->tokenStack.pop();
        checkPredicate();
        this->toMakePredicate = this->emptyStringStack;
        checkPredicateList();
    }
    else if (isTypeExpected(followType))
    {
        return;
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail
    }
    
}

void DatalogProgram::checkParameterList()
{
    stack <TokenType> expectedType;
    stack <TokenType> followType;
    
    TokenType comma = COMMA;
    TokenType rightParen = RIGHT_PAREN; 
    
    expectedType.push(comma);
    followType.push(rightParen);
    
    if (isTypeExpected(expectedType)) //if is comma
    {
        this->tokenStack.pop();
        checkParameter();
        if (isFromExpression)
        {
            toMakePredicate.push(this->expression);
            this->expression = emptyString;
        }
        isFromExpression = false;
        checkParameterList();
    }
    else if (isTypeExpected(followType)) //if is RIGHT_PAREN
    {
        return;
    }
    else
    {
        // cout << "fail here";
        throw this->tokenStack.top(); //fail sequence
    }
}
void DatalogProgram::checkStringList()
{
    stack <TokenType> orderOfTypes;
    stack <TokenType> firstType;
    stack <TokenType> secondType;
    stack <TokenType> followType; //the type to check for in case stringlist is lambda
    
    TokenType comma = COMMA;
    TokenType string = STRING;
    TokenType rightParen = RIGHT_PAREN;
    
    firstType.push(comma);
    secondType.push(string);
    
    followType.push(rightParen);
    
    if (isTypeExpected(firstType))
    {
        this->tokenStack.pop();
    }
    else if (isTypeExpected(followType))
    {
        // this->tokenStack.pop(); //I commented this line out so it does not pop the rightt paren
        return;  // return to mother method
    }
    else
    //update: I think lambda is simply a check for the followw set, and then you return to the mother method
    {
        // cout << "fancee";
        throw this->tokenStack.top();//fail
    }
    
    if(isTypeExpected(secondType))
    {
        this->currentString = tokenStack.top().tokenToString();
        // cout << currentString;
        if (isFactString)
        {
            // cout << "true";
            if (this->domainSize == 0)
            {
                this->domain[0] = currentString;
                // cout << "--->"  << this->domain[0] << "<--";
                this->domainSize++;
            }
            else if (!isDuplicateStringInDomain(currentString))
            {
                // cout <<"Gotetn";
                this->domain[domainSize] = currentString;
                this->domainSize++;
            }
        }
        else
        {
            // cout << "false";
        }
        this->toMakePredicate.push(currentString);
        this->tokenStack.pop();
        checkStringList();
    }
    else
    {
        throw this->tokenStack.top();
    }
    

}

void DatalogProgram::checkIdList()
{
    // cout <<"true";
    
    stack <TokenType> firstType;
    stack <TokenType> secondType;
    stack <TokenType> followType;
    
    TokenType comma = COMMA;
    TokenType id = ID;
    TokenType rightParen = RIGHT_PAREN;
    
    firstType.push(comma);
    secondType.push(id);
    
    followType.push(rightParen);
    
    if (isTypeExpected(firstType))
    {
        this->tokenStack.pop();
    }
    else if (isTypeExpected(followType))
    {
        return;
    }
    else
    {
        throw this->tokenStack.top();
    }
    
    if (isTypeExpected(secondType)) //if is COMMA then ID
    {
        // cout <<"true2";
        // this->tokenStack.pop();
        this->currentString = tokenStack.top().tokenToString();
        this->toMakePredicate.push(currentString);
        this->tokenStack.pop();
        
        checkIdList();
    }
    else 
    {
        throw this->tokenStack.top();//fail
    }

    
    
    
}

void DatalogProgram::checkParameter()
{
    // if (!parseFailFlag)
    {
        stack <TokenType> expectedTypes;
        stack <TokenType> secondExpectedType;
        
        TokenType id = ID;
        TokenType string = STRING;
        TokenType leftParen = LEFT_PAREN;
        
        expectedTypes.push(id);
        expectedTypes.push(string);
        
        secondExpectedType.push(leftParen);
        
        if (isTypeExpected(expectedTypes)) //check if currentTypeStack is a string, or an id
        {
            if (isFromExpression)
            {
                this->expression += this->tokenStack.top().tokenToString();
            }
            else
            {
                toMakePredicate.push(this->tokenStack.top().tokenToString());
            }
            // cout << this->tokenStack.top().tokenToString();
            this->tokenStack.pop();
            return;
        }
        else if (isTypeExpected(secondExpectedType)) //if is an expression
        {
            isFromExpression = true;
            checkExpression();
        }
        else
        {
            // cout << this->tokenStack.top().tokenTypeToString();
            // cout << "fail4";//fail sequence
            // parseFail(this->tokenStack.top());
            // cout << "fail here";
            throw this->tokenStack.top();
        }
    }
}

void DatalogProgram::checkExpression()
{
    stack <TokenType> expectedType;
    
    TokenType leftParen = LEFT_PAREN;
    TokenType rightParen = RIGHT_PAREN;
    
    expectedType.push(leftParen);
    
    if (isTypeExpected(expectedType)) //check if first type matches LEFT_PAREN
    {
        this->expression += tokenStack.top().tokenToString();
        // toMakePredicate.push(tokenStack.top().tokenToString());
        this->tokenStack.pop();
        
        checkParameter();
        checkOperator();
        checkParameter();
        
        expectedType.pop();//this could be an issue if there are more sets of left parenthesis inside the first set ie ('3'+'2'('2'))
        expectedType.push(rightParen);
    }
    else
    {
        // cout << "fail3";//fail
        // parseFail(this->tokenStack.top());
        throw this->tokenStack.top();
    }
    
    
    
    if (isTypeExpected(expectedType)) //check if is equivalent to RIGHT_PAREN. This is the end of the checks
    {
        this->expression += tokenStack.top().tokenToString();
        // toMakePredicate.push(tokenStack.top().tokenToString());
        this->tokenStack.pop();
        // isFromExpression = false;
        return;
    }
    else
    {
    //   cout << "fail2";//fail
    //   parseFail(this->tokenStack.top());
        throw this->tokenStack.top();
    }
    // else if (parseFailFlag)
    // {
    //     //Do Nothing, pass it forward.
    // }
        
}
void DatalogProgram::checkOperator()
{
    // if (!parseFailFlag)
    {
        //maybe do a 'Try - Throw exception' implementation here, instead of if/else
        stack <TokenType> expectedTypes;
        
        TokenType add = ADD;
        TokenType multiply = MULTIPLY;
        
        expectedTypes.push(add);
        expectedTypes.push(multiply);
        
        
        if (isTypeExpected(expectedTypes)) //AKA is current type an ADD or MULTIPLY symbol?
        {
            this->expression += this->tokenStack.top().tokenToString();
            // toMakePredicate.push(this->tokenStack.top().tokenToString());
            // this->toMakePredicate.push(this->tokenStack.top().tokenToString());
            this->tokenStack.pop();
            return;
        }
        else
        {
            // cout << "fail1";//else, throw error somehow
            // parseFail(this->tokenStack.top());
            throw this->tokenStack.top();
        }
    }
}