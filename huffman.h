#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#define SIZE 130

////////////////////// STRUCT ////////////////////////
typedef struct Noeud Noeud;
struct Noeud{ //notre liste 
    Noeud *branche_droite;
    Noeud *branche_gauche;
    Noeud *accroche;
    char valeur; 
    int frequence;
};

typedef struct ListeNoeud ListeNoeud;  //on declare une liste, qui est enfaite une structure qui sauvegarde 
struct ListeNoeud {                     //le nombre d'avion dans la liste et qui pointe sur le premier element de la liste
    int nbNoeud;
    Noeud *premier;
};

typedef struct Dictionnary{
    char text[SIZE]; //all the caracter existing in the text file
    int occ_text[SIZE]; //nbr of occ for all the caracters
    //int counter_l1;
    int counter;//_l2; 
    char code[SIZE][20]; //pseudo binary code for each caracter
    short int dec_code[SIZE]; //decimal version of array 'code'
    char *dec; //array of code1 for creating the tree
}Dictionnary;

////////////////////// FUNCTIONS //////////////////////

ListeNoeud *initListeNoe();

Noeud *huff(Noeud *Arbre);
Noeud* triElements(Noeud* liste);
void insererElement(ListeNoeud *liste, int freq, char val);
//void afficherListe(ListeNoeud *liste);
void remplirChaine(ListeNoeud *Arbre, Dictionnary *occ);
Noeud *concatener(Noeud *Arbre);
Dictionnary *create_code2(Dictionnary *tabs, Noeud *Arbre, char Temp[20]);
char* creerAbrDec(Noeud *oky,  char* bleu);
void creerFils(Noeud *parent);

Dictionnary *init_occ();
Dictionnary *verif(Dictionnary *occ, char car);
Dictionnary *reading_file(Dictionnary *occ, FILE *fp);
Dictionnary *size(Dictionnary *occ);
void pseudo_compression(Dictionnary *dico, FILE *fp, char filename[20], FILE *ft);
//void create_code1(Dictionnary *occ, Noeud *node);//, FILE *f);
void create_code1(Dictionnary *dico, Noeud *node, FILE *f);
Dictionnary *data_from_file(Dictionnary *occ, FILE *f);
int menu();
void display_file(FILE *tmp);
void decompression(Dictionnary *dico, char *code1, FILE *ft);
int cursor_l1(char c, FILE *ft);
//void pseudo_bin_to_dec(Dictionnary *dico, FILE *b);