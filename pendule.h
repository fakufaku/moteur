#ifndef PENDULE_H
#define PENDULE_H

#include "vecteur.h"
#include "pointMateriel.h"

/* definition d'un pendule */

typedef struct {

  Vecteur o; /* pt fixe */
  PointMateriel e; /* pt qui bouge */

} Pendule;

/* fonction qui renvoie l'acceleration subie par le pendule sous l'acceleration a */

Vecteur accPend (Pendule *p, Vecteur a);

#endif
