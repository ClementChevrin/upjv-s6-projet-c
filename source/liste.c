#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/common.h"

// Structure Liste
typedef struct Cellule
{
    char* item;
    struct Cellule *next;
}*Liste;

// Affiche une liste
void Liste_Print(Liste lst)
{
	Liste lst2 = lst;
	while(lst2!=NULL)
	{
		printf("%s\n",lst2->item);
		lst2 = lst2 ->next;
	}
}

// Ajoute une cellule contenant valeur dans cette cellule a une liste
Liste Liste_Add(Liste lst, char* valeur)
{
	if(valeur==NULL) return lst;
	Liste lst2 = (Liste)malloc(sizeof(struct Cellule));
	lst2 -> item = (char*)malloc(sizeof(char)*strlen(valeur));
    strcpy(lst2 -> item, valeur);
    lst2 -> next = lst;
    return lst2;
}

// Ajoute une cellule contenant valeur dans cette cellule a la fin d'une liste
Liste Liste_AddEnd(Liste lst, char* valeur)
{
	if (valeur == NULL) return lst;
    else if (lst == NULL) return Liste_Add(lst,valeur);
    else
    {
	    Liste lst3 = lst;
	    while(lst -> next!=NULL) lst = lst -> next;
		Liste lst2 = (Liste)malloc(sizeof(struct Cellule));
		lst2 -> item = (char*)malloc(sizeof(char)*strlen(valeur));
	    strcpy(lst2 -> item, valeur);
	    lst2 -> next = NULL;
	    lst -> next = lst2;
	    return lst3;
	}
}

// Free une Liste
void Liste_Free(Liste lst)
{
	if (lst != NULL)
	{
		if (lst->next != NULL) Liste_Free(lst->next);
		free(lst);
	}
}

// Renvoie une liste des mots de taille size avec une occurance pour chaque
Liste Liste_Longest(Liste lst,int size)
{
	Liste lsr = NULL;
	Liste lstb = lst;
	while(lstb!=NULL)
	{
		if (lstb->item!=NULL)
		{
			if (strlen(lstb->item)==size)
			{
				Liste lsrb = lsr;
				int b = 1;
				while(lsrb)
				{
					if (lsrb->item!=NULL)
					{
						if (Common_Equals(lsrb->item,lstb->item)) b = 0;
					}
					lsrb=lsrb->next;
				}
				if(b)lsr=Liste_AddEnd(lsr,lstb->item);
			}		
		}
		lstb=lstb->next;
	}
	return lsr;
}

// Renvoie la taille de la liste
int Liste_Size(Liste lst)
{
	if (lst == NULL) return 0;
	if (lst -> next == NULL && lst -> item != NULL) return 1;
	int size = 1;
	Liste lst2 = lst;
	while(lst2 -> next != NULL)
	{
		lst2 = lst2 -> next;
		size++;
	}
	return size;
}

// Renvoie la taille du mot le plus long de la liste
int Liste_SizeLongestWord(Liste lst)
{
	Liste ls = lst;
	int size = 0;
	while(ls!=NULL) 
	{
		if(ls->item!=NULL) 
		{
			if(strlen(ls->item)>size) 
			{
				size = strlen(ls->item);
			}
			ls = ls->next;
		} 
	}
	return size;
}