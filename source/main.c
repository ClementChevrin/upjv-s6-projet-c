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
	Config c = newConfig("data/config.ini");
	if (c!=NULL)
	{
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
				Arbre arb = createArbre(c);
				char retour_3[500];
				strcpy(retour_3,"o");
				while(equals(retour_3,"o"))
				{
					strcpy(retour_3,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
					char* tirage = pullTirage(c);
					while(contient(arb,retour_3,0)!=1  /* Verifier que le mot est possible avec le tirage*/)
					{
						affichage_clear();
						printf("%s",title);
						affichage_WordList("Liste de mot possible",4,15,4,NULL);
						affichage_LetterList("Tirage",tirage);
						printf("\n\n\\>");
						scanf("%s",retour_3);
					}
					while(!equals(retour_3,"o") && !equals(retour_3,"n"))
					{
						affichage_clear();
						printf("%s",title);
						affichage_WordList("Liste de mot possible",4,15,4,NULL);
						affichage_LetterList("Tirage",tirage);
						printf("\nVoulez-vous rejouer? [o/n]\n\\>");
						scanf("%s",retour_3);
					}
					free(tirage);
				}
				arbre_Free(arb);
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
	}
	else fprintf(stderr, "Erreur : Fichier config.ini introuvable dans le repertoire data\n");
	system("pause");
	return 0;
}