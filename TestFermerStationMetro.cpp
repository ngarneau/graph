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

TEST_GROUP(FermerStationMetro)
{
};

TEST(FermerStationMetro, testFermerStationMetro)
{
	Metro unMetro(fichierEntree);
	std::vector<std::string> listeStations;

	listeStations = unMetro.fermerStationMetro();
	CHECK_EQUAL("Alexandre Dumas", listeStations[0]);
	CHECK_EQUAL("Arts et Métiers", listeStations[1]);
}

