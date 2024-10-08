#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/common.h"
#include "../header/liste.h"

// Vide l'affichage
void Affichage_Clear()
{
	#ifdef _WIN64
	 	system("cls");
	#else
	 	#ifdef _WIN32
		 	system("cls");
		#else
		 	system("clear");
		#endif
	#endif
}

// Affiche le titre
char* Affichage_Title()
{
	return "   __                                      __         ___     \n  /\\ \\                                    /\\ \\__     /\\_ \\            \n  \\ \\ \\         __         ___ ___     ___\\ \\ ,_\\    \\//\\ \\      __   \n   \\ \\ \\  __  /'__`\\     /' __` __`\\  / __`\\ \\ \\/      \\ \\ \\   /'__`\\ \n    \\ \\ \\L\\ \\/\\  __/     /\\ \\/\\ \\/\\ \\/\\ \\L\\ \\ \\ \\_      \\_\\ \\_/\\  __/ \n     \\ \\____/\\ \\____\\    \\ \\_\\ \\_\\ \\_\\ \\____/\\ \\__\\     /\\____\\ \\____\\\n      \\/___/  \\/____/     \\/_/\\/_/\\/_/\\/___/  \\/__/     \\/____/\\/____/\n         ___                         ___                               \n        /\\_ \\                       /\\_ \\                              \n   _____\\//\\ \\    __  __    ____    \\//\\ \\     ___     ___      __     \n  /\\ '__`\\\\ \\ \\  /\\ \\/\\ \\  /',__\\     \\ \\ \\   / __`\\ /' _ `\\  /'_ `\\   \n  \\ \\ \\L\\ \\\\_\\ \\_\\ \\ \\_\\ \\/\\__, `\\     \\_\\ \\_/\\ \\L\\ \\/\\ \\/\\ \\/\\ \\L\\ \\  \n   \\ \\ ,__//\\____\\\\ \\____/\\/\\____/     /\\____\\ \\____/\\ \\_\\ \\_\\ \\____ \\ \n    \\ \\ \\/ \\/____/ \\/___/  \\/___/      \\/____/\\/___/  \\/_/\\/_/\\/___L\\ \\\n     \\ \\_\\                                                      /\\____/\n      \\/_/                                                      \\_/__/ \n";
}

// Affiche une liste de mot dans un cadre
void Affichage_WordList(char * title,int col,int widthcol,int line,Liste mot)
{
	#ifdef _WIN32
		if (title!=NULL) printf("  %s:\n",title);
		Liste lst = mot;
		printf("   \xda");
		for (int i = 0; i < col; ++i) for (int j = 0; j < widthcol; ++j)printf("\xc4");
		printf("\b\xbf\n");
		for (int i = 0; i < line; ++i)
		{
			printf("   \xb3");
			for (int j = 0; j < col; ++j)
			{
				if (lst!=NULL)
				{
					int size_mot = strlen(lst->item);
					printf("-%s",lst->item);
					for (int k = size_mot; k < widthcol-1; ++k)printf(" ");
				}
				else 
				{
					for (int k = 0; k < widthcol; ++k)printf(" ");
				}
				if (lst!=NULL) lst = lst->next;
			}
			printf("\b\xb3\n");
		}
		printf("   \xc0");
		for (int i = 0; i < col; ++i) for (int j = 0; j < widthcol; ++j)printf("\xc4");
		printf("\b\xd9\n");
	#else
	 	if (title!=NULL) printf("  %s:\n",title);
		Liste lst = mot;
		printf("   +");
		for (int i = 0; i < col; ++i) for (int j = 0; j < widthcol; ++j)printf("-");
		printf("+\n");
		for (int i = 0; i < line; ++i)
		{
			printf("   |");
			for (int j = 0; j < col; ++j)
			{
				if (lst!=NULL)
				{
					int size_mot = strlen(lst->item);
					printf("-%s",lst->item);
					for (int k = size_mot; k < widthcol-1; ++k)printf(" ");
				}
				else 
				{
					for (int k = 0; k < widthcol; ++k)printf(" ");
				}
				if (lst!=NULL) lst = lst->next;
			}
			printf("|\n");
		}
		printf("   +");
		for (int i = 0; i < col; ++i) for (int j = 0; j < widthcol; ++j)printf("-");
		printf("+\n");
	#endif
}

// Affiche une liste de lettre
void Affichage_LetterList(char* title,char* listletter)
{
	#ifdef _WIN32
		if (title!=NULL) printf("  %s:\n",title);
		int nbletter = strlen(listletter);
		printf("   \xda");
		for (int i = 0; i < nbletter; ++i) printf("\xc4\xc4\xc4\xc2");
		printf("\b\xbf\n   ");
		for (int i = 0; i < nbletter; ++i) printf("\xb3 %c ",listletter[i]);
		printf("\xb3\n");
		printf("   \xc0");
		for (int i = 0; i < nbletter; ++i) printf("\xc4\xc4\xc4\xc1");
		printf("\b\xd9\n");
	#else
	 	if (title!=NULL) printf("  %s:\n",title);
		int nbletter = strlen(listletter);
		printf("   +");
		for (int i = 0; i < nbletter; ++i) printf("---+");
		printf("\n   ");
		for (int i = 0; i < nbletter; ++i) printf("| %c ",listletter[i]);
		printf("|\n");
		printf("   +");
		for (int i = 0; i < nbletter; ++i) printf("---+");
		printf("\n");
	#endif
}

// Affiche un menu de choix
char* Affichage_Menu(char* title,int nb_option,...)
{
	va_list content,size;
	va_start(content, nb_option);
	va_copy(size,content);

	// Allocation de la chaine total
	int sizealloc=strlen(title)+9+(5*nb_option);
	int zero=1;
	for (int i = nb_option; i > 0; i=i/10)
	{
		sizealloc += i*(1*zero);
		zero = zero*10;
	}
	for (int i = 0; i < nb_option; ++i) sizealloc = sizealloc + strlen(va_arg(size, char*));
	va_end(size);
	char* menu = (char*)malloc(sizeof(char)*sizealloc);

	strcat(strcat(strcpy(menu,"\n\n      "),title)," :\n");
	for (int i = 0; i < nb_option; ++i) strcat(strcat(strcat(strcat(strcat(menu,"\t"),Common_IntToString(i+1))," - "),va_arg(content, char*)),"\n");
	va_end(content);
	return menu;
}

// Affiche une liste de dictionnaire
char* Affichage_DictionnaireListe(char* dic)
{
	struct dirent *dir;
	int size = 0,nb_option = 0; 
    DIR *d = opendir(dic); 
    if (d!=NULL)
    {
        while ((dir = readdir(d)) != NULL)
        {
        	int strsize = strlen(dir->d_name);
        	if (strsize>5) 
        	{
        		if (dir->d_name[strsize-1]=='t' && dir->d_name[strsize-2]=='x' && dir->d_name[strsize-3]=='t' && dir->d_name[strsize-4]=='.') 
        		{
        			size +=strsize;
        			nb_option++;
        		}
        	}
        }
        closedir(d);
    }
	size +=28+113+(6*nb_option);
	char* menu = (char*)malloc(sizeof(char)*size);

	strcpy(menu,"\n\n      LISTE DES LANGUES :\n");
    d = opendir(dic); 
    if (d!=NULL)
    {
    	int i = 1;
        while ((dir = readdir(d)) != NULL)
        {
        	int strsize = strlen(dir->d_name);
        	if (strsize>5) 
    		{
    			if (dir->d_name[strsize-1]=='t' && dir->d_name[strsize-2]=='x' && dir->d_name[strsize-3]=='t' && dir->d_name[strsize-4]=='.') 
				{
					strcat(strcat(strcat(strcat(strcat(menu,"\t"),Common_IntToString(i))," - "),dir->d_name),"\n");
					i++;
				}
			}
        }
        closedir(d);
    }
    strcat(menu,"\n(Pour ajouter un dictionnaire ajouter votre liste de mot dans un fichier .txt, il sera automatiquement detecte)\n");
    return menu;
}

// Demande à l'utilisateur un saisie et test si cette saisie est juste
char* Affichage_InputConditionnelle(char* format,...)
{
	// Compte le nombre d'argument a partir du format
	int nb_arg = 0,cpt=0;
	while(format[cpt]!='\0')
	{
		if (format[cpt]=='%')
		{
			if (format[cpt+1]=='s')nb_arg++;
			else if (format[cpt+1]=='&')nb_arg++;
		}
		cpt++;
	}

	// Recuperation des chaines et des conditions
	char** tab = (char**)malloc(sizeof(char*)*nb_arg);
	va_list content,copy;
	va_start(content,nb_arg);
	va_copy(copy,content);
	for (int i = 0; i < nb_arg; ++i) 
	{
		tab[i] = (char*)malloc(sizeof(char)*strlen(va_arg(copy,char*)));
		strcpy(tab[i],va_arg(content,char*));
	}
	va_end(copy);
	va_end(content);


	// Afficher la question
	cpt=0;
	int ind_s = 0;
	while(format[cpt]!='\0')
	{
		if (format[cpt]=='%')
		{
			if (format[cpt+1]=='s')
			{
				printf("%s",tab[ind_s]);
				ind_s++;
				cpt++;
			}
			else if (format[cpt+1]=='&') 
			{
				while(format[cpt]!='\0') cpt++;
				cpt--;
			}
		}
		else putchar(format[cpt]);
		cpt++;
	}
	// Alloue un buffer suffiant pour la saisie
	int maxbuffer=0;
	char* reponse = (char*)malloc(sizeof(char)*1024);

	while(1)
	{	
		// Saisie conditionnelle
		scanf("%s",reponse);
		for (int i = ind_s; i < nb_arg; ++i) 
		{
			if (Common_Equals(tab[i],reponse)) 
			{
				for (int i = 0; i < nb_arg; ++i) free(tab[i]);
				free(tab);
				return reponse;
			}
		}

		// Reaffichage
		Affichage_Clear();
		cpt = 0;
		ind_s = 0;
		while(format[cpt]!='\0')
		{
			if (format[cpt]=='%')
			{
				if (format[cpt+1]=='s')
				{
					printf("%s",tab[ind_s]);
					ind_s++;
					cpt++;
				}
				else if (format[cpt+1]=='&') 
				{
					while(format[cpt]!='\0') cpt++;
					cpt--;
				}
			}
			else putchar(format[cpt]);
			cpt++;
		}
	}
}
