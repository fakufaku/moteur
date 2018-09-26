SHELL=/bin/sh
CC=gcc
#CDEBUG=-g
CFLAGS=-I. -Wall -pedantic -ansi $(CDEBUG)
#LIBS=-lGL -lGLU -lglut  -lX11 -lXmu -lXi -lm
LIBS=-framework GLUT -framework OpenGL -framework Cocoa
LIBSDIR= -L/usr/X11R6/lib

all : test5



test5 : vecteur.o balistique.o plan.o balle.o test5.o microtime.o
	$(CC) $(CFLAGS) microtime.o vecteur.o balistique.o plan.o balle.o test5.o -o test5 ${LIBS} ${LIBSDIR}


microtime.o : microtime.h microtime.c
	$(CC) $(CFLAGS) -c microtime.c

vecteur.o : vecteur.h vecteur.c
	$(CC) $(CFLAGS) -c vecteur.c

balistique.o : balistique.h vecteur.h balistique.c
	$(CC) $(CFLAGS) -c balistique.c

pendule.o : pendule.h vecteur.h pointMateriel.h pendule.c
	$(CC) $(CFLAGS) -c pendule.c

plan.o : vecteur.h plan.h plan.c
	$(CC) $(CFLAGS) -c plan.c

balle.o : vecteur.h plan.h baseCanonique.h balle.c
	$(CC) $(CFLAGS) -c balle.c



test3.o : vecteur.h baseCanonique.h pointMateriel.h constantes.h plan.h test3.c
	$(CC) $(CFLAGS) -c test3.c

test5.o : microtime.h vecteur.h baseCanonique.h pointMateriel.h constantes.h plan.h balle.h test5.c
	$(CC) $(CFLAGS) -c test5.c



clean :
	-rm test5 *.o
