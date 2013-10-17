/*
 * RunAllTests.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Nicolas
 */

#include <CppUTest/CommandLineTestRunner.h>
#include "Metro.h"

std::ifstream fichierEntree ("Metro_light.txt", std::ifstream::in);
int temps;
std::vector<std::string> route;

int main(int argc, char **argv){
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

TEST_GROUP(CheminPlusLong)
{
	void setup()
	{
		temps = 0;
	}
};

TEST(CheminPlusLong, testCheminPlusLong)
{
	Metro unMetro(fichierEntree);
	std::vector<std::string> route;
	int temps = 0;
	int nbChemins;

	route = unMetro.cheminLePlusLongMetro("Anvers", "Alma Marceau", temps);
	nbChemins = route.size();

	CHECK_EQUAL(temps, 145);
	CHECK_EQUAL("Anvers", route.front());
	CHECK_EQUAL("Alma Marceau", route.back());
	CHECK_EQUAL(3, nbChemins);

	route = unMetro.cheminLePlusLongMetro("Anatole France", "Assemblée Nationale", temps);
	nbChemins = route.size();

	CHECK_EQUAL(temps, 355);
	CHECK_EQUAL("Anatole France", route.front());
	CHECK_EQUAL("Assemblée Nationale", route.back());
	CHECK_EQUAL(7, nbChemins);
}
