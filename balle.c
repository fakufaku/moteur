#include "balle.h"

/* creation d'une nouvelle balle */
/* attention position et vitesse valent zero a la creation */

Balle balle_new (double R, double m, double coefReb, Vecteur couleur) {
  Balle b;
  
  b.R = R;
  b.m = m;
  b.coefReb = coefReb;
  b.couleur = couleur;

  b.t = 0.0;
  b.r = vect_new( 0.0 , 0.0 , 0.0 );
  b.v = vect_new( 0.0 , 0.0 , 0.0 );

  b.t0 = 0.0;
  b.r0 = vect_new( 0.0 , 0.0 , 0.0 );
  b.v0 = vect_new( 0.0 , 0.0 , 0.0 );
  
  return b;

}

/* renvoie >0 si la balle est au-dessus du plan, 0 sur ou <0 dessous */

double balle_isOn_plan (Balle *b, Plan *pi) {
  return plan_isOn( vect_add(vect_multiScal(-b->R, pi->n), b->r), pi);
}  

/* calcul s'il y a rebond sur un plan et cas echeant le rebond */

void balle_rebond_plan (Balle *b, Plan *pi, double delta) {
  if (vect_prodScal(b->v, pi->n) <= 0.0 && balle_isOn_plan(b, pi) <= (0.0 + cte_epsilon)) {

    b->v = vect_multiScal(b->coefReb, vect_reflect(vect_oppose(b->v), pi->n));
    b->v0 = b->v;
    b->r0 = b->r;
    b->t0 += b->t;
    b->t = 0.0;

  }

  return;

}

/* affiche la balle en opengl */

void balle_afficher (Balle *b) {
  glColor3d(b->couleur.x, b->couleur.y, b->couleur.z);
  glTranslated(b->r.x, b->r.y, b->r.z);
  glutSolidSphere(b->R,20,20);

  return;
}

/* gere la collision de deux balles */

void balle_collision (Balle *b1, Balle *b2) {
  Vecteur v1Nrm, v1Par, v2Nrm, v2Par;
  Vecteur temp, n;
  double v1foisv2, nV1, nV2, nfoisV1, nfoisV2;
  int test1, test2, test3;

  n = vect_soust(b2->r, b1->r);
  v1foisv2 = vect_prodScal(b1->v, b2->v);
  nfoisV1 = vect_prodScal(b1->v, n);
  nfoisV2 = vect_prodScal(b2->v, n);
  nV1 = vect_norme(b1->v);
  nV2 = vect_norme(b2->v);

  test1 = nV1 > nV2 && nfoisV1 > 0 && nfoisV2 > 0;
  test2 = nV1 < nV2 && nfoisV1 < 0 && nfoisV2 < 0;
  test3 = v1foisv2 < 0 && nfoisV1 > 0 && nfoisV2 < 0;

  if ( (vect_norme(n) - (b1->R + b2->R) < cte_epsilon) &&  (test1 || test2 || test3)) {

    printf("%.4f\n", vect_norme(n) - (b1->R + b2->R));

    v1Nrm = vect_project(b1->v, n);
    v1Par = vect_orthoProject(b1->v, n);
    
    v2Nrm = vect_project(b2->v, n);
    v2Par = vect_orthoProject(b2->v, n);

    temp = v1Nrm;

    v1Nrm = vect_multiScal(1/(b1->m + b2->m),vect_add(vect_add(vect_multiScal(b1->m, temp), vect_multiScal(-b2->m, temp)), vect_multiScal(2*b2->m, v2Nrm)));
    v2Nrm = vect_multiScal(1/(b1->m + b2->m),vect_add(vect_add(vect_multiScal(2*b1->m, temp), vect_multiScal(-b1->m, v2Nrm)), vect_multiScal(b2->m, v2Nrm)));

    b1->v = vect_add(v1Nrm, v1Par);
    b2->v = vect_add(v2Nrm, v2Par);

    b1->v0 = b1->v;
    b1->r0 = b1->r;
    b1->t0 += b1->t;
    b1->t = 0.0;

    b2->v0 = b2->v;
    b2->r0 = b2->r;
    b2->t0 += b2->t;
    b2->t = 0.0;

  }

  return;
}
