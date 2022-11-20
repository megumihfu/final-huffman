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

////////////////////// FUNCTIONS //////////////////////
ListeCellule *initListeCel();
ListeNoeud *initListeNoe();

Noeud *huff(Noeud *Arbre);
Noeud* triElements(Noeud* liste);
void insererElement(ListeNoeud *liste, int freq, char val);
void afficherListe(ListeNoeud *liste);
void remplirChaine(ListeNoeud *Arbre, Dictionnary *dico);
Noeud *concatener(Noeud *Arbre);
//char *create_code1(Dictionnary *dico, Noeud *Arbre);
//void create_code1(Dictionnary *dico, Noeud *node);
//char *create_code1(Dictionnary *dico, Noeud *node, char code1[SIZE]);
//Dictionnary *create_code1(Dictionnary *dico, Noeud *node);
void create_code1(Dictionnary *dico, Noeud *node, FILE *f);
Dictionnary *create_code2(Dictionnary *tabs, Noeud *Arbre, char Temp[20]);
char* creerAbrDec(Noeud *actuel,  char* code1);
//Dictionnary *creerAbrDec(Noeud *actuel);//,  char* code1) // recrer l'arbre binaire a partir de l'entete dans le fichier compressé
void creerFils(Noeud *parent);

Dictionnary *init_dico();
Dictionnary *verif(Dictionnary *dico, char car);
Dictionnary *reading_file(Dictionnary *dico, FILE *fp);
//Dictionnary *set_counter(Dictionnary *dico, char tmp[]);
Dictionnary *set_counter(Dictionnary *dico);
//int set_counter(char tmp[]);
int file_size(FILE *fp);
void compression(Dictionnary *dico, char filename[20], FILE* fp, FILE *f);
Dictionnary *data_from_file(Dictionnary *dico, FILE *f);

int menu();
void display_file(FILE *tmp);
