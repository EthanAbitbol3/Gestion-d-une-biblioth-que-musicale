/*main.c*/
#include "biblio.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void menu()
{

	printf(" Menu:\n");
	printf("0 − Sortie\n");
	printf("1 − Affichage\n");
	printf("2 − Recherche les morceaux uniques \n");
	printf("3 − Recherche les morceaux a l'aide du titre du morceau \n");
	printf("4 − Recherche le morceau a l'aide du numero \n");
	printf("5 − Recherche les morceaux d'un artiste \n");
	printf("6 − Ajoute un morceau dans la bibliotheque \n");
	printf("7 − Supprimer un morceaux \n");
	printf("8 - graphe \n");
	printf("Votre choix:\n");
}
int main(int argc, const char *argv[])
{

	if (argc != 3)
	{
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}

	const char *nomfic = argv[1];
	int nlignes = atoi(argv[2]);
	char titre[249];
	char artiste[249];
	int i;
	printf("Lecture :\n");
	Biblio *biblio = charge_n_entrees(nomfic, nlignes);
	int ch;
	do
	{
		menu();
		int lus = scanf("%d", &ch);
		if (lus == 0)
			ch = 0;
		float time;
		clock_t t1,t2;

		switch (ch)
		{
		case 1:
			t1=clock();
			printf("Affichage\n");
			affiche(biblio);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %08f ms \n",time);
			break;
		case 2:
		{
			t1=clock();
			Biblio *Bunique = uniques(biblio);
			affiche(Bunique);
			libere_biblio(Bunique);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %f ms \n", time);
			break;
		}
		case 3:
		{
			t1=clock();
			printf("Saisir le titre du morceau :\n");
			scanf(" %248[^\n]", titre);
			recherche_morceau_avec_titre(biblio, titre);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %f ms \n", time);
			break;
		}
		case 4:
		{
			t1=clock();
			printf("saisir le numero : \n");
			scanf("%d", &i);
			recherche_morceau_avec_numero(biblio, i);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %f ms \n", time);
			break;
		}
		case 5:
		{
			t1=clock();
			printf("Saisir le nom de l'artiste :\n");
			scanf(" %248[^\n]", artiste);
			recherche_morceau_avec_artiste(biblio, artiste);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %f ms \n", time);
			break;
		}
		case 6:
		{
			t1=clock();
			printf("saisir le numero : \n");
			scanf("%d", &i);
			printf("Saisir le titre du morceau :\n");
			scanf(" %248[^\n]", titre);
			printf("Saisir le nom de l'artiste :\n");
			scanf(" %248[^\n]", artiste);
			insere(biblio, i, titre, artiste);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %f ms \n", time);
			break;
		}
		case 7:
		{
			t1=clock();
			printf("quel morceau souhaitez-vous supprimer ? \n");
			printf("saisir le numero : \n");
			scanf("%d", &i);
			printf("Saisir le titre du morceau :\n");
			scanf(" %248[^\n]", titre);
			printf("Saisir le nom de l'artiste :\n");
			scanf(" %248[^\n]", artiste);
			supprime_morceau(biblio, i, titre, artiste);
			t2=clock();
			time = (float)(t2-t1)/CLOCKS_PER_SEC;
			printf("temps d'executions = %f ms \n", time);
			break;
		}
		case 8:
		{
			uniques_graphe(0,2000,300000,"unique_liste.txt");
			break;
		}
		default:
			ch = 0;
			break;
		}

	} while (ch != 0);

	libere_biblio(biblio);
	printf("Au revoir\n");

	return 0;
}
