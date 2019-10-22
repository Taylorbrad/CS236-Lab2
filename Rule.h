#ifndef RULE_H
#define RULE_H
#include "Predicate.h"
#include <stack>
#include <iostream>
// #pragma once

using namespace std;

class Rule
{
    public:
    Rule();
        Rule(Predicate headPredicate, stack <Predicate> predicateList);
        string toString();
        
    private:
        Predicate headPredicate;
        stack <Predicate> listOfPredicates;
};
#endif