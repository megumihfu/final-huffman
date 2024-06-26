#include "huffman.h"


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

    element->branche_droite = NULL;
    element->branche_gauche = NULL;
    element->accroche = liste->premier;
    liste->premier = element;
    liste->nbNoeud ++;
}

void afficherListe(ListeNoeud *liste) // affiches tout les avion d'une liste
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
}

void remplirChaine(ListeNoeud *Arbre, Occurency *occ)
{
    
    int i = 0;
    //remplir la liste avec chaque cellule, une valeur unique et son occurence
    //faire pointer la branche gauche du noeud sur NULL et la doite, sur le noeud accroche
    //les cellule elle meme pointe toute sur NULL
    while (occ->occ_text[i] != 0)
    {
        insererElement(Arbre, occ->occ_text[i], occ->text[i]);
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
                if( precedent == NULL )
                {
                    
                    premier = suivant;
                }

                else
                {
                    precedent->accroche = suivant;
                }

                element->accroche = suivant->accroche;
                suivant->accroche = element;
                //printf("yes boiii\n");
                

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
    } while( recommencer );
  
  // retourne la nouvelle liste
    return premier;
}
Noeud *concatener(Noeud *Arbre)
{
    if(Arbre == NULL)
    {
        return Arbre;
    }
    Noeud *temp, *temp1, *new;
    temp = Arbre;
    
    temp1 = Arbre->accroche;
    new = malloc(sizeof (Noeud));

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

void create_code1(Occurency *occ, Noeud *node, FILE *f)
{
    if(node == NULL) //if the tree doesnt exist, just exit the function
        return;

    if(node->branche_gauche == NULL && node->branche_droite == NULL){ //if the current node is the leaf
        fprintf(f, "0%c", node->valeur);
        printf("0%c", node->valeur);
    }

    if(node->branche_droite != NULL || node->branche_gauche != NULL){ //if it's the left branch, assign 0
        fprintf(f, "1");
        printf("1");
        create_code1(occ, node->branche_droite, f);
        create_code1(occ, node->branche_gauche, f);
    }
}



Occurency *create_code2(Occurency *tabs, Noeud *Arbre, char Temp[20]) //void ?
{
    
    if(Arbre->branche_droite != NULL)
    {
        strncat(Temp, "0", 2);
        create_code2(tabs, Arbre->branche_droite, Temp);
    }
    
    if(Arbre->branche_gauche != NULL)
    {
        strncat(Temp, "1", 2);
        create_code2(tabs, Arbre->branche_gauche, Temp);
    }
    
    for (size_t i = 0; i < 130; i++)
    {
        if(tabs->text[i] == Arbre->valeur)
        {
            strcpy(tabs->code[i], Temp);
        }

    }
    int i = 0;
    while(Temp[i] != '\0')
    {
        i++;
    }
   Temp[i-1] = '\0';
    return tabs;
    
    
}

Occurency *init() //rajouter le nom du fichier en parametre mais vazy à la fin
{
    Occurency *occ = malloc(sizeof(*occ));
    FILE *fp;   
    fp = fopen("file.txt", "r");

    if(occ == NULL){
        printf("Allocating memory failed\n");
    }

    fseek(fp, 0L, SEEK_END);
    occ->counter = ftell(fp);
    printf("%d = counter\n", occ->counter);

    for(int i = 0; i < occ->counter; i++){
        occ->text[i] = 0;
        occ->occ_text[i] = 0;
    }
    
    fclose(fp);

    return occ;
}
Occurency *verif(Occurency *occ, char car)
{
    int i, freq = 1;
    bool checked; //pas oublier de rajouter le #include <stdbool.h>

    for(i = 0; i < occ->counter; i++){ //parcourt tt le tab text pr verifier si la valeur y est deja ou pas
        if(car == occ->text[i]){ //si elle y est deja
            occ->occ_text[i] += 1; //incrémente sa freq
            checked = true; //renvoie que la case a été check
            break;
        }

        else    //si le caracter n'a pas été trouvé ds le tab 
            checked = false; //renvoie que la case n'est pas check
    }

    if(checked == false){ //si la valeur n'est pas dans le tab
        for(i = 0; i < occ->counter; i++){ //parcourt le tab jusqu'a une case vide
            if(occ->text[i] == 0){
                occ->text[i] = car; //ajoute le caracter à la case vide
                occ->occ_text[i] = freq; //incremente sa freq
                break;
            }
        }
    } 

    return occ;
}
Occurency *reading_file(Occurency *occ, FILE *fp)
{   
    //FILE *fp;   
    //fp = fopen("file.txt", "r");
    char tmp;

    while((tmp = fgetc(fp)) != EOF){ 
        verif(occ, tmp);
        printf("%c", tmp); //test 
    }

    return occ;
}
Occurency *size(Occurency *occ) //pour pas avoir le reste du tableau pas rempli (qui est constitué de 0 dcp)
{
    for(int i = 0; i < occ->counter; i++){
        if(occ->text[i] == 0){
            occ->counter = i;
        }
    }
    return occ;
}

void compression(Occurency *dico, char filename[20], FILE* fp, FILE *f)
{
    char tmp;
    //FILE *fp;

    //fp = fopen(filename, "r");

    while((tmp = fgetc(fp)) != EOF){ 
        for(int i = 0; i < dico->counter; i++){
            if(tmp == dico->text[i]){
                //fprintf(f, "%s", dico->code[i]);
                printf("on a donc :\n");
                printf("%s", dico->code[i]);
            }
        }
    }
}


///////////////////////////////////////
//decompression
Occurency *data_from_file(Occurency *occ, FILE *f)
{
    char tmp;
    int i = 0, j = 0;

    /*while((tmp = fgetc(f)) != '\n'){    
        i++;
    }*/

    printf("cursor's position is : %d\n", i+1);
    //fseek(f, i+1, SEEK_SET); //on se place sur la deuxième ligne 

    //tmp = fgetc(f);
    printf("avant while\n");
    occ->dec = (int *)malloc(occ->counter * sizeof(int));

    while((tmp = fgetc(f)) != EOF){
        //printf("tmp = %c\n",tmp);
        occ->dec[j] = tmp;
        printf("%c - ", occ->dec[j]);
        j++;
    }

    printf("\n");
    occ->counter = j; 
    printf("j counter is : %d\n", occ->counter);

    return occ;
}

void creerFils(Noeud *parent)
{    
    Noeud *droit = malloc(sizeof (Noeud));
    Noeud *gauche = malloc(sizeof (Noeud));

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

char* creerAbrDec(Noeud *actuel,  char* code1) // recrer l'arbre binaire a partir de l'entete dans le fichier compressé
{
        // 'code1' est la chaine de caractere qui comporte l'entete (c'est l'arbre encodé)
    if(*code1 == '1') //donc l'arbre a des fils
    {
        creerFils(actuel);
        code1 = creerAbrDec(actuel->branche_droite, code1 + 1);
        code1 = creerAbrDec(actuel->branche_gauche, code1 + 1);
    }
    else if(*code1 == '0')
    {
        code1 = code1 + 1;
        actuel->valeur = *code1;
        
    }
    
    return code1;
}

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
