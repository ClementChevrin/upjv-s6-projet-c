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
			char* langue = (char*)malloc(sizeof(char)*(strlen("Langue : ")+strlen(c->dictionnaire)));
			strcat(strcpy(langue,"Langue : "),c->dictionnaire);
			char* nblttr = affichage_IntToString(c->nb_lettre_tirage);
			char* nblt = (char*)malloc(sizeof(char)*(strlen("Nombre de lettre tire : ")+strlen(nblttr)));
			strcat(strcpy(nblt,"Nombre de lettre tire : "),nblttr);

			title = affichage_Title();
			menu_1 = affichage_Menu("MENU",3,"Lancer une partie","Parametre","Quitter");
			menu_2 = affichage_Menu("PARAMETRE",3,langue,nblt,"Quitter parametre");
			retour_1 = affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_1,"1","2","3");
			if (equals(retour_1,"1"))
			{
				Arbre arb = createArbre(c);
				char retour_3[500];
				strcpy(retour_3,"o");
				while(equals(retour_3,"o"))
				{
					strcpy(retour_3,"");
					char* tirage = pullTirage(c);
					while(contient(arb,retour_3,0)!=1 || inTirage(tirage,retour_3)!=1)
					{
						affichage_clear();
						printf("%s",title);
						affichage_WordList("Liste de mot possible",4,15,4,NULL);
						affichage_LetterList("Tirage",tirage);
						printf("\n\n\\>");
						scanf("%s",retour_3);
					}
					Liste lst = NULL;
					lst = Liste_add(lst,"");
					longestsWord(arb,lst,tirage,NULL);
					while(!equals(retour_3,"o") && !equals(retour_3,"n"))
					{
						affichage_clear();
						printf("%s",title);
						affichage_WordList("Liste de mot possible",4,15,4,lst);
						affichage_LetterList("Tirage",tirage);
						Liste_print(lst);
						printf("Size : %d\n",Liste_sizelongestword(lst));
						printf("*Votre mot est correct*\nVoulez-vous rejouer? [o/n]\n\\>");
						scanf("%s",retour_3);
					}
					Liste_free(lst);
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
					char buffer[200];
					strcpy(buffer,"...");
					while(!isDictionnaire(buffer))
					{
						affichage_clear();
						printf("%s%s\nSaisissez une valeur sans \".txt\"\n\\>",title,affichage_DictionnaireListe("data"));
						scanf("%s",buffer);
					}
					strcpy(c->dictionnaire,buffer);
					notifyIni("Langue",buffer);
				}
				else if (equals(retour_2,"2"))
				{
					int i = 0;
					while(i<2 || i>50)
					{
						affichage_clear();
						printf("%s\n\n\nSaisissez une valeur entre 2 et 50\n\\>",title);
						scanf("%d",&i);
					}
					c->nb_lettre_tirage = i;
					notifyIni("Tirage",affichage_IntToString(i));
				}
				free(retour_2);
			}
			else loop=0;
			free(menu_1);
			free(menu_2);
			free(nblt);
			free(nblttr);
			free(retour_1);
			affichage_clear();
		}
	}
	else fprintf(stderr, "Erreur : Fichier config.ini introuvable dans le repertoire data\n");
	system("pause");
	return 0;
}