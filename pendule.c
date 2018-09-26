#include "pendule.h"

Vecteur accPend (Pendule *p, Vecteur a) {
  Vecteur resultante, mg, t, corde;
  corde = soustVect(p->e.r0, p->o);
  mg = multiScal(p->e.m, a);
  t = opposeVect(projectVect(mg, corde));
  resultante = addVect(mg, t);
  
  return multiScal( (1.0/p->e.m), resultante);
}
