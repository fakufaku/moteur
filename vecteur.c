#include "vecteur.h"

/* definition de l'affichage d'un vecteur */

void vect_print (const Vecteur v) {
  printf("( %.3f ; %.3f ; %f )",v.x, v.y, v.z);
}

/* definition de la creation d'un nouveau vecteur */

Vecteur vect_new (const double vx, const double vy, const double vz) {
  Vecteur new;

  new.x = vx;
  new.y = vy;
  new.z = vz;

  return new;

}

/* definition de l'addition */

Vecteur vect_add (const Vecteur v1, const Vecteur v2) {
  Vecteur v1plusv2;

  v1plusv2.x = v1.x + v2.x;
  v1plusv2.y = v1.y + v2.y;
  v1plusv2.z = v1.z + v2.z;

  return v1plusv2;

}

/* definition de la soustraction */

Vecteur vect_soust (const Vecteur v1, const Vecteur v2) {
  Vecteur v1moinsv2;

  v1moinsv2.x = v1.x - v2.x;
  v1moinsv2.y = v1.y - v2.y;
  v1moinsv2.z = v1.z - v2.z;

  return v1moinsv2;

}

/* definition de l'oppose d'un vecteur */

Vecteur vect_oppose (const Vecteur v) {
  Vecteur moinsV;
  
  moinsV.x = -v.x;
  moinsV.y = -v.y;
  moinsV.z = -v.z;

  return moinsV;

}

/* definition de la multiplication par un scalaire */

Vecteur vect_multiScal (const double scalaire, const Vecteur v) {
  Vecteur kfoisv;
  
  kfoisv.x = scalaire * v.x;
  kfoisv.y = scalaire * v.y;
  kfoisv.z = scalaire * v.z;

  return kfoisv;

}

/* definition du produit scalaire */

double vect_prodScal (const Vecteur v1, const Vecteur v2) {
  double result;
  
  result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

  return result;

}

/* definition du produit vectoriel */

Vecteur vect_prodVect (const Vecteur v1, const Vecteur v2) {
  Vecteur v1crossv2;

  v1crossv2.x = (v1.y * v2.z) - (v1.z * v2.y);
  v1crossv2.y = (v1.z * v2.x) - (v1.x * v2.z);
  v1crossv2.z = (v1.x * v2.y) - (v1.y * v2.x);

  return v1crossv2;

}

/* definition de la norme */
 
double vect_norme (const Vecteur v) {
  return sqrt(vect_prodScal(v, v));
}

/* definition de la norme au carré */

double vect_normeCarree (const Vecteur v) {
  return vect_prodScal(v, v);
}

/* definition du vecteur unité */

Vecteur vect_unit (const Vecteur v) {
  return vect_multiScal(1/vect_norme(v), v);
}

/* definition de l'angle entre deux vecteurs */

double vect_angle (const Vecteur v1, const Vecteur v2) {
  return acos(vect_prodScal(v1, v2)/(vect_norme(v1) * vect_norme(v2)));
}

/* definition de la projection orthogonale */

Vecteur vect_project (const Vecteur v, const Vecteur u) {
  return vect_multiScal(vect_prodScal(v, u)/vect_normeCarree(u), u);
}

/* definition d'un vecteur orthogonal a la projection orthogonale sur u */

Vecteur vect_orthoProject (const Vecteur v, const Vecteur u) {
  return vect_soust(v, vect_project(v, u));
}

/* definition de la symetrie par rapport a l'axe donné par u */

Vecteur vect_reflect (const Vecteur v, const Vecteur u) {
  return vect_soust(vect_project(v, u), vect_orthoProject(v,u));
}
