#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio_tabdyn.h"
#include <time.h>

/*Fonction qui alloue et initialise un espace pour une nouvelle bibliotheque*/
Biblio *nouvelle_biblio()
{
    Biblio *bibli = (Biblio *)malloc(sizeof(Biblio));
     if (bibli == NULL)
    {
        printf("Erreur d'allocation de la biblioteque ");
        return NULL;
    }
    bibli->T = NULL;
    bibli->nE = 0;
    bibli->capacite = 0;
    return bibli;
}

/*Fonction qui alloue et initialise un espace pour une nouveau morceau*/
CellMorceau *nouveau_morceau(int num, char *titre, char *artiste)
{

    CellMorceau *cell = (CellMorceau *)malloc(sizeof(CellMorceau));
     if (cell == NULL)
    {
        printf("Erreur d'allocation du morceau ");
        return NULL;
    }
    cell->num = num;
    cell->titre = strdup(titre);     // On duplique le titre
    cell->artiste = strdup(artiste); // On duplique l artiste
    return cell;
}

/*Fonction qui libere l'espace de la bibliotheque*/
void libere_biblio(Biblio *bibli)
{
    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    int i;
    //Parcourt l'ensemble du tableau et on libere le titre et l'artiste de chaque case
    for (i = 0; i < bibli->nE; i++)
    {
        //Test si le titre n'est pas NULL
        if (bibli->T[i].titre)
        {
            free(bibli->T[i].titre);
        }
        //Test si l'artiste n'est pas NULL
        if (bibli->T[i].artiste)
        {
            free(bibli->T[i].artiste);
        }
    }

    free(bibli->T);
    free(bibli);
}

/*Fonction qui affiche les differentes caracteristique d'une biblioteque : numero, titre, artiste */
void affiche(Biblio *bibli)
{
    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    int i;
    //Parcourt l'ensemble du tableau
    for (i = bibli->nE; i >= 0; i--)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {
            affiche_morceau(&bibli->T[i]);
        }
    }
    printf("il y a %d elements dans un tableau de capacite : %d \n", bibli->nE, bibli->capacite);
}

/*Fonction qui affiche les differentes caracteristique d'un morceau : numero, titre, artiste */
void affiche_morceau(CellMorceau *cell)
{
    //Test si le titre et l artiste ne sont pas NULL
    if (cell->titre != NULL && cell->artiste != NULL)
    {
        printf("*T* %8d * %-32.32s * %-32.32s *T*\n", cell->num, cell->titre, cell->artiste);
    }
}

//Fonction qui insert un morceau dans le tableau de morceau de la biblioteque
void insere(Biblio *bibli, int num, char *titre, char *artiste)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    //Test si le tableau est null est si oui on l'alloue
    if (bibli->T == NULL)
    {
        bibli->T = nouveau_morceau(num, titre, artiste);
        bibli->capacite = 1;
        bibli->nE = 1;
        return;
    }

    //Test si la capacite a ete atteinte on realloue alors le tableau
    if (bibli->capacite == bibli->nE)
    {
        bibli->capacite *= 2;
        bibli->T = realloc(bibli->T, bibli->capacite * sizeof(CellMorceau));
        //On parcourt le tableau a partir des cases reallouer et on initialise les differents elements
        for (int i = bibli->nE; i < bibli->capacite; i++)
        {
            bibli->T[i].artiste = NULL;
            bibli->T[i].titre = NULL;
            bibli->T[i].num = 0;
        }
        //On insert l'element dans le tableau une fois qu on est certain qu'il y a une place
        insere(bibli, num, titre, artiste);
        return;
    }

    int i;
    //Parcourt le tableau jusqu'a tomber une case vide et on insert alors le morceau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste == NULL && bibli->T[i].titre == NULL)
        {
            bibli->T[i] = *nouveau_morceau(num, titre, artiste);
            bibli->nE++; //Incremente le nombre de d'element courant
            return;
        }
    }
}

/* Pour l'ensemble des fonctions de recherche on se contentera de faire des affichages
   Afin d'une part d'optimiser la recherche
   D'autre part ainsi evite l'allocation et desallocation de different element 
*/

/* Fonction qui recherche un morceau dans la biblioteque en fonction du titre de l artiste et du numero */
void recherche_morceau(Biblio *bibli, int num, char *artiste, char *titre)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    int i;
    //Parcourt le tableau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {

            /*Fonction qui recherche un morceau par le nom d artiste et le titre dans une bibliotheque*/
            if (strcmp(bibli->T[i].artiste, artiste) == 0 && strcmp(bibli->T[i].titre, titre) == 0 && bibli->T[i].num == num)
            {
                affiche_morceau(&bibli->T[i]);
                return;
            }
        }
    }
}
/*Fonction qui recherche un morceau par le numero dans une bibliotheque*/
void recherche_morceau_avec_numero(Biblio *bibli, int numero)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    int i;
    //Parcourt le tableau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {
            if (bibli->T[i].num == numero) //Test si meme numero
            {
                affiche_morceau(&bibli->T[i]);
                return;
            }
        }
    }
}
/*Fonction qui recherche un morceau par le titre dans une bibliotheque*/
void recherche_morceau_avec_titre(Biblio *bibli, char *titre)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }
    int i;
    //Parcourt le tableau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {
            if (strcmp(bibli->T[i].titre, titre) == 0) //Test si meme titre avec strcmp car chaine caractere
            {
                affiche_morceau(&bibli->T[i]);
                return;
            }
        }
    }
}
/*Fonction qui recherche un morceau par le nom d artiste dans une bibliotheque*/
void recherche_morceau_avec_artiste(Biblio *bibli, char *artiste)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }
    int i;
    //Parcourt le tableau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {
            if (strcmp(bibli->T[i].artiste, artiste) == 0) //Test si meme artiste avec strcmp car chaine caractere
            {
                affiche_morceau(&bibli->T[i]);
            }
        }
    }
}

/*Fonction qui recherche un morceau par le nom d artiste et le titre dans une bibliotheque*/
int recherche_morceau_avec_artiste_et_titre(Biblio *bibli, char *titre, char *artiste)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return 0;
    }

    int cmp = 0;
    int i;
    //Parcourt le tableau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {
            //Test si meme titre et meme artiste
            if (strcmp(bibli->T[i].artiste, artiste) == 0 && strcmp(bibli->T[i].titre, titre) == 0)
            {
                cmp++;
                if (cmp == 2)
                {
                    // Si le nombre retourner est 0 c’est qu'il existe deux morceaux avec le meme titre
                    // Et le nom d'artiste a au moins 2 reprise
                    return 0;
                }
            }
        }
    }
    return 1; // Si le nombre retourner est 1 c’est que le morceau est unique
}
/*Fonction qui supprime un morceau dans une biblioteque */
void supprime_morceau(Biblio *bibli, int num, char *titre, char *artiste)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    int i;
    //Parcourt le tableau
    for (i = 0; i < bibli->capacite; i++)
    {
        //Test si le titre et l artiste ne sont pas NULL
        if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL)
        {
            //Test si meme titre et meme artiste avec strcmp car chaine caractere et test si meme numero
            if (strcmp(bibli->T[i].titre, titre) == 0 && strcmp(bibli->T[i].artiste, artiste) == 0 && bibli->T[i].num == num)
            {
                free(bibli->T[i].titre);
                free(bibli->T[i].artiste);
                bibli->T[i].artiste = NULL;
                bibli->T[i].titre = NULL;
                bibli->nE--; //On desincremente le nombre d'element courant
                return;
            }
        }
    }
}
/*Fonction qui renvoie les morceaux unique d'une bibliotheque*/
Biblio *uniques(Biblio *bibli)
{
    //Test si biblio est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return NULL;
    }
    Biblio *new_bibli = nouvelle_biblio();
    int i;
    int j;
    int ajoute;

    //Parcourt le tableau une premiere fois
    for (i = 0; i < bibli->nE; i++)
    {
        ajoute = 1;
        //Parcourt le tableau  une deuxieme fois
        // On a besoin de parcourir les tableaux 2 fois pour comparer chaque element avec le tableau
        for (j = 0; j < bibli->nE; j++)
        {
            //Test si le titre et l artiste ne sont pas NULL
            if (bibli->T[i].artiste != NULL && bibli->T[i].titre != NULL && bibli->T[j].artiste != NULL && bibli->T[j].titre != NULL)
            {
                //Test si meme titre et meme artiste avec strcmp car chaine caractere et test si meme numero
                //Test index different pour exclure dans le parcourt la comparaison du meme element
                if ((strcmp(bibli->T[i].artiste, bibli->T[j].artiste) == 0) && (strcmp(bibli->T[i].titre, bibli->T[j].titre) == 0) && i != j)
                {
                    // Si le nombre retourner est 0 c’est qu'il existe deux morceaux avec le meme titre
                    // Et le nom d'artiste a au moins 2 reprise donc on ne l'ajoutera pas
                    ajoute = 0;
                    break;
                }
            }
        }
        // Si le nombre retourner est 1 c’est que le morceau est unique donc on l'ajoute dans la biblioteque
        if (ajoute == 1)
        {
            insere(new_bibli, bibli->T[i].num, bibli->T[i].titre, bibli->T[i].artiste);
        }
    }
    //On retourne la biblioteque constituer uniquement des morceaux unique
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