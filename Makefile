all: main

main: main.o genetic_solver.o parser.o sat.o random.o
	g++ -g main.o genetic_solver.o parser.o sat.o random.o -o main

main.o: main.cpp sat.hpp
	g++ -g -c main.cpp -o main.o

genetic_solver.o: genetic_solver.cpp  sat.hpp
	g++ -g -c genetic_solver.cpp -o genetic_solver.o

parser.o: parser.cpp  sat.hpp
	g++ -g -c parser.cpp -o parser.o

sat.o: sat.cpp sat.hpp
	g++ -g -c sat.cpp -o sat.o

random.o: random_generator.cpp random_generator.hpp
	g++ -g -c random_generator.cpp -o random.o

clean:
	rm -f *.o main