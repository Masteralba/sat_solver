#include <vector>
#include <random>
#include <algorithm>

#include "sat.hpp"
#include "genetic_solver.hpp"
#include "random_generator.hpp"

#define POP_SIZE 100

std::vector<int> randomBinaryVector(int n) {
    std::vector<int> vec(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    
    for (int i = 0; i < n; ++i) {
        vec[i] = distrib(gen);
    }
    return vec;
}

Population::Population(const SAT& sat_obj) : sat(sat_obj){}


void Population::count_fitness()
{
    for (int i=0; i<this->individuals.size(); i++)
        this->individuals[i].count_fitness(this->sat);
}


void Population::generate_population(int size)
{
    for (int i=0; i<size; i++)
    {
        Individual individual(this->sat.number_of_variables );
        this->individuals.push_back(individual);
    }
}

void Population::check_max_fitness()
{
    for (int i=0; i<this->individuals.size(); i++)
    {
        if (individuals[i].fitness > this->MAX_FITNESS)
        {
            this->MAX_FITNESS = individuals[i].fitness;
            this->LAST_GEN = this->CUR_GEN;
        }
    }
}

bool Population::check_solution()
{
    return this->MAX_FITNESS == this->sat.number_of_clauses;
}

bool compare(Individual a, Individual b)
{
    return a.fitness > b.fitness;
}

void Population::sort()
{
    std::sort(begin(this->individuals), end(this->individuals), compare);
}

/*std::vector<Individual> Population::choose_individual(int number)
{
    std::vector<int> cumulative_probability;
    std::vector<Individual> selected;

    int runnig_sum = 0;

    for (int i=0; i<this->individuals.size(); i++)
    {
        runnig_sum += individuals[i].fitness;
        cumulative_probability.push_back(runnig_sum);
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    for (int i=0; i<number; i++)
    {
        std::uniform_int_distribution<int> dist(0, this->TOTAL_FITNESS - 1);
        auto it = std::lower_bound(cumulative_probability.begin(), cumulative_probability.end(), dist(gen));
        int index = it - cumulative_probability.begin();
        selected.push_back(this->individuals[index]);
    }

    return selected;
}*/

#include <iostream>

Individual Population::two_point_crossover(int ind1, int ind2)
{
    Individual* individual1 = &this->individuals[ind1];
    Individual* individual2 = &this->individuals[ind2];

    int r1 = random_int(0, individual1->soluion.size()-1);
    int r2 = random_int(0, individual2->soluion.size()-1);

    if (r2 < r1)
    {
        int t = r1;
        r1 = r2;
        r2 = t;
    }

    std::vector<int> child;

    for (int i=0; i<individual1->soluion.size(); i++)
    {
        if ( i< r1) child.push_back(individual1->soluion[i]);
        if (i >= r1 && i < r2) child.push_back(individual2->soluion[i]);
        if (i>=r2) child.push_back(individual1->soluion[i]);
    }

    Individual newind = Individual();
    newind.soluion = child;

    return newind;

}

void Individual::multi_bit_greedy(const SAT& sat)
{
    int cur_fitness = this->fitness;

    for(int i=0; i<this->soluion.size(); i++)
    {
        this->soluion[i] = !this->soluion[i];
        this->count_fitness(sat);
        if (this->fitness < cur_fitness)
        {
            this->soluion[i] = !this->soluion[i];
            this->fitness = cur_fitness;
        }
        else cur_fitness = this->fitness;
    }

}