//ESSALEH Achraf 21118166 L2 Sorbonne Universite UE C avancé 
//Au dessus de chaque ligne je fait un petit commentaire pour expliquer comment j'ai procede pour 
//resoudre le probleme ou bien pour indiquer que le code ne marche pas a 100%
#include "ecosys.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  //assert pour verifier que les cordonnees sont positives et inferieures a SIZE_X ET Y
  assert(x >= 0 && x < SIZE_X);
  assert(y >= 0 && y < SIZE_Y);
  //ON AJOUTE l'annimal a la liste chainee liste_animal
  Animal *n =
      ajouter_en_tete_animal(*liste_animal, creer_animal(x, y, energie));
  //passage du pointeur par adresse(pour pouvoir le modifier directement en fonction )
  *liste_animal = n;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *pa;
  assert(liste);
  pa = *liste;//on fait passer la liste par adresse du coup ona joute une etoile pour faire - etoile 
  // si c'est la tete qu'il faut supprimer
  if (*liste == animal) {  
    *liste = (*liste)->suivant;
    free(pa);
  } else {  // sinon c'est au milieu 
    while (pa->suivant && pa->suivant != animal) {//du coup on se place juste avant l'element à supprimer
                                                  // c pour ca je met pa->suivant != animal comme condition
      pa = pa->suivant;
    }
    if (pa->suivant) {
      Animal *la = pa->suivant;
      pa->suivant = la->suivant;
      free(la);
    }
  }
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal *liberer_liste_animaux(Animal *liste) {
  Animal *tmp = NULL;
  while (liste) {
    //on utilise la variable temporaire pour stocker la cellule qu'on veut liberer
    tmp = liste;
    //on passe a la cellule suivante de la liste
    liste = liste->suivant;
    //on libere la premiere cellule
    free(tmp);
  }

  return NULL; // on peut meme renvoyer liste puisque elle va etre egale a NULL a la fin
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt = 0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de
 * contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa = NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j] = ' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa = pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
    if ((ecosys[pa->x][pa->y] == '@') ||
        (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
      ecosys[pa->x][pa->y] = '@';
    } else {
      ecosys[pa->x][pa->y] = 'O';
    }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie = compte_animal_it(liste_proie);
  int nbpred = compte_animal_it(liste_predateur);

  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */

void bouger_animaux(Animal *la) {
  /*A Completer*/
  while (la) {
    // dir[0]
    float a = (float)rand() / (float)RAND_MAX;
    if (a < p_ch_dir) {
      la->dir[0] = rand() % 3 - 1;
    }
    // dir[1]
    a = (float)rand() / (float)RAND_MAX;
    if (a < p_ch_dir) {
      la->dir[1] = rand() % 3 - 1;
    }
    la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;
    la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;
    la = la->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  /*A Completer*/
  assert(liste_animal);
  Animal *pa = *liste_animal;
  float a;
  while (pa) {
    a = (float)rand() / (float)RAND_MAX;
    if (a < p_reproduce) {
      ajouter_animal(pa->x, pa->y, pa->energie / 2.0, liste_animal);
      pa->energie /= 2.0;
    }
    pa = pa->suivant;
  }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  //on teste si liste proie n'est pas vide 
  assert(liste_proie); 
  //on fait bouger la proie 
  bouger_animaux(*liste_proie);
  Animal *la = *liste_proie; //on pose unr liste temporaire de proies pour pouvoir la parcourire sans contrainte 
  Animal *tmp = NULL;        // variable tamporaire pour stocker les cellules dans le champs energie est <0
  while (la) {              //on parcour la liste de proies
    la->energie -= 1;       //on baisse l'energie de 1
    if (monde[la->x][la->y] >= 0) {       //si les positions x et y de la liste de proies sont >=0 
      la->energie += monde[la->x][la->y]; 
      monde[la->x][la->y] = temps_repousse_herbe;
    }
    if (la->energie < 0) {  //si le champs energie de la proie est <0 
      tmp = la;             //on stocke les cellules dont  le champs energie est <0
      la = la->suivant;
      enlever_animal(liste_proie, tmp);//on supprime la cellule dont le champs ne d=satisfait pas la condi
    } else {
      la = la->suivant;      //si la condition est satisfaite on continue 
    }
  }

  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 6, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) { //renvoie la proie si elle existe en pos XY NULL sinn
  Animal *p = l;                                //variable tempo p= tete de la liste l pour parcourir avec
  while (p) {
    if (p->x == x && p->y == y) {   //si elle existe on  renvoie  un pointeur sur la proie p de crdn (x,y)
      return p;
    }
    p = p->suivant;             //on parcour toute la liste p+
  }
  return NULL;                 //on renvoie NULL sinn
}
/* Part 2. Exercice 6, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  
  assert(liste_predateur);   //je verifie si la liste n'est pas vide
  assert(liste_proie);      //idem
  Animal *la = *liste_predateur;  //on ajoute etoile a liste predateur pour faire -* puisque elle est de type **
  bouger_animaux(la);
  Animal *proie = NULL;
  Animal *tmp = NULL;

  while (la) {
    la->energie -= 1;  // on baisse l'energie du predateur
    proie = animal_en_XY(*liste_proie, la->x, la->y); //r 

    if (proie) {     //i.e si la proie est dans la meme case d'un predateur 
      la->energie += proie->energie;   //  j'ajoute l'energie du predateur puisq'il va la manger
      enlever_animal(liste_proie, proie); // la proie est manger par le predateur
    }

    if (la->energie < 0) {      //si le champs energie de la proie est <0 
      tmp = la->suivant;
      
      enlever_animal(liste_predateur, la); //on supprime la cellule dont le champs ne satisfait pas la condi
      la = tmp;                 //on avance i.e la=la->suivant
    }

    else {
      la = la->suivant;                // si la condition est satisfaite on continue
    }
  }
  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
  /*A Completer*/
  int i, j;
  for (i = 0; i < SIZE_X; i++)
    for (j = 0; j < SIZE_Y; j++) monde[i][j]++;
}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur,
                   Animal *liste_proie) {
  FILE *fichier = NULL;
  fichier = fopen(nom_fichier, "w"); //On ouvre le fichier en mode ecriture
  assert(fichier);  //on teste que notre fichier n'est pas egale a NULL
  Animal *pa = liste_proie;
  fprintf(fichier, "<proies>\n");
  while (pa) {
    fprintf(fichier, "x=%d y=%d dir=[%d %d] e=%f\n", pa->x, pa->y, pa->dir[0],
            pa->dir[1], pa->energie);
    pa = pa->suivant;
  }
  fprintf(fichier, "</proies>\n");
  pa = liste_predateur;
  fprintf(fichier, "<predateurs>\n");
  while (pa) {
    fprintf(fichier, "x=%d y=%d dir=[%d %d] e=%f\n", pa->x, pa->y, pa->dir[0],
            pa->dir[1], pa->energie);
    pa = pa->suivant;
  }
  fprintf(fichier, "</predateurs>\n");
  fclose(fichier);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur,
                 Animal **liste_proie) {
  FILE *fichier = fopen(nom_fichier, "r");
  assert(fichier);
  char str[256]; //buffer
  int x_lu;
  int y_lu;
  int dir1;
  int dir2;
  float e_lu;
  fgets(str, 256, fichier);      // on lit ligne par ligne dans le fichier fichier 
  assert((strncmp(str, "<proies>", 8)) == 0); 
  fgets(str, 256, fichier);                   //puisque la taille maximal d'un char non signe est 256oct
  while (strncmp(str, "</proies>", 9) != 0) {
    sscanf(str, "x=%d y=%d dir=[%d %d] e=%f", &x_lu, &y_lu, &dir1, &dir2,
           &e_lu);
    Animal *a = creer_animal(x_lu, y_lu, e_lu);
    a->dir[0] = dir1;
    a->dir[1] = dir2;
    a->suivant = *liste_proie;
    *liste_proie = a;
    fgets(str, 256, fichier);
  }
  fgets(str, 256, fichier);
  assert((strncmp(str, "<predateurs>", 12)) == 0);
  fgets(str, 256, fichier);
  while (strncmp(str, "</predateurs>", 13) != 0) {
    sscanf(str, "x=%d y=%d dir=[%d %d] e=%f", &x_lu, &y_lu, &dir1, &dir2,
           &e_lu);
    Animal *a = creer_animal(x_lu, y_lu, e_lu);
    a->dir[0] = dir1;
    a->dir[1] = dir2;
    a->suivant = *liste_predateur;
    *liste_predateur = a;
    fgets(str, 256, fichier);
  }
  fclose(fichier);
}
