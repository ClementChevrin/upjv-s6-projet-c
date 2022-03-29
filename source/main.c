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
			char* nblttr = Common_IntToString(c->nb_lettre_tirage);
			char* nblt = (char*)malloc(sizeof(char)*(strlen("Nombre de lettre tire : ")+strlen(nblttr)));
			strcat(strcpy(nblt,"Nombre de lettre tire : "),nblttr);

			title = Affichage_Title();
			menu_1 = Affichage_Menu("MENU",3,"Lancer une partie","Parametre","Quitter");
			menu_2 = Affichage_Menu("PARAMETRE",3,langue,nblt,"Quitter parametre");
			retour_1 = Affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_1,"1","2","3");
			if (Common_Equals(retour_1,"1"))
			{
				Arbre arb = Arbre_CreateArbre(c);
				char retour_3[500];
				strcpy(retour_3,"o");
				while(Common_Equals(retour_3,"o"))
				{
					strcpy(retour_3,"");
					char* tirage = Arbre_PullTirage(c);
					while(Arbre_Contient(arb,retour_3,0)!=1 || Arbre_InTirage(tirage,retour_3)!=1)
					{
						Affichage_Clear();
						printf("%s",title);
						Affichage_WordList("Liste de mot les plus long",4,c->nb_lettre_tirage+2,4,NULL);
						Affichage_LetterList("Tirage",tirage);
						printf("\n\n\\>");
						scanf("%s",retour_3);
					}
					printf("patientez...\n");
					Liste lst = NULL;
					lst = Liste_Add(lst,"");
					Arbre_LongestsWord(arb,lst,tirage,NULL);
					Liste lstlong = NULL;
					lstlong = Liste_Longest(lst,Liste_SizeLongestWord(lst));
					while(!Common_Equals(retour_3,"o") && !Common_Equals(retour_3,"n"))
					{
						Affichage_Clear();
						printf("%s",title);
						Affichage_WordList("Liste de mot les plus long",4,c->nb_lettre_tirage+2,4,lstlong);
						Affichage_LetterList("Tirage",tirage);
						printf(" *Votre mot est correct*\nVoulez-vous rejouer? [o/n]\n\\>");
						scanf("%s",retour_3);
					}
					Liste_Free(lst);
					Liste_Free(lstlong);
					free(tirage);
				}
				Arbre_Free(arb);
			}
			else if (Common_Equals(retour_1,"2"))
			{
				Affichage_Clear();
				char* retour_2 = Affichage_InputConditionnelle("%s%s\n\n\\>%&%&%&",title,menu_2,"1","2","3");
				if (Common_Equals(retour_2,"1"))
				{
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
				free(retour_2);
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
	system("pause");
	return 0;
}