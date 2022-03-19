#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../header/liste.h"
#include "../header/arbre.h"
#include "../header/affichage.h"




int main(int argc, char const *argv[])
{
	srand(time(NULL));
	// Interface de menu
	affichage_Title();
	affichage_Menu("MENU",3,"Lancer une partie","Parametre","Quitter");
	char* retour = affichage_InputConditionnelle(3,"1","2","3");

	// Interface de jeu

	Config c = newConfig();
	Arbre arb = createArbre("fr",c);
	char* liste_lettre = pullTirage(c,10);
	
	
	system("pause");
	Liste lst = longestsWord(arb,liste_lettre);
	Liste lst2 = lst;
	while(lst2 != NULL)
	{
		printf("%s\n",lst2 -> item);
		lst2 = lst2 ->next;
	} 
	Liste_free(lst);
	system("pause");

	/*
	affichage_Title();
	affichage_Menu();
	int choix = 0;
	printf("\n\n\\>");
	scanf("%d",&choix);
	while(choix == 0)
	{
		affichage_clear();
		affichage_Title();
		affichage_Menu();
		printf("\n*saisi incorrect\n\\>");
		scanf("%d",&choix);
	}

	system("cls");
	affichage_Title();

	system("pause");*/
	return 0;
}