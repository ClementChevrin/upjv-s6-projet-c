// Structure Liste
typedef struct Cellule
{
    char* item;
    struct Cellule *next;
}*Liste;

// Affiche une liste
void Liste_Print(Liste lst);

// Ajoute une cellule contenant valeur dans cette cellule a une liste
Liste Liste_Add(Liste lst, char* valeur);

// Ajoute une cellule contenant valeur dans cette cellule a la fin d'une liste
Liste Liste_AddEnd(Liste lst, char* valeur);

// Free une Liste
void Liste_Free(Liste lst);

// Renvoie une liste des mots de taille size avec une occurance pour chaque
Liste Liste_Longest(Liste lst,int size);

// Renvoie la taille de la liste
int Liste_Size(Liste lst);

// Renvoie la taille du mot le plus long de la liste
int Liste_SizeLongestWord(Liste lst);