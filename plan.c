#include "plan.h"

/* cree un nouveau plan */

Plan plan_new (Vecteur p, Vecteur n, Vecteur couleur) {
  Plan pi;

  pi.p = p;
  pi.n = vect_unit(n);
  pi.couleur = couleur;

  
  pi.d1 = vect_prodVect(pi.n, vect_new(pi.n.x - 1, pi.n.y - 2, pi.n.z));
  pi.d2 = vect_prodVect(pi.n, pi.d1);

  pi.d1 = vect_unit(pi.d1);
  pi.d2 = vect_unit(pi.d2);

  pi.p1 = vect_add(p, vect_add(vect_multiScal(500.0, pi.d1), vect_multiScal(500.0, pi.d2)));
  pi.p2 = vect_add(p, vect_add(vect_multiScal(500.0, pi.d1), vect_multiScal(-500.0, pi.d2)));
  pi.p3 = vect_add(p, vect_add(vect_multiScal(-500.0, pi.d1), vect_multiScal(-500.0, pi.d2)));
  pi.p4 = vect_add(p, vect_add(vect_multiScal(-500.0, pi.d1), vect_multiScal(500.0, pi.d2)));

  return pi;

}

/* renvoie 0 si le point p est sur le plan pi */

double plan_isOn (Vecteur p, Plan *pi) {
  return vect_prodScal(pi->n, vect_soust(p, pi->p));
}

/* affiche le plan avec opengl */

void plan_afficher (Plan *pi) {
  glBegin(GL_POLYGON);
  glColor3d(pi->couleur.x, pi->couleur.y, pi->couleur.z);
  glVertex3d(pi->p1.x, pi->p1.y, pi->p1.z);
  glVertex3d(pi->p2.x, pi->p2.y, pi->p2.z);
  glVertex3d(pi->p3.x, pi->p3.y, pi->p3.z);
  glVertex3d(pi->p4.x, pi->p4.y, pi->p4.z);
  glEnd();

  return;
}
  
