#include "Predicate.h"

using namespace std;

Predicate::Predicate()
{
    
}
Predicate::Predicate(string headId, stack <string> listOfParameters)
{
    this->headId = headId;
    this->listOfParameters = listOfParameters;
}
//
string Predicate::toString()
{
    string returnString;
    int counter = 0;
    
    returnString = this->headId + "(";
    
    while (!this->listOfParameters.empty())
    {
        if (counter != 0) //Don't add a comma on the first iteration, but do every other time
        {
            returnString += ",";
        }
        else
        {
            counter++;
        }
        
        returnString += this->listOfParameters.top(); //Parameters have not been created, including the toString method
        
        this->listOfParameters.pop();
    }
    returnString += ")";
    
    return returnString;
}