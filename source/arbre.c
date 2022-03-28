#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
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
	char* dictionnaire;
}*Config;






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

char* addChar(char* chaine,char c)
{
	if (chaine!=NULL)
	{
		char* nchaine = (char*)malloc(sizeof(char)*strlen(chaine)+2);
		strcpy(nchaine,chaine);
		nchaine[strlen(chaine)]=c;
		nchaine[strlen(chaine)+1]='\0';
		return nchaine;
	}
	else
	{
		char* nchaine = (char*)malloc(sizeof(char)*2);
		nchaine[0]=c;
		nchaine[1]='\0';
		return nchaine;
	}
}

// Donne une lettre tire aleatoirement
char* pullTirage(Config c)
{
	char* tirage = (char*)malloc(sizeof(char)*c->nb_lettre_tirage+1);
	for (int i = 0; i < c->nb_lettre_tirage+1; ++i) tirage[i]=0;
	for (int i = 0; i < c->nb_lettre_tirage; ++i)
	{
		int var = randnumber(0,c->total);
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
int inTirage(char* tirage,char* mot)
{
	if (equals(mot,"")) return 0;
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
		strcpy(t,delChar(t,mot[i]));
		i++;
	}
	return 1;

}

int isDictionnaire(char* dic)
{
	struct dirent *dir;
    // opendir() renvoie un pointeur de type DIR. 
    DIR *d = opendir("data"); 
    if (d!=NULL)
    {
        while ((dir = readdir(d)) != NULL)
        {
        	int b = 1;
        	if (strlen(dir->d_name)>strlen(dic))
        	{
        		for (int i = 0; dic[i]!='\0' ; ++i) if (dic[i]!=dir->d_name[i]) b = 0; 
        		if (b) return 1;
        	}
        }
        closedir(d);
    }
    return 0;
}

void notifyIni(char* property,char* value)
{
	FILE * newfile = fopen("data/nconfig.ini","w");
	if (newfile!=NULL)
	{
		FILE * oldfile = fopen("data/config.ini","r");
		if (oldfile!=NULL)
		{		
			fprintf(newfile, "%s=%s\n",property,value);
			char buffer[100];
			while(fgets(buffer,100,oldfile)!=NULL)
			{
				if(strstr( buffer, property)==NULL && !equals(buffer,"\n")) fprintf(newfile, "%s\n",buffer);
			}
			fclose(oldfile);
		}
		fclose(newfile);
	}
	remove("data/config.ini");
	rename("data/nconfig.ini","data/config.ini");
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
Config newConfig(char* path)
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
				strcpy(c->dictionnaire,delChar(strToken,'\n'));
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
Arbre createArbre(Config c)
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
	else fprintf(stderr, "Erreur : Dictionnaire introuvable\n");
	free(path);
	return NULL;
}
void arbre_Free(Arbre a)
{
	if (a!=NULL)
	{
		if(a->frere!=NULL) arbre_Free(a->frere);
		if(a->suivant!=NULL) arbre_Free(a->suivant);
		free(a);
	}
}

void longestsWord(Arbre a,Liste lst,char* tirage,char* currentword)
{
	if (a!=NULL && equals(tirage,"")!=1)
	{
		for (int i = 0; i < tirage[i]!='\0'; ++i)
		{
			Arbre abis = a;
			//printf("Test avec %c\n",tirage[i]);
			while(abis!=NULL)
			{
				//printf("tour de while\n");
				if (abis->caractere == tirage[i])
				{
					//printf("Suivant : %s%c\n",currentword,tirage[i]);
					longestsWord(abis->suivant,lst,delChar(tirage,tirage[i]),addChar(currentword,tirage[i]));
					//printf("1cur = %s\n",currentword );
				}
				else if (abis->caractere == '#') 
				{
					lst = Liste_add(lst,currentword);
					//printf("2cur = %s\n",currentword );
				}
				abis = abis->frere;
			}
			//system("pause");
		}
		if(currentword != NULL) free(currentword);
	}
	else if (a!=NULL)
	{
		//printf("Tirage vide\n");
		Arbre abis = a;
		while(abis!=NULL)
		{
			if (abis->caractere == '#')
			{
				lst = Liste_add(lst,currentword);
			}
			else abis= abis->frere;
		}
	}
	else 
	{
		//printf("Tirage  et arbre vide\n");
		if(currentword != NULL) free(currentword);
	}
	//printf("Fin\n");
}


/*void longestsWord(Arbre a,Liste lst,char* tirage,char* currentword)
{
	if (a!=NULL)
	{
		if (a->frere!=NULL) 
		{
			printf("a->frere\n");
			longestsWord(a->frere,lst,tirage,currentword);
		}
		if (a->suivant!=NULL)
		{
			printf("a->suivant\n");
			printf("addChar(%s,%c)=%s\n",currentword,a->caractere,addChar(currentword,a->caractere) );
			longestsWord(a->suivant,lst,tirage,addChar(currentword,a->caractere));
		}
		if (a->caractere=='#')
		{
			if (currentword!=NULL)
			{
				printf("#\n");
				char*tiragebis = (char*)malloc(sizeof(char)*strlen(tirage));
				strcpy(tiragebis,tirage);
				printf("alloc succes : %s\n",tiragebis);
				system("pause");
				printf("currentword = %s\n",currentword );
				system("pause");
				for (int i = 0; i < currentword[i]!='\0'; ++i)
				{
					//printf("currentword[%d] = %c\n",i,currentword[i]);
					//system("pause");
					int b = 1;
					for (int j = 0; j < tiragebis[j]!='\0' && b==1; ++j)
					{
						//printf("tiragebis[%d] = %c\n",j,tiragebis[j]);
						//system("pause");
						if (currentword[i]==tiragebis[i])
						{
							//printf("oui\n");
							strcpy(tiragebis,delChar(tiragebis,currentword[i]));
							b=0;
						}
					}
				}
				printf("out #\n");
				if (strlen(tirage)-strlen(tiragebis)==strlen(currentword)) 
				{
					lst = Liste_add(lst,currentword);
					printf("lst = Liste_add(lst,%s)\n",currentword);
					system("pause");
				}
				free(currentword);
				free(tiragebis);
			}
		}
	}
}*/

