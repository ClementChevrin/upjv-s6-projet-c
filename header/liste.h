// Type string
typedef char* string;

typedef struct Cellule
{
    string item;
    struct Cellule *next;
} *Liste;

Liste Liste_add(Liste lst, string valeur);
Liste Liste_addend(Liste lst, string valeur);
int Liste_sizelongestword(Liste lst);
int Liste_size(Liste lst);
void Liste_free(Liste lst);
void Liste_print(Liste lst);
// Compare si 2 chaines sont equivalentes
int equals(char* c1,char* c2);