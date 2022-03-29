// Vide l'affichage
void Affichage_Clear();

// Affiche le titre
char* Affichage_Title();

// Affiche une liste de mot dans un cadre
void Affichage_WordList(char * title,int col,int widthcol,int line,Liste mot);

// Affiche une liste de lettre
void Affichage_LetterList(char* title,char* listletter);

// Affiche un menu de choix
char* Affichage_Menu(char* title,int nb_option,...);

// Affiche une liste de dictionnaire
char* Affichage_DictionnaireListe(char* dic);

// Demande à l'utilisateur un saisie et test si cette saisie est juste
char* Affichage_InputConditionnelle(char* format,...);