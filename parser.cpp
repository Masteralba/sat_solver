#include <fstream> 
#include <iostream>
#include <sstream>
#include <string>

#include "sat.hpp"

#include "parser.hpp"


bool parse_file_into_sat(SAT* sat, std::string filename)
{

    std::ifstream file(filename);  // Открываем файл для чтения
    
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        return false;
    }
    
    std::string line;
    
    // Чтение по строкам
    while (std::getline(file, line)) {
        if (line[0] == 'c')
        {
            if (line.find("NOTE: Not Satisfiable") != std::string::npos)
                sat->satisfiable = false;
            if (line.find("NOTE: Satisfiable") != std::string::npos)
                sat->satisfiable = true;

            continue;
        }

        if (line[0] == 'p')
        {
            std::istringstream iss(line);
            std::string token;
            iss >> token >> token;
            iss >> sat->number_of_variables >> sat->number_of_clauses;

            continue;

        }

        if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        continue; // Пропускаем пустые строки
        }

        std::istringstream iss(line);

        Clause new_clause;

        int literal;

        while (iss >> literal && literal != 0) {
            if (literal > 0)
                new_clause.formula.push_back(literal-1);
            else
                new_clause.formula.push_back(literal+1);
        }

        sat->clauses.push_back(new_clause);

        
    }
    
    file.close();  // Закрываем файл

    return true;

}

