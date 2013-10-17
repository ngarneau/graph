/**
* \file Metro.h
* \brief Gestion d'un m�tro.
* \author �tudiants
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
	* \brief constructeur par d�faut
	* 
	* \post Un m�tro vide est instanci�.
	*
	*/
	Metro(){}	//Le constructeur ne fait rien vu que le type Metro est compos� d'un graphe. 
			//C'est le constructeur de ce dernier qui sera appel� �ventuellement.
	
	/**                       
	* \brief D�truit et lib�re tout la m�moire allou�e auparavant pour le M�tro.
	* 
	* \post Tout la m�moire allou�e auparavant pour le Metro est lib�r�e.
	* \post L'Objet Metro n'est plus valide.
	*/
	  ~Metro(){}; //Le destructeur ne fait rien, c'est celui du type Graphe qui sera appel� implicitement

	/**
	* \brief Constructeur de copie.
	* \pre Il y a assez de m�moire.
	* \exception bad_alloc S'il n'y a pas assez de m�moire.
	*/
	Metro(const Metro &source);
	
	/**
	* \brief Surcharge de l'op�rateur d'affectation.
	* \pre Il doit y avoir assez de m�moire.
	* \post Le Metro a un contenu identique � src.
	* \exception bad_alloc S'il n'y a pas assez de m�moire.
	*/
	const Metro& operator=(const Metro& src);


	/*************************************************************
	On vous fournit les deux m�thodes suivantes, voir Metro.cpp
	**************************************************************/
	/**                       
	* \brief Affiche une liste de stations de m�tro � l'�cran.
	* \param[in] v Une liste de stations dans un vector. 
	* \post Le contenu de la liste v est affich�.
	*/
	void afficherStations(const std::vector<std::string>&v);
	
	/**                       
	* \brief Constructeur � partir d'un fichier en entr�e.
	* Construit un Metro � partir d'une liste de stations ainsi que leurs liens re�us a partir d'un fichier en entr�e.
	* 
	* \param[in] fichierEntree, pointeur sur le fichier contenant la liste de stations � charger. 
	* \pre Il y a assez de m�moire pour charger toute les stations de la liste.
	* \pre Le fichier \a fichierEntree est ouvert corectement. 
	* \post Le fichier \a fichierEntree n'est pas ferm� par la fonction.
	* \post Si les pr�conditions sont respect�es, les donn�es du m�tro contenu 
	*       dans le fichier en entr�e sont organis�es dans un graphe en m�moire.
	* \exception bad_alloc si pas assez de m�moire contenir toute la liste du fichier.
	* \exception logic_error si le fichier \a fichierEntree n'est pas ouvert correctement. 
	*/
	Metro(std::ifstream &fichierEntree); 
	


	// ���������������������������������������������������������������������������������������������
	//	Chemin le plus court, chemin le plus long...
	// _____________________________________________________________________________________________

	/**
	* \brief	Trouve le plus court chemin entre deux points en utilisant l'algorithme de Dijsktra et le retourne
	* \pre		Il y a assez de m�moire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retourn�e, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchang�
	* \post		La liste des stations � parcourir est retourn�e
	* \exception	bad_alloc		Il n'y a pas assez de m�moire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> determinerMinParcours(const std::string & origine, const std::string & destination, int & nbSec);

	/**
	* \brief	Trouve le plus court chemin entre deux points en utilisant l'algorithme de Bellman-Ford et le retourne
	* \pre		Il y a assez de m�moire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retourn�e, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchang�
	* \post		La liste des stations � parcourir est retourn�e
	* \exception	bad_alloc		Il n'y a pas assez de m�moire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> bellmanFord(const std::string & origine, const std::string & destination, int & nbSec);

	/**
	* \brief	Trouve le plus court chemin entre deux points en utilisant l'algorithme de A Star (A*) et le retourne
	* \pre		Il y a assez de m�moire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retourn�e, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchang�
	* \post		La liste des stations � parcourir est retourn�e
	* \exception	bad_alloc		Il n'y a pas assez de m�moire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> algorithmeAStar(const std::string & origine, const std::string & destination, int & nbSec);

	/**
	* \brief	Trouve le plus long chemin entre deux points en utilisant l'algorithme de A Star (A*) et le retourne
	* \pre		Il y a assez de m�moire pour retourner les composantes du chemin
	* \post		Le temps pris pour parcourir la distance est retourn�e, -1 s'il n'y a pas de chemin
	* \post		Le graphe original reste inchang�
	* \post		La liste des stations � parcourir est retourn�e
	* \exception	bad_alloc		Il n'y a pas assez de m�moire pour retourner le chemin
	* \exception	logic_error		Le sommet d'origine ou de destination n'existe pas
	*/
	std::vector<std::string> cheminLePlusLongMetro(const std::string& origine, const std::string& destination, int &cout);


	// ���������������������������������������������������������������������������������������������
	//	Composantes connexes, point d'articulation
	// _____________________________________________________________________________________________

	/**
	* \brief	D�termine si toutes les stations du m�tro sont accessibles � partir de n'importe o�
	* \pre		Il y a assez de m�moire pour placer les composantes fortements connexes dans 'tab'
	* \post		Les composantes fortement connexes du graphe sont plac�es dans 'tab'
	* \exception	bad_alloc		Il n'y a pas assez de m�moire pour placer les composantes fortements connexes dans 'composantes'
	* \exception	logic_error		Le graphe contient aucun sommet
	*/
	bool estAccessibleMetro(std::vector< std::vector<std::string> > &tab);

	/**
	* \brief	Trouve les points d'articulation du m�tro et les retourne
	* \pre		Il y a assez de m�moire pour retourner les points d'articulation
	* \post		La liste de tous les sommets d'articulation sont retourn�s
	* \post		Le graphe original reste inchang�
	* \exception	bad_alloc		Il n'y a pas assez de m�moire pour retourner les noms des sommets
	* \exception	logic_error		Si le m�tro ne contient aucune station
	*/
	std::vector<std::string> fermerStationMetro();


	/**
	* \brief	Retourne le nombre de stations dans le metro
	* \post		Le nombre de sommet est retourn�
	* \post		Le graphe original reste inchang�
	*/
	int nbStations();

private:
	Graphe unGraphe; //Le type Metro est compos� d'un graphe

	// Vous pouvez d�finir des constantes ici.

	// D�claration �ventuelles de m�thodes priv�es. � vous de voir! 

	int relacher(const int & Ya, const int & Yb, int cout);
	int relacherLong(const int & Ya, const int & Yb, int cout);
	bool contient(const std::vector<int> &E, const int &sommet);
	};

#endif
