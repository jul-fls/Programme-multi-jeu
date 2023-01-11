#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
//Variables des scores
float scorejoueur = 0; //declaration de la variable qui stocke le score du joueur
float scorepc = 0; //declaration de la variable qui stocke le score du pc/robot

const int maxcaractersforpseudo = 20; //definition de la constante maxcaractersforpseudo qui défini le nombre de caractères max pour le pseudoi (oui j'avais pas d'idées de nom de variable)
char name[20]; //declaration du tableau de string "name" de 20 caractères comme le nb de caractères pour le pseudo, tiens, comme par hasard ;-)

int init(){ //fonction init qui permet d'initialiser du code uniquement au début du programme
    for(int i = 0;i<maxcaractersforpseudo+1;i++){ //pour i allant de 0 à l'infini jusqu'à ce qu'i soit égale au nombre de caractères max pour le pseudo, cela permet d'initialiser le tableau de caractères "name" de '\n' avant de l'utiliser 
        name[i]='\n'; //on remplace le contenu du tableau de caractères "name" à l'index correspondant à la valeur de i par '\n' cela permettra de savoir que le pseudo est terminé
    }
}

int scores(); //prototype de la fonction scores
int menu(); //prototype de la fonction menu
char os; //variable pour stocker l'os utilisé pour éxécuter des commandes spécifiques comme l'effacement de l'écran

int clearscreen(){ //fonction permettant d'effacer l'écran de manière native sur chaque plateforme
    if(os=='w'){
        system("cls"); //clear console pour windows
        return 0; //on retourne 0 pour indiquer que tout s'est bien passé
    }else if(os=='l'){
        system("clear"); //clear console pour linux et mac os
        return 0; //on retourne 0 pour indiquer que tout s'est bien passé
    }else{
        return 1; //on retourne 1 pour indiquer qu'il y a eu une erreur
    }
}

int pause(){ //fonction pause permettant d'effectuer une pause console de manière native sur chaque plateforme
    if(os=='w'){
        system("pause"); //pause console pour windows
            return 0; //on retourne 0 pour indiquer que tout s'est bien passé
    }else if(os=='l'){
        system("read -p 'Appuyez sur une touche pour continuer...' var1"); //pause console pour linux et mac os
            return 0; //on retourne 0 pour indiquer que tout s'est bien passé
    }else{
        return 1; //on retourne 1 pour indiquer qu'il y a eu une erreur
    }
}

int loading(int duration){ //fonction permettant d'afficher un compte à rebours pour laisser une information affiché à l'écran un certain temps
    for(int i=duration;i>0;i--){ //pour i allant de la durée passée comme parametre jusqu'à ce que i soit égal à 1, on décrémente i
        printf("%d...",i); //on affiche la valeur de i suivi de "..."
        fflush(stdout); //instruction permettant d'afficher le contenu du buffer de sortie (stdout) car la fonction sleep juste après bloque l'affichage du contenu du buffer avant la fin
        sleep(1); //on attends 1 seconde
    }
    return 0; //on retourne 0 pour indiquer que tout s'est bien passé
}

int getsizeofname(){ //fonction qui retourne le nb de caractères du pseudo du joueur
    int size; //declaration de la variable size
    for(size = 0;size<maxcaractersforpseudo;size++){ //pour size allant de 0 à l'infini jusqu'à ce qu'elle soit égale à maxcaractersforpseudo (oui j'avais pas d'idées de nom de variable)
        if(name[size]=='\n'){ //si le contenu du tableau de caractères "name" à l'index correspondant à la valeur de size est "\n" cela signifie que le pseudo est terminé
            break; //donc on sort de la boucle et on arrete de compter le nb de caractères du pseudo
        }
    }
    size-=1; //on decremente la taille de 1 car on a commencé à compter à 0 et non pas à 1
    return size; //on retourne la valeur de size
}
int choosename(){ //fonction qui permet à l'utilisateur de choisir son pseudo
    clearscreen(); //on efface l'écran
    printf("Quel pseudo souhaites-tu ? (20 caracteres maximum)\nChoix: "); //on lui demande le pseudo qu'il souhaite
    scanf("%20s",&name); //on recupere son pseudo (uniquement les 20 premiers caractères) en tant que string que l'on vient stocker dans le tableau de caractères "name"
    printf("\nParfait %s, ton nom est sauvegarde !\n",name); //on informe l'utilisateur
    loading(5); //compte à rebours de 5 secondes
    menu(); //on affiche le menu
}

int detectionos(){ //fonction detectionos permettant à l'utilisateur de spécifier sur quelle plateforme il se trouve
    if(!system("cls")){ //retourne 1 si ce n'est pas la bonne plateforme
        os='w'; //cela signifie que l'on se trouve sur windows
    }else{
        os='l'; //cela signifie que l'on se trouve sur linux ou macos
    }
    choosename(); //on affiche le menu du choix du pseudo
}

int plusoumoins(){ //fonction qui permet de lancer une partie du jeu + ou -
    srand(time(NULL)); //genere une seeed aleaoire pour le nb mystère
    int nbrandom = rand() % 100; //genere un nb random entre 0 et 100
    int nb = -1; //valeur par defaut du nb choisi par l'utilisateur
    int tentatives = 0; //nb de tentatives
    char term; //creation de la variable qui contiendra le caractère de fin de saisie (normalement le '\n')
    clearscreen();
    printf("                  /$$$$$$  /$$   /$$              \n"); //Magnigique Ascii Art :-)
    printf("    /$$          /$$__  $$| $$  | $$              \n");
    printf("   | $$         | $$  \\ $$| $$  | $$              \n");
    printf(" /$$$$$$$$      | $$  | $$| $$  | $$       /$$$$$$\n");
    printf("|__  $$__/      | $$  | $$| $$  | $$      |______/\n");
    printf("   | $$         | $$  | $$| $$  | $$              \n");
    printf("   |__/         |  $$$$$$/|  $$$$$$/              \n");
    printf("                 \\______/  \\______/               \n");
    loading(5); //compte à rebours de 5 secondes
    clearscreen(); //on efface l'écran
    printf("%s cherche le nombre que j'ai choisi entre 0 et 100:\nChoix: ",name); //on demande le choix de l'utilisateur
    while(nb != nbrandom){ //tant que l'utilisateur n'as pas trouvé le bon nombre
        if(scanf("%d%c", &nb, &term) != 2 || term != '\n'){ //on recupere son choix et on le stocke dans la variable nb tout en vérifiant que l'entrée est un bien un chiffre terminée par un retour à la ligne 
            clearscreen(); //on efface l'écran
            printf("%s tu as fait un choix invalide !\nLe programme s'arrete !\n",name); //on informe l'utilisateur
            exit(1); //on quitte avec le code d'erreur 1 pour signifier qu'il y a eu un pb
        }else if(nb <0 || nb > 100){ //si le nombre entrée n'est pas dans la bonne plage
                clearscreen(); //on efface l'écran
                printf("%s tu as fait un choix invalide !\nLe programme s'arrete !\n",name); //on informe l'utilisateur
                exit(1); //on quitte avec le code d'erreur 1 pour signifier qu'il y a eu un pb
            }
        tentatives++; //on incremente la variable tentatives
        if(nb < nbrandom){ //si le nb mystère est supérieur
            clearscreen(); //on efface l'écran
            printf("\n    /$$   %d\n",tentatives); //on affiche la premièr ligne de l'ascii art avec le nb de tentatives en haut à droite
            printf("   | $$   \n"); //Magnigique Ascii Art :-)
            printf(" /$$$$$$$$\n");
            printf("|__  $$__/\n");
            printf("   | $$   \n");
            printf("   |__/   \n");
        }else if(nb > nbrandom){ //si le nb mystère est inférieur
            clearscreen(); //on efface l'écran
            printf("\n /$$$$$$ %d\n",tentatives); //on affiche la premièr ligne de l'ascii art avec le nb de tentatives en haut à droite
            printf("|______/\n"); //Magnigique Ascii Art :-)
        }
    }
    scorejoueur = 100.0 / tentatives; //le score du joueur correspond à 100 / par le nombre de tentatives
    printf("Bravo %s tu as trouve le nombre mystere en %d tentatives !\n",name,tentatives);
    printf("  /$$$$$$   /$$$$$$ %d\n",tentatives); //on affiche la premièr ligne de l'ascii art avec le nb de tentatives en haut à droite
    printf(" /$$__  $$ /$$__  $$\n"); //Magnigique Ascii Art :-)
    printf("| $$  \\__/| $$  \\__/\n");
    printf("| $$ /$$$$| $$ /$$$$\n");
    printf("| $$|_  $$| $$|_  $$\n");
    printf("| $$  \\ $$| $$  \\ $$\n");
    printf("|  $$$$$$/|  $$$$$$/\n");
    printf(" \\______/  \\______/ \n");
    loading(5); //compte à rebours de 5 secondes
    scores(0); //on affiche les scores et le 0 signifie "jeu non multijoueurs" car le robot (le programme) ne peut ni gagner ni perdre, il se contente seulement de generer le nb mystère
    loading(5); //compte à rebours de 5 secondes
    menu(); //on affiche le menu
}

int pfc(){ //Fonction permettant de lancer une partie de pierre feuille ciseaux
    clearscreen(); //on efface l'écran
    printf(" /$$$$$$$ /$$$$$$/$$$$$$$$/$$$$$$$ /$$$$$$$ /$$$$$$$$         \n"); //Magnigique Ascii Art :-)
    printf("| $$__  $|_  $$_| $$_____| $$__  $| $$__  $| $$_____/         \n");
    printf("| $$  \\ $$ | $$ | $$     | $$  \\ $| $$  \\ $| $$               \n");
    printf("| $$$$$$$/ | $$ | $$$$$  | $$$$$$$| $$$$$$$| $$$$$            \n");
    printf("| $$____/  | $$ | $$__/  | $$__  $| $$__  $| $$__/            \n");
    printf("| $$       | $$ | $$     | $$  \\ $| $$  \\ $| $$               \n");
    printf("| $$      /$$$$$| $$$$$$$| $$  | $| $$  | $| $$$$$$$$         \n");
    printf("|__/     |______|________|__/  |__|__/  |__|________/         \n");
    printf("                                                              \n");
    printf(" /$$$$$$$$/$$$$$$$$/$$   /$$/$$$$$$/$$      /$$      /$$$$$$$$\n");
    printf("| $$_____| $$_____| $$  | $|_  $$_| $$     | $$     | $$_____/\n");
    printf("| $$     | $$     | $$  | $$ | $$ | $$     | $$     | $$      \n");
    printf("| $$$$$  | $$$$$  | $$  | $$ | $$ | $$     | $$     | $$$$$   \n");
    printf("| $$__/  | $$__/  | $$  | $$ | $$ | $$     | $$     | $$__/   \n");
    printf("| $$     | $$     | $$  | $$ | $$ | $$     | $$     | $$      \n");
    printf("| $$     | $$$$$$$|  $$$$$$//$$$$$| $$$$$$$| $$$$$$$| $$$$$$$$\n");
    printf("|__/     |________/\\______/|______|________|________|________/\n");
    printf("                                                              \n");
    printf("  /$$$$$$ /$$$$$$ /$$$$$$ /$$$$$$$$ /$$$$$$ /$$   /$$/$$   /$$\n");
    printf(" /$$__  $|_  $$_//$$__  $| $$_____//$$__  $| $$  | $| $$  / $$\n");
    printf("| $$  \\__/ | $$ | $$  \\__| $$     | $$  \\ $| $$  | $|  $$/ $$/\n");
    printf("| $$       | $$ |  $$$$$$| $$$$$  | $$$$$$$| $$  | $$\\  $$$$/ \n");
    printf("| $$       | $$  \\____  $| $$__/  | $$__  $| $$  | $$ >$$  $$ \n");
    printf("| $$    $$ | $$  /$$  \\ $| $$     | $$  | $| $$  | $$/$$/\\  $$\n");
    printf("|  $$$$$$//$$$$$|  $$$$$$| $$$$$$$| $$  | $|  $$$$$$| $$  \\ $$\n");
    printf(" \\______/|______/\\______/|________|__/  |__/\\______/|__/  |__/\n");
    loading(5); //compte à rebours de 5 secondes
    clearscreen(); //on efface l'écran
    printf("Les regles sont les suivantes:"); //affichage des regles pour que les non inites puissent jouer
    printf("\n- La pierre gagne contre les ciseaux");
    printf("\n- La feuille gagne contre la pierre");
    printf("\n- Les ciseaux gagne contre la feuille");
    printf("\n\n%s a combien de points souhaites-tu que la partie se termine ?\nChoix: ",name); //demande de la longueur de la partie
    int longueurpartiepfc; //creation de la variable qui contiendra la longueur de la partie
    char term; //creation de la variable qui contiendra le caractère de fin de saisie (normalement le '\n')
    if(scanf("%d%c", &longueurpartiepfc, &term) != 2 || term != '\n'){ //on recupere son choix et on le stocke dans la variable longueurpartiepfc tout en vérifiant que l'entrée est un bien un chiffre terminée par un retour à la ligne 
        clearscreen(); //on efface l'écran
        printf("%s tu as fait un choix invalide !\nLe programme s'arrete !\n",name); //on informe l'utilisateur
        exit(1); //on quitte avec le code d'erreur 1 pour signifier qu'il y a eu un pb
    }else if(longueurpartiepfc <1){ //si le nombre entrée n'est pas dans la bonne plage
        clearscreen(); //on efface l'écran
        printf("%s tu as fait un choix invalide !\nImpossible de faire moins de 1 partie !\n",name); //on informe l'utilisateur
        exit(1); //on quitte avec le code d'erreur 1 pour signifier qu'il y a eu un pb
    }
    printf("\nLa partie se terminera automatiquement lorsque %s ou le robot atteindra le score de %d points\n",name,longueurpartiepfc); //confirmation de la longueur de la partie
    loading(5); //compte à rebours de 5 secondes
    clearscreen(); //on efface l'écran
    //Debut du programme du pierre feuille ciseau
    srand(time(NULL)); //genere une seeed aleaoire pour le choix de l'action du pc/robot
    char choices[3]={'p','f','c'}; //tableau contenant les choix classés par index (0 = pierre, 1 = feuille, 2 = ciseaux)
    char char_actionchoisiejoueur; //creation de la variable qui contiendra l'action choisie par le joueur sous forme de caractère pour l'affichage à l'écran
    int int_actionchoisiejoueur; //creation de la variable qui contiendra l'action choisie par le joueur sous forme de chiffre pour le traitement
    while(scorejoueur < longueurpartiepfc && scorepc < longueurpartiepfc){ //tant que le score du joueur et que le score du pc (le robot) est inférieure à la longueur de la partie, on continue la partie
        int int_actionchoisiepc = rand() % 3; //l'action choisie par le pc (le robot) est un nb aléatoire entre 0 et 2 compris, symbolisé en maths par [0;2]
        char char_actionchoisiepc = choices[int_actionchoisiepc]; //le choix du pc sosu forme de caractère correspond à la valeur du choix du pc à l'index correspondant au choix numérique qu'il a fait auparavant
        startpfc: clearscreen(); //on mets un label "startpfc" sur cette ligne permettant de revenir à cette ligne directement depuis le reste du programme via l'instruction goto et on efface l'écran
        printf("%s choisi une action :\nPierre [p]\nFeuille [f]\nCiseaux [c]\nChoix: ",name); //on demande au joueur son choix d'action
        scanf(" %c",&char_actionchoisiejoueur); //on recupere ce choix et on le stocke dans la variable char_actionchoisiejoueur
        if(char_actionchoisiejoueur=='p' || char_actionchoisiejoueur=='f' || char_actionchoisiejoueur=='c'){ //si le contenu de la variable est correct (p,f ou c)
            for(int i=0;i<=2;i++){ //on cherche l'index correspondant au choix alphabetique
                if(char_actionchoisiejoueur==choices[i]){ //si le caractère choisi et la valeur à l'index i correspond, alors...
                    int_actionchoisiejoueur = i; //on stocke la valeur i (la position dans le tablau) dans la variable int_actionchoisiejoueur
                }
            }
        }else{ //si le contenu de la variable choix d'action est incorrect (l'utilisateur a rentré autre chose que p,f ou c) alors...
            printf("\n%s tu as fait un choix incorrect, merci de recommencer\n"); //on lui demande de recommencer
            fflush(stdin); //on efface le buffer d'entrée au cas où il aurait entré plusieurs caractères
            loading(1); //on affiche un compte à rebours de 1 seconde
            goto startpfc; //on repars à la ligne qui comporte le label "startpfc"
        }
        if(int_actionchoisiejoueur == int_actionchoisiepc){ //si on as le meme choix pour le pc (le robot) et le joueur
            //match nul
            printf("\nVous avez tout les 2 choisi la meme chose\n"); //on informe l'utilisateur que c'est une manche nulle
            printf("\nManche nulle, personne ne marque de points\n");
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }else if(int_actionchoisiejoueur == 0 && int_actionchoisiepc == 1){ //si le joueur choisi la pierre et le pc/robot la feuille
            //le robot gagne, le joueur perds
            scorepc++;  //on incremente le score du pc/robot
            printf("\n%s a choisi la pierre, le robot quant a lui a choisi la feuille\n",name);
            printf("\n%s a perdu, le robot gagne 1 pts !\n",name);
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }else if(int_actionchoisiejoueur == 1 && int_actionchoisiepc == 0){ //si le joueur choisi la feuille et le pc/robot la pierre
            //le joueur gagne, le robot perds
            scorejoueur++; //on incremente le score du joueur
            printf("\n%s a choisi la feuille, le robot quant a lui a choisi la pierre\n",name);
            printf("\n%s a gagne, tu gagnes 1 pts !\n",name);
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }else if(int_actionchoisiejoueur == 0 && int_actionchoisiepc == 2){ //si le joueur choisi la pierre et le pc/robot le ciseaux
            //le joueur gagne, le robot perds
            scorejoueur++; //on incremente le score du joueur
            printf("\n%s a choisi la pierre, le robot quant a lui a choisi le ciseaux\n",name);
            printf("\n%s a gagne, tu gagnes 1 pts !\n",name);
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }else if(int_actionchoisiejoueur == 2 && int_actionchoisiepc == 0){ //si le joueur choisi le ciseaux et le pc/robot la pierre
            //le joueur perds, le robot gagne
            scorepc++; //on increment le score du pc/robot
            printf("\n%s a choisi le ciseaux, le robot quant a lui a choisi la pierre\n",name);
            printf("\n%s a perdu, le robot gagne 1 pts !\n",name);
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }else if(int_actionchoisiejoueur == 1 && int_actionchoisiepc == 2){ //si le joueur choisi la feuille et le pc/robot le ciseaux
            //le joueur perds, le robot gagne
            scorepc++; //on increment le score du joueur
            printf("\n%s a choisi la feuille, le robot quant a lui a choisi le ciseaux\n",name);
            printf("\n%s a perdu, le robot gagne 1 pts !\n",name);
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }else if(int_actionchoisiejoueur == 2 && int_actionchoisiepc == 1){ //si le joueur choisi le ciseaux et le pc/robot la feuille
            //le joueur gagne, le robot perds
            scorejoueur++; //on increment le score du joueur
            printf("\n%s a choisi le ciseaux, le robot quant a lui a choisi la feuille\n",name);
            printf("\n%s a gagne, tu gagnes 1 pts !\n",name);
            loading(3); //on affiche un compte à rebours de 3 secondes
            scores(1); //on affiche les scores en précisant qu'il s'agit d'un jeu multijoueur (le pc / robot) peut gagner / perdre
            loading(2); //on affiche un compte à rebours de 2 secondes
            clearscreen(); //on efface l'écran
        }
    }
    if(scorejoueur>=longueurpartiepfc){ //si le score du joueur est supérieur ou égal à la longueur de la partie
        printf("%s a gagne contre le robot avec %4.1f pts contre %4.1f pts pour le robot !\n",name,scorejoueur,scorepc); //on informe l'utilisateur du résultat de la partie
        loading(5); //on affiche un compte à rebours de 5 secondes
        menu(); //on affiche le menu
    }else if(scorepc>=longueurpartiepfc){ //si le score du pc/robot est supérieur ou égal à la longueur de la partie
        printf("%s a perdu contre le robot avec %4.1f pts contre %4.1f pts pour le robot !\n",name,scorejoueur,scorepc); //on informe l'utilisateur du résultat de la partie
        loading(5); //on affiche un compte à rebours de 5 secondes
        menu(); //on affiche le menu
    }
}

int scores(int multi){ //Fonction permettant d'afficher les scores
    clearscreen(); //on efface l'écran
    printf("#");
    if(getsizeofname()%2==0){ //le nombre de caractère du pseudo est pair
        if(multi==0){ //il s'agit d'un jeu solo (le pc/robot ne peut ni gagner ni perdre)
            int nbdecaracteresdechaquecotedupseudo = ((maxcaractersforpseudo-getsizeofname())/2)-1; //on défini le nb de caractères '#' a ecrire avant et après le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' avant le pseudo
                printf("#");
            }
            printf(" %s ",name); //permet d'afficher le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' après le pseudo
                printf("#");
            }
            printf("#\n");
            printf("#                    #\n");
            printf("#       %4.1f         #\n",scorejoueur);  //on affiche le score du joueur et du pc/robot avec un total de 4 caractères, 2 pour la partie entière, le point et 1 pour la partie décimale
            printf("#        PTS         #\n"); //on affiche "PTS"
            printf("#                    #\n");
            printf("######################\n");
        }else{ //il s'agit d'un jeu multi joueur (le pc/robot peut gagner/perdre)
            int nbdecaracteresdechaquecotedupseudo = ((maxcaractersforpseudo-getsizeofname())/2)-1; //on défini le nb de caractères '#' a ecrire avant et après le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' avant le pseudo
                printf("#");
            }
            printf(" %s ",name); //permet d'afficher le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' après le pseudo
                printf("#");
            }
            printf("## ROBOT ##\n");
            printf("#                    #         #\n");
            printf("#       %4.1f         #  %4.1f   #\n",scorejoueur,scorepc);  //on affiche le score du joueur et du pc/robot avec un total de 4 caractères, 2 pour la partie entière, le point et 1 pour la partie décimale
            printf("#        PTS         #   PTS   #\n"); //on affiche "PTS"
            printf("#                    #         #\n");
            printf("################################\n");
        }
    }else{ //le nombre de caractère du pseudo est impair
        if(multi==0){ //il s'agit d'un jeu solo (le pc/robot ne peut ni gagner ni perdre)
            int nbdecaracteresdechaquecotedupseudo = ((maxcaractersforpseudo-getsizeofname())/2)-1; //on défini le nb de caractères '#' a ecrire avant et après le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' avant le pseudo
                printf("#");
            }
            printf(" %s ",name); //permet d'afficher le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' après le pseudo
                printf("#");
            }
            printf("##\n");
            printf("#                    #\n");
            printf("#       %4.1f         #\n",scorejoueur);  //on affiche le score du joueur et du pc/robot avec un total de 4 caractères, 2 pour la partie entière, le point et 1 pour la partie décimale
            printf("#        PTS         #\n"); //on affiche "PTS"
            printf("#                    #\n");
            printf("######################\n");
        }else{ //il s'agit d'un jeu multi joueur (le pc/robot peut gagner/perdre)
            int nbdecaracteresdechaquecotedupseudo = ((maxcaractersforpseudo-getsizeofname())-1)/2; //on défini le nb de caractères '#' a ecrire avant et après le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' avant le pseudo
                printf("#");
            }
            printf(" %s ",name); //permet d'afficher le pseudo
            for(int i=1;i<=nbdecaracteresdechaquecotedupseudo;i++){ //permet d'afficher le bon nb de '#' après le pseudo
                printf("#");
            }
            printf("# ROBOT ##\n");
            printf("#                    #         #\n");
            printf("#       %4.1f         #  %4.1f   #\n",scorejoueur,scorepc);  //on affiche le score du joueur et du pc/robot avec un total de 4 caractères, 2 pour la partie entière, le point et 1 pour la partie décimale
            printf("#        PTS         #   PTS   #\n"); //on affiche "PTS"
            printf("#                    #         #\n");
            printf("################################\n");
        }
    }
}

int menu(){ //Fonction permettant d'afficher le menu
    int choix; //creation de la variable qui contiendra le choix de l'utilisateur
    char term; //creation de la variable qui contiendra le caractère de fin de saisie (normalement le '\n')
    fflush(stdin); //on efface le buffer d'entrée au cas où il aurait entré plusieurs caractères
    clearscreen(); //on efface l'écran
    printf("Une creation originale de Julien Flusin !\n"); //pour le copy right ;-)
    printf(" /$$      /$$ /$$$$$$$$ /$$   /$$ /$$   /$$\n"); //Magnigique Ascii Art :-)
    printf("| $$$    /$$$| $$_____/| $$$ | $$| $$  | $$\n");
    printf("| $$$$  /$$$$| $$      | $$$$| $$| $$  | $$\n");
    printf("| $$ $$/$$ $$| $$$$$   | $$ $$ $$| $$  | $$\n");
    printf("| $$  $$$| $$| $$__/   | $$  $$$$| $$  | $$\n");
    printf("| $$\\  $ | $$| $$      | $$\\  $$$| $$  | $$\n");
    printf("| $$ \\/  | $$| $$$$$$$$| $$ \\  $$|  $$$$$$/\n");
    printf("|__/     |__/|________/|__/  \\__/ \\______/ \n");
    printf("\nQue souhaites-tu faire %s ?\n",name); //on demande à l'utilisateur ce qu'il souhaite faire
    printf("Ecrire 1 pour afficher les scores de la derniere partie [1]\n"); //option 1 afficher les scores de la dernière partie
    printf("Ecrire 2 pour jouer au plus ou moins [2]\n"); //option 2 lancer une partie du jeu plus ou moins 
    printf("Ecrire 3 pour jouer a pierre feuille ciseaux [3]\n"); //option 3 lancer une partie du jeu pierre/feuille/ciseaux
    printf("Ecrire 4 pour quitter [4]\n"); //option 4 quitter le jeu
    printf("Ecrire 5 pour changer de pseudo [5]\nChoix: "); //option 5 changer de pseudo
    if(scanf("%d%c", &choix, &term) != 2 || term != '\n'){ //on recupere son choix et on le stocke dans la variable choix tout en vérifiant que l'entrée est un bien un chiffre terminée par un retour à la ligne 
        clearscreen(); // on efface l'écran
        printf("Choix invalide !\nLe programme s'arrete !\n"); //on informe l'utilisateur
        exit(1); //on quitte avec le code d'erreur 1 pour signifier qu'il y a eu un pb
    }else{
        if(choix <1 || choix > 5){ //on vérifie que le choix de l'utilisateur est entre 1 et 4 compris
            clearscreen(); // on efface l'écran
            printf("Choix invalide !\nLe programme s'arrete !\n"); //on informe l'utilisateur
            exit(1);  //on quitte avec le code d'erreur 1 pour signifier qu'il y a eu un pb
        }
        switch(choix){ //switch cas du choix de l'utilisateur
            case 1: //si il choisi 1 (afficher les scores)
                scores(0); //on affiche les scores en tant que jeu multijoueur car on ne connait pas le dernier jeu auquel il a joué
                loading(5); //compte à rebours de 5 secondes
                menu(); //on affiche le menu
                break;
            case 2: //si il choisi 2 (lancer une partie de plus ou moins)
                scorejoueur = 0; //on reinitialise le score du joueur
                scorepc = 0; //on reinitialise le score du pc
                plusoumoins(); //on lance la fonction qui créé la partie de plus ou moins
                break;
            case 3: //si il choisi 3 (lancer une partie de pierre/feuille/ciseaux)
                scorejoueur = 0; //on reinitialise le score du joueur
                scorepc = 0; //on reinitialise le score du pc
                pfc(); //on lance la fonction qui créé une partie de pierre/feuille/ciseaux
                break;
            case 4: //si il choisi de quitter
                clearscreen(); //on efface l'écran
                printf("  /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$  /$$     /$$ /$$$$$$$$\n"); //Magnigique Ascii Art :-)
                printf(" /$$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$__  $$|  $$   /$$/| $$_____/\n");
                printf("| $$  \\__/| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$ \\  $$ /$$/ | $$      \n");
                printf("| $$ /$$$$| $$  | $$| $$  | $$| $$  | $$| $$$$$$$   \\  $$$$/  | $$$$$   \n");
                printf("| $$|_  $$| $$  | $$| $$  | $$| $$  | $$| $$__  $$   \\  $$/   | $$__/   \n");
                printf("| $$  \\ $$| $$  | $$| $$  | $$| $$  | $$| $$  \\ $$    | $$    | $$      \n");
                printf("|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$/| $$$$$$$/    | $$    | $$$$$$$$\n");
                printf(" \\______/  \\______/  \\______/ |_______/ |_______/     |__/    |________/\n");
                pause(); //effectue une pause console cross-platform
                exit(0); //on quitte le programme avec la valeur de retour 0 pour indiquer qu'il n'y as pas eu d'erreur
                break;
            case 5:
                choosename(); //permet à l'utilisateur de changer son pseudo
                break;
            default: //si il entre un nb autre que 1 ou 2 ou 3 ou 4
                fflush(stdin); //on efface le buffer d'entrée au cas où il aurait entré plusieurs caractères
                menu(); //on affiche de nouveau le menu
                break;
        }
    }
}

void main(){ //point d'entrée du programme c'est la première fonction éxécutée par le programme quand on le lance
    init(); //Fonction dans laquelle les instructions d'initialisation sont exécutées
    detectionos(); //on lance la fonction detectionos qui permet de detecter de quel os il s'agit
}