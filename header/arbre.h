// Structure Arbre
typedef struct Feuille
{
	char caractere; // '#' fin de mot
	struct Feuille* frere;
	struct Feuille* suivant;
}*Arbre;

// Structure Config
typedef struct config
{
	int occLettre[26];
	int total;
	int nb_lettre_tirage;
	char* dictionnaire;
}*Config;

// Donne une lettre tire aleatoirement
char* Arbre_PullTirage(Config c);

// Verifie si le mot et dans le tirage
int Arbre_InTirage(char* tirage,char* mot);

// Alloue une nouvelle feuille de l'arbre
Arbre Arbre_NewArbre(char c,struct Feuille* frere,struct Feuille* suivant);

// Alloue la configuration
Config Arbre_NewConfig(char* path);

// Ajoute un mot dans un arbre
void Arbre_AddMot(Arbre feuille,char* mot,int i);

// Ajoute le nombre d'occurance dans le struct
void Arbre_AddOcLettre(char* buffer,Config c);

// Renvoie 1 si le mot est present dans l'arbre sinon 0
int Arbre_Contient(Arbre feuille,char* mot,int i);

// Creer un arbre a partir d'un dictionnaire
Arbre Arbre_CreateArbre(Config c);

// Free un Arbre
void Arbre_Free(Arbre a);

// Recherche tout les mots dans l'arbre compris dans le tirage
void Arbre_LongestsWord(Arbre a,Liste lst,char* tirage,char* currentword);