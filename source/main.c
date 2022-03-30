#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../header/liste.h"
#include "../header/affichage.h"
#include "../header/arbre.h"
#include "../header/common.h"

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Config c = Arbre_NewConfig("data/config.ini");
	if (c!=NULL)
	{
		int loop = 1,loop2 = 1;    // Pour boucler les while
		char* title;               // Contient le titre ecrie en ascii 
		char* menu_1;              // Contient le menu de selection
		char* menu_2;              // Contient le menu des parametres
		char* retour_1;            // stdin menu de selection
		char* retour_2;            // stdin menu de parametres
		char retour_3[500];        // stdin en jeu
		char* langue;              // Contient "Langue : #valeur"
		char* nblttr;              // Contient le nombre de lettre a tirer
		char* nblt ;               // Contient "Nombre de lettre tire : #nombre"
		char* ouinon;              // stdin recommencer ou quitter

		// Interface de menu
		while(loop)
		{
			// Recuperation des informations du config.ini
			langue = (char*)malloc(sizeof(char)*(strlen("Langue : ")+strlen(c->dictionnaire)));
			strcat(strcpy(langue,"Langue : "),c->dictionnaire);
			nblttr = Common_IntToString(c->nb_lettre_tirage);
			nblt = (char*)malloc(sizeof(char)*(strlen("Nombre de lettre tire : ")+strlen(nblttr)));
			strcat(strcpy(nblt,"Nombre de lettre tire : "),nblttr);

			// Affectation de toute les chaines
			title = Affichage_Title();
			menu_1 = Affichage_Menu("MENU",3,"Lancer une partie","Parametre","Quitter");
			menu_2 = Affichage_Menu("PARAMETRE",3,langue,nblt,"Quitter parametre");

			// Menu de selection
			retour_1 = Affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_1,"1","2","3");
			if (Common_Equals(retour_1,"1"))
			{
				Arbre arb = Arbre_CreateArbre(c);
				ouinon = (char*)malloc(sizeof(char)*500);
				strcpy(ouinon,"o");

				// Saisie d'un mot valide
				while(Common_Equals(ouinon,"o"))
				{
					strcpy(retour_3,"");

					Liste lstlong = NULL;
					char* tirage;
					int b=1;
					printf("patientez...\n");
					while(b)
					{
						tirage = Arbre_PullTirage(c);
						// Recuperation d'une liste de mot possible et garde les plus cours
						Liste lst = NULL;
						lst = Liste_Add(lst,"");
						Liste_Print(lst);
						Arbre_LongestsWord(arb,lst,tirage,NULL);
						if (Liste_Size(lst) > 1)
						{
							lstlong = Liste_Longest(lst,Liste_SizeLongestWord(lst));
							b=0;
						}
						Liste_Free(lst);
					}
					
					// Saisie d'un mot valide
					while(Arbre_Contient(arb,retour_3,0)!=1 || Arbre_InTirage(tirage,retour_3)!=1)
					{
						Affichage_Clear();
						printf("%s",title);
						Affichage_WordList("Liste de mot les plus long",4,c->nb_lettre_tirage+2,4,NULL);
						Affichage_LetterList("Tirage",tirage);
						printf("\n\n\\>");
						scanf("%s",retour_3);
					}

					// Affiche les mots les plus longs et propose de recommencer ou de quitter
					strcpy(ouinon,"");
					while(!Common_Equals(ouinon,"o") && !Common_Equals(ouinon,"n"))
					{
						Affichage_Clear();
						printf("%s",title);
						Affichage_WordList("Liste de mot les plus long",4,c->nb_lettre_tirage+2,4,lstlong);
						Affichage_LetterList("Tirage",tirage);
						printf(" * \"%s\" est un mot correct *\nVoulez-vous rejouer? [o/n]\n\\>",retour_3);
						scanf("%s",ouinon);
					}
					Liste_Free(lstlong);
					free(tirage);
				}
				free(ouinon);
				Arbre_Free(arb);
			}
			else if (Common_Equals(retour_1,"2"))
			{

				// Interface des parametres
				loop2=1;
				while(loop2)
				{
					// Selection d'un parametre
					Affichage_Clear();
					retour_2 = Affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_2,"1","2","3");
					if (Common_Equals(retour_2,"1"))
					{
						// Modification du dictionnaire
						char buffer[200];
						strcpy(buffer,"...");
						while(!Common_IsDictionnaire(buffer))
						{
							Affichage_Clear();
							printf("%s%s\nSaisissez une valeur sans \".txt\"\n\\>",title,Affichage_DictionnaireListe("data"));
							scanf("%s",buffer);
						}
						strcpy(c->dictionnaire,buffer);
						Common_NotifyIni("Langue",buffer);
					}
					else if (Common_Equals(retour_2,"2"))
					{
						// Modification du nombre de lettre tire
						int i = 0;
						while(i<2 || i>15)
						{
							Affichage_Clear();
							printf("%s\n\n\nSaisissez une valeur entre 2 et 15\n\\>",title);
							scanf("%d",&i);
						}
						c->nb_lettre_tirage = i;
						Common_NotifyIni("Tirage",Common_IntToString(i));
					}
					else loop2=0;
					free(retour_2);
				}
			}
			else loop=0;
			free(menu_1);
			free(menu_2);
			free(nblt);
			free(nblttr);
			free(retour_1);
			Affichage_Clear();
		}
	}
	else fprintf(stderr, "Erreur : Fichier config.ini introuvable dans le repertoire data\n");
	return 0;
}
