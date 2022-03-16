// Type string
typedef char* string;

typedef struct Cellule
{
    string item;
    struct Cellule *next;
} *Liste;

Liste Liste_add(Liste lst, string valeur);
int Liste_size(Liste lst);
void Liste_free(Liste lst);