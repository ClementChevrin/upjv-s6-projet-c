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

/*
char* openBalise(char* content);

char* closeBalise(char* content);

char* uniqueBalise(char* content);*/

// Genere un nombre aleatoire
int randnumber(int min,int max);

// Supprime la premier occurence d'un caractere dans une chaine
char* delChar(char* chaine,char c);

// Donne une lettre tire aleatoirement
char* pullTirage(Config c);

// Alloue une nouvelle feuille de l'arbre
Arbre newArbre(char c,struct Feuille* frere,struct Feuille* suivant);

// Alloue la configuration
Config newConfig(char* path);

// Ajoute un mot dans un arbre
void addMot(Arbre feuille,char* mot,int i);

// Ajoute le nombre d'occurance dans le struct
void addOcLettre(char* buffer,Config c);

// Renvoie 1 si le mot est present dans l'arbre sinon 0
int contient(Arbre feuille,char* mot,int i);

// Creer un arbre a partir d'un dictionnaire
Arbre createArbre(Config c);

void arbre_Free(Arbre a);

Liste longestsWord(Arbre a,char* lst);
