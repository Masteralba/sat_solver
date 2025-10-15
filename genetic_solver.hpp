#pragma once

#include <vector>

#include "sat.hpp"

std::vector<int> randomBinaryVector(int n);

class Individual
{
    public:

    std::vector<int> soluion;

    int fitness=0;

    Individual(int size)
    {
        this->soluion = randomBinaryVector(size);
    }

    Individual(){;}

    void count_fitness(const SAT& sat){this->fitness = sat.solve(this->soluion);}

    void multi_bit_greedy(const SAT& sat);
};

class Population
{

    public:

    int MAX_FITNESS = 0;
    int CUR_GEN = 0;
    int TOTAL_GEN = 0;
    int LAST_GEN = 0;

    const SAT& sat;

    Population(const SAT& sat);

    std::vector<Individual> individuals;

    void count_fitness();

    void generate_population(int size);

    void check_max_fitness();

    bool check_solution();

    void sort();

    Individual two_point_crossover(int index1, int index2);

    //std::vector<Individual> choose_individual(int number);

};