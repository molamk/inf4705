all:
	g++ Problem.cpp utils.cpp ProgramArguments.cpp glouton.cpp progdyn1.cpp main.cpp -o main.out
	./main.out -a progdyn1 -e ../../jeux_de_donnees/PR_100_400_1.txt -p -t

utils:
	g++ Problem.cpp utils.cpp -o utils.out
	./utils.out

clean:
	rm *out