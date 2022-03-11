#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct CellMorceau
{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

/* Cellule de l'arbre lexicographique */
typedef struct Noeud
{
    struct Noeud *liste_car;     //Liste des choix possibles des caract`eres
    struct Noeud *car_suiv;      //caract`ere suivant dans la chaine
    CellMorceau *liste_morceaux; // liste des morceaux ayant le m^eme interpr`ete
    char car;
} Noeud;

struct Biblio
{
    int nE;   // nombre d''element contenus dans l'arbre
    Noeud *A; //arbre lexicograpj=hique
};

/*Fonction qui alloue et initialise un espace pour une nouvelle bibliotheque*/
Biblio *nouvelle_biblio()
{
    Biblio *bibli = (Biblio *)malloc(sizeof(Biblio));
    if (bibli == NULL)
    {
        printf("Erreur d'allocation de la biblioteque ");
        return NULL;
    }
    bibli->nE = 0;
    bibli->A = NULL;
    return bibli;
}

/*Fonction qui alloue et initialise un espace pour une nouveau noeud*/
Noeud *nouveau_noeud(char caractere)
{
    Noeud *noeud = (Noeud *)malloc(sizeof(Noeud));
    noeud->liste_car = NULL;
    noeud->car_suiv = NULL;
    noeud->liste_morceaux = NULL;
    noeud->car = caractere;
    return noeud;
}

/*Fonction qui alloue et initialise un espace pour une nouveau morceau*/
CellMorceau *nouveau_morceau(int num, char *titre, char *artiste)
{
    CellMorceau *cell = (CellMorceau *)malloc(sizeof(CellMorceau));
    if (cell == NULL)
    {
        printf("Erreur d'allocation de la CellMorceau\n");
        return NULL;
    }
    cell->num = num;
    cell->titre = strdup(titre);
    cell->artiste = strdup(artiste);
    cell->suiv = NULL;
    return cell;
}
/*Fonction qui libere l'espace d'une liste chaine*/
void libere_morceau(CellMorceau *cell)
{
    if (cell == NULL)
    {
        return;
    }
    CellMorceau *temp;
    //Parcourt la liste chaine
    while (cell)
    {
        temp = cell->suiv; // On retiens le suivant pour ne pas perdre le pointeur sur la liste
        free(cell->titre);
        free(cell->artiste);
        free(cell);
        cell = temp;
    }
}
/*Fonction qui libere d'un noeud*/
void libere_noeud(Noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }

    libere_morceau(noeud->liste_morceaux);
    libere_noeud(noeud->car_suiv);
    libere_noeud(noeud->liste_car);
    free(noeud);
}

/*Fonction qui libere l'espace de la bibliotheque*/
void libere_biblio(Biblio *bibli)
{
    if (bibli == NULL)
        return;
    libere_noeud(bibli->A);
    free(bibli);
}

/*Fonction qui affiche les differentes caracteristique d'un morceau : numero, titre, artiste */
void affiche_morceau(CellMorceau *cell)
{
    printf("\t$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

/*Fonction qui affiche la liste chaine de morceau ainsi que les caracteristique de chaque morceau */
void affiche_cell_morceau(CellMorceau *liste)
{
    printf("Musique(s) de  %s :\n", liste->artiste);
    CellMorceau *temp = liste;
    while (temp)
    {
        affiche_morceau(temp);
        temp = temp->suiv;
    }
}

/*Fonction qui affiche les differentes caracteristique d'un noeud*/
void affiche_noeud(const Noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    if (noeud->liste_morceaux != NULL)
    {
        //printf("Musique(s) de  %s :\n", noeud->liste_morceaux->artiste);
        CellMorceau *temp = noeud->liste_morceaux;
        while (temp)
        {
            affiche_morceau(temp);
            temp = temp->suiv;
        }
    }
    affiche_noeud(noeud->car_suiv);
    affiche_noeud(noeud->liste_car);
}

/*Fonction qui affiche les differentes caracteristique d'une biblioteque */
void affiche(Biblio *bibli)
{
    if (bibli == NULL)
    {
        printf("La Biblioteque n'est pas alloué\n");
        return;
    }
    if (bibli->A == NULL)
    {
        printf("La biblioteque est vide\n");
    }
    affiche_noeud(bibli->A);
    printf("Nombre de morceaux : %d\n", bibli->nE);
}

/* Fonction qui insert un morceau dans une liste chaine */
void insere_liste(CellMorceau **liste, int num, char *titre, char *artiste)
{
    CellMorceau *cell = nouveau_morceau(num, titre, artiste);
    if (*liste == NULL)
    {
        *liste = cell;
        return;
    }
    CellMorceau *temp = *liste;
    while (temp->suiv)
    {
        temp = temp->suiv;
    }
    temp->suiv = cell;
}

/* Fonction qui insert un morceau dans un noeud */
void insere_morceau(Noeud **noeud, int num, char *titre, char *artiste)
{
    if (*noeud == NULL)
    {
        printf("Erreur noeud null");
        return;
    }
    CellMorceau *temp = (*noeud)->liste_morceaux;
    if (temp == NULL)
    {
        insere_liste(&temp, num, titre, artiste);
        (*noeud)->liste_morceaux = temp;
        return;
    }
    while (temp->suiv)
    {
        temp = temp->suiv;
    }
    CellMorceau *new = nouveau_morceau(num, titre, artiste);
    temp->suiv = new;
}

/* Fonction qui insert un morceau dans une biblioteque */
void insere(Biblio *bibli, int num, char *titre, char *artiste)
{
    int i = 0;
    Noeud *temp, *cell, *temp2;
    bibli->nE++;
    if (bibli->A == NULL)
    { // si l'arbre est vide
        bibli->A = nouveau_noeud(artiste[0]);
        temp = NULL;
        cell = bibli->A;
        for (i = 1; i < strlen(artiste); i++)
        {
            temp = nouveau_noeud(artiste[i]);
            cell->car_suiv = temp;
            cell = temp;
        }
        insere_morceau(&cell, num, titre, artiste);
        return;
    }
    cell = bibli->A;
    int len_artiste = strlen(artiste);
    while (cell)
    {
        if (artiste[i] == cell->car)
        {
            i++;
            if (artiste[i] == '\0')
            {
                insere_morceau(&cell, num, titre, artiste);
                return;
            }
            if (cell->car_suiv != NULL)
            {
                cell = cell->car_suiv;
            }
            else
            {
                //rajouter les caractères qui manquent à car_suiv
                while (i < len_artiste)
                {
                    temp = nouveau_noeud(artiste[i]);
                    cell->car_suiv = temp;
                    cell = temp;
                    i++;
                }
                insere_morceau(&cell, num, titre, artiste);
                return;
            }
        }
        else
        {
            temp2 = cell;
            cell = cell->liste_car;
        }
    }
    //rajoutez les caracteres qui manquent à list_car
    cell = temp2;
    cell->liste_car = nouveau_noeud(artiste[i]);
    i++;
    cell = cell->liste_car;
    while (i < len_artiste)
    {
        temp = nouveau_noeud(artiste[i]);
        cell->car_suiv = temp;
        cell = temp;
        i++;
    }
    insere_morceau(&cell, num, titre, artiste);
}

/* Fonction qui supprime un morceau de la liste chaine */
CellMorceau *supprimer_cell_morceau(Biblio *bibli, CellMorceau *liste, char *titre)
{
    CellMorceau *temp1 = NULL;
    CellMorceau *temp2 = NULL;
    if (!strcmp((liste)->titre, titre))
    { //Si le premier element doit etre supprime
        temp1 = liste;
        temp2 = liste->suiv;
        free(temp1->titre);
        free(temp1->artiste);
        free(temp1);
        (bibli->nE)--;
        return temp2;
    }
    CellMorceau *cell = liste;
    temp2 = cell;
    cell = cell->suiv;

    while (cell)
    {
        if (!strcmp(cell->titre, titre))
        {
            temp1 = cell;
            temp2->suiv = cell->suiv;
            cell = temp2->suiv;
            free(temp1->titre);
            free(temp1->artiste);
            free(temp1);
            (bibli->nE)--;
            return liste;
        }
        else
        {
            temp2 = cell;
            cell = temp2->suiv;
        }
    }
    printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, liste->artiste);
    return liste;
}
/* Fonction qui supprime un morceau de la biblioteque */
void supprime_morceau(Biblio *bibli, int numero, char *titre, char *artiste)
{
    if (bibli->A == NULL)
    {
        return;
    }
    int i = 0;

    Noeud *cell = bibli->A;
    while (cell)
    {
        if (artiste[i] == cell->car)
        {
            i++;
            if (cell->car_suiv != NULL)
            {
                cell = cell->car_suiv;
            }
            else
            {
                break;
            }
        }
        else
        {
            cell = cell->liste_car;
        }
    }
    if (cell == NULL)
    {
        printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, artiste);
    }
    else
    {
        cell->liste_morceaux = supprimer_cell_morceau(bibli, cell->liste_morceaux, titre);
    }
    return;
}

/* Fonction qui recherche un morceaux dans liste chaine en fonction de son numero*/
int recherche_cell_morceau_numero(CellMorceau *cell, int num)
{
    if (cell == NULL)
    {
        return 0;
    }

    CellMorceau *temp = cell;
    while (temp)
    {
        if (temp->num == num)
        {
            printf("\nLe morceau de numero %d correspond au titre suivant :\n", num);
            affiche_morceau(temp);
            //Retourne 1 si le morceau est trouver
            return 1;
        }
        temp = temp->suiv;
    }
    //Retourne 0 si le morceau n'est pas trouver
    return 0;
}

/* Fonction qui recherche un morceaux dans un noeux en fonction de son numero*/
int recherche_noeud_numero(Noeud *noeud, int num)
{
    if (noeud == NULL)
    {
        return 0;
    }

    int test = 0;
    if (noeud->liste_morceaux != NULL)
    {
        test = recherche_cell_morceau_numero(noeud->liste_morceaux, num);
    }
    if (test)
    {
        return 1;
    }

    if (recherche_noeud_numero(noeud->car_suiv, num))
    {
        return 1;
    }

    if (recherche_noeud_numero(noeud->liste_car, num))
    {
        return 1;
    }

    return 0;
}

/* Fonction qui recherche un morceaux dans la biblioteque en fonction de son numero*/
void recherche_morceau_avec_numero(Biblio *bibli, int numero)
{
    if (bibli == NULL)
    {
        printf("La Biblioteque est vide \n");
        return;
    }
    if (!recherche_noeud_numero(bibli->A, numero))
    {
        printf("Le morceau de numero %d n'est pas dans cette biblioteque\n", numero);
    }
}

/* Fonction qui recherche un morceaux dans liste chaine en fonction de son titre*/
int recherche_cell_morceau_titre(CellMorceau *cell, char *titre)
{
    if (cell == NULL)
    {
        return 0;
    }

    CellMorceau *temp = cell;
    while (temp)
    {
        if (!strcmp(temp->titre, titre))
        {
            printf("\nLe morceau que vous recherchez est le suivant :\n");
            affiche_morceau(temp);
            return 1;
        }
        temp = temp->suiv;
    }
    return 0;
}

/* Fonction qui recherche un morceaux dans un noeux en fonction de son titre*/
int recherche_noeud_titre(Noeud *noeud, char *titre)
{
    if (noeud == NULL)
    {
        return 0;
    }
    int test = 0;
    if (noeud->liste_morceaux != NULL)
    {
        test = recherche_cell_morceau_titre(noeud->liste_morceaux, titre);
    }
    if (test)
    {
        return 1;
    }
    if (recherche_noeud_titre(noeud->car_suiv, titre))
    {
        return 1;
    }
    if (recherche_noeud_titre(noeud->liste_car, titre))
    {
        return 1;
    }
    return 0;
}

/* Fonction qui recherche un morceaux dans la biblioteque en fonction de son titre*/
void recherche_morceau_avec_titre(Biblio *bibli, char *titre)
{
    if (bibli == NULL)
    {
        printf("La Biblioteque est vide\n");
        return;
    }
    if (!recherche_noeud_titre(bibli->A, titre))
        printf("Il n'y a aucun morceau %s dans cette biblioteque \n", titre);
}
/* Fonction qui recherche un morceaux dans la biblioteque en fonction de l'artiste */
void recherche_morceau_avec_artiste(Biblio *bibli, char *artiste)
{
    Noeud *cell = bibli->A;
    int i = 0;
    while (cell != NULL)
    {
        if (artiste[i] == cell->car)
        {
            i++;
            if (artiste[i] == '\0')
            {
                affiche_cell_morceau(cell->liste_morceaux);
                return;
            }
            if (cell->car_suiv != NULL)
                cell = cell->car_suiv;
        }
        else
        {
            cell = cell->liste_car;
        }
    }
    printf("Il n'y a aucun morceau de %s dans cette biblioteque\n", artiste);
}

/* Fonction qui nous informe si le morceau donne en parametre est en double dans cell ou pas*/
int recherche_doublons_sans(CellMorceau *cell, CellMorceau *morceau)
{
    if (cell == NULL)
    {
        return 0;
    }
    char *titre = morceau->titre;
    char *artiste = morceau->artiste;
    CellMorceau *temp = cell;
    int test = 0;
    while (temp)
    {
        if (!strcmp(temp->titre, titre) && !strcmp(temp->artiste, artiste))
        {
            if (test)
            {
                return 0;
            }
            else
            {
                test = 1;
            }
        }
        temp = temp->suiv;
    }
    return 1;
}

/* Fonction qui insert dans la biblioteque les morceaux sans doublons */
void uniques_cell_morceaux(CellMorceau *cell, Biblio *bibli)
{
    CellMorceau *temp = cell;
    while (temp)
    {
        if (recherche_doublons_sans(cell, temp))
        {
            insere(bibli, temp->num, temp->titre, temp->artiste);
        }
        temp = temp->suiv;
    }
}

/* Fonction qui insert dans la biblioteque les morceaux sans doublons */
void uniques_noeud(Noeud *noeud, Biblio *bibli)
{
    if (noeud == NULL)
    {
        return;
    }
    if (noeud->liste_morceaux != NULL)
    {
        uniques_cell_morceaux(noeud->liste_morceaux, bibli);
    }
    uniques_noeud(noeud->car_suiv, bibli);
    uniques_noeud(noeud->liste_car, bibli);
}

/* Fonction qui insert dans la biblioteque les morceaux sans doublons */
// Cette fonctions sera decomposer en 2 partie : Sans doublons dans noeud puis dans cell 
Biblio *uniques(Biblio *bibli)
{
    if (bibli == NULL)
    {
        printf("La biblioteque est vide");
        return NULL;
    }
    Biblio *new_bibli = nouvelle_biblio();
    uniques_noeud(bibli->A, new_bibli);
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
