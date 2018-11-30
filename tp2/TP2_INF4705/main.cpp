
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */


using namespace std;


struct dynamite {
	dynamite(unsigned int p, unsigned int w) :profit(p), weight(w)
	{}

	unsigned int profit;
	unsigned int weight;
};

unsigned int dynamique1(const std::vector<dynamite>& data, unsigned int d, unsigned int n)
{
	if (n == 0)    // pas d'objet ?
		return 0;  // la solution est vide
	else
	{
		// Nous allons considérer le dernier objet, dont les données sont dans la
		// case n-1 des vecteurs
		const unsigned int i(n - 1);

		// Si l'objet i ne rentre pas dans le sac, il ne peut pas être choisi. La
		// valeur de la solution est donc obtenue en considérant les autres
		// objets, en gardant la même capacité.
		if (data[i].weight > d)
			return dynamique1(data, d, n - 1);
		else
			// Si l'objet i tient dans le sac, il y a deux possibilités. Soit il
			// participe à la solution d'une valeur p[i], auquel cas il ne
			// reste qu'une capacité de d - w[i] pour les autres objets. Soit il ne
			// participe pas à la solution, auquel cas la capacité est
			// inchangée. La valeur de la solution optimale est obtenue en gardant
			// la meilleure de ces deux solutions.
			return std::max
			(dynamique1(data, d - data[i].weight, n - 1) + data[i].profit,
				dynamique1(data, d, n - 1));
	}
}

vector<dynamite> convertToDyn(const std::vector<int>& data) {
	vector<dynamite> retour;
	
	for (unsigned int i = 0; i < data.size(); i++) {
		retour.push_back(dynamite(data[i], data[i]));
	}
	return retour;
}


//la fonction recois le nom du fichier en parametre et retourne un vecteur dentier trié
vector<int> tri(string nom_fichier,int& poidTotal) {

	// Création et initialisation du vecteur
	unsigned int index;
	unsigned int poid;
	std::vector <int> poids;

	
	ifstream fichier(nom_fichier.c_str(), ios::in);  // on ouvre le fichier en lecture

	if (fichier)  // si l'ouverture a réussi
	{
		// instructions
		unsigned int taille;
		fichier >> taille;
		for (unsigned int i = 0; i < taille; i++) {
			fichier >> index;
			fichier >> poid;
			poids.push_back(poid);

		}
		fichier >> poidTotal;

		fichier.close();  // on ferme le fichier
	}
	else  // sinon
		cerr << "Impossible d'ouvrir le fichier !" << endl;


	std::sort(poids.begin(), poids.end());


	return poids;
}

int glouton(int podLimit, vector<int> poids, vector<int>& resultat) {
	int poidUtil = 0;
	int temp;

	do{
		temp = poids.back();
		if (poidUtil + temp < podLimit) {
			poidUtil += temp;
			resultat.push_back(temp);
		}
			
	} while (poidUtil + temp < podLimit);

	return poidUtil;
}

int genererNombre(int a, int b) {
	int rslt;
	/* initialize random seed: */
	srand(time(NULL));
	/* generate secret number between 1 and 10: */
	rslt = rand() % b + a;
	//cout << "number: " << rslt;
	return rslt;

}

vector<int> gloutonSolutionVoisine(vector<int> tableautri, vector<int> resultat, int poidTotal) {
	vector<int> solutionVoisine;
	vector<int> uneSolution;
	int poid = 0;
	int index = 0;

	for (unsigned int i = resultat.size(); i < tableautri.size(); i++) {
		solutionVoisine.push_back(tableautri[i]);
	}


	while (poid < poidTotal) {
		if (solutionVoisine.size() > 1) {
			index = genererNombre(0, solutionVoisine.size() - 1);
		}
		else
			index = 0;
		poid += solutionVoisine[index];
		uneSolution.push_back(solutionVoisine[index]);
		//solutionVoisine.erase(solutionVoisine.begin() + index);
	}

	if (poid > poidTotal) {
		
		while (poid > poidTotal) {
			if (uneSolution.size() > 1) {
				index = genererNombre(0, uneSolution.size() - 1);
			}
			else
				index = 0;
			poid -= uneSolution[index];
			uneSolution.erase(uneSolution.begin() + index);
		}
	}


	return uneSolution;
}

int sommeTab(vector<int> tab) {
	int sm = 0;
	for (unsigned int i = 0; i < tab.size(); i++) {
		sm += tab[i];
	}
	return sm;
}

vector<int> circuit(vector<int> So, int T, int kmax, int P ,int alpha, vector<int>& tabTrier, int& poidTotal) {
	vector<int> S, sMeilleur, sPrime;
	int teta, delta;
	double valeur;


	S = So;
	sMeilleur = S;
	teta = T;

	for (unsigned int i = 0; i < kmax; i++) {
		for (unsigned int j = 0; j < P; j++) {
			sPrime = gloutonSolutionVoisine(S, tabTrier, poidTotal);
			delta = sommeTab(sPrime) - sommeTab(S);
			valeur = exp((double)delta / ((double)teta*(double)i));
			if (delta >= 0 || (valeur >= 0.0 && valeur <= 1.0)) {
				S = sPrime;
				if (sommeTab(S) > sommeTab(sMeilleur))
					sMeilleur = S;
			}
			teta *= alpha;
		}
	}

	return sMeilleur;
}





int MAX(int a, int b) {
	if (a < b)
		return b;
	else
		return a;
}





int main(int argc, const char * argv[]) {

	string nom_fichier = "jeux_de_donnees/WC-10-1000-10.txt";
	cout << "nom du fichier: " << nom_fichier << endl;
	int poidLimite = 0;
	int poidUtil;

	float temps;
	clock_t t1, t2;
	///////////////////////////////////// GLOUTON //////////////////////////////////////////
	t1 = clock(); //Prise du temps.
	vector<int> tabTrier = tri(nom_fichier, poidLimite); //Tris decroissant des dynamites  
	vector<int> resultat;
	cout << "\n\t\t GLOUTON " << endl;
	cout << "Poid limite: " << poidLimite << endl;
	poidUtil = glouton(poidLimite, tabTrier, resultat); //Application de l'agorithme glouton
	cout << "poid utile: " << poidUtil << endl;
	t2 = clock(); //Fin de la prise du temps

	temps = (float)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "temps = " << temps << "s" << endl;
/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////dYNAMIQUE /////////////////////////////////////////
	
	vector<dynamite> tableauDePoids;

	tableauDePoids = convertToDyn(tabTrier);
	cout << "\n\t\t DYNAMIQUE1 " << endl;
	cout << "Poid limite: " << poidLimite << endl;
	t1 = clock(); //Prise du temps.
	poidUtil = dynamique1(tableauDePoids, poidLimite, tableauDePoids.size());
	t2 = clock();
	cout << "poid utile: " << poidUtil << endl;

	temps = (float)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "temps = " << temps << "s" << endl;

/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////// circuit ////////////////////////////////////////////////
	

	cout << "\n\t\t Circuit " << endl;
	cout << "Poid limite: " << poidLimite << endl;
	cout << "Poid limite: " << poidLimite << endl;
	t1 = clock(); //Prise du temps.
	vector<int> So = circuit(tabTrier, 100, 10, 10, 0.6, resultat,poidLimite);
	t2 = clock();
	//vector<int> uneSolution = gloutonSolutionVoisine(tabTrier, resultat,poidLimite);
	poidUtil = 0;
	for (unsigned int i = 0; i < So.size(); i++) {
		poidUtil += So[i];
	}
	cout << "poid utile: " << poidUtil << endl;

	temps = (float)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "temps = " << temps << "s" << endl;

	

/////////////////////////////////////////////////////////////////////////////////////////////
	

	return 0;
}