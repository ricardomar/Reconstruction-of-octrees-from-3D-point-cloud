//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/glut.h>
#include "Node.h"


void eventKeyboard(unsigned char, int, int);
void drawFilledCube(float, float, float, float, float, float);
void drawSkelethonCube(float, float, float, float, float, float);
void displayOctree(Node *,int);
void mainLoop(void);
void glSetup(int, int);
void init(void);
void displayOctreeTree(Node *,int) ;

#endif /*DISPLAY_H_*/
