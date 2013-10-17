/**
* \file Metro.h
* \brief Gestion d'un métro.
* \author Étudiants
* \version 0.1
* \date avril 2013
*/

#include "Graphe.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
//vous pouvez inclure d'autres librairies de la STL si vous pensez les utiliser

//#pragma warning( disable : 4290 )  // pour Visual Studio

#ifndef _METRO__H
#define _METRO__H

		
class Metro{
public:
	
	/**                       
	* \brief constructeur par défaut
	* 
	* \post Un métro vide est instancié.
	*
	*/
	Metro(){}	//Le constructeur ne fait rien vu que le type Metro est composé d'un graphe. 
			//C'est le constructeur de ce dernier qui sera appelé éventuellement.
	
	/**                       
	* \brief Détruit et libère tout la mémoire allouée auparavant pour le Métro.
	* 
	* \post Tout la mémoire allouée auparavant pour le Metro est libérée.
	* \post L'Objet Metro n'est plus valide.
	*/
	  ~Metro(){}; //Le destructeur ne fait rien, c'est celui du type Graphe qui sera appelé implicitement

	/**
	* \brief Constructeur de copie.
	* \pre Il y a assez de mémoire.
	* \exception bad_alloc S'il n'y a pas assez de mémoire.
	*/
	Metro(const Metro &source);
	
	/**
	* \brief Surcharge de l'opérateur d'affectation.
	* \pre Il doit y avoir assez de mémoire.
	* \post Le Metro a un contenu identique à src.
	* \exception bad_alloc S'il n'y a pas assez de mémoire.
	*/
	const Metro& operator=(const Metro& src);


	/*************************************************************
	On vous fournit les deux méthodes suivantes, voir Metro.cpp
	**************************************************************/
	/**                       
	* \brief Affiche une liste de stations de métro à l'écran.
	* \param[in] v Une liste de stations dans un vector. 
	* \post Le contenu de la liste v est affiché.
	*/
	void afficherStations(const std::vector<std::string>&v);
	
	/**                       
	* \brief Constructeur à partir d'un fichier en entrée.
	* Construit un Metro à partir d'une liste de stations ainsi que leurs liens reçus a partir d'un fichier en entrée.
	* 
	* \param[in] fichierEntree, pointeur sur le fichier contenant la liste de stations à charger. 
	* \pre Il y a assez de mémoire pour charger toute les stations de la liste.
	* \pre Le fichier \a fichierEntree est ouvert corectement. 
	* \post Le fichier \a fichierEntree n'est pas fermé par la fonction.
	* \post Si les préconditions sont respectées, les données du métro contenu 
	*       dans le fichier en entrée sont organisées dans un graphe en mémoire.
	* \exception bad_alloc si pas assez de mémoire contenir toute la liste du fichier.
	* \exception logic_error si le fichier \a fichierEntree n'est pas ouvert correctement. 
	*/
	Metro(std::ifstream &fichierEntree); 
	


	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Chemin le plus court, chemin le plus long...
	// _____________________________________________________________________________________________

	/**
	* \brief	Trouve le plus court chemin entre deux points en utilisant l'algorithme de Dijsktra et le retourne
	* \pre		Il y a assez de mémoire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retournée, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchangé
	* \post		La liste des stations à parcourir est retournée
	* \exception	bad_alloc		Il n'y a pas assez de mémoire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> determinerMinParcours(const std::string & origine, const std::string & destination, int & nbSec);

	/**
	* \brief	Trouve le plus court chemin entre deux points en utilisant l'algorithme de Bellman-Ford et le retourne
	* \pre		Il y a assez de mémoire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retournée, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchangé
	* \post		La liste des stations à parcourir est retournée
	* \exception	bad_alloc		Il n'y a pas assez de mémoire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> bellmanFord(const std::string & origine, const std::string & destination, int & nbSec);

	/**
	* \brief	Trouve le plus court chemin entre deux points en utilisant l'algorithme de A Star (A*) et le retourne
	* \pre		Il y a assez de mémoire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retournée, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchangé
	* \post		La liste des stations à parcourir est retournée
	* \exception	bad_alloc		Il n'y a pas assez de mémoire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> algorithmeAStar(const std::string & origine, const std::string & destination, int & nbSec);

	/**
	* \brief	Trouve le plus long chemin entre deux points en utilisant l'algorithme de A Star (A*) et le retourne
	* \pre		Il y a assez de mémoire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retournée, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchangé
	* \post		La liste des stations à parcourir est retournée
	* \exception	bad_alloc		Il n'y a pas assez de mémoire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> cheminLePlusLongMetro(const std::string& origine, const std::string& destination, int &cout);


	// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	//	Composantes connexes, point d'articulation
	// _____________________________________________________________________________________________

	/**
	* \brief	Détermine si toutes les stations du métro sont accessibles à partir de n'importe où
	* \pre		Il y a assez de mémoire pour placer les composantes fortements connexes dans 'tab'
	* \post		Les composantes fortement connexes du graphe sont placées dans 'tab'
	* \exception	bad_alloc		Il n'y a pas assez de mémoire pour placer les composantes fortements connexes dans 'composantes'
	* \exception	logic_error		Le graphe contient aucun sommet
	*/
	bool estAccessibleMetro(std::vector< std::vector<std::string> > &tab);

	/**
	* \brief	Trouve les points d'articulation du métro et les retourne
	* \pre		Il y a assez de mémoire pour retourner les points d'articulation
	* \post		La liste de tous les sommets d'articulation sont retournés
	* \post		Le graphe original reste inchangé
	* \exception	bad_alloc		Il n'y a pas assez de mémoire pour retourner les noms des sommets
	* \exception	logic_error		Si le métro ne contient aucune station
	*/
	std::vector<std::string> fermerStationMetro();


	/**
	* \brief	Retourne le nombre de stations dans le metro
	* \post		Le nombre de sommet est retournŽ
	* \post		Le graphe original reste inchangé
	*/
	int nbStations();

private:
	Graphe unGraphe; //Le type Metro est composé d'un graphe

	// Vous pouvez définir des constantes ici.

	// Déclaration éventuelles de méthodes privées. À vous de voir! 

	int relacher(const int & Ya, const int & Yb, int cout);
	int relacherLong(const int & Ya, const int & Yb, int cout);
	bool contient(const std::vector<int> &E, const int &sommet);
	};

#endif
