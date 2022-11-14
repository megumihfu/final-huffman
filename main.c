#include "huffman.h"

int main()
{
    char Temp[20], filename[20];
    int size;

    printf("Please enter the file you want : ");
    scanf("%s", filename);

    Occurency *occ;
    occ = init_occ(filename); 
    occ = reading_file(occ, filename);

    ListeNoeud *Arbre;
    Arbre = initListeNoe();
    remplirChaine(Arbre, occ);   
    Arbre->premier = triElements(Arbre->premier);

    printf("counter is : %d\n", occ->counter);
    
    Arbre->premier = huff(Arbre->premier);
    //afficherListe(Arbre);
    create_code1(occ, Arbre->premier);
    printf("first code is done\n");
    occ = create_code2(occ, Arbre->premier, Temp);
    compression(occ, filename); //compress the file using the dictionnary from the binary tree
    
    set_counter(occ); //set the counter of the array text and occ_text 
    printf("\nsize for the new tab is %d\n", occ->counter);
    
    for(int i = 0; i < occ->counter; i++){ //test 
        printf("car %c = code %s et son occ est %d\n", occ->text[i], occ->code[i], occ->occ_text[i]);
        //printf("caracter : %c\n", occ->text[i]);
        //printf("occurency : %d\n", occ->occ_text[i]);
        //printf("\n");
    }
    
    size = file_size(filename);
    printf("%d\n", size);

    return 0;
}
