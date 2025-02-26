//ESSALEH Achraf 21118166 L2 Sorbonne Universite UE C avancé 
//Au dessus de chaque ligne je fait un petit commentaire pour expliquer comment j'ai procede pour 
//resoudre le probleme ou bien pour indiquer que le code ne marche pas a 100%
#include <stdio.h>
#include <stdlib.h>

#include "ecosys.h"

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

int main() {
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie = 10;
  //on cree 20 proies et preda par une boucle for
  for (int i = 0; i < 20; i++) { //dans le monde SIZE X c 20 donc sur untableau de 20 cases j'ai de tab 0 jusqu'a tab 19
    //on utilise la primitive rand pour avoir des positions X ET Y aleatoir
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y + 1), energie,  //Normalement on utilise rand comme suit 
                   &liste_proie);                                      //(max-min+1)+min -> size_x -1 +0 +1 ca fait sizex
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y + 1), energie,
                   &liste_predateur);
  }
  //verification du nombre de pro et pred en faisant appel aux fcts de comptage
  printf("Nombre de prédateurs : %d, Nombre de proies : %d\n",
         compte_animal_rec(liste_predateur), compte_animal_rec(liste_proie));
  //affichage de l'eco sys
  afficher_ecosys(liste_proie, liste_predateur);
  //ON ecrit l'ecosysteme cree
  ecrire_ecosys("test", liste_predateur, liste_proie);

  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

  liste_predateur = NULL;   //nouvelle liste dont on va lire les predas
  liste_proie = NULL;      //nouvelle liste dont on va lire les proies
  
  //lire l'ecosys dans de nouvelles listes
  lire_ecosys("test", &liste_predateur, &liste_proie);
  afficher_ecosys(liste_proie, liste_predateur);  //on verifie que les ecosys lus et ecrit sont bien les memes

  liberer_liste_animaux(liste_predateur); //on libere la memoire allouee
  liberer_liste_animaux(liste_proie);   //on libere la memoire allouee pour eviter toute fuite memoire

  return 0;
}
