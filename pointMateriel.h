#ifndef POINTMATERIEL_H
#define POINTMATERIEL_H

#include "vecteur.h"

/* Definition d'un point materiel */

typedef struct {

  double m; /* masse */

  double t0; /* temps initial */
  double t; /* temps */
  
  Vecteur r; /* vecteur position */
  Vecteur v; /* vecteur vitesse */

  Vecteur r0; /* vecteur position au temps t0 */
  Vecteur v0; /* vecteur vitesse au temps t0 */

} PointMateriel;
  
#endif
