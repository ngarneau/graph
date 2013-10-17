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

TEST_GROUP(ChargementMetro)
{
};

TEST(ChargementMetro, testChargementMetro)
{
	Metro unMetro(fichierEntree);
	int nbStations = unMetro.nbStations();
	CHECK_EQUAL(376, nbStations);

	Metro unMetro2(unMetro);
	int nbStations2 = unMetro2.nbStations();
	CHECK_EQUAL(376, nbStations2);

	Metro unMetro3 = unMetro2;
	int nbStations3 = unMetro3.nbStations();
	CHECK_EQUAL(376, nbStations3);
}

TEST(ChargementMetro, constructeurCopie)
{
	//Metro unMetro(fichierEntree);
	//int nbStations = unMetro.nbStations();
	//CHECK_EQUAL(376, nbStations);

	//Metro unMetro2(unMetro);
	//int nbStations2 = unMetro2.nbStations();
	//CHECK_EQUAL(376, nbStations2);
}

