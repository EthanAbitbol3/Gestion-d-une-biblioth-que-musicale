/* biblio.h */

#ifndef biblio_h 
#define biblio_h 

typedef struct CellMorceau CellMorceau;
typedef struct Biblio  Biblio; 
typedef struct Noeud Noeud;

// fonction presente dans bliblio.c 
Biblio *charge_n_entrees(const char *nom_fichier , int n);

//Fonction commun
Biblio *nouvelle_biblio(void);
CellMorceau *nouveau_morceau(int num ,char *titre,char *artiste);
void affiche(Biblio *B);
void affiche_morceau(CellMorceau *cell);
void insere(Biblio *B, int num , char *titre , char *artiste);
void recherche_morceau(Biblio *B,int num, char *titre,char *artiste);
void recherche_morceau_avec_numero(Biblio *B, int numero);
void recherche_morceau_avec_titre(Biblio *B, char *titre);
void recherche_morceau_avec_artiste(Biblio *B, char *artiste);
int recherche_morceau_avec_artiste_et_titre(Biblio *B, char *titre,char *artiste);
void libere_biblio(Biblio *B);
void supprime_morceau(Biblio *B, int numero, char *titre, char *artiste ); 
Biblio *uniques (Biblio *B);
void uniques_graphe(int borne_inf , int pas, int borne_sup, char*fichier);
#endif/* biblio_h */