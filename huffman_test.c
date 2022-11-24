#include "huffman.h"

int main()
{
    char *code1;
    FILE *f;
    f = fopen("compressed.txt", "r");

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
   
    ListeNoeud *newArbre;    
    newArbre = initListeNoe();
    
    Noeud *prems = malloc(sizeof (Noeud));
    prems->accroche = NULL;
    prems->branche_droite = NULL;
    prems->branche_gauche = NULL;
    prems->valeur = '\0';

    newArbre->premier = prems;

    occ = data_from_file(occ, f);  //bug ici !!!!
    printf("counter is : %d\n", occ->counter);

    //occ->dec = (int *)malloc(occ->counter * sizeof(int));
    code1 = (int *)malloc(occ->counter * sizeof(int));
    
    for(int i = 0; i < occ->counter; i++){
        code1[i] = 0;
    }

    strcpy(code1, occ->dec);
    for(int i = 0; i < occ->counter; i++){
        printf("code1[%d] = %c\n", i, code1[i]);
    }

    //char *entete = {"10A110R0P10B0T"};
    creerAbrDec(prems, code1);
    printf("lui %c\n", prems->branche_gauche->branche_droite->branche_droite->valeur);

    free(code1);
    fclose(f);

    return 0;
}
