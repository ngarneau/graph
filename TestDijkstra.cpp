/*
 * RunAllTests.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Nicolas
 */

#include <CppUTest/CommandLineTestRunner.h>
#include "Metro.h"

std::ifstream fichierEntree ("Metro.txt", std::ifstream::in);
int temps;
std::vector<std::string> route;

int main(int argc, char **argv){
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

TEST_GROUP(Dijkstra)
{
	void setup()
	{
		temps = 0;
	}
};

TEST(Dijkstra, testCheminPlusCourt)
{
	Metro unMetro(fichierEntree);
	std::vector<std::string> route;
	int temps = 0;
	route = unMetro.determinerMinParcours("Hoche", "Madeleine", temps);
	int nbChemins = route.size();

	CHECK_EQUAL(temps, 1334);
	CHECK_EQUAL("Hoche", route.front());
	CHECK_EQUAL("Madeleine", route.back());
	CHECK_EQUAL(17, nbChemins);

	route = unMetro.determinerMinParcours("Bastille", "Les Halles", temps);

	CHECK_EQUAL(temps, 500);
	CHECK_EQUAL("Bastille", route.front());
	CHECK_EQUAL("Les Halles", route.back());

	route = unMetro.bellmanFord("Jasmin", "Danube", temps);
	CHECK_EQUAL(temps, 1950);
	CHECK_EQUAL("Jasmin", route.front());
	CHECK_EQUAL("Danube", route.back());
}
