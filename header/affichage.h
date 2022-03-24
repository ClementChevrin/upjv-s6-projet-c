int equals(char* c1,char* c2);

// Vide l'affichage
void affichage_clear();

// Affiche le titre
char* affichage_Title();

// Affiche une liste de mot dans un cadre
void affichage_WordList(char * title,int col,int widthcol,int line,Liste mot);

// Affiche une liste de lettre
void affichage_LetterList(char* title,char* listletter);

// Affiche le menu
char* affichage_Menu(char* title,int nb_option,...);

// Retourne un choix
char* affichage_InputConditionnelle(char* format,...);