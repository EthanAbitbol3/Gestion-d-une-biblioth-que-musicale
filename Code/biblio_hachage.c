/* biblio_hachage.h */

#include "biblio.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAILLE_TABLE 60000
#define A 0.6180339887498949

typedef struct CellMorceau
{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
} CellMorceau;

struct Biblio
{
    int nE;
    int m;
    CellMorceau **T;
};

Biblio *nouvelle_biblio(void)
{
    Biblio *bibli = (Biblio *)malloc(sizeof(Biblio));
    bibli->nE = 0;
    bibli->m = TAILLE_TABLE;
    bibli->T = malloc(sizeof(CellMorceau *) * TAILLE_TABLE);
    CellMorceau **tab = bibli->T;
    for (int i = 0; i < TAILLE_TABLE; i++)
        tab[i] = NULL;
    return bibli;
}

void libere_CellMorceau(CellMorceau *cell)
{
    if (cell == NULL)
        return;
    while (cell)
    {
        CellMorceau *tmp = cell;
        cell = cell->suiv;
        free(tmp->artiste);
        free(tmp->titre);
        free(tmp);
    }
}

void libere_biblio(Biblio *bibli)
{
    int k = 0; // Compte le nombire de cases parcourues dans le tableau
    int capacite = bibli->m;
    CellMorceau **tab = bibli->T;
    while (k < capacite)
    {
        if (tab[k] != NULL)
        {
            libere_CellMorceau(tab[k]);
        }
        k++;
    }
    free(bibli->T);
    free(bibli);
}

void affiche_morceau(CellMorceau *cell)
{
    printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
}

CellMorceau *nouveau_morceau(int num, char *titre, char *artiste)
{
    CellMorceau *cell = malloc(sizeof(CellMorceau));
    cell->num = num;
    cell->titre = strdup(titre);
    cell->artiste = strdup(artiste);
    cell->suiv = NULL;
    return cell;
}

unsigned int fonction_cle1(const char *artiste)
{
    int cpt = 0;

    for (int i = 0; artiste[i] != '\0'; i++)
    {
        cpt += artiste[i];
    }
    return cpt;
}

unsigned long fonction_cle2(const char *artiste)
{
    int cpt = 0;

    for (int i = 0; artiste[i] != '\0'; i++)
    {
        cpt += artiste[i] * (i + 1);
    }
    return cpt;
}

unsigned int fonction_hachage(unsigned long cle, int m)
{
    unsigned int temp = floor(cle * A);
    double resultat = floor(m * (cle * A - temp));
    return (int)resultat;
}

void affiche(Biblio *bibli)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if (bibli->T == NULL)
    {
        printf("La biblioteque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE = bibli->nE;
    int capacite = bibli->m;
    CellMorceau **tab = bibli->T;
    while (i < nE && k < capacite)
    {
        if (tab[k] != NULL)
        {
            affiche_morceau(tab[k]);
            i++;
        }

        k++;
    }
    printf("Nombre de morceaux : %d\n \n", bibli->nE);
}

void insere(Biblio *bibli, int num, char *titre, char *artiste)
{
    if (bibli == NULL)
    {
        printf("L'insertion a echoue la biblioteque pointe vers NULL\n");
        return;
    }
    //on trouve la clef pour chaque morceau et on insere dans le tableau de hachage
    unsigned int hash = fonction_hachage(fonction_cle2(artiste), bibli->m);
    //si le tableau est nul on cree le morceau et on l'insere dirctement
    if (bibli->T[hash] == NULL)
    {
        bibli->T[hash] = nouveau_morceau(num, titre, artiste);
        bibli->nE++;
        return;
    }
    //si le tableau n'est pas nul, on insere le nouveau morceau en tete d'une liste chainee qui gere les collisions
    else
    {
        CellMorceau *new = nouveau_morceau(num, titre, artiste);
        new->suiv = bibli->T[hash];
        bibli->T[hash] = new;
        bibli->nE++;
        return;
    }
}

CellMorceau *rechercheNumCellMorceau(CellMorceau *cell, int num)
{
    if (cell == NULL)
        return NULL;
    CellMorceau *temp = cell;
    while (temp)
    {
        if (temp->num == num)
        {
            printf("\nLe num %d correspond au titre suivant :\n", num);
            printf("%d\t%s\t%s\n", temp->num, temp->titre, temp->artiste);
            return temp;
        }
        temp = temp->suiv;
    }
    return NULL;
}

void recherche_morceau_avec_numero(Biblio *bibli, int numero)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if (bibli->T == NULL)
    {
        printf("Erreur le tableau de hachage n'est pas alloue\n");
        return;
    }
    CellMorceau **tab = bibli->T;
    int i = 0, k = 0;
    while (i < bibli->nE && k < bibli->m)
    {
        if (tab[k] != NULL)
        {
            CellMorceau *res = rechercheNumCellMorceau(tab[k], numero);
            if (res)
            {
                affiche_morceau(res);
            }
            i++;
        }
        k++;
    }
    return;
}

CellMorceau *rechercheTitreCellMorceau(CellMorceau *cell, const char *titre)
{
    if (cell == NULL)
        return NULL;
    CellMorceau *temp = cell;
    while (temp)
    {
        if (!strcmp(temp->titre, titre))
        {
            return temp;
        }
        temp = temp->suiv;
    }
    return NULL;
}
CellMorceau *rechercheartisteCellMorceau(CellMorceau *cell, const char *artiste)
{
    if (cell == NULL)
        return NULL;
    CellMorceau *temp = cell;
    while (temp)
    {
        if (!strcmp(temp->artiste, artiste))
        {
            return temp;
        }
        temp = temp->suiv;
    }
    return NULL;
}

void recherche_morceau_avec_titre(Biblio *bibli, char *titre)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if (bibli->T == NULL)
    {
        printf("Erreur d'allocation du tableau de hachage\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE = bibli->nE;
    int m = bibli->m;
    CellMorceau **tab = bibli->T;
    while (i < nE && k < m)
    {
        if (tab[k] != NULL)
        {
            CellMorceau *res = rechercheTitreCellMorceau(tab[k], titre);
            if (res)
            {
                affiche_morceau(res);
            }
            i++;
        }
        k++;
    }
    return;
}
Biblio *extraireMorceauxDe(Biblio *bibli, char *artiste)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    if (bibli->T == NULL)
    {
        printf("Erreur d'allocation du tableau de hachage\n");
        return NULL;
    }
    Biblio *new_bibli = nouvelle_biblio();

    int m = bibli->m;
    CellMorceau **tab = bibli->T;
    unsigned int hashKey = fonction_hachage(fonction_cle2(artiste), m);
    CellMorceau *liste = tab[hashKey];
    while (liste != NULL)
    {
        if (strcmp(artiste, liste->artiste) == 0)
        {
            insere(new_bibli, liste->num, liste->titre, liste->artiste);
        }
        liste = liste->suiv;
    }
    if (new_bibli == NULL)
        printf("Il n'y a pas de morceaux de %s dans cette biblioteque\n", artiste);
    return new_bibli;
}

void supprimerCellMorceau(CellMorceau **list, int num)
{
    CellMorceau *temp = *list;
    CellMorceau *prev;
    if (temp == NULL)
    {
        printf("Error");
        return;
    }

    if (num == temp->num)
    {
        (*list) = (*list)->suiv;
        free(temp->artiste);
        free(temp->titre);
        free(temp);
        return;
    }

    while (temp != NULL && temp->num != num)
    {
        prev = temp;
        temp = temp->suiv;
    }

    if (temp == NULL)
    {
        printf("Not Found");
        return;
    }
    prev->suiv = temp->suiv;
    free(temp->titre);
    free(temp->artiste);
    free(temp);
}

CellMorceau *rechercheParNum(Biblio *bibli, int num){
     if ( bibli == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return NULL;
    }
    if ( bibli->T == NULL){
        printf("Erreur le tableau de hachage n'est pas alloue\n");
        return NULL;
    }
    CellMorceau **tab=bibli->T;
    int i=0,k=0;
    while(i<bibli->nE && k<bibli->m){
        if(tab[k]!=NULL){
            CellMorceau *res=rechercheNumCellMorceau(tab[k],num);
            if(res){
                return res;
            }
            i++;
        }
        k++;
    }
    printf("Le morceau %d n'est pas dans cette biblioteque\n",num);
    return NULL;

}

void supprime_morceau(Biblio *bibli, int numero, char *titre, char *artiste)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if (bibli->T == NULL)
    {
        printf("La biblioteque est vide\n");
        return;
    }
    int m = bibli->m;
    CellMorceau *morceauNum = rechercheParNum(bibli, numero);
    artiste = morceauNum->artiste;
    unsigned int hashKey = fonction_hachage(fonction_cle2(artiste), m);
    CellMorceau *liste = bibli->T[hashKey];
    while (liste != NULL)
    {
        if (strcmp(artiste, liste->artiste) == 0 && strcmp(artiste, liste->artiste) == 0)
        {
            supprimerCellMorceau(&liste, numero);
            bibli->T[hashKey] = liste;
            (bibli->nE)--;
            return;
        }
        liste = liste->suiv;
    }
}

Biblio *uniques(Biblio *bibli)
{
    if (bibli == NULL)
    {
        printf("Erreur d'allocation de la bibliotheque");
        return NULL;
    }
    if (bibli->T == NULL)
    {
        printf("Erreur d'allocation du tableau de hachage");
        return NULL;
    }

    Biblio *new_bibli = nouvelle_biblio();
    int i = 0;
    int k = 0;
    int nE = bibli->nE;
    int m = bibli->m;
    CellMorceau **tab = bibli->T;
    while (i < nE && k < m)
    {
        if (tab[k] != NULL)
        {
            CellMorceau *courant = tab[k];
            CellMorceau *suivant = tab[k];
            insere(new_bibli, courant->num, courant->titre, courant->artiste);
            while (courant->suiv != NULL && courant != NULL)
            {
                suivant = courant->suiv;
                while ((suivant != NULL) && ((strcmp(courant->artiste, suivant->artiste) != 0) && (strcmp(courant->titre, suivant->titre) != 0)))
                {
                    suivant = suivant->suiv;
                }
                if (suivant == NULL)
                    insere(new_bibli, courant->num, courant->titre, courant->artiste);
                courant = courant->suiv;
            }
            i++;
        }
        k++;
    }
    return new_bibli;
}

void uniques_graphe(int borne_inf , int pas, int borne_sup, char*fichier){
    FILE *F= fopen(fichier,"w");
    Biblio *B, *Bunique;
    clock_t temps_initial ; // Temps initial en micro-secondes 
    clock_t temps_final ;
    for (int i = borne_inf; i<=borne_sup; i= i +pas){
        printf("%d\n",i);
        B = charge_n_entrees("BiblioMusicale.txt", i);
        temps_initial = clock () ; 
        Bunique= uniques(B);
        temps_final = clock () ;
        libere_biblio(Bunique);
        libere_biblio(B);
        fprintf(F, "%d %f\n",i, (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC);
    }
    fclose(F);
}

void recherche_morceau_avec_artiste(Biblio *bibli, char *artiste)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    if (bibli->T == NULL)
    {
        printf("Erreur d'allocation du tableau de hachage\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE = bibli->nE;
    int m = bibli->m;
    CellMorceau **tab = bibli->T;
    while (i < nE && k < m)
    {
        if (tab[k] != NULL)
        {
            CellMorceau *res = rechercheartisteCellMorceau(tab[k], artiste);
            if (res)
            {
                affiche_morceau(res);
            }
            i++;
        }
        k++;
    }
    return ;
}

int recherche_morceau_avec_artiste_et_titre(Biblio *bibli, char *titre, char *artiste)
{
    if (bibli == NULL)
    {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return 0;
    }
    if (bibli->T == NULL)
    {
        printf("Erreur d'allocation du tableau de hachage\n");
        return 0;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE = bibli->nE;
    int m = bibli->m;
    int cmp=0;
    CellMorceau **tab = bibli->T;
    while (i < nE && k < m)
    {
        if (tab[k] != NULL)
        {
            CellMorceau *res = rechercheTitreCellMorceau(tab[k], titre);
            if (strcmp(res->artiste, artiste) == 0)
            {
                cmp++;
                if(cmp==2){
                    return 0;
                }
            }
            i++;
        }
        k++;
    }
    return 1;
}