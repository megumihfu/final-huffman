#include "huffman.h"

int main()
{
    int choix1, choix2, choix3;
    char *code1;
    char Temp[20], filename[20];

    FILE *f, *fp, *fd;
    f = fopen("compressed.txt", "r");
    fd = fopen("decompressed.txt", "r");

    Occurency *occ;
    occ = init(); 
    ListeNoeud *Arbre;
    Arbre = initListeNoe();

    while(1){
        choix1 = menu();
        
        switch(choix1){
            case 1 : 
                printf("\nSouhaitez vous compresser votre fichier [1] ou le décompresser [2]?\n");
                scanf("%d", &choix2);

                if(choix2 == 1){
                    f = freopen("compressed.txt", "w", f);
                    printf("\nVeuillez saisir le nom du fichier de votre choix : ");
                    scanf("%s", filename);

                    fp = fopen(filename, "r");
                    if(fp == NULL || f == NULL)
                        printf("Error, we cannot open your file\n");

                    occ = reading_file(occ, fp);
                    remplirChaine(Arbre, occ);  
                    Arbre->premier = triElements(Arbre->premier);
                    Arbre->premier = huff(Arbre->premier);

                    create_code1(occ, Arbre->premier, f);
                    sleep(2);
                    //fclose(fp);

                    printf("compression's done\n");
                    sleep(3);
                }

                if(choix2 == 2){
                    printf("decompression's done\n");
                    sleep(3);
                }
            break;

            case 2 : 
                printf("display to implement later\n");
            break;

            default : 
                printf("we will quit the program\n");
            return 0;
        }
    }
/*    
    Occurency *occ;
    occ = init(); 

    //1 --> occ = reading_file(occ, fp);
    size(occ); //on donne la nouvelle taille au compteur 
    printf("\nnbr : %d\n", occ->counter);
    
    ListeNoeud *Arbre;
    Arbre = initListeNoe();
    // 2 -->remplirChaine(Arbre, occ);   
    //3 --> Arbre->premier = triElements(Arbre->premier);
    
    //4 --> Arbre->premier = huff(Arbre->premier);
    //afficherListe(Arbre);
    /*occ = create_code2(occ, Arbre->premier, Temp);
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
    //printf("lui %c\n", prems->branche_gauche->branche_droite->branche_droite->valeur);
*/
    free(code1);
    free(occ->dec);
    fclose(f);
    fclose(fp);

    return 0;
}
