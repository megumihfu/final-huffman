// C program to count occurrences in a linked list
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Cellule{ 
    int valeur; 
    int frequence; 
    struct cellule *suivant;
}cellule;

typedef struct Occurency{
    char text[130];
    int occ_text[130];
    int counter;
    //char code[130][10];
}Occurency;

typedef struct listeCellule {  
    int nbCellule;
    struct cellule *premier; 
}listeCellule;

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

Occurency *reading_file()
{   
    FILE *fp;   
    fp = fopen("dora.txt", "r");
    char tmp;

    if(fp == NULL)
        printf("Error, we cannot open your file\n");

    Occurency *occ;
    occ->counter = 0;

    while((tmp = fgetc(fp)) != EOF){
        occ->text[occ->counter] = tmp;
        //printf("%c", occ->text[i]); //test
        occ->counter++;
    }

    free(fp);

    return occ;
}


int main()
{
    Occurency *occ;
    occ = reading_file();

    for(int i = 0; i < occ->counter; i++){
        printf("%c", occ->text[i]);
    }

	return 0;
}
