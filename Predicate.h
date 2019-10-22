#ifndef PREDICATE_H
#define PREDICATE_H
#include <stack>
#include <iostream>



using namespace std;

class Predicate
{
    public:
        Predicate();
        Predicate(string headId, stack <string> listOfParameters);
        string toString();
        
    private:
        string headId;
        stack <string> listOfParameters;
};
#endif