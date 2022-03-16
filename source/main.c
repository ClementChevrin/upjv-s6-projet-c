#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "liste.h"
#include "arbre.h"
#include "affichage.h"

char* delChar(char* chaine,char c)
{
	int boolean=1,j=0;
	char* retour = (char*)malloc(sizeof(char)*strlen(chaine)-1);
	for (int i = 0; i < chaine[i]!='\0'; ++i)
	{
		if(boolean && chaine[i]==c)
		{
			boolean = 0;
		}
		else
		{
			retour[j]=retour[i];
			j++;
		}
	}
	retour[strlen(chaine)-1]='\0';
	return retour;
}


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Config c = (Config)malloc(sizeof(struct config));
	for (int i = 0; i < 26; ++i) c->occLettre[i]=0;
	c->total = 0;
	Arbre arb = createArbre("fr",c);
	for (int i = 0; i < 26; ++i)
	{
		printf("%c : %d\n",i+'a',c->occLettre[i] );
	}
	printf("total : %d\n",c->total );
	char* liste_lettre = (char*)malloc(sizeof(char)*10);
	for (int i = 0; i < 9; ++i)
	{
		liste_lettre[i] = pullLetter(c);
	}
	liste_lettre[9]='\0';
	system("pause");
	printf("%s\n", delChar("egeferfa",'f'));
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