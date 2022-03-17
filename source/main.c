#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../header/liste.h"
#include "../header/arbre.h"
#include "../header/affichage.h"

char* delChar(char* chaine,char c)
{
	int contient = 0;
	for (int i = 0; i < strlen(chaine); ++i)
	{
		if (chaine[i] == c) contient = 1;
	}
	if (contient)
	{
		int j=0,i=0;
		char* retour = (char*)malloc(sizeof(char)*strlen(chaine)-1);
		while (chaine[i]!=c && chaine[i]!='\0')
		{
			retour[i] = chaine[i];
			i++;
		}
		j=i;
		i++;
		while (chaine[i]!='\0')
		{
			retour[j] = chaine[i];
			i++;
			j++;
		}
		retour[strlen(chaine)-1]='\0';
		return retour;
	}
	else return chaine;
}


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Config c = newConfig();
	Arbre arb = createArbre("fr",c);
	char* liste_lettre = (char*)malloc(sizeof(char)*10);
	for (int i = 0; i < 9; ++i) liste_lettre[i] = pullLetter(c);
	liste_lettre[9]='\0';
	printf("%s\n", delChar("egeferfa",'z'));
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