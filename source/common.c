#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ajoute un caractere en fin de chaine
char* Common_AddChar(char* chaine,char c)
{
	if (chaine!=NULL)
	{
		char* nchaine = (char*)malloc(sizeof(char)*strlen(chaine)+1);
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

// Supprime la premier occurence d'un caractere dans une chaine
char* Common_DelChar(char* chaine,char c)
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

// Compare si 2 chaines sont equivalentes
int Common_Equals(char* c1,char* c2)
{
	if (strlen(c1)!=strlen(c2)) return 0;
	else for (int i = 0; i < strlen(c1); ++i) if (c1[i] != c2[i]) return 0;
	return 1;
}

// Verifie si une langue est presente dans la liste des dictionnaires
int Common_IsDictionnaire(char* dic)
{
	struct dirent *dir;
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

// Actulaise des modificationd ans le fichier ini
void Common_NotifyIni(char* property,char* value)
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
				if(strstr( buffer, property)==NULL && !Common_Equals(buffer,"\n")) fprintf(newfile, "%s\n",buffer);
			}
			fclose(oldfile);
		}
		else fprintf(stderr, "Erreur : Fichier config.ini introuvable dans le repertoire data\n");
		fclose(newfile);
	}
	else fprintf(stderr, "Erreur : Fichier de modification impossible a creer dans le repertoire data\n");
	remove("data/config.ini");
	rename("data/nconfig.ini","data/config.ini");
}

// Genere un nombre aleatoire
int Common_Rand(int min,int max)
{ 
	return (rand()%(max-min+1))+min;
}

// Convertie int to string
char* Common_IntToString(int number)
{
    char* string = (char*)malloc(sizeof(char)*15);
    int i = 0;
    if (number==0) return "0";
    while (number)
    {
        string[i]=number%10+'0';
        number = number/10;
        i++;
    }
    string[i]='\0';
    i--;
    for (int j = 0; j <= i/2; ++j)
    {
        char c = string[j];
        string[j] = string[i-j];
        string[i-j] = c;
    }
    return string; 
}