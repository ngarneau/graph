/**
* \file Graphe.h
* \brief Gestion d'un graphe
* \author Étudiants
* \version 0.1
* \date avril 2013
*
*  Travail pratique numéro 3
*/

#include <iostream>
#include <fstream>      // Pour les fichiers
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
//Vous pouvez ajouter d'autres librairies de la STL


//#pragma warning( disable : 4290 ) //pour Visual Studio

#ifndef _GRAPHE__H
#define _GRAPHE__H


class Graphe
{
public:

    /**
    * \brief      Constructeur par défaut
    * \post       Un graphe vide est créé
    */
    Graphe();

    /**
    * \brief      Destructeur
    * \post       Le graphe a été détruit
    */
    ~Graphe();

    /**
    * \brief Constructeur de copie.
    * \pre Il y a assez de mémoire.
    * \exception bad_alloc S'il n'y a pas assez de mémoire.
    */
    Graphe(const Graphe &source);

    /**
    * \brief Surcharge de l'opérateur d'affectation.
    * \pre Il doit y avoir assez de mémoire.
    * \post Le graphe a un contenu identique à src.
    * \exception bad_alloc S'il n'y a pas assez de mémoire.
    */
    const Graphe& operator=(const Graphe& src);

    /**
    * \brief      Ajout d'un sommet au graphe
    * \pre        Il doit y avoir assez de mémoire.
    * \pre        Le sommet ne doit pas déjà exister
    * \post       Un sommet content les informations passées en argument a été ajouté au Graphe
    * \exception  bad_alloc      Pas assez de mémoire pour alloué le nouveau sommet
    * \exception  logic_error    Le sommet existe déjà
    */
    void ajouterSommet(int numero, const std::string& nom, int x, int y);

    /**
    * \brief      Ajout d'un arc au graphe
    * \pre        Les deux sommets doivent exister
    * \post       Un arc a été ajouté entre le sommet 'numero1' et le sommet 'numero2'
    * \exception  bad_alloc      Pas assez de mémoire pour alloué le nouvel arc
    * \exception  logic_error    Un des deux sommets n'existe pas
    * \exception  logic_error    Il y a déjà un arc orienté entre ces deux sommets
    */
    void ajouterArc(int numero1, int numero2, int cout);

    /**
    * \brief      Enlève un sommet du graphe ainsi que tous les arcs qui vont et partent de ce sommet
    * \pre        Le sommet doit exister
    * \post       Le sommet identifié par 'numero' a été enlevé du graphe
    * \exception  logic_error    Le sommet spécifié en argument n'existe pas
    */
    void enleverSommet(int numero);

    /**
    * \brief      Enlève tous les sommet du graphe ainsi que tous les arcs qui vont et partent d'un sommet
    *         portant un tel nom (si un tel sommet existe; sinon rien n'est fait).
    * \pre
    * \post       Le(s) sommet(s) identifié(s) par 'nom' a été enlevé du graphe
    * \exception  logic_error    Il n'y a pas de sommets dans le graphe
    */
    void enleverSommets(const std::string& nom);

    /**
    * \brief      Enlève un arc du graphe
    * \pre        Les deux sommets identifiés apr leur numéro doivent appartenir au graphe.
    * \pre        Un arc reliant les deux stations doit exister.
    * \post       Le graphe contient un arc en moins, le graphe inchangé sinon
    * \exception  logic_error    Un des deux sommets, ou les deux, n'existent pas
    * \exception  logic_error    Il n'y a pas d'arc entre les 2 sommets
    */
    void enleverArc(int numero1, int numero2);

    /**
    * \brief     Retourne la liste des numéros des sommets dans un vecteur d'entiers
    * \post      Le graphe reste inchangé.
    */
    std::vector<int> listerSommets() const;

    /**
    * \brief     Retourne la liste des noms des sommets dans un vecteur
    * \post      Le graphe reste inchangé.
    */
    std::vector<std::string> listerNomsSommets() const;


    /**
    * \brief      Retourne la liste des numéros des sommets adjacents au sommet passé en argument dans un vecteur d'entiers
    * \pre        Le sommet doit appartenir au graphe
    * \post       Le graphe reste inchangé.
    * \exception  logic_error si le sommet n'existe pas
    */
    std::vector<int> listerSommetsAdjacents(int numero) const;

    /**
    * \brief      Retourne le nombre de sommets dans la liste des sommets
    * \post        Le graphe reste inchangé.
    */
    int nombreSommets() const;

    /**
    * \brief      Indique si la liste des sommets est vide
    * \post       Le graphe reste inchangé.
    */
    bool estVide() const;

    /**
    * \brief      Retourne l'ordre de sortie d'un sommet
    * \pre        Le sommet doit exister
    * \exception  logic_error    Le sommet n'existe pas
    */
    int ordreSortieSommet(int numero);

    /**
    * \brief      Retourne l'ordre d'entrée d'un sommet
    * \pre        Le sommet doit exister
    * \post       Le graphe reste inchangé.
    * \exception  logic_error    Le sommet n'existe pas
    */
    int ordreEntreeSommet(int numero) const;

    /**
    * \brief      Retourne l'existence d'un sommet
    * \post       Le graphe reste inchangé.
    */
    bool sommetExiste(int numero) const;

    /**
    * \brief      Retourne l'existence d'un sommet
    * \post       Le graphe reste inchangé.
    */
    bool sommetExiste(std::string nom) const;

    /**
    * \brief      Retourne l'existence d'un arc
    * \pre        Les sommets doivent appartenir au graphe
    * \post      Le graphe reste inchangé.
    * \exception  logic_error    L'un ou l'autre, ou les 2 sommets ne font pas partie du graphe
    */
    bool arcExiste(int sommetUn, int sommetDeux) const;

    /**
    * \brief      Retourne le coût d'un arc passé en argument
    * \pre        L'arc doit exister
    * \post      Le graphe reste inchangé.
    * \exception  logic_error    Le sommet source et/ou destination n'existent pas
    * \exception  logic_error    L'arc n'existe pas
    */
    int getCoutArc(int sommetUn, int sommetDeux) const;

    /**
    * \brief      Retourne le numéro d'un sommet selon ses coordonnées
    * \pre        Le sommet doit faire partie du graphe
    * \post       Le graphe reste inchangé.
    * \exception  logic_error    Le sommet n'existe pas
    */
    int getNumeroSommet(int x, int y) const;

    /**
    * \brief      Retourne le nom du sommet dont le numéro est passé en argument
    * \pre        Le sommet doit exister
    * \post       Le graphe reste inchangé.
    * \exception  logic_error    Le sommet n'existe pas
    */
    std::string getNomSommet(int numero) const;

    /**
    * \brief      Retourne le numéro d'un sommet selon son nom
    * \pre        Le sommet doit exister
    * \post      Le graphe reste inchangé.
    * \exception  logic_error    Il n'y a pas de sommets dans le graphe
    * \exception  logic_error    Le sommet n'existe pas
    */
    int getNumeroSommet(const std::string& nom) const;

    /**
    * \brief      Retourne les coordonnées d'un sommet
    * \pre        Le sommet doit exister
    * \exception  logic_error    Il n'y a pas de sommets dans le graphe
    * \exception  logic_error    Le sommet n'existe pas
    */
    void getCoordonnesSommet(int numeroSommet, int& x, int& y) const;

    /**
    * \brief      Déterminer la fermeture transitive du graphe.
    * \pre        Le graphe est correctement initialisé.
    * \post       La fermeture transitive du graphe est retournée.
    * \post       Le graphe original reste inchangé.
    *
    * \exception   bad_alloc  si pas assez de mémoire
    */
    Graphe fermetureGraphe() const;

    /********************************************
    Méthode fournie dans le fichier Graphe.cpp
    *********************************************/
    /**
    * \brief Surcharge de l'opérateur de sortie.
    * Il vous incombe de choisir le format d'affichage le plus lisible sur l'écran
    *
    * \post Le nombre de sommets du graphe sera affiché
    * \post chaque sommet, son numéro et son nom, sera affiché
    * \post pour chaque sommet, tous ses liens, le numéro des voisins, seront affichés
    */
    friend std::ostream& operator<<(std::ostream& out, const Graphe& g);

    //Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité


private:
    class Sommet;       /**< Un sommet du graphe, on le déclare ici à cause de la classe Arc qui s'en sert*/

    struct Coordonnees  /**< Les coordonnées d'une station dans un plan */
    {
        int x;          /**< L'abcisse */
        int y;          /**< L'ordonnée */
    };

    class Arc           /**< Description d'un arc */
    {
    public:
        /**
        * \brief    Constructeur avec paramètres
        * \post     Un arc est créé avec les paramètres indiqués
        */
        Arc(Sommet * dest, int cout);

        /**
        * \brief    Destructeur
        * \post     Un arc est détruit
        */
        ~Arc();

        Sommet * dest;      /**< Un pointeur sur la station de destination */
        int cout;           /**< Le coût du trajet (durée en seconde) entre les deux stations reliées par l'arc */
        Arc *  suivDest;    /**< La prochaine station de destination */
    };

    class Sommet        /*Description d'un sommet*/
    {
    public:
        /**
        * \brief        Constructeur avec paramètres
        * \post     Le sommet est initialisé avec les paramètres indiqués
        */
        Sommet(int numero, const std::string & nom, int x, int y);

        /**
        * \brief        Constructeur de copie
        * \post     Une copie profonde du sommet a été effectuée à partir du sommet source
        */
        Sommet(Sommet * source);

        /**
        * \brief        Destructeur
        * \post     Le sommet est détruit
        */
        ~Sommet();

        /**
        * \brief    Detruit les arcs du sommet
        * \post     Les arcs du sommet sont d�truit
        */
        void deleteArcs();

        int numero;         /**< Le numéro d'une station */
        std::string nom;        /**< Le nom de la station */
        Coordonnees coord;      /**< Les coordonnées de la station */
        Arc * listeDest;        /**< La liste des arcs entre la station et les stations qui lui sont adjacentes */
        bool etat;              /**< Pour marquer une station */
        Sommet *precedent;      /**< La station précédente dans la liste des stations */
        Sommet *suivant;        /**< La prochaine station dans la liste */
    };

    int nbSommets;              /**< Le nombre de sommets dans le graphe */
    Sommet * listSommets;           /**< Liste des sommets du graphe */

    /* méthodes privées */
    /**
    * \brief      Méthode interne de support à la destruction d'un graphe
    * \post       Le graphe est détruit
    */
    void _detruireGraphe();

    /**
    * \brief      Méthode interne de support à la copie d'un graphe
    * \post       Une copie profonde du graphe source a été effectuée
    */
    void _copierGraphe(const Graphe &source);

    /**
    * \brief      Methode qui retourne un pointeur sur un sommet
    */
    Graphe::Sommet* _trouverSommet(int numero) const;

    /**
    * \brief      Methode qui retourne un pointeur sur un sommet
    */
    Graphe::Sommet* _trouverSommet(std::string nom) const;

    /**
    * \brief      Methode qui retourne un pointeur sur un sommet utile lors de modification de sommet
    */
};


#endif

