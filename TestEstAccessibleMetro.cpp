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

TEST_GROUP(EstAccessibleMetro)
{
};

TEST(EstAccessibleMetro, testEstAccessibleMetro)
{
	Metro unMetro(fichierEntree);
	std::vector< std::vector<std::string> > tableau;
	bool estAccessible = unMetro.estAccessibleMetro(tableau);
	CHECK(estAccessible);
}

