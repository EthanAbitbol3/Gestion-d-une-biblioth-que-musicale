#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

/*Fonction qui alloue et initialise un espace pour une nouvelle bibliotheque*/
Biblio *nouvelle_biblio()
{
    Biblio *bibli = (Biblio *)malloc(sizeof(Biblio));
    if (bibli == NULL)
    {
        printf("Erreur d'allocation de la biblioteque ");
        return NULL;
    }
    bibli->L = NULL;
    bibli->nE = 0;
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
    cell->suiv = NULL;

    return cell;
}

/*Fonction qui affiche les differentes caracteristique d'un morceau : numero, titre, artiste */
void affiche_morceau(CellMorceau *cell)
{
    //Test si le morceau est NULL
    if (cell == NULL)
    {
        printf("Erreur le morceau est null");
        return;
    }

    if (cell->titre != NULL && cell->artiste != NULL)
    {
        printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
    }
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

    CellMorceau *temp; //On utilise un pointeur temporaire pour ne pas perdre la tete de liste
    //Parcourt la liste chaine
    while (bibli->L)
    {
        temp = bibli->L->suiv; // On retiens le suivant pour ne pas perdre le pointeur sur la liste
        free(bibli->L->titre);
        free(bibli->L->artiste);
        free(bibli->L);
        bibli->L = temp;
    }
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

    CellMorceau *temp = bibli->L;
    ; //On utilise un pointeur temporaire pour ne pas perdre la tete de liste
    //Parcourt la liste chaine
    while (temp)
    {
        affiche_morceau(temp);
        temp = temp->suiv;
    }
    printf("il y a %d morceaux \n", bibli->nE);
}

/*Fonction qui insert un morceau dans une liste de morceau de la biblioteque*/
void insere(Biblio *bibli, int num, char *titre, char *artiste)
{
    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        bibli = nouvelle_biblio();
    }
    CellMorceau *cell = (CellMorceau *)malloc(sizeof(CellMorceau));
    cell->suiv = bibli->L; // Ajout en tete de liste
    cell->num = num;
    cell->titre = strdup(titre);
    cell->artiste = strdup(artiste);
    bibli->L = cell;
    bibli->nE++; //Incremente nombre element
}

/*Fonction qui recherche un morceau par le numero dans une bibliotheque*/
void recherche_morceau_avec_numero(Biblio *bibli, int numero)
{

    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    CellMorceau *temp = bibli->L; //On utilise un pointeur temporaire pour ne pas perdre la tete de liste
    //Parcourt la liste chaine
    while (temp)
    {
        if (temp->num == numero) // Test meme numero
        {
            affiche_morceau(temp);
            return;
        }
        temp = temp->suiv;
    }
}

/*Fonction qui recherche un morceau par le titre dans une bibliotheque*/
void recherche_morceau_avec_titre(Biblio *bibli, char *titre)
{

    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }
    CellMorceau *temp = bibli->L; //On utilise un pointeur temporaire pour ne pas perdre la tete de liste
    //Parcourt la liste chaine
    while (temp)
    {
        if (strcmp(temp->titre, titre) == 0) // Test meme titre
        {
            affiche_morceau(temp);
            return;
        }
        temp = temp->suiv;
    }
}

/*Fonction qui recherche un morceau par le nom d artiste dans une bibliotheque*/
void recherche_morceau_avec_artiste(Biblio *bibli, char *artiste)
{
    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }

    CellMorceau *temp = bibli->L; //On utilise un pointeur temporaire pour ne pas perdre la tete de liste
    //Parcourt la liste chaine
    while (temp)
    {
        if (strcmp(temp->artiste, artiste) == 0) //Test meme artiste
        {
            affiche_morceau(temp);
        }
        temp = temp->suiv;
    }
}

/*Fonction qui supprime un morceau dans une biblioteque */
void supprime_morceau(Biblio *bibli, int numero, char *titre, char *artiste)
{
    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return;
    }
    //Test si la liste est NULL
    if (bibli->L == NULL)
    {
        printf("Erreur la liste de morceau est null");
        return;
    }
    CellMorceau *temp1 = NULL;
    CellMorceau *temp2 = NULL;
    if (strcmp((bibli->L)->titre, titre) == 0 && strcmp((bibli->L)->artiste, artiste) == 0 && bibli->L->num == numero)
    {                           //Tete de liste
        temp1 = bibli->L;       //pointe premier element
        temp2 = bibli->L->suiv; //pointe sur deuxieme element
        free(temp1->titre);
        free(temp1->artiste);
        free(temp1);
        bibli->nE += -1;  //Desincremente le nombre d element
        bibli->L = temp2; //On refais le chainage
        return;
    }
    CellMorceau *cell = bibli->L;
    temp2 = cell; //Pour ne pas perdre la tete de liste
    cell = cell->suiv;

    while (cell)
    {
        //Milieu et Fin de liste
        if (strcmp(cell->titre, titre) == 0 && strcmp(cell->artiste, artiste) == 0 && cell->num == numero)
        {
            temp1 = cell;             //On retiens element courant a supprimer
            temp2->suiv = cell->suiv; //On fait pointer vers l'element suivant
            cell = temp2->suiv;       //On refait chainage
            free(temp1->titre);       //On desaloue l'element
            free(temp1->artiste);
            free(temp1);
            bibli->nE += -1; //Desincremente le nombre d element
            return;
        }
        else
        {
            //On passe au suivant
            temp2 = cell;
            cell = temp2->suiv;
        }
    }
    printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, bibli->L->artiste);
    return;
}

/*Fonction qui recherche un morceau par le nom d artiste et le titre dans une bibliotheque*/
int recherche_morceau_avec_artiste_et_titre(Biblio *bibli, char *titre, char *artiste)
{
    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return 0;
    }

    int cmp = 0;
    CellMorceau *temp = bibli->L;
    //Parcourt la liste chaine
    while (temp)
    {
        //Test si meme artiste et meme titre
        if (strcmp(temp->artiste, artiste) == 0 && strcmp(temp->titre, titre) == 0)
        {
            cmp++;
            if (cmp == 2)
            {
                // Si le nombre retourner est 0 c’est qu'il existe deux morceaux avec le meme titre
                // Et le nom d'artiste a au moins 2 reprise
                return 0;
            }
        }
        temp = temp->suiv;
    }
    // Si le nombre retourner est 1 c’est que le morceau est unique
    return 1;
}

/*Fonction qui renvoie les morceaux unique d'une bibliotheque*/
Biblio *uniques(Biblio *bibli)
{

    //Test si la bibliotheque est NULL
    if (bibli == NULL)
    {
        printf("Erreur la bibliotheque est null");
        return 0;
    }
    Biblio *new_bibli = nouvelle_biblio();
    CellMorceau *temp = bibli->L;
    int compt = 1;
    int cmp;
    //Parcourt la liste chaine
    while (temp)
    {
        //Test si meme artiste et meme titre
        cmp = recherche_morceau_avec_artiste_et_titre(bibli, temp->titre, temp->artiste);
        if (cmp == 1)
        {
            insere(new_bibli, compt, temp->titre, temp->artiste);
            compt++;
        }

        temp = temp->suiv;
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