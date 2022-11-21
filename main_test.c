#include "huffman.h"

int main()
{

    Occurency *occ;
    occ = init(); 
    char Temp[20];
    occ = reading_file(occ);
    size(occ); //on donne la nouvelle taille au compteur 
    printf("\nnbr : %d\n", occ->counter);
    
    ListeNoeud *Arbre;
    Arbre = initListeNoe();
    remplirChaine(Arbre, occ);   
    Arbre->premier = triElements(Arbre->premier);
    
    Arbre->premier = huff(Arbre->premier);
    //afficherListe(Arbre);
    occ = create_code2(occ, Arbre->premier, Temp);
    int i = 0;
    while(occ->text[i] != '\0')
    {
        printf("compteur : %d -- ", i);
        printf("on a le caractere %c --> %s\n", occ->text[i], occ->code[i]);
        
        i++;
    }
    //compression(occ);
    //printf("1");
    create_code1(occ, Arbre->premier);
    printf("\n");

    //printf("nbr of node is : %d\n", count_node(Arbre->premier));
   
   /* ListeNoeud *newArbre;    
    newArbre = initListeNoe();
    
    Noeud *prems = malloc(sizeof (Noeud));
    prems->accroche = NULL;
    prems->branche_droite = NULL;
    prems->branche_gauche = NULL;
    prems->valeur = '\0';

    newArbre->premier = prems;

    char *entete = {"10A110R0P10B0T"};
    creerAbrDec(prems,  entete);
    printf("lui %c\n", prems->branche_gauche->branche_droite->branche_droite->valeur);*/

    return 0;
}
