#pragma once

#include <vector>

class Clause
{

    public:

    std::vector<int> formula;

    bool solve(const std::vector<int>& solution) const;

};


class SAT
{

    public:

    bool satisfiable;

    int number_of_variables;

    int number_of_clauses;

    std::vector<Clause> clauses;

    SAT();

    // return the number of True clauses
    int solve(const std::vector<int>& solution) const;

    void numer_of_variables_setter(int num) {this->number_of_variables = num;}
    void numer_of_clauses_setter(int num) {this->number_of_clauses = num;}

};