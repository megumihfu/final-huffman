#include "huffman.h"

ListeCellule *initListeCel() //retourne la tete initialisée
{
    ListeCellule *listeC = malloc(sizeof(*listeC));
    listeC->premier=NULL;
    listeC->nbCellule=0;
    return listeC;
}

ListeNoeud *initListeNoe() //retourne la tete initialisée
{
    ListeNoeud *listeN = malloc(sizeof(*listeN));
    listeN->premier=NULL;
    listeN->nbNoeud=0;
    return listeN;
}

void insererElement(ListeNoeud *liste, int freq, char val) 
{
    Noeud *element = malloc(sizeof (Noeud));  // Fonction qui rajoute un element en tete de liste
    element->frequence = freq;
    element->valeur = val;

    element->branche_gauche = NULL;
    element->branche_droite = NULL;
    element->accroche = liste->premier;
    liste->premier = element;
    liste->nbNoeud++;
}

/*void afficherListe(ListeNoeud *liste) // affiches la liste
{
    if (liste != NULL)
    {
        Noeud *actuel = liste->premier;

        while (actuel != NULL)
        {          
            printf("Le cara '%c' apparait %d fois\n", actuel->valeur, actuel->frequence);
            actuel = actuel->accroche;
        }
    }
}*/

void remplirChaine(ListeNoeud *Arbre, Dictionnary *dico)
{
    
    int i = 0;
    //remplir la liste avec chaque cellule, une valeur unique et son dicourence
    //faire pointer la branche gauche du noeud sur NULL et la doite, sur le noeud accroche
    //les cellule elle meme pointe toute sur NULL
    while (dico->occ_text[i] != 0){
        insererElement(Arbre, dico->occ_text[i], dico->text[i]);
        i++;
    }    
}

// Tri de la liste par ordre croissant du champ nombre
Noeud* triElements(Noeud* liste)
{
  if( liste == NULL )
    return NULL;  // liste vide, rien à trier
  if( liste->accroche == NULL )
    return liste; // un seul élément, rien à trier

  Noeud* premier = liste;
    
  int recommencer;
    do 
    {
        // commence au début de la liste
        Noeud* precedent = NULL;
        Noeud* element = premier;
        Noeud* suivant = element->accroche;
        recommencer = 0;
    
        while( suivant != NULL ) 
        {      
            if( suivant->frequence < element->frequence ) 
            {
                // si le classement de l'élément et de son accroche est incorrect :
                // la liste devra être re-parcourue
                recommencer = 1;

                // inverse l'élément courant et son accroche
                if(precedent == NULL) 
                    premier = suivant;

                else
                    precedent->accroche = suivant;

                element->accroche = suivant->accroche;
                suivant->accroche = element;                

                // avance dans la liste
                precedent = suivant;        // nouveau précédent = ancien accroche
                // nouvel élément = ancien élément (inchangé)
                suivant = element->accroche; // nouveau accroche = accroche du nouvel élément
            } 

            else 
            {
                // si le classement de l'élément et de son accroche est correct :
                // avance dans la liste 
                precedent = element;        // nouveau précédent = ancien élément
                element = element->accroche; // nouvel élément = ancien accroche
                suivant = element->accroche; // nouveau accroche = accroche du nouvel élément
            }
        }
    } while(recommencer);
  
  // retourne la nouvelle liste
    return premier;
}

Noeud *concatener(Noeud *Arbre)
{
    if(Arbre == NULL)
        return Arbre;

    Noeud *temp, *temp1, *new;
    temp = Arbre;
    temp1 = Arbre->accroche;
    
    new = malloc(sizeof(Noeud));

    new->branche_droite = temp; // NON INVERSEE 
    new->branche_gauche = temp1; //NON INVERSEE 
    new->frequence = temp->frequence + temp1->frequence;
    new->accroche = temp1->accroche;
    new->valeur = '\0';
    temp->accroche = new;
    temp1->accroche = new;

    //free(Noeud);

    return new;
}

Noeud *huff(Noeud *Arbre)
{
    int i = 0;
    while(Arbre->accroche != NULL)
    { 
        Arbre = concatener(Arbre);
        Arbre = triElements(Arbre);
        i++;   
    }
    return Arbre;
}

/*void create_code1(Dictionnary *dico, Noeud *node)
{
    Noeud *Arbre;
    char tmp[SIZE];
    FILE *f; 
    f = fopen("compressed.txt", "w");
    int i = 0;
    //fprintf(f, "\n1"); //because first node is always 1 in the tree

        if(node == NULL) //if the tree doesnt exist, just exit the function
                return;

        if(node->branche_gauche == NULL && node->branche_gauche == NULL){ //if the current node is the leaf
            tmp[i] = node->valeur;
            printf("counter1 is %d\n", i);
            fprintf(f, "%c", tmp[i]);
            //printf("%c", tmp[i]);
        }

        if(node->branche_gauche != NULL){ //if it's the left branch, assign 0
            fprintf(f, "0");
            printf("counter2 is %d\n", i);
            //printf("0");
            tmp[i] = '0';
            create_code1(dico, node->branche_gauche);
        }

        if(node->branche_droite != NULL){ //if it's the right branch, assign 1
            fprintf(f, "1");
            printf("counter3 is %d\n", i);
            tmp[i] = '1';
            //printf("1");
            create_code1(dico, node->branche_droite);
        }

    for(int i = 0; i < SIZE; i++){
        printf("%c", tmp[i]);
    }

    fclose(f);
}*/

void create_code1(Dictionnary *dico, Noeud *node, FILE *f)
{    
    if(node == NULL) //if the tree doesnt exist, just exit the function
        return;

    if(node->branche_gauche == NULL && node->branche_gauche == NULL){ //if the current node is the leaf
        //tmp = node->valeur;
        fprintf(f, "%c", node->valeur);
        //printf("%c", node->valeur);
    }

    if(node->branche_gauche != NULL){ //if it's the left branch, assign 0
        fprintf(f, "0");
        //printf("0");
        create_code1(dico, node->branche_gauche, f);
    }

    if(node->branche_droite != NULL){ //if it's the right branch, assign 1
        fprintf(f, "1");
        //printf("1");
        create_code1(dico, node->branche_droite, f);
    }
}

Dictionnary *create_code2(Dictionnary *tabs, Noeud *Arbre, char tmp[20]) //assigner les val 1 et 0 sur les branches pour le code binaire d'huffman
{
    if(Arbre->branche_gauche != NULL) //branche droite -> valeur binaire 0
    {
        strncat(tmp, "0", 2);
        create_code2(tabs, Arbre->branche_gauche, tmp);
    }
    
    if(Arbre->branche_droite != NULL) //branche gauche -> valeur binaire 1
    {
        strncat(tmp, "1", 2);
        create_code2(tabs, Arbre->branche_droite, tmp);
    }
    
    for(size_t i = 0; i < SIZE; i++)
    {
        if(tabs->text[i] == Arbre->valeur)
            strcpy(tabs->code[i], tmp);
    }
    
    int i = 0;
    while(tmp[i] != '\0'){
        i++;
    }

    tmp[i-1] = '\0';
   
    return tabs; 
}

Dictionnary *init_dico()
{
    Dictionnary *dico = malloc(sizeof(*dico));

    if(dico == NULL)
        printf("Memory allocation failed\n");

    dico->counter = SIZE;

    for(int i = 0; i < dico->counter; i++){
        dico->text[i] = 0;
        dico->occ_text[i] = 0;
        dico->dec[i] = 0;
    }

    return dico;
}

Dictionnary *verif(Dictionnary *dico, char car)
{
    int i, freq = 1;
    bool checked;

    for(i = 0; i < dico->counter; i++){ //parcourt tt le tab text pr verifier si la valeur y est deja ou pas
        if(car == dico->text[i]){ 
            dico->occ_text[i] += 1;
            checked = true; //renvoie que la case a été check
            break;
        }

        else    
            checked = false; 
    }

    if(checked == false){ //si la valeur n'est pas dans le tab on l'ajoute
        for(i = 0; i < dico->counter; i++){ 
            if(dico->text[i] == 0){
                dico->text[i] = car; 
                dico->occ_text[i] = freq;
                break;
            }
        }
    } 

    return dico;
}

Dictionnary *reading_file(Dictionnary *dico, FILE *fp)
{   
    char tmp;

    while((tmp = fgetc(fp)) != EOF){ 
        verif(dico, tmp);
    }

    return dico;
}

Dictionnary *set_counter(Dictionnary *dico) //pour pas avoir le reste du tableau pas rempli (qui est egal à 0 dcp)
{
    for(int i = 0; i < SIZE; i++){ //SIZE a la place de dico->counter
        if(dico->dec[i] == '0'){
            dico->counter = i;
        }
    }

    printf("set counter seems ok\n");
    return dico;
}

int file_size(FILE *fp) //pour mettre en première ligne du fichier de compression 
{
    int size;

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    
    return size;
}

void compression(Dictionnary *dico, char filename[20], FILE* fp, FILE *f)
{
    char tmp;

    fp = fopen(filename, "r");

    while((tmp = fgetc(fp)) != EOF){ 
        for(int i = 0; i < dico->counter; i++){
            if(tmp == dico->text[i]){
                fprintf(f, "%s", dico->code[i]);
                //printf("%s", dico->code[i]);
            }
        }
    }
}

///////////////////////////////////////
//decompression
Dictionnary *data_from_file(Dictionnary *dico, FILE *f)
{
    char tmp;
    int i = 0, j = 0;

    while((tmp = fgetc(f)) != '\n'){    
        i++;
    }

    printf("cursor's position is : %d\n", i+1);
    fseek(f, i+1, SEEK_SET);

    while((tmp = fgetc(f)) != '\n'){
        dico->dec[j] = tmp;
        printf("%c - ", dico->dec[j]);
        j++;
    }

    dico->counter = j; //on compte le premier noeud tjr égal à 1 + le fait que j commence à 0 et pas à 1
    printf("j counter is : %d\n", dico->counter);

    return dico;
}

void creerFils(Noeud *parent)
{    
    Noeud *droit = malloc(sizeof (Noeud));
    Noeud *gauche = malloc(sizeof (Noeud));
    printf("creerFils 1 is fine too\n");

    droit->valeur = '\0';
    droit->branche_droite = NULL;
    droit->branche_gauche = NULL;
    droit->accroche = parent;

    gauche->valeur = '\0';
    gauche->branche_droite = NULL;
    gauche->branche_gauche = NULL;
    gauche->accroche = parent;
    
    parent->branche_droite = droit;
    parent->branche_gauche = gauche;
}

char *creerAbrDec(Noeud *actuel,  char *code1) // recrer l'arbre binaire a partir de l'entete dans le fichier compressé
{
        // 'bleu' est la chaine de caractere qui comporte l'entete (c'est l'arbre encodé)
    if(*code1 == '1'){ //donc l'arbre a des fils
        creerFils(actuel);
        code1 = creerAbrDec(actuel->branche_droite, code1 + 1);
        code1 = creerAbrDec(actuel->branche_gauche, code1 + 1);
    }
    else if(*code1 == '0'){
        code1 = code1 + 1;
        actuel->valeur = *code1;
    }

    return code1;
}

/*Dictionnary *creerAbrDec(Noeud *actuel, Dictionnary *dico) // recrer l'arbre binaire a partir de l'entete dans le fichier compressé
{
        // 'bleu' est la chaine de caractere qui comporte l'entete (c'est l'arbre encodé)
    for(int i = 0; i < SIZE; i++){
        if(dico->code1[i] == '1'){ //donc l'arbre a des fils
            creerFils(actuel);
            dico->code1[i] = creerAbrDec(actuel->branche_droite, dico->code1[i] + 1);
            dico->code1[i] = creerAbrDec(actuel->branche_gauche, dico->code1[i] + 1);
        }
    
        else if(dico->code1[i] == '0'){
            dico->code1[i] = dico->code1[i] + 1;
            actuel->valeur = dico->code1[i];
        }
    }
    
    return dico;
}*/

int menu()
{
    int choix1;

    system("clear");
    printf("\n                        MENU                        \n");
    printf("HUFFMAN : compression/décompression -------------- 1\n");
    printf("Affichage du fichier ----------------------------- 2\n");
    printf("Quitter le programme ----------------------------- 3\n\n");
    printf("Veuillez entrer la valeur de votre choix :\n");
    scanf("%d", &choix1);

    return choix1;
}

void display_file(FILE *tmp)
{   
    char car;
    while((car = fgetc(tmp)) != EOF){ 
        printf("%c", car);
    }
    printf("\n");
    fclose(tmp);
}
