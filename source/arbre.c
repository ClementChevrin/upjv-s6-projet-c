#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../header/liste.h"

typedef struct Feuille
{
	char caractere; // '#' fin de mot
	struct Feuille* frere;
	struct Feuille* suivant;
}*Arbre;

typedef struct config
{
	int occLettre[26];
	int total;
	int nb_lettre_tirage;
}*Config;


/*char* openBalise(char* content)
{
	char* long_content=(char*) malloc((strlen(content)+2) * sizeof(char));
	return strcat(strcat(strcpy(long_content,"<"),content),">");
}

char* closeBalise(char* content)
{
	char* long_content=(char*) malloc((strlen(content)+3) * sizeof(char));
	return strcat(strcat(strcpy(long_content,"</"),content),">");
}

char* uniqueBalise(char* content)
{
	char* long_content=(char*) malloc((strlen(content)+3) * sizeof(char));
	return strcat(strcat(strcpy(long_content,"<"),content),"/>");
}*/

/*ListeInt ListeInt_addEnd(ListeInt lst, int valeur)
{
    if (lst == NULL){
        ListeInt lst2 = (ListeInt)malloc(sizeof(struct CelluleInt));
        lst2 -> item = valeur;
        lst2 -> next = lst;
        return lst2;
    }
    else
    {
        ListeInt lst3 = lst;
        while(lst -> next!=NULL) lst = lst -> next;
        ListeInt lst2 = (ListeInt)malloc(sizeof(struct CelluleInt));
        lst2 -> item = valeur;
        lst2 -> next = NULL;
        lst -> next = lst2;
        return lst3;
    }
}*/

/*void printFeuille(Arbre a)
{
	printf("Caractere : %c Frere : %p Suivant : %p\n", a -> caractere,a -> frere,a -> suivant);
}*/





// Genere un nombre aleatoire
int randnumber(int min,int max)
{ 
	return (rand()%(max-min+1))+min;
}

// Supprime la premier occurence d'un caractere dans une chaine
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

// Donne une lettre tire aleatoirement
char* pullTirage(Config c,int taille)
{
	char* tirage = (char*)malloc(sizeof(char)*taille);
	for (int i = 0; i < taille; ++i) tirage[i]=0;
	for (int i = 0; i < taille-1; ++i)
	{
		int var = randnumber(0,c->total);
		for (int j = 0; j < 26 && tirage[i]==0; ++j)
		{
			var=var-c->occLettre[j];
			if (var<=0) tirage[i] = j+'a';
		}
	}
	return tirage;
}

// Alloue une nouvelle feuille de l'arbre
Arbre newArbre(char c,struct Feuille* frere,struct Feuille* suivant)
{
	Arbre a = (Arbre)malloc(sizeof(struct Feuille));
	a -> caractere = c;
	a -> frere = frere;
	a -> suivant = suivant;	
	return a;
}

// Alloue la configuration
Config newConfig()
{
	Config c = (Config)malloc(sizeof(struct config));
	for (int i = 0; i < 26; ++i) c->occLettre[i]=0;
	c->total = 0;
	c->nb_lettre_tirage = 0;
	return c;
}

// Ajoute un mot dans un arbre
void addMot(Arbre feuille,char* mot,int i)
{
	Arbre feuillebis = feuille;
	if (mot[i]!='\n' && mot[i]!='\0')
	{
		while(feuillebis != NULL)
		{
			if (feuillebis -> caractere == mot[i])
			{
				if (feuillebis -> suivant == NULL) feuillebis -> suivant = newArbre(0,NULL,NULL);
				addMot(feuillebis -> suivant,mot,i+1);
				return ;
			}
			else if (feuillebis -> frere != NULL)
			{
				if (feuillebis -> caractere == 0)
				{
					feuillebis -> caractere = mot[i];
					addMot(feuillebis -> suivant,mot,i+1);
					return ;
				}
				else feuillebis = feuillebis -> frere;
			}
			else 
			{		
				if (feuillebis -> caractere == 0)
				{
					feuillebis -> caractere = mot[i];
					feuillebis -> suivant = newArbre(0,NULL,NULL);
				}
				else
				{
					feuillebis -> frere = newArbre(mot[i],NULL,newArbre(0,NULL,NULL));
					feuillebis = feuillebis -> frere;

				}
				addMot(feuillebis -> suivant,mot,i+1);
				return ;
			}
		}
	}
	else
	{
		while(feuillebis != NULL)
		{
			if (feuillebis -> caractere != 0 && feuillebis -> caractere != '#')
			{
				//printf("if \n");
				if (feuillebis -> frere == NULL) feuillebis -> frere = newArbre(0,NULL,NULL);
				feuillebis = feuillebis -> frere;
			}
			else if (feuillebis -> caractere == 0) feuillebis -> caractere = '#';
			else return ;
		}
	}
}

// Ajoute le nombre d'occurance dans le struct
void addOcLettre(char* buffer,Config c)
{
	int i = 0;
	while(buffer[i]!='\n' && buffer[i]!='\0')
	{
		c->occLettre[buffer[i]-'a']++;
		i++;
	}
}

// Renvoie 1 si le mot est present dans l'arbre sinon 0
int contient(Arbre feuille,char* mot,int i)
{
    Arbre feuillebis = feuille;
    if (mot[i]!='\0' && mot[i]!='\n')
    {
    	while (feuillebis != NULL)
    	{
    		if (feuillebis -> caractere == mot[i]) return contient(feuillebis -> suivant,mot,i+1);
    		else feuillebis = feuillebis -> frere;
    	}
    	return 0;
    }
    else
    {
    	while (feuillebis != NULL)
    	{
    		if (feuillebis -> caractere == '#') return 1;
    		else feuillebis = feuillebis -> frere;
    	}
    	return 0;
    }
}

// Creer un arbre a partir d'un dictionnaire
Arbre createArbre(char* langue,Config c)
{
	// Chemin d'acces du dictionnaire
	char* path = (char*)malloc((strlen(langue)+9)*sizeof(char));
	strcat(strcat(strcpy(path,"data/"),langue),".txt");

	// Creation arbre
	Arbre dictionnaire = newArbre(0,NULL,NULL);

	// Ouverture du fichier
	FILE * dico = fopen(path,"r");
	if (dico != NULL)
	{
		char buffer[100];
		while(fgets(buffer,100,dico)!=NULL)
		{
			// Ajout des mots dans le dictionnaire
            addMot(dictionnaire,buffer,0);
            // Compte les occurences de chaque lettre et les stocks
            addOcLettre(buffer,c);
		}
		fclose(dico);
		free(path);
		// Calcul total de lettre;
		for (int i = 0; i < 26; ++i) c->total=c->occLettre[i]+c->total;
		// Reduction des totaux pour rand()
		int ratio = c->total/30000;
		c->total = 0;
		for (int i = 0; i < 26; ++i) 
		{
			c->occLettre[i] = c->occLettre[i]/ratio; 	
			c->total=c->occLettre[i]+c->total;
		}
		return dictionnaire;
	}
	else fprintf(stderr, "Erreur : lecture du dictionnaire impossible\n");
	free(path);
	return NULL;
}

Liste longestsWord(Arbre a,char* lst)
{
	return NULL;
}



