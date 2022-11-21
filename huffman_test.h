#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

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

typedef struct Occurency{
    char text[130];
    int occ_text[130];
    int counter;
    char code[130][20];
}Occurency;

////////////////////// FUNCTIONS //////////////////////

ListeNoeud *initListeNoe();

Noeud *huff(Noeud *Arbre);
Noeud* triElements(Noeud* liste);
void insererElement(ListeNoeud *liste, int freq, char val);
//void afficherListe(ListeNoeud *liste);
void remplirChaine(ListeNoeud *Arbre, Occurency *occ);
Noeud *concatener(Noeud *Arbre);
Occurency *create_code2(Occurency *tabs, Noeud *Arbre, char Temp[20]);
char* creerAbrDec(Noeud *oky,  char* bleu);
void creerFils(Noeud *parent);

Occurency *init();
Occurency *verif(Occurency *occ, char car);
Occurency *reading_file(Occurency *occ);
Occurency *size(Occurency *occ);
void compression(Occurency *occ);// char filename[20], FILE* fp, FILE *f)
void create_code1(Occurency *occ, Noeud *node);//, FILE *f);
/*
Noeud *init(); 
Noeud *reading_file(Noeud *noeud);
Noeud *add_element(Noeud *noeud, int nouv);
void display_list(Noeud *premier, Cellule *cel); 
*/
