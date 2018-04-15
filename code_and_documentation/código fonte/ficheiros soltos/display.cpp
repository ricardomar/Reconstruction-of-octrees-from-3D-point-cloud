//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//

#include "display.h"


Node *node;
int Grid;
double rx=0,ry=0,rz=0;
double zoom=-40;


void eventKeyboard(unsigned char key, int x, int y)  
{
  switch(key) {
  case '2':
    rx--;
    return;
  case '8':
    rx++;
    return;
  case '4':
    ry--;
    return;
  case '6':
    ry++;
    return;
  case '9':
    rz--;
    return;
  case '7':
    rz++;
    return;
  case ' ':
    rx=0;
    ry=0;
    rz=0;
    zoom=-40;
    return;
  case '+':
    zoom += 1.0;
    return;
  case '-':
    zoom -=1.0;
    return;
  case '.':
  	Grid=0;
  	return;
  case ',':
  	Grid=1;
    return;	
  }
}


void drawFilledCube(float posX, float posY, float posZ, float dX, float dY, float dZ)
{
  glBegin(GL_QUADS);
  
  glColor3d(0,0,0);
  glVertex3f(posX,posY,posZ);
  glVertex3f(posX+dZ,posY,posZ);
  glVertex3f(posX+dX,posY+dY,posZ);
  glVertex3f(posX,posY+dY,posZ);
  
  glVertex3f(posX,posY,posZ+dZ);
  glVertex3f(posX+dX,posY,posZ+dZ);
  glVertex3f(posX+dX,posY+dY,posZ+dZ);
  glVertex3f(posX,posY+dY,posZ+dZ);
  
  glVertex3f(posX,posY,posZ);
  glVertex3f(posX,posY,posZ+dZ);
  glVertex3f(posX,posY+dY,posZ+dZ);
  glVertex3f(posX,posY+dY,posZ);
  
  glVertex3f(posX+dX,posY,posZ);
  glVertex3f(posX+dX,posY,posZ+dZ);
  glVertex3f(posX+dX,posY+dY,posZ+dZ);
  glVertex3f(posX+dX,posY+dY,posZ);
  
  glVertex3f(posX,posY,posZ);
  glVertex3f(posX+dX,posY,posZ);
  glVertex3f(posX+dX,posY,posZ+dZ);
  glVertex3f(posX,posY,posZ+dZ);
  
  glVertex3f(posX,posY+dY,posZ);
  glVertex3f(posX+dX,posY+dY,posZ);
  glVertex3f(posX+dX,posY+dY,posZ+dZ);
  glVertex3f(posX,posY+dY,posZ+dZ);
  glEnd();
 
};


void drawSkelethonCube(float posX, float posY,float posZ,float dX, float dY,float dZ)
{
	glBegin(GL_LINE_LOOP);	
  	glColor3d(1,0,0);
  	glVertex3f(posX,posY,posZ);
  	glVertex3f(posX+dX,posY,posZ);
  	glVertex3f(posX+dX,posY+dY,posZ);
	glVertex3f(posX,posY+dY,posZ);
  	glEnd();
  	
 	glBegin(GL_LINE_LOOP);	
  	glColor3d(1,0,0);
  	glVertex3f(posX,posY,posZ+dZ);
  	glVertex3f(posX+dX,posY,posZ+dZ);
  	glVertex3f(posX+dX,posY+dY,posZ+dZ);
	glVertex3f(posX,posY+dY,posZ+dZ);
  	glEnd();
  	
  	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3f(posX,posY,posZ);
	glVertex3f(posX,posY,posZ+dZ);
	glEnd();
	
  	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3f(posX+dX,posY,posZ);
	glVertex3f(posX+dX,posY,posZ+dZ);
	glEnd();

  	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3f(posX+dX,posY+dY,posZ);
	glVertex3f(posX+dX,posY+dY,posZ+dZ);
	glEnd();  	

  	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3f(posX,posY+dY,posZ);
	glVertex3f(posX,posY+dY,posZ+dZ);
	glEnd();

};

void displayOctree(Node * n,int grid)
{               
        if (n->child[0] == NULL)
        {
                int points = (int) n->pointArray.size();              
                if (points > 0)
                {
                	drawFilledCube(n->posX,n->posY,n->posZ,n->dX,n->dY,n->dZ);
                	drawSkelethonCube(n->posX,n->posY,n->posZ,n->dX,n->dY,n->dZ);
                }
                else
                {	if(grid==1)
                	{
                		drawSkelethonCube(n->posX,n->posY,n->posZ,n->dX,n->dY,n->dZ);
                	}
                };
                return;
        }
        else if (n->child[0] != NULL)
        {
                for (int i = 0; i < 8; i++)
                        displayOctree(n->child[i],grid);
                return;
        }
};


void mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	glTranslatef(0,0, zoom);

	glRotatef(rx,1, 0, 0);
	glRotatef(ry,0, 1, 0);
	glRotatef(rz,0, 0, 1);	
	
	displayOctree(node,Grid);

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();

}

void glSetup(int width, int height)
{
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glEnable(GL_DEPTH_TEST);
	gluPerspective(45, (float)width/height, .01, 100 );
	glMatrixMode(GL_MODELVIEW );
};

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClearDepth(80.0);
};


void displayOctreeTree(Node * n,int grid) 
{	
	int argc=0;
	char** argv=NULL;
	node=n;
	Grid=grid;
	glutInit(&argc,argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH);
	glutCreateWindow("Octree Demonstration");
	glutDisplayFunc(mainLoop);
	
	glutKeyboardFunc(eventKeyboard);
	init();
	glSetup(640,480);
	glutMainLoop();
}


