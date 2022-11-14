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

    element->branche_droite = NULL;
    element->branche_gauche = NULL;
    element->accroche = liste->premier;
    liste->premier = element;
    liste->nbNoeud++;
}

void afficherListe(ListeNoeud *liste) // affiches la liste
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
/*
Noeud *trier(Noeud *element)
{// ici on va ranger les elemants dans l'ordre croisssant avant de les afficher...
 
   Noeud *temp, *temp1, *temp2;
   int min, a; 
   //temp2=(Noeud)malloc(sizeof(Noeud));
   //temp1=(Noeud)malloc(sizeof(Noeud));
   temp=element;
   
 
   while(temp!=NULL)
   {  
        
        min=temp->frequence;
        temp1=temp->accroche;           
 
        while(temp1!=NULL)
        {           
            
            if(min > temp1->frequence)
            {  
                temp2=temp1;      // le 3è tempraire me permet de savoir l'adresse de l'élement ou j'ai reperé le minimum pour faciliter l'échange
                min=temp2->frequence;
            }                
            temp1=temp1->accroche; 
        } //a ce niveau je sors de la 2iem boucle
        
        a=temp->frequence; //echange des 2 elements...
        
        temp->frequence=min;
        printf("ok\n");
        temp2->frequence=a;  
        printf("ok\n");     
        
        temp=temp->accroche;  
                              
    }          
 
    return element;
}
*/
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
        return Arbre;

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

void create_code1(Occurency *occ, Noeud *Arbre)
{
    FILE *f; 
    f = fopen("compressed.txt", "w");

    if(Arbre == NULL)
        fprintf(f, "0%c ", Arbre->valeur);

    else{
        fprintf(f, "1 "); //idk if it's needed
        create_code(occ, Arbre->branche_droite);
        fprintf(f, "1");
        cerate_code(occ, Arbre->branche_gauche);
    }
    fprintf(f, "\n");  //let the 3rd line for the binary compression
    fclose(f);
}

Occurency *create_code2(Occurency *tabs, Noeud *Arbre, char Temp[20]) //assigner les val 1 et 0 sur les branches pour le code binaire d'huffman
{
    int i = 0;

    if(Arbre->branche_droite != NULL) //branche droite -> valeur binaire 0
    {
        strncat(Temp, "0", 2);
        create_code2(tabs, Arbre->branche_droite, Temp);
    }
    
    if(Arbre->branche_gauche != NULL) //branche gauche -> valeur binaire 1
    {
        strncat(Temp, "1", 2);
        create_code2(tabs, Arbre->branche_gauche, Temp);
    }

    Arbre = branch_value(tabs, Arbre, Temp);
    
    for(size_t i = 0; i < 130; i++)
    {
        if(tabs->text[i] == Arbre->valeur)
            strcpy(tabs->code[i], Temp);
    }
    
    while(Temp[i] != '\0')
    {
        i++;
    }
   Temp[i-1] = '\0';
   
    return tabs; 
}

Occurency *init_occ(char filename[20])
{
    Occurency *occ = malloc(sizeof(*occ));
    FILE *fp;   
    fp = fopen(filename, "r");

    if(occ == NULL){
        printf("Memory allocation failed\n");
    }

    occ->counter = 130;

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
    bool checked;

    for(i = 0; i < occ->counter; i++){ //parcourt tt le tab text pr verifier si la valeur y est deja ou pas
        if(car == occ->text[i]){ 
            occ->occ_text[i] += 1;
            checked = true; //renvoie que la case a été check
            break;
        }

        else    
            checked = false; 
    }

    if(checked == false){ //si la valeur n'est pas dans le tab on l'ajoute
        for(i = 0; i < occ->counter; i++){ 
            if(occ->text[i] == 0){
                occ->text[i] = car; 
                occ->occ_text[i] = freq;
                break;
            }
        }
    } 

    return occ;
}
Occurency *reading_file(Occurency *occ, char filename[20])
{   
    FILE *fp;   
    fp = fopen(filename, "r");
    char tmp;

    if(fp == NULL)
        printf("Error, we cannot open your file\n");

    while((tmp = fgetc(fp)) != EOF){ 
        /*if(tmp == ' '){ //skip the spaces 
            continue;
        }*/
    
        verif(occ, tmp);
        //printf("%c", tmp); //test 
    }

    fclose(fp);

    return occ;
}

Occurency *set_counter(Occurency *occ) //pour pas avoir le reste du tableau pas rempli (qui est egal à 0 dcp)
{
    for(int i = 0; i < occ->counter; i++){
        if(occ->text[i] == 0){
            occ->counter = i;
        }
    }
    return occ;
}

int file_size(char filename[20]) //pour mettre en première ligne du fichier de compression 
{
    int size;
    FILE *fp;
    fp = fopen(filename, "r");

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    
    return size;
}

void *compression(Occurency *occ, char filename[20])
{
    char tmp;
    int size;
    FILE *fp;  
    FILE *f; 

    fp = fopen(filename, "r");
    f = fopen("compressed.txt", "w");

    if(fp == NULL || f == NULL)
        printf("Error, we cannot open your file\n");

    size = file_size(filename);
    fprintf(f, "%d\n", size);

    while((tmp = fgetc(fp)) != EOF){ 
        //printf("\ntmp = %c", tmp);

        for(int i = 0; i < occ->counter; i++){
            if(tmp == occ->text[i]){
                fprintf(f, "%s ", occ->code[i]);
            }
        }
    }

    fclose(fp);
    fclose(f);
}
