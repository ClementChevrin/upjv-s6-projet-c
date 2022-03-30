cd binaire && gcc -c ../source/common.c
gcc -c ../source/liste.c
gcc -c ../source/arbre.c
gcc -c ../source/affichage.c
gcc -c ../source/main.c
cd ../
gcc binaire/main.o binaire/common.o binaire/liste.o binaire/arbre.o binaire/affichage.o -o LeMotLePlusLong
