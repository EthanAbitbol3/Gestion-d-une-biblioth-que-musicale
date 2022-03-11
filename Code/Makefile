liste : biblio_liste.o parser.o biblio.o main.o
	gcc -o -g -Wall biblio_liste.o parser.o biblio.o main.o -o main 

tableau: biblio_tabdyn.o biblio.o parser.o main.o
	gcc -o -g -Wall  biblio_tabdyn.o biblio.o parser.o main.o -o main

arbre: biblio_arbrelex.o biblio.o parser.o main.o
	gcc -o -g -Wall biblio_arbrelex.o biblio.o parser.o main.o -o main 

hachage: biblio_hachage.o biblio.o parser.o main.o
	gcc -o -g -Wall biblio_hachage.o biblio.o parser.o main.o -o main -lm

biblio_hachage.o : biblio_hachage.c biblio.h
	gcc -c -g -Wall biblio_hachage.c

biblio_arbrelex.o: biblio_arbrelex.c biblio.h
	gcc -c -g -Wall biblio_arbrelex.c 
	
biblio_tabdyn.o: biblio_tabdyn.c biblio.h
	gcc -c -g -Wall biblio_tabdyn.c 

main.o: main.c biblio.h 
	gcc -c -g -Wall main.c 

biblio_liste.o: biblio_liste.c  biblio.h 
	gcc -c -g -Wall biblio_liste.c 

parser.o : parser.c parser.h
	gcc -c -g -Wall parser.c  
	
biblio.o: biblio.c biblio.h 
	gcc -c -g -Wall biblio.c
	
clean: 
	rm -fr *.0
	rm -fr main 
