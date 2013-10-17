/**
* \file Metro.cpp
* \brief Impl√©mentattion de la classe Metro.
* \author √âtudiants
* \version 0.1
* \date avril 2013
*/

#include "Metro.h"
#include <limits>
#include <cmath>


/**
* \fn void Metro::afficherStations(std::vector<std::string>&v)
*
* \param[in] v un vector de string
* 
*/
void Metro::afficherStations(const std::vector<std::string>&v)
{
	if (v.size() == 0)
	{
		std::cout << "La liste est vide\n";
		return;
	}
	
	for (unsigned int i=v.size(); i>0; i--)
	{
		std::cout << v[i-1] << std::endl;
	}
}


/**
* \fn Metro:: Metro(std::ifstream &f)
*
* \param[in] f un flux sur un fichier d'entr√©e
* 
*/
Metro:: Metro(std::ifstream &f)
{
	if (f  == NULL) throw std::logic_error("Metro: fichier non ouvert\n");

	//Lecture Ligne Entete
	int nbStations, noStation, nbLiens;
	f >> nbStations >> nbLiens; 

	//Lecture du nom des stations
	std:: vector<std::string> l; //Pour le nom des stations
	l.resize(nbStations);
	char buff[255];
	for(int i =0; i< nbStations ; i++)
	{
		
		f >> noStation; 
		f.ignore();
		f.getline(buff, 100);
		std:: string s(buff);
		l[i] = s; 
	}

	//Lecture des coordonn√©es et placement des sommets dans le graphe en m√©moire
	int x, y;
	f.ignore(); 
	for(int i =0; i< nbStations ; i++)
	{
		f >>noStation >> x >> y;
		unGraphe.ajouterSommet(i, l[i], x, y);
	}

	//Lecture des arc et placement des arcs dans le graphe en m√©moire
	f.ignore();f.ignore();
	int s1, s2, cout;
	for (int i =0; i<nbLiens; i++)
	{
		f>> s1 >> s2 >> cout;
		unGraphe.ajouterArc(s1, s2, cout);
	}
}


/**
* \fn Metro::Metro(const Metro &source)
*
* \param[in] source reprsentant un metro
*
*/
Metro::Metro(const Metro &source)
{
	unGraphe = source.unGraphe;
}

/**
* \fn const Metro& Metro::operator=(const Metro& src)
*
* \param[in] src representant un Metro
* \return 	 Metro
*
*/
const Metro& Metro::operator=(const Metro& src)
{
	unGraphe = src.unGraphe;
	return *this;
}

/**
* \fn int Metro::nbStations()
*
* \brief nbStations() donne le nombre de stations dans le metro
* \param[in] Aucun
* \param[out] Aucun
*
* \return Un entier contenant le nombre de stations
*/
int Metro::nbStations()
{
	return unGraphe.nombreSommets();
}

/**
* \fn std::vector<std::string> Metro::determinerMinParcours(const std::string & origine, const std::string & destination, int & nbSec)
*
* \brief determinerMinParcours(const std::string & origine, const std::string & destination, int & nbSec) permet de trouver le parcours le plus court selon l'algorithme de Dijkstra
* \param[in] origine : Est le nom de la station d'origine du parcours
* \param[in] destination : Est le nom de la station de destination du parcours
* \param[out] nbSec : Est le nombre de secondre qu'il faudra pour exécuter le parcours
*
* \return Un vector de String representant le parcours le plus rapide entre les deux stations
*/
std::vector<std::string> Metro::determinerMinParcours(const std::string & origine, const std::string & destination, int & nbSec)
{
	try
	{
		std::vector<int> T;	//Sommets √† traiter
		std::vector<int> P;	//pr√©d√©cesseurs
		std::vector<int> S;	//pr√©d√©cesseurs
		std::vector<int> Y;			//Co√ªt entre 2 sommets
		std::vector<std::string> route; //Chemin le plus court entre la source et la destination
		int t_source, t_destination;				//Source et destination
		int J;					//Variable de navigation

		//On teste si la source et la destination existent
		if(!unGraphe.sommetExiste(unGraphe.getNumeroSommet(origine)) || !unGraphe.sommetExiste(unGraphe.getNumeroSommet(destination)))
			throw std::logic_error("Le sommet d'origine ou de destination n'existe pas.");

		//std::cout << P.size() << "\n";
		t_source = unGraphe.getNumeroSommet(origine);
		t_destination = unGraphe.getNumeroSommet(destination);

		//On inscrit tous les sommets dans un tableau
		T = unGraphe.listerSommets();

		//On initialise tous les co√ªts √† l'infini
		for(int i=0; i<unGraphe.nombreSommets(); i++)
		{
			Y.push_back(std::numeric_limits<int>::max());
			//P.push_back(-1);
		}

		P.reserve(unGraphe.nombreSommets());
		Y[t_source] = 0;

		while(!T.empty())
		{
			//1.S√©lectionner le sommet j de T de plus petite valeur yi
			int j = 0;
			J = T[0];

			for(unsigned int i=0; i<T.size(); i++)
				if(Y[J] > Y[T[i]])
				{
					J=T[i];
					j=i;
				}

			//2.Faire T = T \ j et S = S u j
			T.erase(T.begin()+j);
			S.push_back(J);

			//3.Pour tous les sommets k de T adjacents à j, faire RELÂCHER(j, k, c(j,k))
			std::vector<int> adjacents = unGraphe.listerSommetsAdjacents(J);

			for(unsigned int i = 0; i < adjacents.size(); i++)
				if(contient(T, adjacents[i]))
				{
					int cout;
					cout = relacher(Y[J], Y[adjacents[i]], unGraphe.getCoutArc(J,adjacents[i]));
					if(Y[adjacents[i]] != cout)
					{
						Y[adjacents[i]] = cout;
						P[adjacents[i]] = J;
					}
				}
		}

		if(Y[t_destination] != std::numeric_limits<int>::max())
		{
			//On trouve la premi√®re station de la destination
			while(unGraphe.getNomSommet(P[t_destination]) == unGraphe.getNomSommet(t_destination))
				t_destination = P[t_destination];

			int v = t_destination;		//Station √† visiter √† l'envers
			do
			{
				route.insert(route.begin(), unGraphe.getNomSommet(v));
				v = P[v];
			}while(v != t_source);
			route.insert(route.begin(), unGraphe.getNomSommet(v));

			nbSec = Y[t_destination] + ((route.size() - 1) * 20);
		}
		else
			nbSec = -1;

		return route;
	}
	catch(std::logic_error e)
	{
		throw std::logic_error(e.what());
	}
	catch(std::bad_alloc e)
	{
		throw std::logic_error("Dijsktra: Il n'y a plus de memoire necessaire pour la methode.");
	}
}

/**
* \fn std::vector<std::string> Metro::bellmanFord(const std::string & origine, const std::string & destination, int & nbSec)
*
* \brief Metro::bellmanFord(const std::string & origine, const std::string & destination, int & nbSec) permet de trouver le parcours le plus court selon l'algorithme de Bellman-Ford
* \param[in] origine : Est le nom de la station d'origine du parcours
* \param[in] destination : Est le nom de la station de destination du parcours
* \param[out] nbSec : Est le nombre de secondre qu'il faudra pour exécuter le parcours
*
* \return Un vector de String representant le parcours le plus rapide entre les deux stations
*/
std::vector<std::string> Metro::bellmanFord(const std::string & origine, const std::string & destination, int & nbSec)
{
	if(!unGraphe.sommetExiste(unGraphe.getNumeroSommet(origine)) || !unGraphe.sommetExiste(unGraphe.getNumeroSommet(destination)))
		throw std::logic_error("Le sommet d'origine ou de destination n'existe pas.");

	try
	{
		int S, T;
		int nbSommets = unGraphe.nombreSommets();
		std::vector<std::string> route;
		std::vector<int> Yi;
		std::vector<int> P;
		int k = 0;

		S = unGraphe.getNumeroSommet(origine);
		T = unGraphe.getNumeroSommet(destination);

		//On initialise tous les coÀöts ‚Ä° l'infini
		for(int i=0; i<nbSommets; i++){
			Yi.push_back(9999);
		}

		Yi[S] = 0; // initialise la source a 0
		P.reserve(nbSommets);

		do{
			for(int i = 0; i < nbSommets; i++){
				std::vector<int> adjacents = unGraphe.listerSommetsAdjacents(i); // sommets adjacents
				for(unsigned int ii = 0; ii < adjacents.size(); ii++)
				{
					int cout = relacher(Yi[i], Yi[adjacents[ii]], unGraphe.getCoutArc(i,adjacents[ii]));
					if(Yi[adjacents[ii]] != cout)
					{
						Yi[adjacents[ii]] = cout;
						P[adjacents[ii]] = i;
					}
				}
			}
			k++;
		}while(k < nbSommets -1);


		int j = T;
		int tempsSecondes = Yi[T];
		if(tempsSecondes != 9999){
			route.insert(route.begin(), unGraphe.getNomSommet(j));
			do
			{
				route.insert(route.begin(), unGraphe.getNomSommet(P[j]));
				j = P[j];
				tempsSecondes += 20;
			}while( j != S );
			nbSec = tempsSecondes;
		}
		else{
			nbSec = -1;
		}

		return route;
	}
	catch(std::logic_error e)
	{
		throw std::logic_error(e.what());
	}
	catch(std::bad_alloc e)
	{
		throw std::logic_error("Bellman-ford: Il n'y a plus de memoire necessaire pour la methode.");
	}
}

/**
* \fn std::vector<std::string> Metro::algorithmeAStar(const std::string & origine, const std::string & destination, int & nbSec)
*
* \brief Metro::algorithmeAStar(const std::string & origine, const std::string & destination, int & nbSec) permet de trouver le parcours le plus court selon l'algorithme de A*
* \param[in] origine : Est le nom de la station d'origine du parcours
* \param[in] destination : Est le nom de la station de destination du parcours
* \param[out] nbSec : Est le nombre de secondre qu'il faudra pour exécuter le parcours
*
* \return Un vector de String representant le parcours le plus rapide entre les deux stations
*/
std::vector<std::string> Metro::algorithmeAStar(const std::string & origine, const std::string & destination, int & nbSec)
{
	try
	{
		if(!unGraphe.sommetExiste(unGraphe.getNumeroSommet(origine)) || !unGraphe.sommetExiste(unGraphe.getNumeroSommet(destination)))
			throw std::logic_error("Le sommet d'origine ou de destination n'existe pas.");

		std::vector<std::string> route;	//Route optimale de la source vers la destination
		std::vector<int> E; 				//Sommets √† explorer
		std::vector<int> V; 				//Sommets visit√©s
		std::vector<int> P;					//Pr√©d√©cesseurs
		std::vector<int> G;					//Co√ªt depuis la source
		std::vector<int> H;					//Co√ªt vers destination
		int X;						//Variable de navigation
		int S, D;					//Source et destination
		int nb = unGraphe.nombreSommets();
		int coordSommetX, coordSommetY;		//Coordonn√©es du sommet initial
		int	coordAdjX, coordAdjY;			//Coordonn√©es du sommet adjacent

		//On initialise tous les co√ªts √† l'infini
		for(int i=0; i<nb; i++)
			G.push_back(std::numeric_limits<int>::max());


		P.reserve(unGraphe.nombreSommets());
		H.reserve(unGraphe.nombreSommets());

		S = unGraphe.getNumeroSommet(origine);
		D = unGraphe.getNumeroSommet(destination);

		unGraphe.getCoordonnesSommet(D, coordSommetX, coordSommetY);

		E.push_back(S);
		X = S;

		G[X] = 0;

		while(!E.empty() && !contient(E, D))
		{
			for(unsigned int i=0; i<E.size(); i++)
				if(!contient(V, E[i]))
				{
					X = E[i];
					break;
				}

			//+ R√©cup√©rer le sommet X de co√ªt total F minimum.
			for(unsigned int i=0; i<E.size(); i++)
			{
				if((G[X]+H[X]) > (G[E[i]]+H[E[i]]) && !contient(V, E[i]))
				{
					X = E[i];
				}
			}

			V.push_back(X);

			std::vector<int> adjacents = unGraphe.listerSommetsAdjacents(X);
			for(unsigned int i=0; i<adjacents.size(); i++)
				if(!contient(V, adjacents[i]))
				{
					if(!contient(E, adjacents[i]))
					{
						unGraphe.getCoordonnesSommet(E[i], coordAdjX, coordAdjY);

						E.push_back(adjacents[i]);

						G[adjacents[i]] = relacher(G[X], G[adjacents[i]], unGraphe.getCoutArc(X,adjacents[i]));
						P[adjacents[i]] = X;
						H[adjacents[i]] = sqrt(((coordSommetX - coordAdjX)*(coordSommetX - coordAdjX)) + ((coordSommetY - coordAdjY)*(coordSommetY - coordAdjY)));
					}
					else
					{
						E.push_back(adjacents[i]);

						int cout = relacher(G[X], G[adjacents[i]], unGraphe.getCoutArc(X,adjacents[i]));

						if(G[adjacents[i]] > cout)
						{
							G[adjacents[i]] = cout;
							P[adjacents[i]] = X;
						}
					}
				}
		}

		if(G[D] != std::numeric_limits<int>::max()){
			//On trouve la premi√®re station de la destination
			while(unGraphe.getNomSommet(P[D]) == unGraphe.getNomSommet(D))
				D = P[D];

			int v = D;		//Station a visiter a l'envers
			do
			{
				route.insert(route.begin(), unGraphe.getNomSommet(v));
				v = P[v];
			}while(v != S);
			route.insert(route.begin(), unGraphe.getNomSommet(v));

			nbSec = G[D] + ((route.size() - 1) * 20);
		}
		else{
			nbSec = -1;
		}

		return route;
	}
	catch(std::logic_error e)
	{
		throw std::logic_error(e.what());
	}
	catch(std::bad_alloc e)
	{
		throw std::logic_error("A*: Il n'y a plus de memoire necessaire pour la methode.");
	}

}

/**
* \fn std::vector<std::string> Metro::cheminLePlusLongMetro(const std::string& origine, const std::string& destination, int &cout)
*
* \brief Metro::cheminLePlusLongMetro(const std::string& origine, const std::string& destination, int &cout) permet de trouver le parcours le plus long selon l'algorithme de A*
* \param[in] origine : Est le nom de la station d'origine du parcours
* \param[in] destination : Est le nom de la station de destination du parcours
* \param[out] cout : Est le nombre de secondre qu'il faudra pour exécuter le parcours
*
* \return Un vector de String representant le parcours le plus long entre les deux stations
*/
std::vector<std::string> Metro::cheminLePlusLongMetro(const std::string& origine, const std::string& destination, int &cout)
{
	if(!unGraphe.sommetExiste(unGraphe.getNumeroSommet(origine)) || !unGraphe.sommetExiste(unGraphe.getNumeroSommet(destination)))
		throw std::logic_error("Le sommet d'origine ou de destination n'existe pas.");

	std::vector<std::string> route;	//Route optimale de la source vers la destination
	std::vector<int> E; 				//Sommets v† explorer
	std::vector<int> V; 				//Sommets visitv©s
	std::vector<int> P;					//Prv©dv©cesseurs
	std::vector<int> G;					//Covªt depuis la source
	std::vector<int> H;					//Covªt vers destination
	int X;						//Variable de navigation
	int S, D;					//Source et destination
	int nb = unGraphe.nombreSommets();
	int coordSommetX, coordSommetY;		//Coordonnv©es du sommet initial
	int	coordAdjX, coordAdjY;			//Coordonnv©es du sommet adjacent

	//On initialise tous les covªts v† l'infini
	for(int i=0; i<nb; i++)
		G.push_back(std::numeric_limits<int>::max());


	P.reserve(unGraphe.nombreSommets());
	H.reserve(unGraphe.nombreSommets());

	S = unGraphe.getNumeroSommet(origine);
	D = unGraphe.getNumeroSommet(destination);

	unGraphe.getCoordonnesSommet(D, coordSommetX, coordSommetY);

	E.push_back(S);
	X = S;

	G[X] = 0;

	while(!E.empty() && !contient(E, D))
	{
		for(unsigned int i=0; i<E.size(); i++)
			if(!contient(V, E[i]))
			{
				X = E[i];
				break;
			}

		//+ Rv©cupv©rer le sommet X de covªt total F minimum.
		for(unsigned int i=0; i<E.size(); i++)
			if((G[X]+H[X]) < (G[E[i]]+H[E[i]]) && !contient(V, E[i]))
				X = E[i];

		V.push_back(X);

		std::vector<int> adjacents = unGraphe.listerSommetsAdjacents(X);
		for(unsigned int i=0; i<adjacents.size(); i++)
			if(!contient(V, adjacents[i]))
			{
				if(!contient(E, adjacents[i]))
				{
					unGraphe.getCoordonnesSommet(adjacents[i], coordAdjX, coordAdjY);

					E.push_back(adjacents[i]);

					G[adjacents[i]] = relacher(G[X], G[adjacents[i]], unGraphe.getCoutArc(X,adjacents[i]));
					P[adjacents[i]] = X;
					H[adjacents[i]] = sqrt(((coordSommetX - coordAdjX)*(coordSommetX - coordAdjX)) + ((coordSommetY - coordAdjY)*(coordSommetY - coordAdjY)));
				}
				else
				{
					E.push_back(adjacents[i]);

					int cout = relacherLong(G[X], G[adjacents[i]], unGraphe.getCoutArc(X,adjacents[i]));

					if(G[adjacents[i]] < cout)
					{
						G[adjacents[i]] = cout;
						P[adjacents[i]] = X;
					}
				}
			}
	}

	//On trouve la premiv®re station de la destination
	while(unGraphe.getNomSommet(P[D]) == unGraphe.getNomSommet(D))
		D = P[D];

	int v = D;		//Station v† visiter v† l'envers
	do
	{
		route.insert(route.begin(), unGraphe.getNomSommet(v));
		v = P[v];
	}while(v != S);
	route.insert(route.begin(), unGraphe.getNomSommet(v));

	cout = G[D] + ((route.size() - 1) * 20);

	return route;
}

	/**
	* \brief	D√©termine si toutes les stations du m√©tro sont accessibles √† partir de n'importe o√π
	* \pre		Il y a assez de m√©moire pour placer les composantes fortements connexes dans 'tab'
	* \post		Les composantes fortement connexes du graphe sont plac√©es dans 'tab'
	* \exception	bad_alloc		Il n'y a pas assez de m√©moire pour placer les composantes fortements connexes dans 'composantes'
	* \exception	logic_error		Le graphe contient aucun sommet
	*/

/**
* \fn bool Metro::estAccessibleMetro(std::vector< std::vector<std::string> > &tab)
*
* \brief Metro::estAccessibleMetro(std::vector< std::vector<std::string> > &tab) Determine si toutes les stations du metro sont accessibles a partir de n'importe ou
* \param[in] Aucun
* \param[out] tab : Est un Vector de String à deux dimensions contenant toutes les stations accessibles
*
* \return Un booleen indiquant si le toutes les stations sont accessibles
*/
bool Metro::estAccessibleMetro(std::vector< std::vector<std::string> > &tab)
{
	if(unGraphe.estVide())
			throw std::logic_error("Metro: Il n'y a aucun sommet dans le graphe");

	bool estAccessible = true;

	Graphe grapheFerme = unGraphe.fermetureGraphe();
	int nbSommets = grapheFerme.nombreSommets();
	std::vector<int> T = grapheFerme.listerSommets();

	for(int i = 0; i < nbSommets; i++){
		std::vector<std::string> listeTmp;
		for(int y = 0; y < nbSommets; y++){
			if(!grapheFerme.arcExiste(T[i], T[y])){
				estAccessible = false;
			}
			else{
				listeTmp.push_back(grapheFerme.getNomSommet(T[i]));
			}
		}
		tab.push_back(listeTmp);
	}

	return estAccessible;
}

/**
* \fn std::vector<std::string> Metro::fermerStationMetro()
*
* \brief Metro::fermerStationMetro() Trouve les points d'articulation du metro et les retourne
* \param[in] Aucun
* \param[out] Aucun
*
* \return Un Vector de String contenant la liste des points d'articulations du metro
*/
std::vector<std::string> Metro::fermerStationMetro()
{
	std::vector<std::string> listeConnexe;

	if(unGraphe.estVide())
		throw std::logic_error("Metro: Il n'y a aucun sommet dans le graphe");


	int nbSommets = unGraphe.nombreSommets();
	std::vector<int> listeOfficiel = unGraphe.listerSommets();

	for(int k = 0; k < nbSommets; k++){

		// creation du graphe tmp et retrait d'un noeud
		Graphe grapheTmp = unGraphe;
		grapheTmp.enleverSommet(listeOfficiel[k]);


		Graphe grapheFerme = grapheTmp.fermetureGraphe();
		std::vector<int> listeTmp = grapheFerme.listerSommets();
		int nbSommetsTmp = grapheFerme.nombreSommets();

		bool composanteConnexe = false;
		for(int i = 0; i < nbSommetsTmp; i++){
			for(int y = 0; y < nbSommetsTmp; y++){
				if(!grapheFerme.arcExiste(listeTmp[i], listeTmp[y])){
					composanteConnexe = true;
					break;
				}
			}
		}

		if(composanteConnexe){
			listeConnexe.push_back(unGraphe.getNomSommet(listeOfficiel[k]));
		}
	}

	return listeConnexe;
}

/**
* \fn int Metro::relacher(const int & Ya, const int & Yb, int cout)
*
* \brief Metro::relacher(const int & Ya, const int & Yb, int cout) Fait le relachement des couts de deux sommets
* \param[in] Ya : Est le cout du sommet courant
* \param[in] Yb : Est le cout du sommet adjacent
* \param[in] cout : Est le cout de l'arc/arrete entre les deux sommets
* \param[out] Aucun
*
* \return Un entier contenant le cout du sommet adjacent
*/
int Metro::relacher(const int & Ya, const int & Yb, int cout)
{
	if(Yb > (Ya + cout))
		return (Ya + cout);
	else
		return Yb;
}

/**
* \fn int Metro::relacher(const int & Ya, const int & Yb, int cout)
*
* \brief Metro::relacher(const int & Ya, const int & Yb, int cout) Fait le relachement des couts de deux sommets
* \param[in] Ya : Est le cout du sommet courant
* \param[in] Yb : Est le cout du sommet adjacent
* \param[in] cout : Est le cout de l'arc/arrete entre les deux sommets
* \param[out] Aucun
*
* \return Un entier contenant le cout du sommet adjacent
*/
int Metro::relacherLong(const int & Ya, const int & Yb, int cout)
{
	if(Yb < (Ya + cout))
		return (Ya + cout);
	else
		return Yb;
}

/**
* \fn bool Metro::contient(const std::vector<int> & E, const int & sommet)
*
* \brief Metro::contient(const std::vector<int> & E, const int & sommet) Vérifie si le Vector contient un sommet donné
* \param[in] E : Est un Vector d'Entiers contenant une liste de sommet
* \param[in] sommet : Est le sommet dont on valide la présence dans la liste
* \param[out] Aucun
*
* \return Un booléen indiquant si la liste contient le sommet
*/
bool Metro::contient(const std::vector<int> & E, const int & sommet)
{
	for(unsigned int i = 0; i < E.size(); i++)
		if(E[i] == sommet)
			return true;

	return false;
}



/**
 * ====================
 * Comparaison des algorithmes
 * ====================
 * Comparaison faites pour un chemin de Bastille => Les Halles
 *
 * Bellman-ford
 * temps: 2.97 secondes
 * nombre de stations: 6
 *
 * A*
 * temps: 0.000922 secondes
 * nombre de stations: 6
 *
 * Dijkstra
 * temps: 0.007714 secondes
 * nombre de stations: 6
 *
 * On peut voir que Bellman-ford est plus lent du au fait qu'il va relâcher
 * les arcs du graphe plus d'une fois.
 * Le plus rapide est évidemment A* mais suivi de très près par Dijkstra.
 *
 */
