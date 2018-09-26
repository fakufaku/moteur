#ifndef PLAN_H
#define PLAN_H

#include <GLUT/glut.h>

#include "vecteur.h"

/* type Plan */

typedef struct {
  
  Vecteur p; /* un point du plan */
  Vecteur n; /* vecteur unite normal au plan */
  Vecteur couleur; /* couleur du plan RGB */
  
  Vecteur d1, d2; /* deux vecteurs unité du plan, orthogonaux */

  Vecteur p1, p2, p3, p4; /* Les quatre coins du plan */

} Plan;

/* fonctions sur les plans */

Plan plan_new (Vecteur p, Vecteur n, Vecteur couleur); /* cree un plan a partir d'un point et d'un vecteur unite normal */
double plan_isOn (Vecteur p, Plan *pi);  /* renvoie 0 si le point est sur le plan >0 au-dessus, <0 en-dessous */
void plan_afficher (Plan *pi);        /* affiche le plan avec opengl */

#endif
