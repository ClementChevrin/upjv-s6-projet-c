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
	int loop = 1;
	char* title;
	char* menu_1;
	char* menu_2;
	char* retour_1;
	// Interface de menu
	while(loop)
	{
		title = affichage_Title();
		menu_1 = affichage_Menu("MENU",3,"Lancer une partie","Parametre","Quitter");
		menu_2 = affichage_Menu("PARAMETRE",3,"Langue : fr","Nombre de lettre tire : 10","Quitter parametre");
		retour_1 = affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_1,"1","2","3");
		if (equals(retour_1,"1"))
		{
			affichage_clear();
		}
		else if (equals(retour_1,"2"))
		{
			affichage_clear();
			char* retour_2 = affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_2,"1","2","3");
			if (equals(retour_2,"1"))
			{
				/* code */
			}
			else if (equals(retour_2,"2"))
			{
				/* code */
			}
			free(retour_2);
		}
		else loop=0;
		free(menu_1);
		free(menu_2);
		free(retour_1);
		affichage_clear();
	}
	return 0;
	// Interface de jeu

	/*Config c = newConfig();
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
	system("pause");*/

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