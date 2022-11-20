#include "huffman.h"

int main()
{
    char Temp[20], filename[20], fileName[20];
    int size, choix1, choix2, choix3;
    //char *code1, *tmp;

    //printf("Please enter the file you want : ");
    //scanf("%s", filename);
    
    FILE *fp; //pointer for the file where is our text
    FILE *f = fopen("compressed.txt", "a");  //pointer for the compressed file
    FILE *fd = fopen("decompressed.txt", "a");//pointer for the decompressed file
    //fp = fopen(filename, "r");
    //f = fopen("compressed.txt", "a");
    //fd = fopen("decompressed.txt", "a");

/*initialisation*/
    Dictionnary *dico;
    dico = init_dico(filename); 
    ListeNoeud *Arbre;
    Arbre = initListeNoe();

while(1){
    choix1 = menu();

    switch(choix1)
    {
        case 1 : 
            printf("\nSouhaitez vous compresser votre fichier [1] ou le décompresser [2]?\n");
            scanf("%d", &choix2);

            if(choix2 == 1)
            {  
                printf("\nVeuillez saisir le nom du fichier de votre choix : ");
                scanf("%s", filename);

                fp = fopen(filename, "r");
                    if(fp == NULL || f == NULL)
                        printf("Error, we cannot open your file\n");

                dico = reading_file(dico, fp);
                remplirChaine(Arbre, dico);   
                Arbre->premier = triElements(Arbre->premier);
                Arbre->premier = huff(Arbre->premier);
                size = file_size(fp);
                printf("file size if %d\n", size);
                fprintf(f, "%d\n", size);
                
                fprintf(f, "1"); //because first node is always 1 in the tree
                create_code1(dico, Arbre->premier, f);
                fprintf(f, "\n");

                dico = create_code2(dico, Arbre->premier, Temp); 
                printf("\nsize for the new tab is %d\n", dico->counter);
                compression(dico, filename, fp, f);   

                printf("Votre compression s'est bien effectuée. Vous allez être dirigé vers le menu\n");
                sleep(2);
                fclose(fp);
                //fclose(f);
                //system("clear");
            }

            if(choix2 == 2)
            {
                //appeler la fonction de décompression
                printf("Votre décompression s'est bien effectuée. Vous allez être dirigé vers le menu\n");
                sleep(2);
                system("clear");
            }            
            break;

        case 2 : 
            system("clear");
            freopen("compressed.txt", "r", f); //and w if u want to erase the data in it
            freopen("decompressed.txt", "r", fd);
            fp = fopen("file.txt", "r"); 

            printf("Vous pouvez afficher les fichiers txt suivants :\n");
            printf("- file.txt --------------- 1\n");
            printf("- compressed.txt --------- 2\n");
            printf("- decompressed.txt ------- 3\n");
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
            }
        break;

        default :
            system("clear"); 
            printf("Vous allez quitter le programme\nFermeture des fichiers en cours...");
            sleep(2);
            freopen("compressed.txt", "w", f); //on efface le contenu des fichiers de compression et decompression
            freopen("decompressed.txt", "w", fd); 
            fclose(f); //on ferme nos fichiers ouverts
            fclose(fp);
            fclose(fd);
        return 0;      
    }
}    
    /*Dictionnary *dico;
    dico = init_dico(filename); 
    dico = reading_file(dico, fp);

    ListeNoeud *Arbre;
    Arbre = initListeNoe();
    remplirChaine(Arbre, dico);   
    Arbre->premier = triElements(Arbre->premier);
    Arbre->premier = huff(Arbre->premier);
    //printf("oii my boiiii\n");
    //afficherListe(Arbre);
    //create_code1(dico, Arbre->premier);

    size = file_size(fp);
    printf("file size if %d\n", size);
    fprintf(f, "%d\n", size);
    
    fprintf(f, "1"); //because first node is always 1 in the tree
    create_code1(dico, Arbre->premier, f);
    fprintf(f, "\n");

    dico = create_code2(dico, Arbre->premier, Temp); 
    printf("\nsize for the new tab is %d\n", dico->counter);
    compression(dico, filename, fp, f);   
    //printf("our actual counter is : %d'''\n", dico->counter);
    //fclose(f);
    */

//DECOMPRESSION
 /*  freopen("compressed.txt", "r", f);
    if(f == NULL)
        printf("Error trying to reopen the compressed file with reading mode\n");

    dico = data_from_file(dico, f);
    //dico = set_counter(dico);
    printf("COUNTER IS SET AT : %d\n", dico->counter);
    //strcpy(code1, dico->dec);

    for(int i = 0; i < dico->counter; i++){
        code1[i] = dico->dec[i];
        printf("code1[%d] = %c | ", i, code1[i]);
        printf("dico->[%d] = %c\n", i, dico->dec[i]);
    }

    ListeNoeud *newArbre;    
    newArbre = initListeNoe();

    //printf("our actual counter is : %d''''\n", dico->counter);
    
    Noeud *prem = malloc(sizeof(Noeud));
    prem->accroche = NULL;
    prem->branche_droite = NULL;
    prem->branche_gauche = NULL;
    prem->valeur = '\0';
    newArbre->premier = prem;

    creerAbrDec(prem, code1);
    printf("lui %c\n", prem->branche_gauche->branche_droite->branche_droite->valeur);

    /*strcpy(code1, dico->dec);
    dico = set_counter(dico); 
    printf("dico->counter %d\n", dico->counter);
    //char *code1 = {"10A110R0P10B0T"};
    for(int i = 0; i < SIZE; i++){
        code1[i] = 0;
    }

    for(int i = 0; i < 30; i++){
       // printf("code1[%d] = %c\n", i, code1[i]);
        printf("dico->[%d] = %c\n", i, dico->dec[i]);
    }
   //strcpy(code1, dico->dec);

    for(int i = 0; i < 13; i++){
        printf("code1[%d] = %c\n", i, code1[i]);
    }

    ListeNoeud *newArbre;    
    newArbre = initListeNoe();

    //printf("our actual counter is : %d''''\n", dico->counter);
    
    Noeud *prem = malloc(sizeof(Noeud));
    prem->accroche = NULL;
    prem->branche_droite = NULL;
    prem->branche_gauche = NULL;
    prem->valeur = '\0';
    newArbre->premier = prem;

    creerAbrDec(prem, code1);
    printf("lui %c\n", prem->branche_gauche->branche_droite->branche_droite->valeur);           */

    //printf("our actual counter is : %d'''''\n", dico->counter);


    fclose(fp);
    //freopen("compressed.txt", "w", f); //when u dont need the value that were already compressed
    fclose(fd);
    fclose(f);
    return 0;
}
