#include "sat.hpp"

#include <iostream>

bool Clause::solve(const std::vector<int>& solution) const
{
    for (int i=0; i< formula.size(); i++)
    {

        if (formula[i] > 0)
        {
            if (formula[i] >= solution.size())
            {
                std::cout << "PIZDEC" << std::endl;
            }

            if (solution[this->formula[i]] == 1)
                return true;
        }
        else
        {
            if (-formula[i] >= solution.size())
            {
                std::cout << "PIZDEC2" << std::endl;
            }

            if (solution[-this->formula[i]] == 0)
                return true;
        }
    }
    
    return false;
}

int SAT::solve(const std::vector<int>& solution) const
{
    int counter = 0;

    for (int i=0; i < this->number_of_clauses; i++)
        if (this->clauses[i].solve(solution)) counter++;
    return counter;
}

SAT::SAT()
{
    this->number_of_clauses = 0;
    this->number_of_variables = 0;
}
