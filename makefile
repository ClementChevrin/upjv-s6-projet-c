LeMotLePlusLong:binaire/main.o binaire/common.o binaire/liste.o binaire/arbre.o binaire/affichage.o
	gcc binaire/main.o binaire/common.o binaire/liste.o binaire/arbre.o binaire/affichage.o -o LeMotLePlusLong
binaire/main.o:source/main.c header/arbre.h header/liste.h header/affichage.h
	cd binaire && gcc -c ../source/main.c
binaire/common.o:source/common.c header/common.h
	cd binaire && gcc -c ../source/common.c
binaire/liste.o:source/liste.c header/liste.h
	cd binaire && gcc -c ../source/liste.c
binaire/arbre.o:source/arbre.c header/arbre.h
	cd binaire && gcc -c ../source/arbre.c
binaire/affichage.o:source/affichage.c header/affichage.h
	cd binaire && gcc -c ../source/affichage.c