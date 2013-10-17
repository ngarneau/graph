/*
 * RunAllTests.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Nicolas
 */

#include <CppUTest/CommandLineTestRunner.h>
#include "Graphe.h"

int main(int argc, char **argv){
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

TEST_GROUP(Graphe)
{
};

TEST(Graphe, testConstructeur)
{
	Graphe graphe;
	CHECK_EQUAL(graphe.nombreSommets(), 0);
}

TEST(Graphe, testOperateurEgale)
{
	Graphe graphe;
	Graphe graphe4 = graphe;

	graphe.ajouterSommet(1, "Nicolas", 1, 1);

	Graphe graphe2 = graphe;
	CHECK_EQUAL(1, graphe2.nombreSommets());

	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.ajouterSommet(3, "Nicolas2", 2, 2);
	graphe.ajouterSommet(4, "Nicolas2", 2, 2);
	Graphe graphe3 = graphe;
	CHECK_EQUAL(4, graphe3.nombreSommets());

	graphe.ajouterArc(1, 2, 56);
	Graphe graphe5 = graphe;
	CHECK(graphe5.arcExiste(1, 2));

	graphe.ajouterArc(2, 4, 85);
	Graphe graphe6 = graphe;
	CHECK_EQUAL(4, graphe6.nombreSommets());
	CHECK(graphe6.arcExiste(1, 2));
	CHECK(graphe6.arcExiste(2, 4));
}

TEST(Graphe, testConstructeurCopie)
{
	Graphe graphe;
	Graphe graphe4(graphe);

	graphe.ajouterSommet(1, "Nicolas", 1, 1);

	Graphe graphe2(graphe);
	CHECK_EQUAL(1, graphe2.nombreSommets());

	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.ajouterSommet(3, "Nicolas2", 2, 2);
	graphe.ajouterSommet(4, "Nicolas2", 2, 2);
	Graphe graphe3(graphe);
	CHECK_EQUAL(4, graphe3.nombreSommets());

	graphe.ajouterArc(1, 2, 56);
	Graphe graphe5(graphe);
	CHECK(graphe5.arcExiste(1, 2));

	graphe.ajouterArc(2, 4, 85);
	Graphe graphe6(graphe);
	CHECK_EQUAL(4, graphe6.nombreSommets());
	CHECK(graphe6.arcExiste(1, 2));
	CHECK(graphe6.arcExiste(2, 4));

}

TEST(Graphe, testAjoutSommetsGraphe)
{
	Graphe graphe;

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK_EQUAL(1, graphe.nombreSommets());

	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	CHECK_EQUAL(2, graphe.nombreSommets());

	graphe.ajouterSommet(3, "Nicolas3", 3, 3);
	CHECK_EQUAL(3, graphe.nombreSommets());

	try{
		graphe.ajouterSommet(3, "Nicolas4", 4, 4);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Ajouter sommet: Le sommet existe deja", e.what());
	}
}

TEST(Graphe, testEnleverSommet)
{
	Graphe graphe;

	try{
		graphe.enleverSommet(1);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Enlever sommet: Le sommet existe pas", e.what());
	}

	// enlever le seul sommet
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK_EQUAL(1, graphe.nombreSommets());
	graphe.enleverSommet(1);
	CHECK_EQUAL(0, graphe.nombreSommets());

	// enlever le dernier lorsqu'il en reste
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.enleverSommet(2);
	CHECK_EQUAL(1, graphe.nombreSommets());

	// enlever le premier lorsqu'il en reste
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.enleverSommet(1);
	CHECK_EQUAL(1, graphe.nombreSommets());

	// enlever un sommet quelconque dans la liste
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(3, "Nicolas3", 3, 3);
	graphe.enleverSommet(1);
	CHECK_EQUAL(2, graphe.nombreSommets());

	// retrait d'un sommet dont un arc pointe vers lui
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterArc(1, 2, 3);
	CHECK(graphe.arcExiste(1, 2));
	graphe.enleverSommet(2);
	CHECK(!graphe.arcExiste(1, 2));

}

TEST(Graphe, testEnleverSommets)
{
	Graphe graphe;

	try{
		graphe.enleverSommets("Nicolas");
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Enlever sommet: Le sommet existe pas", e.what());
	}

	// enlever le seul sommet
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.enleverSommets("Nicolas");
	CHECK_EQUAL(0, graphe.nombreSommets());

	// enlever le dernier lorsqu'il en reste
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.enleverSommets("Nicolas2");
	CHECK_EQUAL(1, graphe.nombreSommets());

	// enlever le premier lorsqu'il en reste
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.enleverSommets("Nicolas");
	CHECK_EQUAL(1, graphe.nombreSommets());

	// enlever un sommet quelconque dans la liste
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(3, "Nicolas3", 3, 3);
	graphe.enleverSommets("Nicolas");
	CHECK_EQUAL(2, graphe.nombreSommets());

	// retrait de plusieurs sommets
	graphe.ajouterSommet(4, "Nicolas3", 3, 3);
	graphe.enleverSommets("Nicolas3");
	CHECK_EQUAL(2, graphe.nombreSommets());

	// retrait d'un sommet dont un arc pointe vers lui
	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterArc(1, 2, 3);
	CHECK(graphe.arcExiste(1, 2));
	graphe.enleverSommets("Nicolas");

}

TEST(Graphe, testAjouterArc)
{
	Graphe graphe;

	try{
		graphe.ajouterArc(1, 2, 3);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Ajouter arc: un des 2 sommets n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.ajouterArc(1, 2, 3);
	graphe.arcExiste(1, 2);

	graphe.ajouterSommet(3, "Nicolas3", 3, 3);
	graphe.ajouterArc(1, 3, 6);
	graphe.arcExiste(1, 3);

	Graphe graphe2;
	graphe2.ajouterSommet(1, "Nicolas", 1, 1);
	graphe2.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe2.ajouterArc(1, 2, 3);
	graphe2.arcExiste(1, 2);

}

TEST(Graphe, testEnleverArc)
{
	Graphe graphe;

	try{
		graphe.enleverArc(1, 2);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Enlever arc: un des 2 sommets n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	try{
		graphe.enleverArc(1, 2);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Enlever arc: l'arc entre les 2 sommets n'existe pas.", e.what());
	}

	graphe.ajouterArc(1, 2, 78);
	graphe.enleverArc(1, 2);
	CHECK(!graphe.arcExiste(1, 2));

	graphe.ajouterSommet(3, "Nicolas", 1, 1);
	graphe.ajouterSommet(4, "Nicolas2", 2, 2);

	graphe.ajouterArc(1, 2, 78);
	graphe.ajouterArc(2, 3, 78);
	graphe.enleverArc(1, 2);
	CHECK(!graphe.arcExiste(1, 2));
	CHECK(graphe.arcExiste(2, 3));
	graphe.enleverArc(2, 3);
	CHECK(!graphe.arcExiste(2, 3));

	graphe.ajouterArc(1, 2, 78);
	graphe.ajouterArc(2, 3, 78);
	graphe.ajouterArc(2, 4, 78);
	graphe.enleverArc(2, 3);
	CHECK(!graphe.arcExiste(2, 3));
	graphe.enleverArc(2, 4);
	CHECK(!graphe.arcExiste(2, 4));
	graphe.enleverArc(1, 2);
	CHECK(!graphe.arcExiste(1, 2));

}

TEST(Graphe, testEstVide)
{
	Graphe graphe;

	CHECK(graphe.estVide());

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK(!graphe.estVide());

	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	CHECK(!graphe.estVide());

	graphe.enleverSommet(1);
	graphe.enleverSommet(2);
	CHECK(graphe.estVide());
}

TEST(Graphe, testSommetExiste)
{
	Graphe graphe;

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK(graphe.sommetExiste(1));
	CHECK(!graphe.sommetExiste(2));

	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	graphe.ajouterSommet(3, "Nicolas3", 3, 3);
	CHECK(graphe.sommetExiste(3));
	CHECK(graphe.sommetExiste(2));
	CHECK(!graphe.sommetExiste(4));

	graphe.enleverSommet(2);
	CHECK(!graphe.sommetExiste(2));
}

TEST(Graphe, testArcExiste)
{
	Graphe graphe;

	try{
		graphe.arcExiste(1, 2);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Arc existe: un des 2 sommets n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	CHECK(!graphe.arcExiste(1, 2));

	graphe.ajouterArc(1, 2, 3);
	CHECK(graphe.arcExiste(1, 2));

	graphe.ajouterSommet(3, "Nicolas3", 3, 3);
	graphe.ajouterSommet(4, "Nicolas4", 4, 4);
	CHECK(!graphe.arcExiste(1, 4));
	graphe.ajouterArc(1, 3, 6);
	CHECK(graphe.arcExiste(1, 3));
}

TEST(Graphe, testListerVecteur)
{
	Graphe graphe;
	graphe.ajouterSommet(1, "Nicolas", 3, 3);

	std::vector<int> vecteurSommets;
	vecteurSommets = graphe.listerSommets();
	CHECK( vecteurSommets[0] == 1 );

	graphe.ajouterSommet(2, "Nicolas2", 3, 3);
	vecteurSommets = graphe.listerSommets();
	CHECK( vecteurSommets[0] == 1 );
	CHECK( vecteurSommets[1] == 2 );
}

TEST(Graphe, testListerNomsVecteur)
{
	Graphe graphe;
	graphe.ajouterSommet(1, "Nicolas", 3, 3);

	std::vector<std::string> vecteurSommets;
	vecteurSommets = graphe.listerNomsSommets();
	CHECK( vecteurSommets[0] == "Nicolas" );

	graphe.ajouterSommet(2, "Nicolas2", 3, 3);
	vecteurSommets = graphe.listerNomsSommets();
	CHECK( vecteurSommets[0] == "Nicolas" );
	CHECK( vecteurSommets[1] == "Nicolas2" );
}

TEST(Graphe, testListerSommetsAdjacents)
{
	Graphe graphe;
	try{
		graphe.listerSommetsAdjacents(1);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Sommets adjacents: le sommet n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 1, 1);
	graphe.ajouterArc(1, 2, 3);
	std::vector<int> vecteur;
	vecteur = graphe.listerSommetsAdjacents(1);
	CHECK( vecteur[0] == 2 );

	graphe.ajouterSommet(3, "Nicolas3", 1, 1);
	graphe.ajouterArc(1, 3, 3);
	vecteur = graphe.listerSommetsAdjacents(1);
	CHECK( vecteur[0] == 2 );
	CHECK( vecteur[1] == 3 );
}

TEST(Graphe, testOrdreSortie)
{
	Graphe graphe;
	try{
		graphe.ordreSortieSommet(1);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Ordre sortie: le sommet n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK( graphe.ordreSortieSommet(1) == 0 );

	graphe.ajouterSommet(2, "Nicolas2", 1, 1);
	graphe.ajouterArc(1, 2, 3);
	CHECK( graphe.ordreSortieSommet(1) == 1 );
}

TEST(Graphe, testOrdreEntree)
{
	Graphe graphe;
	try{
		graphe.ordreEntreeSommet(1);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Ordre entree: le sommet n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK( graphe.ordreEntreeSommet(1) == 0 );

	graphe.ajouterSommet(2, "Nicolas2", 1, 1);
	graphe.ajouterArc(2, 1, 3);
	CHECK( graphe.ordreEntreeSommet(1) == 1 );

	graphe.ajouterSommet(3, "Nicolas3", 1, 1);
	graphe.ajouterArc(3, 1, 3);
	CHECK( graphe.ordreEntreeSommet(1) == 2 );
}

TEST(Graphe, testCoutArc)
{
	Graphe graphe;

	try{
		graphe.getCoutArc(1, 2);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Cout arc: un des deux sommets n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	graphe.ajouterSommet(2, "Nicolas2", 2, 2);
	try{
		graphe.getCoutArc(1, 2);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Cout arc: l'arc n'existe pas.", e.what());
	}

	graphe.ajouterArc(1, 2, 78);
	CHECK_EQUAL(78, graphe.getCoutArc(1, 2));

	graphe.ajouterSommet(3, "Nicolas3", 2, 2);

	graphe.ajouterArc(3, 2, 389);
	CHECK_EQUAL(389, graphe.getCoutArc(3, 2));
}

TEST(Graphe, testNumeroSommet)
{
	Graphe graphe;

	try{
		graphe.getNumeroSommet(1, 1);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Numero sommet: le sommet n'est pas dans le graphe.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK_EQUAL(1, graphe.getNumeroSommet(1, 1));

	try{
		graphe.getNumeroSommet(3,21);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Numero sommet: le sommet n'est pas dans le graphe.", e.what());
	}

	graphe.ajouterSommet(2, "Nicolas", 3, 4);
	CHECK_EQUAL(2, graphe.getNumeroSommet(3, 4));
	CHECK_EQUAL(1, graphe.getNumeroSommet(1, 1));
}

TEST(Graphe, testNomSommet)
{
	Graphe graphe;

	try{
		graphe.getNomSommet(1);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Nom sommet: le sommet n'existe pas.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	CHECK_EQUAL("Nicolas", graphe.getNomSommet(1));

	graphe.ajouterSommet(2, "Nicolas2", 1, 1);
	CHECK_EQUAL("Nicolas", graphe.getNomSommet(1));
	CHECK_EQUAL("Nicolas2", graphe.getNomSommet(2));
}

TEST(Graphe, testNumeroSommetNom)
{
	Graphe graphe;

	try{
		graphe.getNumeroSommet("Nicolas");
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Numero sommet nom: il n'y a pas de sommets.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 1, 1);
	try{
		graphe.getNumeroSommet("Nicolas2");
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Numero sommet nom: le sommet n'existe pas.", e.what());
	}

	CHECK_EQUAL(1, graphe.getNumeroSommet("Nicolas"));

	graphe.ajouterSommet(2, "Nicolas2", 1, 1);
	CHECK_EQUAL(1, graphe.getNumeroSommet("Nicolas"));
	CHECK_EQUAL(2, graphe.getNumeroSommet("Nicolas2"));

	graphe.ajouterSommet(3, "Nicolas3", 1, 1);
	CHECK_EQUAL(1, graphe.getNumeroSommet("Nicolas"));
	CHECK_EQUAL(2, graphe.getNumeroSommet("Nicolas2"));
	CHECK_EQUAL(3, graphe.getNumeroSommet("Nicolas3"));
}

TEST(Graphe, testCoordSommet)
{
	Graphe graphe;

	int x, y;

	try{
		graphe.getCoordonnesSommet(1, x, y);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Coord sommet: il n'y a pas de sommets.", e.what());
	}

	graphe.ajouterSommet(1, "Nicolas", 12, 14);
	try{
		graphe.getCoordonnesSommet(2, x, y);
	}catch(std::logic_error &e){
		STRCMP_EQUAL("Coord sommet: le sommet n'existe pas.", e.what());
	}

	graphe.getCoordonnesSommet(1, x, y);
	CHECK_EQUAL(12, x);
	CHECK_EQUAL(14, y);

	graphe.ajouterSommet(2, "Nicolas2", 34, 65);
	graphe.getCoordonnesSommet(2, x, y);
	CHECK_EQUAL(34, x);
	CHECK_EQUAL(65, y);

}

TEST(Graphe, testFermetureGraphe)
{
	Graphe graphe;

	graphe.ajouterSommet(1, "Nicolas", 12, 14);
	graphe.ajouterSommet(2, "Nicolas2", 23, 44);
	graphe.ajouterSommet(3, "Nicolas3", 4, 74);
	graphe.ajouterSommet(4, "Nicolas4", 4, 74);

	graphe.ajouterArc(1, 2, 1);
	graphe.ajouterArc(1, 4, 8);
	graphe.ajouterArc(2, 3, 4);
	graphe.ajouterArc(3, 4, 9);
	graphe.ajouterArc(3, 2, 7);
	graphe.ajouterArc(4, 2, 2);
	graphe.ajouterArc(4, 1, 0);
	Graphe grapheFerme = graphe.fermetureGraphe();
	CHECK(grapheFerme.arcExiste(4, 4));
	CHECK(grapheFerme.arcExiste(1, 3));
	CHECK(grapheFerme.arcExiste(3, 3));
	CHECK(grapheFerme.arcExiste(4, 3));
	CHECK(grapheFerme.arcExiste(2, 2));
	CHECK(grapheFerme.arcExiste(2, 4));
	CHECK(grapheFerme.arcExiste(1, 1));
	CHECK(grapheFerme.arcExiste(2, 1));
	CHECK(grapheFerme.arcExiste(3, 1));


	Graphe graphe2;
	graphe2.ajouterSommet(1, "Nicolas", 12, 14);
	graphe2.ajouterSommet(2, "Nicolas2", 23, 44);
	graphe2.ajouterSommet(3, "Nicolas3", 4, 74);
	graphe2.ajouterArc(1, 2, 1);
	graphe2.ajouterArc(2, 3, 8);
	graphe2.ajouterArc(3, 2, 4);
	graphe2.fermetureGraphe();
	CHECK(grapheFerme.arcExiste(1, 3));
	CHECK(grapheFerme.arcExiste(3, 3));
	CHECK(grapheFerme.arcExiste(2, 2));
}
