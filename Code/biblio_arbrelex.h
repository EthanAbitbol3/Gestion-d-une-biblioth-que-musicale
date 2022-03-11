#ifndef _BIBLIO_ARBRE_LEX_H_
#define _BIBLIO_ARBRE_LEX_H_

#include "biblio.h"

struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};


typedef struct Noeud {
    struct Noeud *liste_car;
    struct Noeud *car_suiv;
    CellMorceau *liste_morceaux;
    char car;
} Noeud;


struct Biblio {
    int nE;
    Noeud *A;
};

// fonctions supplementaires pour arbre lex 
Noeud *nouveau_noeud(char caractere );
void libere_morceau(CellMorceau *cell);
void libere_noeud( Noeud *noeud);
void affiche_cell_morceau( CellMorceau *liste);
void affiche_noeud(const Noeud *noeud);
void insere_liste(CellMorceau **liste, int num , char *titre , char *artiste);
void insere_morceau(Noeud **noeud , int num , char *titre, char *artiste);
CellMorceau *supprimer_cell_morceau( Biblio *bibli, CellMorceau *liste , char *titre);
int recherche_cell_morceau_numero(CellMorceau *cell, int num);
int recherche_noeud_numero(Noeud *noeud, int num);
int recherche_cell_morceau_titre(CellMorceau *cell, char *titre);
int recherche_noeud_titre(Noeud *noeud, char *titre);
int recherche_doublons_sans(CellMorceau *cell, CellMorceau *morceau);
void uniques_cell_morceaux(CellMorceau *cell, Biblio *bibli);
void uniques_noeud(Noeud *noeud, Biblio *bibli);
#endif
