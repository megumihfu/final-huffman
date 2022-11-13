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
    char code[130][10];
}Occurency;

/////////////////////////////////////////////////////////
Occurency *init(char filename[20])
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
        printf("%c", tmp); //wanna see the sentence from the file
    }

    fclose(fp);

    return occ;
}
/////////////////////////////////////////////////////////
Occurency *set_counter(Occurency *occ)
{
    for(int i = 0; i < occ->counter; i++){
        if(occ->text[i] == 0){
            occ->counter = i;
        }
    }
    return occ;
}
/////////////////////////////////////////////////////////
int file_size(char filename[20])
{
    int size;
    FILE *fp;
    fp = fopen(filename, "r");

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    
    return size;
}
/////////////////////////////////////////////////////////
Occurency *compression(Occurency *occ, char *code[], char filename[20])
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
        printf("\ntmp = %c", tmp);

        for(int i = 0; i < occ->counter; i++){
            if(tmp == occ->text[i]){
                fprintf(f, "%s ", code[i]);
            }
        }
    }

    fclose(fp);
    fclose(f);

    return occ;
}

/////////////////////////////////////////////////////////
int main()
{
    Occurency *occ;
    char filename[20]; //let the choice for the user 
    char *code[9] = {"0110", "0001", "0010", "0111", "0", "010", "011", "101", "100"}; //initialize only for testing our functions
    
    // choose the file
    printf("Please enter the file you want to compress : ");
    scanf("%s", filename);

    occ = init(filename); 
    occ = reading_file(occ, filename);

    set_counter(occ); //set the counter of the array text and occ_text
    printf("size for the new tab is %d\n", occ->counter);

    occ = compression(occ, code, filename); //compress the file using the dictionnary from the binary tree

    for(int i = 0; i < occ->counter; i++){ //test 
        printf("caracter : %c\n", occ->text[i]);
        printf("occurency : %d\n", occ->occ_text[i]);
        printf("\n");
    }

	return 0;
}
