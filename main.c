#include "huffman.h"

int main()
{
    int choix1, choix2, choix3, file_size;
    char *code1;
    char Temp[20], filename[20];

    FILE *f, *fp, *fd, *ft, *fc, *b;
    f = fopen("compressed.txt", "r");
    ft = fopen("code_tree.txt", "a");
    fd = fopen("decompressed.txt", "r");
    b = fopen("binary_code.bin", "wb");

    Dictionnary *occ;
    occ = init_occ(); 
    ListeNoeud *Arbre;
    Arbre = initListeNoe();

    //freopen("compressed.txt", "w", f); //erase all datas in compressed file
    freopen("decompressed.txt", "w", fd); //erase all datas in decompressed file

    while(1){
        choix1 = menu();
        
        switch(choix1){
            case 1 : 
                printf("\nSouhaitez vous compresser votre fichier [1] ou le décompresser [2]?\n");
                scanf("%d", &choix2);

                if(choix2 == 1){
                    freopen("compressed.txt", "w", f);
                    freopen("code_tree.txt", "w", ft); //erase all datas in those files
                    freopen("code_tree.txt", "a", ft); //now write also to the end of the file 
                    printf("\nVeuillez saisir le nom du fichier de votre choix : ");
                    scanf("%s", filename);

                    fp = fopen(filename, "r");
                    if(fp == NULL || f == NULL || ft == NULL)
                        printf("Error, we cannot open your file\n");

                    occ = reading_file(occ, fp);
                    remplirChaine(Arbre, occ);  
                    Arbre->premier = triElements(Arbre->premier);
                    Arbre->premier = huff(Arbre->premier);

                    occ = create_code2(occ, Arbre->premier, Temp);

                    pseudo_compression(occ, fp, filename, ft); //code binaire du texte -> 1ere ligne
                    create_code1(occ, Arbre->premier, ft); //code de l'arbre -> 2e ligne
                    sleep(2);

                    printf("\ncompression's done\n");
                    sleep(3);
                }

                if(choix2 == 2){
                    freopen("code_tree.txt", "r", ft); 
                    ListeNoeud *newArbre;    
                    newArbre = initListeNoe();
                    Noeud *prem = malloc(sizeof (Noeud));

                    prem->accroche = NULL;
                    prem->branche_droite = NULL;
                    prem->branche_gauche = NULL;
                    prem->valeur = '\0';
                    newArbre->premier = prem;

                    occ = data_from_file(occ, ft);
                    printf("final counter is : %d\n", occ->counter);

                    code1 = (int *)malloc(occ->counter * sizeof(int));
                    
                    /*initialize the code1 array*/
                    for(int i = 0; i < occ->counter; i++){
                        code1[i] = 0;
                    }

                    strcpy(code1, occ->dec);
                    creerAbrDec(prem, code1);
                    printf("lui %c\n", prem->branche_gauche->branche_droite->branche_droite->valeur);


                    printf("decompression's done\n");
                    sleep(10);
                }
            break;

            case 2 : 
                system("clear");
                freopen("compressed.txt", "r", f); //use w if u want to erase the data in it
                freopen("decompressed.txt", "r", fd);
                freopen("code_tree.txt", "r", ft);
                fp = fopen("file.txt", "r"); 

                printf("Vous pouvez afficher les fichiers txt suivants :\n");
                printf("- file.txt --------------- 1\n");
                printf("- compressed.txt --------- 2\n");
                printf("- decompressed.txt ------- 3\n");
                printf("- code_tree.txt ---------- 4\n");
                printf("Quel est votre choix ? ");
                scanf("%d", &choix3);

                switch (choix3){
                    case 1 :
                        system("clear");
                        display_file(fp); //display file
                        return 0;
                    break;

                    case 2 :
                        system("clear");
                        display_file(f); //display compressed file
                        return 0;
                    break;

                    case 3 :
                        system("clear");
                        display_file(fd); //display decompressed file
                        return 0;
                    break;

                    case 4 : 
                        system("clear");
                        display_file(ft);
                        return 0;
                    break;

                    default : 
                        printf("We didn't understant your choice, so please, try again : ");
                        //idk yet tbh, lets do it later
                    break;
                }                
            break;

            default : 
                printf("\nWe will quit the program...\n");
                sleep(3);
                system("clear");      
            return 0;
        }
    }
/*    
    Dictionnary *occ;
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