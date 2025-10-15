#include <iostream>
#include <string>
#include <ctime> 

#include "sat.hpp"
#include "genetic_solver.hpp"
#include "parser.hpp"
#include "random_generator.hpp"


int main(int argc, char** argv)
{
    init_random_engine();

    SAT sat;

    if (argc != 2)
    {
        std::cout << "Filename (.cnf) needed" << std::endl;
        return 0;
    }

    std::string filename = argv[1];

    if (!parse_file_into_sat(&sat, filename)) return 0;

    // parse SAT

    clock_t start = clock(); // Засекаем время начала

    Population population(sat);

    int POP_SIZE = 100;

    int LIMIT = 20;

    population.generate_population(POP_SIZE);

    int MAX_GEN = 500;

    double ELITISM_RATE = 0.7;

    population.count_fitness();
    population.sort();

    for(int TOTAL_GEN=0; TOTAL_GEN<MAX_GEN; TOTAL_GEN++)
    {
        population.count_fitness();
        population.check_max_fitness();

        if (population.MAX_FITNESS == sat.number_of_clauses)
        {
            double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
            std::cout << "Answer: Satisfiable. Duration: " << duration << " ";
            if (sat.satisfiable == true) std::cout << "CORRECT " << std::endl;
            else std::cout << "INCORRECT " <<  std::endl;
            return 0;
        }

        population.sort();

        int n_to_keep = std::round(population.individuals.size()*ELITISM_RATE);

        population.individuals.erase(population.individuals.begin()+n_to_keep, population.individuals.end());

        while(population.individuals.size() != POP_SIZE)
        {
            Individual newind = population.two_point_crossover(random_int(0, population.individuals.size()-1),
            random_int(0, population.individuals.size()-1));
            newind.count_fitness(sat);
            newind.multi_bit_greedy(sat);
            population.individuals.push_back(newind);
        }

        population.CUR_GEN++;

        if (population.CUR_GEN - population.LAST_GEN > LIMIT)
        {
            population.individuals.clear();
            population.generate_population(POP_SIZE);
            population.LAST_GEN = population.CUR_GEN;
        }
    }

    //stop timer

    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Answer: Not Satisfiable. Duration: " << duration << " ";
    if (sat.satisfiable == false) std::cout << "CORRECT " << std::endl;
    else std::cout << "INCORRECT " << std::endl;

    return 0;
}