/** @brief Programme créant un Sudoku
*
*@author PEROU
*
*@version 3.2.5
*
*@date 13 novembre 2023
*
*Ce programme permet de jouer à un sudoku */



#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
/** \def TAILLE
*
*\brief définie la taille du tableau à 2 dimensions */
#define TAILLE 9

/** \def N
*
*\brief définie la taille d'un bloc */
const int N = 3;

/** \def DEFAUT
*
*\brief définie la valeur initiale */
const int DEFAUT = 0;


/**
*
* \typedef tGrille
*
* \brief type tableau de TAILLE caractères
*
* Tableau stockant les valeurs du Sudoku.
*
*/
typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille g);
bool grillePleine(tGrille g);
void multiples(int n);
void afficherGrille(tGrille g);
void saisir(int *valeurSaisir);
bool dansBloc(tGrille g, int debutLigneBloc, int debutColonneBloc, int valeur);
bool possible(tGrille g, int ligne, int colonne, int valeur);


/*****************************************************
 * PROGRAMME PRINCIPAL *
*****************************************************/

int main(){
    // Déclaration des variables
    int numLigne;
    int numColonne;
    int valeur;
    tGrille grille1;
    chargerGrille(grille1);
    while (!grillePleine(grille1)) // Tant qu'il reste des valeurs à insérer.
    {
        afficherGrille(grille1);
        printf("Indice de la ligne ? : ");
        saisir(&numLigne);
        printf("Indice de la colonne ? : ");
        saisir(&numColonne);
        numLigne--;
        numColonne--;
        if (grille1[numLigne][numColonne] != DEFAUT) //Regarde si la case n'a pas déjà un chiffre.
        {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        }
        else{
            printf("Valeur à insérer ? ");
            saisir(&valeur);
            if (possible(grille1, numLigne, numColonne, valeur)) //Regarde tous les cas d'erreur.
            {
                grille1[numLigne][numColonne] = valeur;
            }
            else {
                printf("IMPOSSIBLE, la valeur ne peut pas être placée à cette position.\n");
            }
        }
    }
    printf("Grille pleine, fin de partie");
    return EXIT_SUCCESS;
}

/**
*
* \fn void chargerGrille(tGrille g)
*
* \brief Fonction qui charge une grille
*
* \param g : Grille de sudoku
*
* Charge une grille de Sudoku.
*
*/

void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else{
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}

/**
 * @brief Affiche une barre verticale si nécessaire.
 *
 *
 * @param n Indice de la colonne actuelle.
 *
 * Affiche une barre verticale si la colonne n est
 * égale à un multiple de 3.
 */

void multiples(int n) {
    if (n % N == 0 && n != 0) {
        printf("|");
    } else {
        printf(" ");
    }
}

/**
 * @brief Affiche la grille du Sudoku.
 *
 * @param g La grille du Sudoku à afficher.
 * 
 * Affiche la grille du Sudoku avec des barres verticales pour séparer les blocs.
 */

void afficherGrille(tGrille g) {
    printf("    1   2   3 | 4   5   6 | 7   8   9  \n");
    printf(" +------------+-----------+-----------+\n");
    for (int i = 0; i < TAILLE; i++) {
        if (i % N == 0 && i != 0)  //Rajoute une ligne pour les valeurs multiples de 3 en excluant la première
        {
            printf(" +------------+-----------+-----------+\n");
        }
        printf("%d|", i + 1);
        for (int j = 0; j < TAILLE; j++) {
            multiples(j);
            if (g[i][j] != DEFAUT) {
                printf("%2d", g[i][j]);
            } else {
                printf(" .");
            }
            printf(" ");
        }
        printf("|\n");
    }
    printf(" +------------+-----------+-----------+\n");
}

/**
 * @brief Demande de saisir une valeur
 *
 * @param valeurSaisir La valeur qu'on doit saisir
 * 
 * Demande de saisir une valeur , puis la stock.
 */
void saisir(int *valeurSaisir) {
    char ch[10];
    int x;
    int conversionReussie = 0;

    do {
        printf("Entrez une valeur : ");
        scanf("%s", ch);

        if (sscanf(ch, "%d", &x) == 1) {
            // La conversion a réussi, x contient la valeur entière lue au clavier
            *valeurSaisir = x;
            conversionReussie = 1;
        } else {
            // La conversion en entier a échoué
            printf("Veuillez entrer une valeur entière valide.\n");
        }
    } while (!conversionReussie);
}

/**
*
* \fn dansBloc(tGrille g, int debutLigneBloc, int debutColonneBloc, int valeur)
*
* \brief Fonction qui indique si la valeur est dans le bloc.
*
* \param g : La grille du Sudoku
* \param debutLigneBloc : Première ligne du bloc
* \param debutColonneBloc : Première colonne du bloc
* \param valeur : Valeur à regarder
*
* \return true si la valeur est dans le bloc, false sinon.
*
* Permet de savoir si la valeur est positionné dans le bloc.
*
*/

bool dansBloc(tGrille g, int debutLigneBloc, int debutColonneBloc, int valeur) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (g[debutLigneBloc + i][debutColonneBloc + j] == valeur) {
                return true;
            }
        }
    }
    return false;
}

/**
*
* \fn possible(tGrille g, int ligne, int colonne, int valeur)
*
* \brief Fonction qui indique si la valeur est positionnable.
*
* \param g : La grille du Sudoku
* \param debutLigneBloc : ligne de la valeur à insérer
* \param debutColonneBloc : colonne de la valeur à insérer
* \param valeur : Valeur à regarder
*
* \return true si la valeur est possible, false sinon.
*
* Indique si la valeur n'est pas déjà positionné dans la ligne, la colonne et le bloc.
*
*/

bool possible(tGrille g, int ligne, int colonne, int valeur) {
    for (int i = 0; i < TAILLE; i++) {
        if (g[ligne][i] == valeur)  //Vérifie si la ligne possède déjà la valeur
        {
            return false;
        }
    }
    for (int j = 0; j < TAILLE; j++) {
        if (g[j][colonne] == valeur) //Vérifie si la colonne possède déjà la valeur
        {
            return false;
        }
    }

    int debutLigneBloc = (ligne / N) * N; //Permet de savoir dans quel bloc est la première ligne grâce à la valeur du diviseur
    int debutColonneBloc = (colonne / N) * N; //Permet de savoir dans quel bloc est la première colonne grâce à la valeur du diviseur

/**
 * \see La fonction dansBloc
*/
    return !dansBloc(g, debutLigneBloc, debutColonneBloc, valeur); 
}

/**
*
* \fn grillePleine(tGrille g)
*
* \brief Fonction qui indique si la grille est pleine
*
* \param g : La grille du Sudoku
*
* \return true si la grille est pleine, false sinon.
*
* Parcourt la grille et regarde si aucun n'élément est mis en DEFAUT.
*/

bool grillePleine(tGrille g) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (g[i][j] == DEFAUT) {
                return false; // S'il y a une case vide, la grille n'est pas pleine
            }
        }
    }
    return true; // Aucune case vide, la grille est pleine
}