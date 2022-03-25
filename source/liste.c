#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type string
typedef char* string;

typedef struct Cellule
{
    string item;
    struct Cellule *next;
} *Liste;

Liste Liste_add(Liste lst, string valeur)
{
	Liste lst2 = (Liste)malloc(sizeof(struct Cellule));
	lst2 -> item = (string)malloc(sizeof(char)*strlen(valeur));
    strcpy(lst2 -> item, valeur);
    lst2 -> next = lst;
    return lst2;
}
int Liste_size(Liste lst)
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
void Liste_free(Liste lst)
{
	if (lst != NULL)
	{
		if (lst->next != NULL) Liste_free(lst->next);
		free(lst);
	}
}

void Liste_print(Liste lst)
{
	Liste lst2 = lst;
	while(lst2!=NULL)
	{
		printf("%s\n",lst2->item);
		lst2 = lst2 ->next;
	}
}

// Compare si 2 chaines sont equivalentes
int equals(char* c1,char* c2)
{
	if (strlen(c1)!=strlen(c2)) return 0;
	else for (int i = 0; i < strlen(c1); ++i) if (c1[i] != c2[i]) return 0;
	return 1;
}
