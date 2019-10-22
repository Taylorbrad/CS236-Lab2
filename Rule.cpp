#include "Rule.h"

using namespace std;

Rule::Rule()
{
    
}
Rule::Rule(Predicate headPredicate, stack <Predicate> listOfPredicates)
{
    this->headPredicate = headPredicate;
    this->listOfPredicates = listOfPredicates;
}
string Rule::toString()
{
    string returnString;
    int counter = 0;
    
    returnString = headPredicate.toString() + " :- ";
    
    while (!listOfPredicates.empty())
    {
        if (counter != 0)
        {
            returnString += ",";
        }
        else
        {
            counter++;
        }
        returnString += listOfPredicates.top().toString();
        listOfPredicates.pop();
    }
    
    returnString += ".";
    
    return returnString;
    
}