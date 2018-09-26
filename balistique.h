#ifndef BALISTIQUE_H
#define BALISTIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vecteur.h"
#include "balle.h"

/* tout ce qui concerne la balistique */

void position (Balle *b, double delta_t); /* retrourne la position de p au temps t */


/*Vecteur position (Vecteur *r0, Vecteur *v0, double t, Vecteur a);*/ /* retourne la position de p au temps t */
/*Vecteur vitesse (Vecteur *v0, double t, Vecteur a);*/ /* retourne la vitesse de p au temps t */

#endif

