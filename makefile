progs:binaire/main.o binaire/arbre.o binaire/liste.o binaire/affichage.o
	gcc binaire/main.o binaire/arbre.o binaire/liste.o binaire/affichage.o -o progs
binaire/main.o:source/main.c header/arbre.h header/liste.h header/affichage.h
	cd binaire && gcc -c ../source/main.c
binaire/liste.o:source/liste.c header/liste.h
	cd binaire && gcc -c ../source/liste.c
binaire/affichage.o:source/affichage.c header/affichage.h
	cd binaire && gcc -c ../source/affichage.c
binaire/arbre.o:source/arbre.c header/arbre.h
	cd binaire && gcc -c ../source/arbre.c