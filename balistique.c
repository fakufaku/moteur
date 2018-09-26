
#include "balistique.h"

/* donc, on s'occupe de la balistique */

void position (Balle *b, double delta_t) {
  b->r0 = b->r; /* on sauvegarde r(t-dt) */
  /* r(t+dt) = r(t) + dt*v(t-dt) + dt^2*a(t-dt) */
  b->r = vect_add(vect_add(b->r, vect_multiScal(delta_t, b->v0)), vect_multiScal(delta_t * delta_t, b->a));
  b->v0 = b->v; /* on sauvegarde v(t-dt) */
  /* v(t+dt) = v(t) + dt*a(t) */
  b->v = vect_add(b->v, vect_multiScal(delta_t, b->a));

  return; /* pour la forme */
}

/*
Vecteur position (Vecteur *r0, Vecteur *v0, double t, Vecteur a) {
  return vect_add(vect_add(*r0, vect_multiScal(t, *v0)), vect_multiScal(0.5 * pow(t, 2.0), a));
}

Vecteur vitesse (Vecteur *v0, double t, Vecteur a) {
  return vect_add(*v0, vect_multiScal(t, a));
}
*/
