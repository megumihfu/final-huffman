#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#define SIZE 130

////////////////////// STRUCT ////////////////////////
typedef struct Cellule{
    char valeur; 
    int frequence; 
    struct Cellule *suivant;
}Cellule;

typedef struct ListeCellule {                   
    int nbCellule;
    struct Cellule *premier;
}ListeCellule;

typedef struct Noeud{ //notre liste 
    struct Noeud *branche_droite;
    struct Noeud *branche_gauche;
    struct Noeud *accroche;
    char valeur; 
    int frequence;
}Noeud;

typedef struct ListeNoeud{                    
    int nbNoeud;
    struct Noeud *premier;
}ListeNoeud;

typedef struct Dictionnary{
    char text[SIZE];
    int occ_text[SIZE];
    //char code1[SIZE];
    char code[SIZE][20];
    char dec[SIZE];
    int counter;
}Dictionnary;

//////////////////////////////////////////////////////////////////////////
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

    new->branche_droite = temp; 
    new->branche_gauche = temp1;  
    new->frequence = temp->frequence + temp1->frequence;
    new->accroche = temp1->accroche;
    new->valeur = '\0';
    temp->accroche = new;
    temp1->accroche = new;

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

void create_code1(Dictionnary *dico, Noeud *node, FILE *f)
{
    if(node == NULL) //if the tree doesnt exist, just exit the function
        return;

    if(node->branche_gauche == NULL && node->branche_droite == NULL){ //if the current node is the leaf
        fprintf(f, "0%c", node->valeur);
        printf("0%c", node->valeur);
    }

    if(node->branche_droite != NULL || node->branche_gauche != NULL){ //if it's the left branch, assign 0
        fprintf(f, "0");
        printf("1");
        create_code1(dico, node->branche_droite, f);
        create_code1(dico, node->branche_gauche, f);
    }
}

Dictionnary *create_code2(Dictionnary *tabs, Noeud *Arbre, char tmp[20]) //assigner les val 1 et 0 sur les branches pour le code binaire d'huffman
{
    if(Arbre->branche_droite != NULL) //branche droite -> valeur binaire 0
    {
        strncat(tmp, "0", 2);
        create_code2(tabs, Arbre->branche_droite, tmp);
    }
    
    if(Arbre->branche_gauche != NULL) //branche gauche -> valeur binaire 1
    {
        strncat(tmp, "1", 2);
        create_code2(tabs, Arbre->branche_gauche, tmp);
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
    fseek(f, i+1, SEEK_SET); //on se place sur la deuxième ligne 

    while((tmp = fgetc(f)) != '\n'){
        dico->dec[j] = tmp;
        printf("%c - ", dico->dec[j]);
        j++;
    }

    dico->counter = j; 
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

//////////////////////////////////////////////////////////////////////////////////////////////////
#include "huffman.h"

int main()
{
    char Temp[20], filename[20], fileName[20];
    int size, choix1, choix2, choix3;
    //char *code1, *tmp;

    //printf("Please enter the file you want : ");
    //scanf("%s", filename);
    
    FILE *fp; //pointer for the file where is our text
    FILE *f = fopen("compressed.txt", "a");  //pointer for the compressed file
    FILE *fd = fopen("decompressed.txt", "a");//pointer for the decompressed file
    //fp = fopen(filename, "r");
    //f = fopen("compressed.txt", "a");
    //fd = fopen("decompressed.txt", "a");

/*initialisation*/
    Dictionnary *dico;
    dico = init_dico(filename); 
    ListeNoeud *Arbre;
    Arbre = initListeNoe();

    freopen("compressed.txt", "w", f); //on efface le contenu des fichiers de compression et decompression
    freopen("decompressed.txt", "w", fd);

while(1){
    choix1 = menu();

    switch(choix1)
    {
        case 1 : 
            printf("\nSouhaitez vous compresser votre fichier [1] ou le décompresser [2]?\n");
            scanf("%d", &choix2);

            if(choix2 == 1)
            {  
                printf("\nVeuillez saisir le nom du fichier de votre choix : ");
                scanf("%s", filename);

                fp = fopen(filename, "r");
                    if(fp == NULL || f == NULL)
                        printf("Error, we cannot open your file\n");

                dico = reading_file(dico, fp);
                remplirChaine(Arbre, dico);   
                Arbre->premier = triElements(Arbre->premier);
                Arbre->premier = huff(Arbre->premier);
                size = file_size(fp);
                printf("file size if %d\n", size);
                fprintf(f, "%d\n", size);
                
                create_code1(dico, Arbre->premier, f);
                fprintf(f, "\n");

                dico = create_code2(dico, Arbre->premier, Temp); 
                printf("\nsize for the new tab is %d\n", dico->counter);
                compression(dico, filename, fp, f);   

                printf("Votre compression s'est bien effectuée. Vous allez être dirigé vers le menu\n");
                sleep(2);
                fclose(fp);
                //fclose(f);
                //system("clear");
            }

            if(choix2 == 2)
            {
                //appeler la fonction de décompression
                printf("Votre décompression s'est bien effectuée. Vous allez être dirigé vers le menu\n");
                sleep(2);
                system("clear");
            }            
            break;

        case 2 : 
            system("clear");
            freopen("compressed.txt", "r", f); //and w if u want to erase the data in it
            freopen("decompressed.txt", "r", fd);
            fp = fopen("file.txt", "r"); 

            printf("Vous pouvez afficher les fichiers txt suivants :\n");
            printf("- file.txt --------------- 1\n");
            printf("- compressed.txt --------- 2\n");
            printf("- decompressed.txt ------- 3\n");
            printf("Quel est votre choix ? ");
            scanf("%d", &choix3);

            switch (choix3){
                case 1 :
                    system("clear");
                    display_file(fp); //display file
                    return 0;
                break;

                case 2 :
                    system("clear");
                    display_file(f); //display compressed file
                    return 0;
                break;

                case 3 :
                    system("clear");
                    display_file(fd); //display decompressed file
                    return 0;
                break;
            }
        break;

        default :
            system("clear"); 
            printf("Vous allez quitter le programme");
            //sleep(2);
            //freopen("compressed.txt", "w", f); //on efface le contenu des fichiers de compression et decompression
            //freopen("decompressed.txt", "w", fd); 
            //fclose(f); //on ferme nos fichiers ouverts
            //fclose(fp);
            //fclose(fd);
        return 0;      
    }
}  

printf("Weshhhhh que tallll????\n");
sleep(5);
    /*Dictionnary *dico;
    dico = init_dico(filename); 
    dico = reading_file(dico, fp);

    ListeNoeud *Arbre;
    Arbre = initListeNoe();
    remplirChaine(Arbre, dico);   
    Arbre->premier = triElements(Arbre->premier);
    Arbre->premier = huff(Arbre->premier);
    //printf("oii my boiiii\n");
    //afficherListe(Arbre);
    //create_code1(dico, Arbre->premier);

    size = file_size(fp);
    printf("file size if %d\n", size);
    fprintf(f, "%d\n", size);
    
    fprintf(f, "1"); //because first node is always 1 in the tree
    create_code1(dico, Arbre->premier, f);
    fprintf(f, "\n");

    dico = create_code2(dico, Arbre->premier, Temp); 
    printf("\nsize for the new tab is %d\n", dico->counter);
    compression(dico, filename, fp, f);   
    //printf("our actual counter is : %d'''\n", dico->counter);
    //fclose(f);
    */

//DECOMPRESSION
 /*  freopen("compressed.txt", "r", f);
    if(f == NULL)
        printf("Error trying to reopen the compressed file with reading mode\n");

    dico = data_from_file(dico, f);
    //dico = set_counter(dico);
    printf("COUNTER IS SET AT : %d\n", dico->counter);
    //strcpy(code1, dico->dec);

    for(int i = 0; i < dico->counter; i++){
        code1[i] = dico->dec[i];
        printf("code1[%d] = %c | ", i, code1[i]);
        printf("dico->[%d] = %c\n", i, dico->dec[i]);
    }

    ListeNoeud *newArbre;    
    newArbre = initListeNoe();

    //printf("our actual counter is : %d''''\n", dico->counter);
    
    Noeud *prem = malloc(sizeof(Noeud));
    prem->accroche = NULL;
    prem->branche_droite = NULL;
    prem->branche_gauche = NULL;
    prem->valeur = '\0';
    newArbre->premier = prem;

    creerAbrDec(prem, code1);
    printf("lui %c\n", prem->branche_gauche->branche_droite->branche_droite->valeur);

    /*strcpy(code1, dico->dec);
    dico = set_counter(dico); 
    printf("dico->counter %d\n", dico->counter);
    //char *code1 = {"10A110R0P10B0T"};
    for(int i = 0; i < SIZE; i++){
        code1[i] = 0;
    }

    for(int i = 0; i < 30; i++){
       // printf("code1[%d] = %c\n", i, code1[i]);
        printf("dico->[%d] = %c\n", i, dico->dec[i]);
    }
   //strcpy(code1, dico->dec);

    for(int i = 0; i < 13; i++){
        printf("code1[%d] = %c\n", i, code1[i]);
    }

    ListeNoeud *newArbre;    
    newArbre = initListeNoe();

    //printf("our actual counter is : %d''''\n", dico->counter);
    
    Noeud *prem = malloc(sizeof(Noeud));
    prem->accroche = NULL;
    prem->branche_droite = NULL;
    prem->branche_gauche = NULL;
    prem->valeur = '\0';
    newArbre->premier = prem;

    creerAbrDec(prem, code1);
    printf("lui %c\n", prem->branche_gauche->branche_droite->branche_droite->valeur);           */

    //printf("our actual counter is : %d'''''\n", dico->counter);


    fclose(fp);
    //freopen("compressed.txt", "w", f); //when u dont need the value that were already compressed
    fclose(fd);
    fclose(f);
    return 0;
}
