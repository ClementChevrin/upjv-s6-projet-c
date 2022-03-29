// Ajoute un caractere en fin de chaine
char* Common_AddChar(char* chaine,char c);

// Supprime la premier occurence d'un caractere dans une chaine
char* Common_DelChar(char* chaine,char c);

// Compare si 2 chaines sont equivalentes
int Common_Equals(char* c1,char* c2);

// Verifie si une langue est presente dans la liste des dictionnaires
int Common_IsDictionnaire(char* dic);

// Actulaise des modificationd ans le fichier ini
void Common_NotifyIni(char* property,char* value);

// Genere un nombre aleatoire
int Common_Rand(int min,int max);

// Convertie int to string
char* Common_IntToString(int number);