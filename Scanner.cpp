#include "Scanner.h"
// #include "Token.h"
#include <cctype>
using namespace std;
// syn
TokenType setTokenType(char inChar, char nextChar);
string charStackToString(stack <char> inCharStack);

Scanner::Scanner(string fileName)
{
    this->fileName = fileName;
}
stack <Token> Scanner::tokenize()
{
    // cout << "at least we get here";
    int lineNum = 1;
    int lineNumTemp = 0;
    bool isEndMultiQuoteString = false;
    bool isEofCreated = false;
    ifstream inFile;
    ofstream outFile;
    char currentChar;
    stack <char> currentTokenStack;
    stack <char> emptyStack;
    stack <Token> allTokensInFile;
    TokenType tokenType;
    
    inFile.open(this->fileName);
    
    if(!inFile)
    {
        cout << "Unable to read file";
        return allTokensInFile;
    }
    
    while (inFile.peek() != EOF) //While you have not yet reached the end of file, execute:
    {
        while(isspace(inFile.peek())) //Whenever the scanner encounters whitespace, iterate out until there is no more white space
        {
            if (inFile.peek() == '\n')
            {
                lineNum += 1;
            }
            inFile.get();
        }

        // currentTokenStack = emptyStack; //Empty the stack to fill it with another token
        
        currentChar = inFile.get(); //get the next character
        tokenType = setTokenType(currentChar, inFile.peek());//set token types
        

            currentTokenStack.push(currentChar); //double check this before leaving it in
            
        switch (tokenType)//compare token types
        {
            // currentChar = inFile.get();
            case COLON_DASH:
            {
                // currentTokenStack.push(currentChar); //push the colon
                // currentChar = inFile.get(); //get the dash, wait for the next push to get it on the stack
                
                currentChar = inFile.get(); //get the dash
                currentTokenStack.push(currentChar); //push the dash
                
            }
            case UNDEFINED:
            {
                
            }
            case COMMA: //All single character tokens fall through to ADD case
            {
                
            }
            case PERIOD:
            {
                
            }
            case Q_MARK:
            {
                
            }
            case LEFT_PAREN:
            {
                
            }
            case RIGHT_PAREN:
            {
                
            }
            case COLON:
            {
                
            }
            case MULTIPLY:
            {
                
            }
            case ADD: //All single character tokens fall through to the following ADD case:
            {
                // currentTokenStack.push(currentChar);
                // cout << "where ami1";
                break;
            }
            case SCHEMES:
            case FACTS:
            case RULES:
            case QUERIES:
            case ID:
            {
                while (isalnum(inFile.peek()))
                {
                    // currentTokenStack.push(currentChar);
                    currentChar = inFile.get();
                    currentTokenStack.push(currentChar);
                }
                // currentTokenStack.push(currentChar);
                if (charStackToString(currentTokenStack) == "Schemes")
                {
                    tokenType = SCHEMES;
                }
                else if (charStackToString(currentTokenStack) == "Facts")
                {
                    tokenType = FACTS;
                }
                else if (charStackToString(currentTokenStack) == "Rules")
                {
                    tokenType = RULES;
                }
                else if (charStackToString(currentTokenStack) == "Queries")
                {
                    tokenType = QUERIES;
                }
                // cout << "where ami2";
                break;
            }
            case STRING: // kinda works!
            {
                // cout << "where ami";
                // currentTokenStack.push(currentChar);
                // currentChar = inFile.get();
                isEndMultiQuoteString = false;
                while (!isEndMultiQuoteString && inFile.peek() != EOF)//state 1
                {
                    currentChar = inFile.get();
                    currentTokenStack.push(currentChar);
                    if (currentChar == '\n')
                        {
                            lineNumTemp += 1;
                        }
                    if (currentChar == '\'')//state 2
                    {
                        if(inFile.peek() == '\'') //to state 1
                        {
                            currentChar = inFile.get();
                            currentTokenStack.push(currentChar);
                            if (currentChar == '\n')
                            {
                                lineNumTemp += 1;
                            }
                        }
                        else
                        {
                            isEndMultiQuoteString = true; // send to accept state
                        }
                        
                    }//end state 2 if statement
                }//end string while, state 1
                
                // currentTokenStack.push(currentChar); // I think I need this, not sure tho
                
                if (inFile.peek() == EOF && currentTokenStack.top() != '\'') //If the string terminates with an EOF and not a quote, this executes
                {
                    tokenType = setTokenType('&','a'); //set token type to UNDEFINED by passing random characters to setTokenType
                }
                // cout << "where ami3";
                break;
            }
            case COMMENT:
            {
                // cout << "where ami";
                //currentChar is always '#' when this code executes
                // cout << "where ami1";
                if (inFile.peek() == '|') //If you get a | as your character, push it, and get the #
                {
                    while ((currentChar != '|' || inFile.peek() != '#') && inFile.peek() != EOF) //Iterate until you find a # or EOF
                    {
                        currentChar = inFile.get(); //get the next character
                        currentTokenStack.push(currentChar); //push the current character within the comment
                        if (currentChar == '\n')
                            {
                                lineNumTemp += 1;
                            }
                    }
                    currentChar = inFile.get();
                    currentTokenStack.push(currentChar);
                    // cout << "where ami2";
                }
                else //if its a line comment, this else executes
                {
                    while (inFile.peek() != '\n' && inFile.peek() != EOF)
                    {
                        // cout << currentChar;
                        // currentTokenStack.push(currentChar);
                        currentChar = inFile.get();
                        
                        currentTokenStack.push(currentChar);
                        
                        // cout << "post push";
                        // cout << currentChar;
                        
                        // // cout << "where ami2";
                    }
                    // currentTokenStack.pop(); //I shouldnt have to do this, but this is to get the new line off of the comment which appears every time
                    // currentTokenStack.pop();
                    // currentTokenStack.pop();
                    // lineNum += 1;
                    // currentTokenStack.push(currentChar);
                    // cout << "where ami3";
                    //start debug
                    // stack <char> temp = currentTokenStack;
                    //     while (!temp.empty())
                    //     {
                    //         // cout << iter;
                    //         cout << temp.top();
                    //         temp.pop();
                    //         // iter += 1;
                    //     }
                        //end debug
                }
                // cout << "where ami4";
                break;
            }// end COMMENT case
                
                
            
            case EndOf:
            {
                isEofCreated = true;
                // cout << "where ami5";
                break;
            }
            default:
            {
                // cout << "where ami6";
                break;
            }
        }// end switch statement
        if (isEofCreated)
        {
            currentTokenStack.pop();
        }
        Token currentToken = Token(tokenType, currentTokenStack, lineNum); //Create the token object from the data collected
        if (currentToken.getTokenType() != COMMENT)// added to ignore comments for lab 2
        {
            allTokensInFile.push(currentToken); //push that token to the stack
        }
        
        
        currentTokenStack = emptyStack; //empty the current tokens characters for refilling
        
        lineNum += lineNumTemp; //Add the line increments that happened during a multiline comment, string, or undefined token
        lineNumTemp = 0;
        //
        
    } // end while !eof loop
    
    if (allTokensInFile.size() == 0 || !isEofCreated)
    {
        // currentTokenStack.pop();
        // cout << "yup";
        tokenType = setTokenType(EOF, 'a');
        Token currentToken = Token(tokenType, currentTokenStack, lineNum); //Create the token object from the data collected
        allTokensInFile.push(currentToken); //push that token to the stack
    }
    
    inFile.close(); //Close the input file
    
    
    //for testing purposes v
    //
    
    outFile.open("out_file_test.txt");
    
    if (!outFile.is_open())
    {
        // cout << "Test";
        stack <Token> emptyStack;
        cout << "There was an issue trying to create the output text file :/\n";
        return emptyStack;
    }
    stack <Token> returnTokens;
    //
    //for testing purposes ^
    
    stack <Token> reverseTokens;
    
    

    while (!allTokensInFile.empty())
    {
        reverseTokens.push(allTokensInFile.top());
        allTokensInFile.pop();
    }
    
    //for testing purposes v
    //
    returnTokens = reverseTokens;

    int tokenCounter = 0;
    // cout << reverseTokens.top().toString();
    if (!reverseTokens.empty())
    {
        // reverseTokens.pop();
    }
    
    while (!reverseTokens.empty())
    {//this is currently backwards
        tokenCounter += 1;
        Token writeToken = reverseTokens.top();
        outFile << writeToken.toString() << endl;
        // cout << writeToken.toString() << endl;
        reverseTokens.pop();
    }
    outFile << "Total Tokens = " << tokenCounter;
    // cout << "Total Tokens = " << tokenCounter;
    
    
    
    return returnTokens;
    //
    //for testing purposes ^
    
    
    
    // return reverseTokens; GOOD
    
    
    
} //end of Tokenize


TokenType setTokenType(char inChar, char nextChar)
{
    TokenType tokenTypeToReturn;
    
    if (inChar == ',')
    tokenTypeToReturn = COMMA;
    
    else if (inChar == '.')
    tokenTypeToReturn = PERIOD;
    
    else if (inChar == '?')
    tokenTypeToReturn = Q_MARK;
    
    else if (inChar == '(')
    tokenTypeToReturn = LEFT_PAREN;
    
    else if (inChar == ')')
    tokenTypeToReturn = RIGHT_PAREN;
    
    else if (inChar == ':' && nextChar != '-')
    tokenTypeToReturn = COLON;
    
    else if (inChar == ':' && nextChar == '-')
    tokenTypeToReturn = COLON_DASH;
    
    else if (inChar == '*')
    tokenTypeToReturn = MULTIPLY;
    
    else if (inChar == '+')
    tokenTypeToReturn = ADD;
    
    else if (isalpha(inChar))
    tokenTypeToReturn = ID;
    
    else if (inChar == '\'')
    tokenTypeToReturn = STRING;
    
    else if (inChar == '#')
    tokenTypeToReturn = COMMENT;
    
    else if (inChar == EOF)
    tokenTypeToReturn = EndOf;
    
    else
    tokenTypeToReturn = UNDEFINED;
    
    return tokenTypeToReturn;
}

string charStackToString(stack <char> inCharStack)
{
    string tempString;
    string stringToken;
    char tempTop;
    
    stack <char> temp = inCharStack; //save the token array so that it isnt destroyed in the process. In hindsight I may not have considered scope.
    
    while(!inCharStack.empty())
    {
        tempTop = inCharStack.top();
        stringToken = tempTop + stringToken;
        inCharStack.pop();
    }
    
    inCharStack = temp; //reload the token array to what it was
    // return "test return not null";
    return stringToken;
}
