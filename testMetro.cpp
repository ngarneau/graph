#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Metro.h"


int main(int argc, char **argv){
	//return

	std::ifstream fichierEntree ("./src/Metro.txt", std::ifstream::in);
	Metro unMetro(fichierEntree);

	std::vector<std::string> route;
	int temps = 0;

	route = unMetro.determinerMinParcours("Pigalle", "Riquet", temps);

	//route = unMetro.bellmanFord("Hoche", "Madeleine", temps);

	//route = unMetro.algorithmeAStar("Hoche", "Madeleine", temps);

	//route = unMetro.cheminLePlusLongMetro("Hoche", "Madeleine", temps);

	for(unsigned int i = 0; i < route.size(); i++)
		std::cout << route[i] << "\n";
	std::cout << "Temps = " << temps << "\n";

}
