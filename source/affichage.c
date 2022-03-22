#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../header/liste.h"


#ifdef _WIN64
 	#define OStag 2
#else
 	#ifdef _WIN32
	 	#define OStag 1
	#else
	 	#ifdef __APPLE__
		 	#define OStag 3
		#else
		 	#ifdef __linux__
			 	#define OStag 4
			#else
			 	#define OStag 5 // Other OS
			#endif
		#endif
	#endif
#endif

const int WIN_32 = 1;
const int WIN_64 = 2;
const int APPLE = 3;
const int LINUX = 4;

// Compare si 2 chaines sont equivalentes
int equals(char* c1,char* c2)
{
	if (strlen(c1)!=strlen(c2)) return 0;
	else for (int i = 0; i < strlen(c1); ++i) if (c1[i] != c2[i]) return 0;
	return 1;
}

// Convertie int to string
char* affichage_IntToString(int number)
{
	char* string = (char*)malloc(sizeof(char)*15);
    int i = 0;
    while (number)
    {
        string[i]=number%10+'0';
        number = number/10;
        i++;
    }
    string[i]='\0';
    i--;
    for (int j = 0; j < i/2; ++j)
    {
        char c = string[j];
        string[j] = string[i-i];
        string[i-i] = c;
    }
    return string; 
}

// Vide l'affichage
void affichage_clear()
{
	if (OStag == WIN_64 || OStag == WIN_32) system("cls");
	else system("clear");
}

// Affiche le titre
char* affichage_Title()
{
	return "   __                                      __         ___     \n  /\\ \\                                    /\\ \\__     /\\_ \\            \n  \\ \\ \\         __         ___ ___     ___\\ \\ ,_\\    \\//\\ \\      __   \n   \\ \\ \\  __  /'__`\\     /' __` __`\\  / __`\\ \\ \\/      \\ \\ \\   /'__`\\ \n    \\ \\ \\L\\ \\/\\  __/     /\\ \\/\\ \\/\\ \\/\\ \\L\\ \\ \\ \\_      \\_\\ \\_/\\  __/ \n     \\ \\____/\\ \\____\\    \\ \\_\\ \\_\\ \\_\\ \\____/\\ \\__\\     /\\____\\ \\____\\\n      \\/___/  \\/____/     \\/_/\\/_/\\/_/\\/___/  \\/__/     \\/____/\\/____/\n         ___                         ___                               \n        /\\_ \\                       /\\_ \\                              \n   _____\\//\\ \\    __  __    ____    \\//\\ \\     ___     ___      __     \n  /\\ '__`\\\\ \\ \\  /\\ \\/\\ \\  /',__\\     \\ \\ \\   / __`\\ /' _ `\\  /'_ `\\   \n  \\ \\ \\L\\ \\\\_\\ \\_\\ \\ \\_\\ \\/\\__, `\\     \\_\\ \\_/\\ \\L\\ \\/\\ \\/\\ \\/\\ \\L\\ \\  \n   \\ \\ ,__//\\____\\\\ \\____/\\/\\____/     /\\____\\ \\____/\\ \\_\\ \\_\\ \\____ \\ \n    \\ \\ \\/ \\/____/ \\/___/  \\/___/      \\/____/\\/___/  \\/_/\\/_/\\/___L\\ \\\n     \\ \\_\\                                                      /\\____/\n      \\/_/                                                      \\_/__/ \n";
}

// Affiche une liste de mot dans un cadre
void affichage_WordList(char * title,int col,int widthcol,int line,Liste mot)
{
	if (title!=NULL) printf("%s:\n",title);
	Liste lst = mot;
	printf("\xda");
	for (int i = 0; i < col; ++i) for (int j = 0; j < widthcol; ++j)printf("\xc4");
	printf("\b\xbf\n");
	for (int i = 0; i < line; ++i)
	{
		printf("\xb3");
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
	printf("\xc0");
	for (int i = 0; i < col; ++i) for (int j = 0; j < widthcol; ++j)printf("\xc4");
	printf("\b\xd9\n");
}

// Affiche une liste de lettre
void affichage_LetterList(char* title,char* listletter)
{
	if (title!=NULL) printf("%s:\n",title);
	int nbletter = strlen(listletter);
	printf("\xda");
	for (int i = 0; i < nbletter; ++i) printf("\xc4\xc4\xc4\xc2");
	printf("\b\xbf\n");
	for (int i = 0; i < nbletter; ++i) printf("\xb3 %c ",listletter[i]);
	printf("\xb3\n");
	printf("\xc0");
	for (int i = 0; i < nbletter; ++i) printf("\xc4\xc4\xc4\xc1");
	printf("\b\xd9\n");
}

char* affichage_Menu(char* title,int nb_option,...)
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
	for (int i = 0; i < nb_option; ++i) strcat(strcat(strcat(strcat(strcat(menu,"\t"),affichage_IntToString(i+1))," - "),va_arg(content, char*)),"\n");
	va_end(content);
	return menu;
}

char* affichage_InputConditionnelle(int nb_option,...)
{
	printf("\n\n\\>");
	char** tab = (char**)malloc(sizeof(char*)*nb_option);
	va_list content;
	va_start(content,nb_option);
	for (int i = 0; i < nb_option; ++i) 
	{
		tab[i] = (char*)malloc(sizeof(char)*100);
		strcpy(tab[i],va_arg(content,char*));
	}
	va_end(content);
	int respect_condition = 1;
	char* reponse = (char*)malloc(sizeof(char)*100);
	while(respect_condition)
	{	
		scanf("%s",reponse);
		for (int i = 0; i < nb_option; ++i) 
		{
			if (equals(tab[i],reponse)) 
			{
				for (int i = 0; i < nb_option; ++i) free(tab[i]);
				free(tab);
				return reponse;
			}
		}
		printf("\b                                                \r\\>");
	}
}
