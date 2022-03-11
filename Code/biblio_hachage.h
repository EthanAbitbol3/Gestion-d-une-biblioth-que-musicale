/* biblio_hachage.h */

#ifndef _BIBLIO_HACHAGEH
#define _BIBLIO_HACHAGEH

#include "biblio.h"

typedef struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
} CellMorceau;


struct Biblio {
    int nE;
    int m;
    CellMorceau T;
};

// fonctions supplementaire pour le hachage 
void libere_CellMorceau(CellMorceau *c);
unsigned int fonction_cle1(const char *artiste);
unsigned long fonction_cle2(const char *artiste);
unsigned int fonction_hachage(unsigned long cle, int m);
CellMorceau *rechercheNumCellMorceau(CellMorceau *C, int num);
CellMorceau *rechercheTitreCellMorceau(CellMorceau *C, const char *titre);
Biblio extraireMorceauxDe(Biblio B, char *artiste);
void supprimerCellMorceau( CellMorceau list , int num);
CellMorceau *rechercheartisteCellMorceau(CellMorceau *C, const char *artiste);

#endif