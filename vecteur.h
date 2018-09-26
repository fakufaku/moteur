#ifndef VECTEUR_H
#define VECTEUR_H

#include <stdio.h>
#include <math.h>

/*
 * Definition de la structure "Vecteur"
 */

typedef struct {

  double x;
  double y;
  double z;

} Vecteur;

/*
 * Fonctions d'opérations sur des vecteurs
 */

void vect_print (const Vecteur v); /* affiche un vecteur */
Vecteur vect_new (const double vx, const double vy, const double vz); /* renvoie un nouveau vecteur (vx, vy, vz) */
Vecteur vect_add (const Vecteur v1, const Vecteur v2); /* v1 + v2 */
Vecteur vect_soust (const Vecteur v1, const Vecteur v2); /* v1 - v2 */
Vecteur vect_oppose (const Vecteur v); /* -v */
Vecteur vect_multiScal (const double scalaire, const Vecteur v); /* k * v */
double vect_prodScal (const Vecteur v1, const Vecteur v2); /* v * w */
Vecteur vect_prodVect (const Vecteur v1, const Vecteur v2); /* v ^ w */
double vect_norme (const Vecteur v); /* norme de v */
double vect_normeCarree (const Vecteur v); /* norme de v au carré */
Vecteur vect_unit (const Vecteur v); /* renvoie un vecteur unité créé a partir de v */
double vect_angle (const Vecteur v1, const Vecteur v2); /* renvoie l'angle entre 2 vecteur */
Vecteur vect_project (const Vecteur v, const Vecteur u); /* renvoie la projection de v sur u */
Vecteur vect_orthoProject (const Vecteur v, const Vecteur u); /* renvoie un vecteur orhtogonal a la projection de v sur u et dans le meme plan */
Vecteur vect_reflect (const Vecteur v, const Vecteur u); /* symetrie par rapport a l'axe donné par u */

#endif
