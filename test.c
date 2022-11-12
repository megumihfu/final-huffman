#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Cellule Cellule;
struct Cellule{
    int valeur; 
    int frequence; 
    Cellule *suivant;
};


typedef struct Noeud Noeud;
struct Noeud{ //notre liste 
    Noeud *branche_droite;
    Noeud *branche_gauche;
    Cellule *element;
};

typedef struct ListeCellule ListeCellule;  //on declare une liste, qui est enfaite une structure qui sauvegarde 
struct ListeCellule {                     //le nombre d'avion dans la liste et qui pointe sur le premier element de la liste
    int nbCellule;
    Cellule *premier;
};

typedef struct ListeNoeud ListeNoeud;  //on declare une liste, qui est enfaite une structure qui sauvegarde 
struct ListeNoeud {                     //le nombre d'avion dans la liste et qui pointe sur le premier element de la liste
    int nbNoeud;
    Noeud *premier;
};

typedef struct Occurency{
    char text[130];
    int occ_text[130];
    int counter;
    //char code[130][10];
}Occurency;
/*int count(struct Node* head, int search_for)
{
	struct Node* current = head;
	int count = 0;
	while (current != NULL) {
		if (current->data == search_for)
			count++;
		current = current->next;
	}
	return count;
}
listeCellule *init() //retourne la tete initialisée
{
    listeCellule *tete = malloc(sizeof(*tete));
    cellule *cel = malloc(sizeof(*cel));
    if(tete == NULL || cel == NULL)
        exit(-1);
    cel->valeur = 0; //doit init avec la premiere val du fichier 
    cel->frequence = 0;
    cel->suivant = NULL;
    tete->premier = cel;
    return tete;
}
void add_element(listeCellule *tete, int val, int freq)
{
    cellule *nouv_cel = malloc(sizeof(*nouv_cel));
    if(tete == NULL || nouv_cel == NULL)
        exit(-1);
    nouv_cel->valeur = val;
    nouv_cel->frequence = freq;
    nouv_cel->suivant = tete->premier;
    tete->premier = nouv_cel;
    //printf("element ajouté à la liste : %d, et sa frequence est %d\n", nouv_cel->valeur, freq);
}
void display_list(listeCellule *liste, cellule *cel)
{
    cel = liste->premier;
        while(cel != NULL){
            printf("%d | %d -- ", cel->valeur, cel->frequence);
            cel = cel->suivant;
        }
}
void add_occ_list(listeCellule *tete, int array[], int val, int counter) 
{
    int freq = 0;
    for(int i = 0; i < counter; i++){
            if(val == array[i]){
                freq++;
            }
    } 
    printf("val = %d and freq = %d\n", val, freq);
    add_element(tete, val, freq);
}
void supp_occ(int array[], int val, int counter)
{
    int count = 0, idk = 0;
    int tmp[20];
    for(int i = 0; i < counter; i++){
        if(val == array[i])
            continue;
        else{
            tmp[idk] = val;
            printf("tmp[%d] = %d\n", idk, tmp[val]);
            idk++;
        }
    }
    printf("idk = %d\n", idk);
}
*/
/////////////////////////////////////////////////////////
Occurency *init()
{
    Occurency *occ = malloc(sizeof(*occ));
    FILE *fp;   
    fp = fopen("file.txt", "r");

    if(occ == NULL){
        printf("Memory allocation failed\n");
    }

    occ->counter = 130;
    printf("%d = counter\n", occ->counter);

    for(int i = 0; i < occ->counter; i++){
        occ->text[i] = 0;
        occ->occ_text[i] = 0;
    }

    fclose(fp);

    return occ;
}


/////////////////////////////////////////////////////////
Occurency *verif(Occurency *occ, char car)
{
    int i, freq = 1;
    bool checked;

    for(i = 0; i < occ->counter; i++){
        if(car == occ->text[i]){
            occ->occ_text[i] += 1;
            checked = true;
            break;
        }

        else    
            checked = false;
    }

    if(checked == false){
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
/////////////////////////////////////////////////////////
Occurency *reading_file(Occurency *occ)
{   
    FILE *fp;   
    fp = fopen("file.txt", "r");
    char tmp;

    if(fp == NULL)
        printf("Error, we cannot open your file\n");

    while((tmp = fgetc(fp)) != EOF){ 
        /*if(tmp == ' '){ //skip the spaces 
            continue;
        }*/
        
        verif(occ, tmp);
        printf("%c", tmp); //wanna see the sentence from the file
    }

    fclose(fp);

    return occ;
}
/////////////////////////////////////////////////////////
Occurency *size(Occurency *occ)
{
    for(int i = 0; i < occ->counter; i++){
        if(occ->text[i] == 0){
            occ->counter = i;
        }
    }
    return occ;
}
/////////////////////////////////////////////////////////
Occurency *progressive_sort(Occurency *occ) //order the values 
{
    int i, j, tmp2;
    char tmp1;

    for(i = 0; i < occ->counter-1; i++){
        for(j = i+1; j < occ->counter; j++){
            if(occ->occ_text[i] < occ->occ_text[j]){
                tmp1 = occ->text[i]; /*simultaneously*/ tmp2 = occ->occ_text[i];
                occ->text[i] = occ->text[j]; /*simultaneously*/ occ->occ_text[i] = occ->occ_text[j];
                occ->text[j] = tmp1; /*simultaneously*/ occ->occ_text[j] = tmp2;
            }
        }
    }
    
    return occ;
}

/////////////////////////////////////////////////////////
int main()
{
    Occurency *occ;
    occ = init();
    int i;

    for(i = 0; i < occ->counter; i++){
        occ->occ_text[i] == 0; 
        occ->text[i] == 0;
        }

    occ = reading_file(occ);
    size(occ);
    printf("size for the new tab is %d\n", occ->counter);

 
    for(i = 0; i < occ->counter; i++){ //test to see our arrays
        printf("caracter : %c\n", occ->text[i]);
        printf("occurency : %d\n", occ->occ_text[i]);
        printf("\nn");
    }

	return 0;
}
