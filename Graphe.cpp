/*!
 * \brief   Implementation d'un graphe oriente
 * \author  Nicolas garneau
 * \version 1.0
 * \date    avril 2013
 */

#include "Graphe.h"

using namespace std;

/**
* \brief Constructeur par defaut
* \fn Graphe::Graphe()
*/
Graphe::Graphe()
{
	nbSommets = 0;
	listSommets = 0;
}

/**
* \brief Destructeur
* \fn Graphe::~Graphe()
*/
Graphe::~Graphe()
{
	_detruireGraphe();
}

/**
* \brief Constructeur copie
* \fn Graphe::Graphe(const Graphe &source)
*/
Graphe::Graphe(const Graphe &source)
{
	this->nbSommets = 0;
	this->listSommets = 0;
	this->_copierGraphe(source);
}

/**
* \brief Surcharge de l'operateur =
* \fn const Graphe& operator=(const Graphe& src)
*/
const Graphe& Graphe::operator=(const Graphe& src)
{
	this->nbSommets = 0;
	this->listSommets = 0;
	this->_copierGraphe(src);
	return *this;
}


/**
* \brief Retourne le nombre de sommets present dans le graphe
* \fn int Graphe::nombreSommets() const
*
* \return	Int representant le nombre total de sommets dans le graphe
*/
int Graphe::nombreSommets() const
{
	return nbSommets;
}

/**
* \brief Verifie un graphe pour savoir s'il est vide ou non
* \fn bool Graphe::estVide() const
*
* \return	Bool representant l'etat du graphe, s'il est vide ou non
*/
bool Graphe::estVide() const
{
	bool estVide = true;
	if(listSommets != 0){
		estVide = false;
	}
	return estVide;
}

/**
* \brief Ajoute un nouveau sommet dans le graphe
* \fn void Graphe::ajouterSommet(int numero, const std::string& nom, int x, int y)
*
* \param[in] 	numero 	Le numero du sommet ajoutŽ
* \param[in] 	nom 	Le nom du sommet
* \param[in] 	x 		La position en X
* \param[in] 	y 		La position en Y
*/
void Graphe::ajouterSommet(int numero, const std::string& nom, int x, int y)
{
	if(sommetExiste(numero)){
		throw std::logic_error("Ajouter sommet: Le sommet existe deja");
	}

	Sommet *nouveau = new Sommet(numero, nom, x, y);

	// ajout quand la liste est vide
	if(nbSommets == 0){
		listSommets = nouveau;
		nbSommets++;
		return;
	}
	else{
		// autrement on ajoute ˆ la fin
		Sommet *sentinelle = listSommets;
		while(sentinelle->suivant != 0){
			sentinelle = sentinelle->suivant;
		}
		sentinelle->suivant = nouveau;
		nouveau->precedent = sentinelle;
		nbSommets++;
		return;
	}
}

/**
* \brief Enleve un sommet du graphe
* \fn void Graphe::enleverSommet(int numero)
*
* \param[in] 	numero 	Le numero du sommet retire
*/
void Graphe::enleverSommet(int numero)
{
	// graphe est vide
	if(nbSommets == 0){
		return;
	}

	// le sommet n'est pas dans le graphe
	if(!sommetExiste(numero)){
		throw std::logic_error("Enlever sommet: Le sommet existe pas");
	}
	else{
		Sommet *courant = listSommets;

		// s'il n'y a qu'un seul sommet
		if(nbSommets == 1){
			delete courant;
			listSommets = 0;
			nbSommets--;
			return;
		}
		else{

			// retrait des arcs pointant vers le sommet en question
			Sommet* sentinelle = this->listSommets;
			do{
				if(sentinelle->numero != numero){
					if( arcExiste(sentinelle->numero, numero) ){
						enleverArc(sentinelle->numero, numero);
					}
				}
				sentinelle = sentinelle->suivant;
			}while(sentinelle != 0);

			// retrait du sommet en question
			while(courant->numero != numero)
			{
				courant = courant->suivant;
			}

			if(courant->suivant == 0){
				// c'est le dernier
				courant->precedent->suivant = 0;
			}
			else if(courant->numero == listSommets->numero){
				// c'est le premier, on doit updater listSommets dans ce cas
				listSommets = courant->suivant;
				courant->suivant->precedent = 0;
			}
			else{
				// n'importe quel autre sommet dans la liste
				courant->precedent->suivant = courant->suivant;
				courant->suivant->precedent = courant->precedent;
			}
			courant->precedent = 0;
			courant->suivant = 0;
			delete courant;
			nbSommets--;
			return;
		}
	}
}

/**
* \brief Enleve un ou plusieurs sommets du graphe
* \fn void Graphe::enleverSommets(const std::string& nom)
*
* \param[in] 	numero 	Le numero du sommet retire
*/
void Graphe::enleverSommets(const std::string& nom)
{
	// graphe est vide
	if(nbSommets == 0){
		return;
	}

	// le sommet n'est pas dans le graphe
	if(!sommetExiste(nom)){
		throw std::logic_error("Enlever sommet: Le sommet existe pas");
	}
	else{
		Sommet *courant = listSommets;

		// s'il n'y a qu'un seul sommet
		if(nbSommets == 1){
			delete courant;
			listSommets = 0;
			nbSommets--;
			return;
		}
		else{

			// retrait des arcs pointant vers le sommet en question
			Sommet* sentinelle = this->listSommets;

			do{
				if(sentinelle->nom == nom){
					Sommet* sentinelleCible = this->listSommets;
					do{
						if( arcExiste(sentinelle->numero, sentinelleCible->numero) ){
							enleverArc(sentinelle->numero, sentinelleCible->numero);
						}
						sentinelleCible = sentinelleCible->suivant;
					}while(sentinelleCible->suivant != 0);
				}
				sentinelle = sentinelle->suivant;
			}while(sentinelle != 0);

			// retrait du sommet en question
			while(courant->nom != nom)
			{
				courant = courant->suivant;
			}

			if(courant->suivant == 0){
				// c'est le dernier
				courant->precedent->suivant = 0;
			}
			else if(courant->nom == listSommets->nom){
				// c'est le premier, on doit updater listSommets dans ce cas
				listSommets = courant->suivant;
				courant->suivant->precedent = 0;
			}
			else{
				// n'importe quel autre sommet dans la liste
				courant->precedent->suivant = courant->suivant;
				courant->suivant->precedent = courant->precedent;
			}
			courant->precedent = 0;
			courant->suivant = 0;
			delete courant;
			nbSommets--;
			return;
		}
	}
}

/**
* \brief Ajoute un nouvel arc dans le graphe
* \fn void Graphe::ajouterArc(int numero1, int numero2, int cout)
*
* \param[in] 	numero1 	Le numero du premier sommet
* \param[in] 	numero2 	Le numero du deuxieme sommet
*/
void Graphe::ajouterArc(int numero1, int numero2, int cout)
{
	if(!sommetExiste(numero1) || !sommetExiste(numero2))
	{
		throw std::logic_error("Ajouter arc: un des 2 sommets n'existe pas.");
	}

	Sommet* from = _trouverSommet(numero1);
	Sommet* dest = _trouverSommet(numero2);

	Arc *arc = new Arc(dest, cout);

	if(from->listeDest == 0){
		// liste d'arc vide
		from->listeDest = arc;
	}
	else{
		Arc *sentinelle = from->listeDest;
		while(sentinelle->suivDest != 0){
			sentinelle = sentinelle->suivDest;
		}
		sentinelle->suivDest = arc;
	}
}

/**
* \brief Enleve un arc dans le graphe
* \fn void Graphe::enleverArc(int numero1, int numero2)
*
* \param[in] 	numero1 	Le numero du premier sommet
* \param[in] 	numero2 	Le numero du deuxieme sommet
*/
void Graphe::enleverArc(int numero1, int numero2)
{
	if(!sommetExiste(numero1) || !sommetExiste(numero2))
	{
		throw std::logic_error("Enlever arc: un des 2 sommets n'existe pas.");
	}

	if(!arcExiste(numero1, numero2)){
		throw std::logic_error("Enlever arc: l'arc entre les 2 sommets n'existe pas.");
	}

	Sommet* recherche = listSommets;
	for(int cpt = nbSommets; cpt > 0; cpt--)
	{
		if(recherche->numero == numero1){
			break;
		}
		else{
			recherche = recherche->suivant;
		}
	}

	Arc* sentinelle = recherche->listeDest;
	if(sentinelle->dest->numero == numero2){
		// premier arc est la cible
		if(recherche->listeDest->suivDest != 0){
			// n'est pas le seul
			recherche->listeDest = recherche->listeDest->suivDest;
			delete sentinelle;
		}
		else{
			delete sentinelle;
			recherche->listeDest = 0;
		}
	}

}

/**
* \brief Verifie l'existence d'un arc dans un graphe entre 2 sommets
* \fn bool Graphe::arcExiste(int sommetUn, int sommetDeux) const
*
* \param[in] 	numero1 	Le numero du premier sommet
* \param[in] 	numero2 	Le numero du deuxieme sommet
*/
bool Graphe::arcExiste(int sommetUn, int sommetDeux) const
{
	bool existe  = false;
	if(!sommetExiste(sommetUn) || !sommetExiste(sommetUn))
	{
		throw std::logic_error("Arc existe: un des 2 sommets n'existe pas.");
	}
	else{
		Sommet* recherche = _trouverSommet(sommetUn);
		Arc* sentinelle = recherche->listeDest;
		if(sentinelle != 0){
			do{
				if(sentinelle->dest->numero == sommetDeux){
					existe = true;
				}
				sentinelle = sentinelle->suivDest;
			}while(sentinelle != 0);
		}
	}
	return existe;
}

/**
* \brief Cherche un sommet pour savoir s'il existe
* \fn bool Graphe::sommetExiste(int numero) const
*
* \param[in] 	numero 	Le numero du sommet recherche
*/
bool Graphe::sommetExiste(int numero) const
{
	bool existe = false;
	Sommet* sentinelle = listSommets;
	for(int cpt = nbSommets; cpt > 0; cpt--)
	{
		if(sentinelle->numero == numero){
			existe = true;
			break;
		}
		else{
			sentinelle = sentinelle->suivant;
		}
	}
	return existe;
}

/**
* \brief Cherche un sommet pour savoir s'il existe
* \fn bool Graphe::sommetExiste(std::string nom) const
*
* \param[in] 	numero 	Le numero du sommet recherche
*/
bool Graphe::sommetExiste(std::string nom) const
{
	bool existe = false;
	Sommet* sentinelle = listSommets;
	for(int cpt = nbSommets; cpt > 0; cpt--)
	{
		if(sentinelle->nom == nom){
			existe = true;
			break;
		}
		else{
			sentinelle = sentinelle->suivant;
		}
	}
	return existe;
}

/**
* \brief Retourne un vector de int contenant la liste des sommets
* \fn std::vector<int> Graphe::listerSommets() const
*
* \return 	vector
*/
std::vector<int> Graphe::listerSommets() const
{
	std::vector<int> vecteur;
	if(this->nbSommets > 0){
		Sommet* sentinelle = this->listSommets;
		for(int cpt = this->nbSommets; cpt > 0; cpt--)
		{
			vecteur.push_back(sentinelle->numero);
			sentinelle = sentinelle->suivant;
		}
	}
	return vecteur;
}

/**
* \brief Retourne un vector de string contenant la liste des sommets
* \fn std::vector<std::string> Graphe::listerNomsSommets() const
*
* \return 	vector
*/
std::vector<std::string> Graphe::listerNomsSommets() const
{
	std::vector<std::string> vecteur;
		if(this->nbSommets > 0){
			Sommet* sentinelle = this->listSommets;
			for(int cpt = this->nbSommets; cpt > 0; cpt--)
			{
				vecteur.push_back(sentinelle->nom);
				sentinelle = sentinelle->suivant;
			}
		}
		return vecteur;
}

/**
* \brief Retourne un vector de string contenant la liste des sommets adjacents
* \fn std::vector<int> Graphe::listerSommetsAdjacents(int numero) const
*
* \param[in] 	int 	numero 	Le numero du sommet recherche
* \return 	vector
*/
std::vector<int> Graphe::listerSommetsAdjacents(int numero) const
{
	if(!sommetExiste(numero))
	{
		throw std::logic_error("Sommets adjacents: le sommet n'existe pas.");
	}

	std::vector<int> vecteur;

	Sommet* recherche = _trouverSommet(numero);
	if(recherche->listeDest != 0){
		Arc *sentinelle = recherche->listeDest;
		do{
			vecteur.push_back(sentinelle->dest->numero);
			sentinelle = sentinelle->suivDest;
		}while(sentinelle != 0);
	}

	return vecteur;
}

/**
* \brief Retourne un int representant le nombre de d'arc sortant
* \fn int Graphe::ordreSortieSommet(int numero)
*
* \param[in] 	int 	numero 	Le numero du sommet recherche
* \return 	int
*/
int Graphe::ordreSortieSommet(int numero)
{
	if(!sommetExiste(numero))
	{
		throw std::logic_error("Ordre sortie: le sommet n'existe pas.");
	}

	int nbArcs = 0;

	Sommet* recherche = _trouverSommet(numero);
	if(recherche->listeDest != 0){
		Arc *sentinelle = recherche->listeDest;
		do{
			nbArcs++;
			sentinelle = sentinelle->suivDest;
		}while(sentinelle != 0);
	}


	return nbArcs;
}

/**
* \brief Retourne un int representant le nombre de d'arc entrant
* \fn int Graphe::ordreEntreeSommet(int numero) const
*
* \param[in] 	int 	numero 	Le numero du sommet recherche
* \return 	int
*/
int Graphe::ordreEntreeSommet(int numero) const
{
	if(!sommetExiste(numero))
	{
		throw std::logic_error("Ordre entree: le sommet n'existe pas.");
	}

	int nbArcs = 0;

	if(nbSommets == 1){
		return 0;
	}else{
		Sommet* sentinelle = this->listSommets;
		do{
			if(sentinelle->listeDest != 0){
				Arc *sentinelleArc = sentinelle->listeDest;
				do{
					if(sentinelleArc->dest->numero == numero){
						nbArcs++;
					}
					sentinelleArc = sentinelleArc->suivDest;
				}while(sentinelleArc != 0);
			}
			sentinelle = sentinelle->suivant;
		}while(sentinelle != 0);
	}

	return nbArcs;
}

/**
* \brief Trouve le cout de l'arc entre 2 sommet donne
* \fn int Graphe::getCoutArc(int sommetUn, int sommetDeux) const
*
* \param[in] 	int 	sommetUn 	Le numero du premier sommet
* \param[in] 	int 	sommetDeux 	Le numero du deuxieme sommet
* \return 	int representant le cout de l'arc en question
*/
int Graphe::getCoutArc(int sommetUn, int sommetDeux) const
{
	int cout = 0;

	if(!sommetExiste(sommetUn) || !sommetExiste(sommetDeux))
	{
		throw std::logic_error("Cout arc: un des deux sommets n'existe pas.");
	}

	if(!arcExiste(sommetUn, sommetDeux)){
		throw std::logic_error("Cout arc: l'arc n'existe pas.");
	}

	Sommet* recherche = _trouverSommet(sommetUn);
	Arc* sentinelle = recherche->listeDest;
	while(sentinelle->dest->numero != sommetDeux){
		sentinelle = sentinelle->suivDest;
	}

	if(sentinelle != 0){
		cout = sentinelle->cout;
	}

	return cout;
}

/**
* \brief Trouve le numero du sommet selon les coordonne x y
* \fn int Graphe::getNumeroSommet(int x, int y) const
*
* \param[in] 	int		x 	La coordonne en x
* \param[in] 	int		y 	La coordonne en y
* \return 	int representant le numero du sommet
*/
int Graphe::getNumeroSommet(int x, int y) const
{
	if(this->listSommets == 0){
		throw std::logic_error("Numero sommet: le sommet n'est pas dans le graphe.");
	}

	Sommet* sentinelle = this->listSommets;
	do{
		if(sentinelle->coord.x == x && sentinelle->coord.y == y){
			break;
		}
		sentinelle = sentinelle->suivant;
	}while(sentinelle != 0);

	if(sentinelle != 0){
		return sentinelle->numero;
	}
	else{
		throw std::logic_error("Numero sommet: le sommet n'est pas dans le graphe.");
	}
}

/**
* \brief Trouve le nom du sommet selon le numero
* \fn std::string Graphe::getNomSommet(int numero) const
*
* \param[in] 	int		numero 	Le numero du sommet de recherche
* \return 	std::string representant le nom du sommet
*/
std::string Graphe::getNomSommet(int numero) const
{
	if(!sommetExiste(numero))
	{
		throw std::logic_error("Nom sommet: le sommet n'existe pas.");
	}

	Sommet* recherche = _trouverSommet(numero);
	return recherche->nom;
}

/**
* \brief Trouve le numero du sommet selon le nom
* \fn int Graphe::getNumeroSommet(const std::string& nom) const
*
* \param[in] 	std::string		nom 	Le nom du sommet de recherche
* \return 	int representant le numero du sommet
*/
int Graphe::getNumeroSommet(const std::string& nom) const
{
	if(this->listSommets == 0)
	{
		throw std::logic_error("Numero sommet nom: il n'y a pas de sommets.");
	}

	if(!sommetExiste(nom))
	{
		throw std::logic_error("Numero sommet nom: le sommet n'existe pas.");
	}

	Sommet* recherche = _trouverSommet(nom);
	return recherche->numero;
}

/**
* \brief Assigne les coordonnŽe aux variables passer en parametre
* \fn void getCoordonnesSommet(int numeroSommet, int& x, int& y) const
*
* \param[in] 	numero 	Le numero du sommet recherchŽ
* \param[in] 	x 		variable avec laquelle on assignera la coord x
* \param[in] 	y 		variable avec laquelle on assignera la coord y
*/
void Graphe::getCoordonnesSommet(int numeroSommet, int& x, int& y) const
{
	if(this->listSommets == 0)
	{
		throw std::logic_error("Coord sommet: il n'y a pas de sommets.");
	}

	if(!sommetExiste(numeroSommet))
	{
		throw std::logic_error("Coord sommet: le sommet n'existe pas.");
	}

	Sommet* recherche = _trouverSommet(numeroSommet);
	x = recherche->coord.x;
	y = recherche->coord.y;
}

/**
* \brief Creer la fermeture transitive d'un graphe utilisant Floyd
* \fn Graphe Graphe::fermetureGraphe() const
*
* \return 	Graphe 	representant une copie du gaphe original incluant la fermeture transitive
*/
Graphe Graphe::fermetureGraphe() const
{
	Graphe grapheFerme(*this);
	// algo de floyd
	int k, i, j;
	Sommet* sentinelle1 = this->listSommets;
	for ( k= 0; k< nbSommets; k++)
	{
		Sommet* sentinelle2 = this->listSommets;
		for ( i= 0; i< nbSommets; i++){
			Sommet* sentinelle3 = this->listSommets;
			if(grapheFerme.arcExiste(sentinelle2->numero, sentinelle1->numero)){
				for ( j= 0; j< nbSommets; j++){

					if(!grapheFerme.arcExiste(sentinelle2->numero, sentinelle3->numero)){
						// cas o� je n'ai pas d'arc
						if(grapheFerme.arcExiste(sentinelle2->numero, sentinelle1->numero) && grapheFerme.arcExiste(sentinelle1->numero, sentinelle3->numero)){
							int coutArc = grapheFerme.getCoutArc(sentinelle2->numero, sentinelle1->numero) + grapheFerme.getCoutArc(sentinelle1->numero, sentinelle3->numero);
							grapheFerme.ajouterArc(sentinelle2->numero, sentinelle3->numero, coutArc);
						}
					}
					else{
						// cas o� j'ai un arc, donc on doit comparer
						if(grapheFerme.arcExiste(sentinelle2->numero, sentinelle1->numero) && grapheFerme.arcExiste(sentinelle1->numero, sentinelle3->numero)){
							int nouveauCoutArc = grapheFerme.getCoutArc(sentinelle2->numero, sentinelle1->numero) + grapheFerme.getCoutArc(sentinelle1->numero, sentinelle3->numero);
							if(nouveauCoutArc < grapheFerme.getCoutArc(sentinelle2->numero, sentinelle3->numero)){
								grapheFerme.enleverArc(sentinelle2->numero, sentinelle3->numero);
								grapheFerme.ajouterArc(sentinelle2->numero, sentinelle3->numero, nouveauCoutArc);
							}
						}
					}
					sentinelle3 = sentinelle3->suivant;
				}
			}
			sentinelle2 = sentinelle2->suivant;
		}
		sentinelle1 = sentinelle1->suivant;
	}

	return grapheFerme;
}

/**
* \brief Instancie un nouveau sommet
* \fn Graphe::Sommet::Sommet(int numero, const std::string & nom, int x, int y)
*
* \param[in] 	numero 	Le numero du sommet
* \param[in] 	nom 	Le nom du sommet
* \param[in] 	x 		La position en X
* \param[in] 	y 		La position en Y
*/
Graphe::Sommet::Sommet(int numero, const std::string & nom, int x, int y)
{
	this->numero = numero;
	this->nom = nom;
	this->coord.x = x;
	this->coord.y = y;

	// init empty members
	this->etat = false;
	this->listeDest = 0;
	this->precedent = 0;
	this->suivant = 0;
}

/**
* \brief Constructeur copie d'un sommet
* \fn Graphe::Sommet::Sommet(Sommet * source)
*
* \param[in] 	source 	Le sommet source
*/
Graphe::Sommet::Sommet(Sommet * source)
{
	this->numero = source->numero;
	this->nom = source->nom;
	this->coord.x = source->coord.x;
	this->coord.y = source->coord.y;

	// init empty members
	this->etat = source->etat;
	this->suivant = 0;
	this->precedent = 0;
	this->listeDest = 0;
}

/**
* \brief Destructeur de sommet
* \fn Graphe::Sommet::~Sommet()
*
*/
Graphe::Sommet::~Sommet()
{
	this->deleteArcs();
}

/**
* \brief Methode qui sert ˆ dŽtruire les arcs d'un sommet
* \fn void Graphe::Sommet::deleteArcs()
*
*/
void Graphe::Sommet::deleteArcs()
{
	if(this->listeDest != 0){
		Arc *sentinelle = this->listeDest;
		Arc *courante = this->listeDest;
		do{
			sentinelle = sentinelle->suivDest;
			delete courante;
			courante = sentinelle;
		}while(sentinelle != 0);

		this->listeDest = 0;
	}
}

/**
* \brief Instancie un nouvel arc
* \fn Graphe::Arc::Arc(Sommet * dest, int cout)
*
* \param[in] 	dest 	Un pointeur vers le sommet de destination
* \param[in] 	cout 	Le cout de l'arc
*/
Graphe::Arc::Arc(Sommet * dest, int cout)
{
	this->dest = dest;
	this->cout = cout;
	this->suivDest = 0;
}

/**
* \brief Destructeur de d'arc
* \fn Graphe::Arc::~Arc()
*
*/
Graphe::Arc::~Arc()
{
}

/**
* \brief Sert ˆ trouver un sommet et retourner un pointeur vers ce sommet
* \fn Graphe::Sommet* Graphe::_trouverSommet(int numero)
*
* \param[in] 	int 	nom 	Le numero du sommet de recherche
*/
Graphe::Sommet* Graphe::_trouverSommet(int numero) const
{
	Sommet* recherche = listSommets;
	for(int cpt = nbSommets; cpt > 0; cpt--)
	{
		if(recherche->numero == numero){
			break;
		}
		else{
			recherche = recherche->suivant;
		}
	}
	return recherche;
}

/**
* \brief Sert ˆ trouver un sommet avec son nom et retourner un pointeur vers ce sommet
* \fn Graphe::Sommet* Graphe::_trouverSommet(std::string nom) const
*
* \param[in] 	std::string		nom 	Le nom du sommet de recherche
*/
Graphe::Sommet* Graphe::_trouverSommet(std::string nom) const
{
	Sommet* recherche = listSommets;
	for(int cpt = nbSommets; cpt > 0; cpt--)
	{
		if(recherche->nom == nom){
			break;
		}
		else{
			recherche = recherche->suivant;
		}
	}
	return recherche;
}


/**
* \brief Sert ˆ detruire un graphe
* \fn void Graphe::_detruireGraphe()
*
*/
void Graphe::_detruireGraphe()
{
	if(this->nbSommets > 0){
		for(int cpt = this->nbSommets; cpt > 0; cpt--)
		{
			// liste de 1
			if(this->nbSommets == 1)
			{
				delete this->listSommets;
				this->listSommets = 0;
				this->nbSommets = 0;
				return;
			}
			else{
				this->listSommets = this->listSommets->suivant;
				delete this->listSommets->precedent;
				this->nbSommets--;
			}
		}
	}
}

/**
* \brief Sert ˆ copier un graphe en profondeur
* \fn void Graphe::_copierGraphe(const Graphe &source)
*
* \param[in] 	Graphe 	source 	un graphe source
*/
void Graphe::_copierGraphe(const Graphe &source)
{
	this->_detruireGraphe();
	if(source.nbSommets > 0){

		// creation de tous les sommets
		Sommet* sentinelle = source.listSommets;
		do{
			this->ajouterSommet(sentinelle->numero, sentinelle->nom, sentinelle->coord.x, sentinelle->coord.y);
			sentinelle = sentinelle->suivant;
		}while(sentinelle != 0);

		// ajout de chacun des arcs a chacun des sommets
		Sommet* sentinelleSommets = source.listSommets;
		do{
			Arc* sentinelleArc = sentinelleSommets->listeDest;
			if(sentinelleArc != 0){
				do{
					this->ajouterArc(sentinelleSommets->numero, sentinelleArc->dest->numero, sentinelleArc->cout);
					sentinelleArc = sentinelleArc->suivDest;
				}while(sentinelleArc != 0);
			}
			sentinelleSommets = sentinelleSommets->suivant;
		}while(sentinelleSommets != 0);

	}
}

/**
* \brief Surcharge de l'opÃ©rateur de sortie.
* \fn std::ostream& operator<<(std::ostream& out, const Graphe& g)
*
* \param[in]	out		Le flux de sortie.
* \param[in]	g		Le graphe Ã  afficher.
*
* \return	Le flux de sortie.
*/
ostream& operator<<( ostream& out, const Graphe& g)
{
	out << "Le graphe contient " << g.nbSommets << " sommet(s)" << std::endl;
	Graphe::Sommet* vertex = g.listSommets;
	while (vertex != NULL)
	{
		out << "Sommet no " << vertex->numero << ", nom : " << vertex->nom << std::endl;
		// Afficher les arcs.	
		Graphe::Arc* arc = vertex->listeDest;
		if(arc!=NULL)
		{
			out << "Ce sommet a des liens vers le(s) sommet(s) : ";
			while (arc->suivDest != NULL)
			{
				out << arc->dest->numero << ",";
				arc = arc->suivDest;
			}
			out << arc->dest->numero;
		}
		out << std::endl << std::endl;
		vertex = vertex->suivant;
	}
	return out;
}
