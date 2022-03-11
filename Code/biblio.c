#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#include "parser.h"


Biblio *charge_n_entrees(const char *nomfichier, int n)
{
    Biblio *bibli = nouvelle_biblio();
    FILE *f = NULL;
    f = fopen(nomfichier, "r");
    int i = 0;
    if (f == NULL)
    {
        printf("Erreur ouverture de fichier %s \n", nomfichier);
        exit(1); 
    }
    int num;
    char *titre=NULL;
    char *artiste=NULL;
    int taille_buffer1,taille_buffer2;
    while ((i < n) && !end_of_file(f))
    {

        parse_int(f, &num);
        parse_char(f, '\t');
        parse_string(f, &titre, &taille_buffer1, '\t');
        parse_char(f, '\t');
        parse_string(f, &artiste, &taille_buffer2, '\n');
        parse_char(f, '\n');
        
        insere(bibli, num , titre , artiste);

        i++;
    }
    free(artiste);
    free(titre);
    fclose(f);
    return bibli;
}
