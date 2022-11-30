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

void remplirChaine(ListeNoeud *Arbre, Dictionnary *occ)
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

void create_code1(Dictionnary *occ, Noeud *node, FILE *ft)
{
    if(node == NULL) //if the tree doesnt exist, just exit the function
        return;

    if(node->branche_gauche == NULL && node->branche_droite == NULL){ //if the current node is the leaf
        fprintf(ft, "0%c", node->valeur);
        printf("0%c", node->valeur);
    }

    if(node->branche_droite != NULL || node->branche_gauche != NULL){ //if it's the left branch, assign 0
        fprintf(ft, "1");
        printf("1");
        create_code1(occ, node->branche_droite, ft);
        create_code1(occ, node->branche_gauche, ft);
    }
}

Dictionnary *create_code2(Dictionnary *tabs, Noeud *Arbre, char Temp[20]) //void ?
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

Dictionnary *init_occ() //rajouter le nom du fichier en parametre mais vazy à la fin
{
    Dictionnary *occ = malloc(sizeof(*occ));
    FILE *fp;   
    fp = fopen("file.txt", "r");

    if(occ == NULL){
        printf("Allocating memory failed\n");
    }

    //fseek(fp, 0L, SEEK_END);
    occ->counter = SIZE;
    printf("%d = counter\n", occ->counter);

    for(int i = 0; i < occ->counter; i++){
        occ->text[i] = 0;
        occ->occ_text[i] = 0;
    }
    
    fclose(fp);

    return occ;
}
Dictionnary *verif(Dictionnary *occ, char car)
{
    int i, freq = 1;
    bool checked; 

    for(i = 0; i < occ->counter; i++){ //parcourt tt le tab text pr verifier si la valeur y est deja ou pas
        if(car == occ->text[i]){ 
            occ->occ_text[i] += 1; 
            checked = true; 
            break;
        }

        else    //si le caractere n'a pas été trouvé ds le tab 
            checked = false; 
    }

    if(checked == false){ //si la valeur n'est pas dans le tab
        for(i = 0; i < occ->counter; i++){ 
            if(occ->text[i] == 0){
                occ->text[i] = car; //ajoute le caracter à la première case vide
                occ->occ_text[i] = freq; 
                break;
            }
        }
    } 

    return occ;
}
Dictionnary *reading_file(Dictionnary *occ, FILE *fp)
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
Dictionnary *size(Dictionnary *occ) //pour pas avoir le reste du tableau pas rempli (qui est constitué de 0 dcp)
{
    for(int i = 0; i < occ->counter; i++){
        if(occ->text[i] == 0){
            occ->counter = i;
        }
    }
    return occ;
}

void pseudo_compression(Dictionnary *dico, FILE *fp, char filename[20], FILE *ft)
{
    char tmp;
    fp = fopen(filename, "r");

    while((tmp = fgetc(fp)) != EOF){ 
        for(int i = 0; i < dico->counter; i++){
            if(tmp == dico->text[i]){
                fprintf(ft, "%s", dico->code[i]);
                printf("%s", dico->code[i]);
            }
        }
    }
    fprintf(ft, "\n");
}

/*void pseudo_bin_to_dec(Dictionnary *dico, FILE *b)
{
    b = fopen("binary_code.bin", "wb");
    fwrite(dico->code, sizeof(short int), dico->counter, b);

    while(nb_val_lues == TAILLE_BUF) 
    {
        nb_val_lues = fread( buffer, sizeof(short int), TAILLE_BUF, fic);

        for (i=0; i<dico->counter; i++) 
            printf( "%hd", buffer[i] );
    }

    fclose(b);
    //return dico;
}*/
///////////////////////////////////////
//decompression
int cursor_l1(char c, FILE *ft)
{
    int i = 0; 

    while((c = fgetc(ft)) != '\n'){    
        i++;
    }
    return i;
}

Dictionnary *data_from_file(Dictionnary *occ, FILE *ft)
{
    char tmp;
    int i = 0, j = 0;

    j = cursor_l1(tmp, ft);

    printf("cursor's position is : %d\n", i+1);
    fseek(ft, i+1, SEEK_SET); //on se place sur la deuxième ligne 

    //printf("avant while\n");
    occ->dec = (int *)malloc(occ->counter * sizeof(int));

    while((tmp = fgetc(ft)) != EOF){
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

/*void decompression(Dictionnary *dico, char *code1, FILE *ft)
{
    char c;
    int count; 
    ft = fopen("code_tree.txt", "r");

    count = cursor_l1(c, ft);
    printf("counter in decompression is = %d\n", count);
    
    while((c = fgetc(ft)) != '\n'){
        for(int i = 0; i < count; i++){
            if(code1[i] == '0'){
                code1[i] = c;
                printf("%s", code1[i]);
            }
        }   
    }

    fclose(ft);
}*/

char* creerAbrDec(Noeud *actuel,  char* code1) // recréer l'arbre binaire a partir de l'entete dans le fichier compressé
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


//////////////////////////////// MENU ///////////////////////////////////////
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