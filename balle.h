#ifndef BALLE_H
#define BALLE_H

#include "vecteur.h"
#include "plan.h"

extern const double cte_epsilon;

/* definition d'une balle */

typedef struct {
  
  double R; /* rayon de la balle */
  double m; /* masse de la balle */
  double coefReb; /* coefficient de rebond (0 < coefReb <= 1) */
  Vecteur couleur; /* couleur de la balle */

  Vecteur a; /* acceleration a laquel est soumise la balle */
  
  double t; /* temps écoulé depuis t0 */
  Vecteur r; /* position au temps t */
  Vecteur v; /* vitesse au temps t */

  double t0; /* temps du dernière impact */
  Vecteur r0; /* position au temps t0 */
  Vecteur v0; /* vitesse au temps t0 */

} Balle;

/* fonction sur les balles */

Balle balle_new (double R, double m, double coefReb, Vecteur couleur); /* cree une nouvelle balle */
double balle_isOn_plan (Balle *b, Plan *pi); /* renvoie >1 si la balle est au-dessus du plan, 0 sur ou >0 dessous */
void balle_rebond_plan (Balle *b, Plan *pi, double delta); /* calcul le rebond sur un plan */
void balle_collision (Balle *b1, Balle *b2); /* collision entre deux balles */
void balle_afficher (Balle *b); /* affiche la balle avec opengl */

#endif
