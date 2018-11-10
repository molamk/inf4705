all:
	g++ Problem.cpp utils.cpp ProgramArguments.cpp glouton.cpp progdyn1.cpp progdyn2.cpp main.cpp -o main.out
	./main.out -a progdyn2 -e ../../jeux_de_donnees/PR_100_400_2.txt -p -t

utils:
	g++ Problem.cpp utils.cpp -o utils.out
	./utils.out

clean:
	rm *out
