#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"


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

// Vide l'affichage
void affichage_clear()
{
	if (OStag == WIN_64 || OStag == WIN_32) system("cls");
	else system("clear");
}

// Affiche le titre
void affichage_Title()
{
	printf("   __                                      __         ___     \n");        
	printf("  /\\ \\                                    /\\ \\__     /\\_ \\            \n");
	printf("  \\ \\ \\         __         ___ ___     ___\\ \\ ,_\\    \\//\\ \\      __   \n");
	printf("   \\ \\ \\  __  /'__`\\     /' __` __`\\  / __`\\ \\ \\/      \\ \\ \\   /'__`\\ \n");
	printf("    \\ \\ \\L\\ \\/\\  __/     /\\ \\/\\ \\/\\ \\/\\ \\L\\ \\ \\ \\_      \\_\\ \\_/\\  __/ \n");
	printf("     \\ \\____/\\ \\____\\    \\ \\_\\ \\_\\ \\_\\ \\____/\\ \\__\\     /\\____\\ \\____\\\n");
	printf("      \\/___/  \\/____/     \\/_/\\/_/\\/_/\\/___/  \\/__/     \\/____/\\/____/\n");                                                      
	printf("         ___                         ___                               \n");
	printf("        /\\_ \\                       /\\_ \\                              \n");
	printf("   _____\\//\\ \\    __  __    ____    \\//\\ \\     ___     ___      __     \n");
	printf("  /\\ '__`\\\\ \\ \\  /\\ \\/\\ \\  /',__\\     \\ \\ \\   / __`\\ /' _ `\\  /'_ `\\   \n");
	printf("  \\ \\ \\L\\ \\\\_\\ \\_\\ \\ \\_\\ \\/\\__, `\\     \\_\\ \\_/\\ \\L\\ \\/\\ \\/\\ \\/\\ \\L\\ \\  \n");
	printf("   \\ \\ ,__//\\____\\\\ \\____/\\/\\____/     /\\____\\ \\____/\\ \\_\\ \\_\\ \\____ \\ \n");
	printf("    \\ \\ \\/ \\/____/ \\/___/  \\/___/      \\/____/\\/___/  \\/_/\\/_/\\/___L\\ \\\n");
	printf("     \\ \\_\\                                                      /\\____/\n");
	printf("      \\/_/                                                      \\_/__/ \n");
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

void affichage_Menu()
{
	printf("\n\n      MENU :\n");
	printf("\t1 - Jouer une partie\n");
	printf("\t2 - Changer le dictionnaire\n");
}