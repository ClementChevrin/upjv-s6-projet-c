#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../header/common.h"
#include "../header/liste.h"

// Structure Arbre
typedef struct Feuille
{
	char caractere; // '#' fin de mot
	struct Feuille* frere;
	struct Feuille* suivant;
}*Arbre;

// Structure Config
typedef struct config
{
	int occLettre[26];
	int total;
	int nb_lettre_tirage;
	char* dictionnaire;
}*Config;

// Donne une lettre tire aleatoirement
char* Arbre_PullTirage(Config c)
{
	char* tirage = (char*)malloc(sizeof(char)*c->nb_lettre_tirage+1);
	for (int i = 0; i < c->nb_lettre_tirage+1; ++i) tirage[i]=0;
	for (int i = 0; i < c->nb_lettre_tirage; ++i)
	{
		int var = Common_Rand(0,c->total);
		for (int j = 0; j < 26 && tirage[i]==0; ++j)
		{
			var=var-c->occLettre[j];
			if (var<=0) tirage[i] = j+'a';
		}
	}
	tirage[c->nb_lettre_tirage]='\0';
	return tirage;
}

// Verifie si le mot et dans le tirage
int Arbre_InTirage(char* tirage,char* mot)
{
	if (Common_Equals(mot,"")) return 0;
	char* t=(char*)malloc(sizeof(char)*strlen(tirage));
	strcpy(t,tirage);
	int i = 0,b=1;
	while(mot[i]!='\0')
	{
		b=1;
		for (int j = 0; t[j]!='\0'; ++j)
		{
			if (t[j]==mot[i]) b=0;
		}
		if (b) return 0;
		strcpy(t,Common_DelChar(t,mot[i]));
		i++;
	}
	return 1;
}

// Alloue une nouvelle feuille de l'arbre
Arbre Arbre_NewArbre(char c,struct Feuille* frere,struct Feuille* suivant)
{
	Arbre a = (Arbre)malloc(sizeof(struct Feuille));
	a -> caractere = c;
	a -> frere = frere;
	a -> suivant = suivant;	
	return a;
}

// Alloue la configuration
Config Arbre_NewConfig(char* path)
{
	Config c = (Config)malloc(sizeof(struct config));
	for (int i = 0; i < 26; ++i) c->occLettre[i]=0;
	c->total = 0;
	FILE* ini = fopen(path,"r");
	if (ini != NULL)
	{
		const char * separators = "=";
		char buffer[50];
		while (fgets(buffer,50,ini) != NULL)
		{
			if (strstr(buffer,"Langue")!=NULL)
			{
				char * strToken = strtok ( buffer, separators );
			    if ( strToken != NULL ) 
			    {
			        strToken = strtok ( NULL, separators );
			    }
				c->dictionnaire = (char*)malloc(sizeof(char)*strlen(strToken));
				strcpy(c->dictionnaire,Common_DelChar(strToken,'\n'));
			}
			else if(strstr(buffer,"Tirage")!=NULL)
			{
				char * strToken = strtok ( buffer, separators );
			    if ( strToken != NULL ) 
			    {
			        strToken = strtok ( NULL, separators );
			    }
				c->nb_lettre_tirage = atoi(strToken);
			}
		}
		fclose(ini);
	}
	else
	{
		free(c);
		return NULL;
	}
	return c;
}

// Ajoute un mot dans un arbre
void Arbre_AddMot(Arbre feuille,char* mot,int i)
{
	Arbre feuillebis = feuille;
	if (mot[i]!='\n' && mot[i]!='\0')
	{
		while(feuillebis != NULL)
		{
			if (feuillebis -> caractere == mot[i])
			{
				if (feuillebis -> suivant == NULL) feuillebis -> suivant = Arbre_NewArbre(0,NULL,NULL);
				Arbre_AddMot(feuillebis -> suivant,mot,i+1);
				return ;
			}
			else if (feuillebis -> frere != NULL)
			{
				if (feuillebis -> caractere == 0)
				{
					feuillebis -> caractere = mot[i];
					Arbre_AddMot(feuillebis -> suivant,mot,i+1);
					return ;
				}
				else feuillebis = feuillebis -> frere;
			}
			else 
			{		
				if (feuillebis -> caractere == 0)
				{
					feuillebis -> caractere = mot[i];
					feuillebis -> suivant = Arbre_NewArbre(0,NULL,NULL);
				}
				else
				{
					feuillebis -> frere = Arbre_NewArbre(mot[i],NULL,Arbre_NewArbre(0,NULL,NULL));
					feuillebis = feuillebis -> frere;

				}
				Arbre_AddMot(feuillebis -> suivant,mot,i+1);
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
				if (feuillebis -> frere == NULL) feuillebis -> frere = Arbre_NewArbre(0,NULL,NULL);
				feuillebis = feuillebis -> frere;
			}
			else if (feuillebis -> caractere == 0) feuillebis -> caractere = '#';
			else return ;
		}
	}
}

// Ajoute le nombre d'occurance dans le struct
void Arbre_AddOcLettre(char* buffer,Config c)
{
	int i = 0;
	while(buffer[i]!='\n' && buffer[i]!='\0')
	{
		c->occLettre[buffer[i]-'a']++;
		i++;
	}
}

// Renvoie 1 si le mot est present dans l'arbre sinon 0
int Arbre_Contient(Arbre feuille,char* mot,int i)
{
    Arbre feuillebis = feuille;
    if (mot[i]!='\0' && mot[i]!='\n')
    {
    	while (feuillebis != NULL)
    	{
    		if (feuillebis -> caractere == mot[i]) return Arbre_Contient(feuillebis -> suivant,mot,i+1);
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
Arbre Arbre_CreateArbre(Config c)
{
	// Chemin d'acces du dictionnaire
	if (c->dictionnaire == NULL)
	{
		fprintf(stderr, "Erreur : Aucune langue trouver dans le fichier config.ini, [Langue=]\n");
		return NULL;
	}
	char* path = (char*)malloc((strlen(c->dictionnaire)+9)*sizeof(char));
	strcat(strcat(strcpy(path,"data/"),c->dictionnaire),".txt");

	// Creation arbre
	Arbre dictionnaire = Arbre_NewArbre(0,NULL,NULL);

	// Ouverture du fichier
	FILE * dico = fopen(path,"r");
	if (dico != NULL)
	{
		char buffer[100];
		while(fgets(buffer,100,dico)!=NULL)
		{
			// Ajout des mots dans le dictionnaire
            Arbre_AddMot(dictionnaire,buffer,0);
            // Compte les occurences de chaque lettre et les stocks
            Arbre_AddOcLettre(buffer,c);
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
	else fprintf(stderr, "Erreur : Dictionnaire introuvable\n");
	free(path);
	return NULL;
}

// Free un Arbre
void Arbre_Free(Arbre a)
{
	if (a!=NULL)
	{
		if(a->frere!=NULL) Arbre_Free(a->frere);
		if(a->suivant!=NULL) Arbre_Free(a->suivant);
		free(a);
	}
}

// Recherche tout les mots dans l'arbre compris dans le tirage
void Arbre_LongestsWord(Arbre a,Liste lst,char* tirage,char* currentword)
{
	if (a!=NULL && Common_Equals(tirage,"")!=1)
	{
		for (int i = 0; i < tirage[i]!='\0'; ++i)
		{
			Arbre abis = a;
			while(abis!=NULL)
			{
				if (abis->caractere == tirage[i]) Arbre_LongestsWord(abis->suivant,lst,Common_DelChar(tirage,tirage[i]),Common_AddChar(currentword,tirage[i]));
				else if (abis->caractere == '#') lst = Liste_AddEnd(lst,currentword);
				abis = abis->frere;
			}
		}
	}
	else if (a!=NULL)
	{
		Arbre abis = a;
		while(abis!=NULL)
		{
			if (abis->caractere == '#')
			{
				lst = Liste_AddEnd(lst,currentword);
				return ;
			}
			else abis= abis->frere;
		}
	}
	if(currentword != NULL) free(currentword);
}
