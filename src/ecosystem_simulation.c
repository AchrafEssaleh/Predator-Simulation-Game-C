//ESSALEH Achraf 21118166 L2 Sorbonne Universite UE C avancé 
//Au dessus de chaque ligne je fait un petit commentaire pour expliquer comment j'ai procede pour 
//resoudre le probleme ou bien pour indiquer que le code ne marche pas a 100%
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include "ecosys.h"

#define NB_PROIES 10
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define ITERATION_MAX 100

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

int main(void) {
  srand(time(NULL)); // srand permet de changer le point demarage dans le main 

  /* A completer. Part 2:
   * exercice 4, questions 1 et 2  */
  Animal *liste = NULL;
  Animal *n = creer_animal(SIZE_X - 1, SIZE_Y - 1, 10); //on cree un animal a une position SIZEX-1 idem pour y et d'energie 10
  liste = ajouter_en_tete_animal(liste, n);//on ajoute le nv animal note n dans la liste liste qu'on vient de cree
  //on affiche la liste pour que on voit le changement lorsque on fait bouge le l'animal
  afficher_ecosys(liste, NULL);
  bouger_animaux(liste);         //on deplace l'annimal
  afficher_ecosys(liste, NULL); // on reaffiche pour tester 
  reproduce(&liste, 1); 

  int a = compte_animal_it(liste);
  //avant 
  printf("nb animeaux avant reproduction : %d\n", a);
  reproduce(&liste, 1);// on teste la fonction avec le taux de reproduction 1 
  a = compte_animal_it(liste);
  //apres
  printf("nb animeaux apres reproduction : %d\n", a);
  //on remarque que que le nombre d'animaux est bien multiplier par 2 apres chaque màj

  liberer_liste_animaux(liste);

  // exercice 5/6 question 2 on ajoute l'annimal
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie = 10;
  
  for (int i = 0; i < NB_PROIES; i++) {
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie, &liste_proie);
  }
  for (int i = 0; i < NB_PREDATEURS; i++) {
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie,
                   &liste_predateur);
  }

  // Initialisation du monde
  int monde[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; ++i) {
    for (int j = 0; j < SIZE_Y; ++j) {
      monde[i][j] = 0;
    }
  }

  int nbMax = ITERATION_MAX;
  // La boucle s'arrête si la liste des proies/prédateurs est vide ou qu'on
  // atteint le nombre max d'itérations ici on l'a fixè à 100
  while (liste_proie && liste_predateur && nbMax != 0) {
    rafraichir_proies(&liste_proie, monde);                //  M à jour les proies 
    rafraichir_predateurs(&liste_predateur, &liste_proie); //  M à jour les predateurs
    rafraichir_monde(monde);                               //  M à jour les le monde cree
    afficher_ecosys(liste_proie, liste_predateur);         // j'affiche l'ecosys final
    usleep(T_WAIT);   //  ajouter des poses a fin de voir l'etat de mon ecos
    sleep(1);
    nbMax--;    // on decremente pour ne pas avoir une bcl inf
  }

  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);

  return 0;
}
