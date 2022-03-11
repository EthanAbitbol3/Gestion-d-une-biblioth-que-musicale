/* biblio_liste.h */
#ifndef biblio_liste_h 
#define biblio_liste_h 

#include "biblio.h"

struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

struct Biblio
{
    CellMorceau *L; /* Liste chainee des morceaux */
    int nE;          /* Nombre de morceaux dans la liste */
};

#endif/* biblio_liste.h */