#include <stdio.h>
#include <time.h>
#include <GLUT/glut.h>
#include <math.h>
#include "microtime.h"
#include "vecteur.h"
#include "baseCanonique.h"
#include "constantes.h"
#include "balistique.h"
#include "plan.h"
#include "balle.h"

#define FREQUENCE 0.0005

void affichage();
void idle();
void clavier(unsigned char touche,int x,int y);
void mouv(int touche, int x, int y);

Balle b1, b2, b3;
Plan Oxy, pi, theta, gamma2, lambda, plafond;
double t0, t;
double delta;
int compteur = 0;
Vecteur camera, oeil;

int main(int argc,char **argv)
{

  /* initialisation d'une balle */

  b1 = balle_new (1.0, 1.0, 0.9, vect_new(1.0, 1.0, 1.0));
  b1.r0 = vect_new( 0.0, 0.0, 1.001 ); /* on n'oublie pas de lui fixer sa position */
  b1.v0 = vect_new( -2.0, 0.0, 0.0 );     /* et sa vitesse initiale!!!                */
  b1.r = b1.r0;
  b1.v = b1.v0;

  b2 = balle_new (0.5, 1.0, 0.9, vect_new(1.0, 0.5, 1.0));
  b2.r0 = vect_new( 0.0, -3.0, 3.0 ); /* on n'oublie pas de lui fixer sa position */
  b2.v0 = vect_new( -2.0, 5.0, -5.0 );     /* et sa vitesse initiale!!!                */
  b2.r = b2.r0;
  b2.v = b2.v0;

  b3 = balle_new (0.5, 1.0, 0.9, vect_new(0.5, 0.5, 1.0));
  b3.r0 = vect_new( 0.0, 3.0, 3.0 ); /* on n'oublie pas de lui fixer sa position */
  b3.v0 = vect_new( -2.0, -5.0, -5.0 );     /* et sa vitesse initiale!!!                */
  b3.r = b3.r0;
  b3.v = b3.v0;

  
  /* initialisation des plans pi et Oxy */

  Oxy = plan_new(bc_zero, bc_e3, vect_new(1.0, 0.0, 0.0)); /* (point reference, vecteur normal, couleur) */
  pi = plan_new(vect_new(-5.0, 0.0, 0.0), bc_e1, vect_new(0.7, 0.2, 0.3));
  theta = plan_new(vect_new(0.0, -5.0, 0.0), bc_e2, vect_new(0.0, 0.3, 0.7));
  gamma2 = plan_new(vect_new(5.0, 0.0, 0.0), vect_new(-1.0, 0.0, 0.0), vect_new(0.3, 0.0, 0.1));
  lambda = plan_new(vect_new(0.0, 5.0, 0.0), vect_oppose(bc_e2), vect_new(0.1, 0.2, 0.4));
  plafond = plan_new(vect_new(0.0, 0.0, 10.0), vect_oppose(bc_e3), vect_new(0.5, 0.5, 0.5));

  /* initialisation de la camera */
  oeil = vect_new( 4.0, 0.0, 1.85 );
  camera = vect_new( 0.0, 0.0, 1.8);

  /* initialisation de l'horloge */
  t0 = microtime();
  printf("t0 = %.8f\n", t0);

  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(20,20);
  glutInitWindowSize(700,700);
  glutCreateWindow("Moteur Physique Bourrin");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutIdleFunc(idle);
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutSpecialFunc(mouv);

  /* Entree dans la boucle principale glut */
  glutMainLoop();

  return 0;
}

void affichage()
{
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Definition de la perspective */
  glMatrixMode(GL_PROJECTION); /* passage au mode de perspective des matrices */
  glLoadIdentity();
  gluPerspective(100.0, 1.0, 1.0, 70.0);


  glMatrixMode(GL_MODELVIEW); /* on repasse a la matrice de modelisation */

  /* placement de la camera */
  glLoadIdentity();
  gluLookAt(oeil.x, oeil.y, oeil.z, camera.x, camera.y, camera.z, 0.0, 0.0, 1.0); 
  glPushMatrix();

  /* placement d'un plan horizontal en z = 0 */
  plan_afficher(&Oxy);
  
  /* placement d'un plan vert parallele a 0z en x = -20 */
  plan_afficher(&pi);

  /* autres plans */
  plan_afficher(&theta);
  plan_afficher(&gamma2);
  plan_afficher(&lambda);
  plan_afficher(&plafond);
  
  /* dessin de la sphere */
  glPopMatrix();
  glPushMatrix();
  balle_afficher(&b1);  

  glPopMatrix();
  glPushMatrix();
  balle_afficher(&b2);

  glPopMatrix();
  balle_afficher(&b3);
  /* on force l'affichage du resultat */
  glFlush();

  glutSwapBuffers();
}

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'd': /* deplacement de l'oeil vers l'avant */
      oeil.x -= 0.2;
      break;
    case 'c': /* deplacement de l'oeil vers l'arriere */
      oeil.x += 0.2;
      break;
    case 'x': /* deplacement de l'oeil vers la gauche */
      oeil.y -= 0.2;
      break;
    case 'v': /* deplacement de l'oeil vers la droite */
      oeil.y += 0.2;
      break;
    case 'z':
      oeil.z += 0.2;
      break;
    case 'h':
      oeil.z -= 0.2;
      break;
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
      break;
    }
}

void idle()
{

  while ((delta = ((t = microtime()) - t0)) < (double)FREQUENCE);

  if (balle_isOn_plan(&b1, &Oxy) < (0.0 + cte_epsilon))
    b1.a = bc_zero;
  else
    b1.a = cte_g;

  if (balle_isOn_plan(&b2, &Oxy) < (0.0 + cte_epsilon))
    b2.a = bc_zero;
  else
    b2.a = cte_g;

  if (balle_isOn_plan(&b3, &Oxy) < (0.0 + cte_epsilon))
    b3.a = bc_zero;
  else
    b3.a = cte_g;

  b1.t += delta; /* on met a jour l'horloge de la balle */
  b2.t += delta; /* on met a jour l'horloge de la balle */
  b3.t += delta; /* on met a jour l'horloge de la balle */
  /*  
  b1.r = position(&(b1.r0), &(b1.v0), b1.t, b1.a);
  b1.v = vitesse(&(b1.v0), b1.t, cte_g);

  b2.r = position(&(b2.r0), &(b2.v0), b2.t, b1.a);
  b2.v = vitesse(&(b2.v0), b2.t, cte_g);

  b3.r = position(&(b3.r0), &(b3.v0), b3.t, b1.a);
  b3.v = vitesse(&(b3.v0), b3.t, cte_g);
  */

  position(&b1, delta);
  position(&b2, delta);
  position(&b3, delta);

  balle_collision(&b1, &b2);
  balle_collision(&b1, &b3);
  balle_collision(&b2, &b3);
 
  balle_rebond_plan (&b1, &Oxy, delta);
  balle_rebond_plan (&b1, &pi, delta);
  balle_rebond_plan (&b1, &theta, delta);
  balle_rebond_plan (&b1, &gamma2, delta);
  balle_rebond_plan (&b1, &lambda, delta);
  balle_rebond_plan (&b1, &plafond, delta);
  
  balle_rebond_plan (&b2, &Oxy, delta);
  balle_rebond_plan (&b2, &pi, delta);
  balle_rebond_plan (&b2, &theta, delta);
  balle_rebond_plan (&b2, &gamma2, delta);
  balle_rebond_plan (&b2, &lambda, delta);
  balle_rebond_plan (&b2, &plafond, delta);

  balle_rebond_plan (&b3, &Oxy, delta);
  balle_rebond_plan (&b3, &pi, delta);
  balle_rebond_plan (&b3, &theta, delta);
  balle_rebond_plan (&b3, &gamma2, delta);
  balle_rebond_plan (&b3, &lambda, delta);
  balle_rebond_plan (&b3, &plafond, delta);

  t0 = t;
    
  compteur++;

  glutPostRedisplay();
  
}

void mouv(int touche, int x, int y) {
    switch (touche)
    {
    case GLUT_KEY_UP :
      camera.z += 0.05;
      glutPostRedisplay();
      break;
    case GLUT_KEY_DOWN :
      camera.z -= 0.05;
      glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT :
      camera.y += 0.05;
      glutPostRedisplay();
      break;
    case GLUT_KEY_RIGHT :
      camera.y -= 0.05;
      glutPostRedisplay();
      break;
  }
}
