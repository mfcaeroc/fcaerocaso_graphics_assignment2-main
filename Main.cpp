//---------------------------------------
// Program: Computer Graphics Project 2
// Purpose: Display a flying object along a user generated path.
// Author:  Fernanda Caero
// Date:    3/01/2024
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global constants
#define MIN_X_VIEW -50
#define MAX_X_VIEW 50
#define MIN_Y_VIEW -50
#define MAX_Y_VIEW 50
#define MIN_Z_VIEW -50
#define MAX_Z_VIEW 50
#define MIN_X_SCREEN 0
#define MAX_X_SCREEN 800
#define MIN_Y_SCREEN 0
#define MAX_Y_SCREEN 800

// Global variables 
#define MAX_COUNT 20
float Px[MAX_COUNT], Py[MAX_COUNT];
int transX, transY;
int count = -1;
bool startSquare = false;
float place [MAX_COUNT][MAX_COUNT];

int position = 0;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(MIN_X_VIEW, MAX_X_VIEW, 
      MIN_Y_VIEW, MAX_Y_VIEW, MIN_Z_VIEW, MAX_Z_VIEW);
   glEnable(GL_DEPTH_TEST);
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{
   // Calculate scale factors
   float x_scale = (MAX_X_VIEW - MIN_X_VIEW) / 
      (float)(MAX_X_SCREEN - MIN_X_SCREEN);
   float y_scale = (MIN_Y_VIEW - MAX_Y_VIEW) / 
      (float)(MAX_Y_SCREEN - MIN_Y_SCREEN);

   // Handle mouse down
   if (state == GLUT_DOWN)
   {
      if (count < MAX_COUNT) count++; 
      Px[count] = MIN_X_VIEW + (x - MIN_X_SCREEN) * x_scale;
      Py[count] = MAX_Y_VIEW + (y - MIN_Y_SCREEN) * y_scale;
      place[count][0] = Px[count];
      place[count][1] = Py[count];
      glutPostRedisplay();
   }
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    if(key == 's')
    {
        startSquare = true;
    }
    glutPostRedisplay();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Draw control points
   glColor3f(0.0, 1.0, 0.0);
   glPointSize(3);
   glBegin(GL_POINTS);
   for (int i=0; i<=count; i++)
      glVertex2f(Px[i], Py[i]);
   glEnd();

   // Connect points
   glLineWidth(2);
   glBegin(GL_LINE_STRIP);
   for (int i=0; i<=count; i++)
      glVertex2f(Px[i], Py[i]);
   glEnd();
    
   // Draw the square at the current position
   if (startSquare && position <= count)
   {
      glPushMatrix();
      glTranslatef(Px[position], Py[position], 0.0);
      
      glBegin(GL_POLYGON);
      glColor3f(0.5, 0.0, 1.0);
      glVertex2f(-3.0, -3.0);
      glVertex2f(-3.0, 3.0);
      glVertex2f(3.0, 3.0);
      glVertex2f(3.0, -3.0);
      glEnd();

      glPopMatrix();

      position++; // Move to the next position
   }

   glFlush();
}


//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(MAX_Y_SCREEN, MAX_X_SCREEN);
   glutInitWindowPosition(MAX_Y_SCREEN/2, MAX_X_SCREEN/2);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Flying Square");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   init();
   printf("Commands:\n");
   printf("Mouse operations:\n");
   printf("mouse down to start drawing line\n");
   printf("mouse up to finish drawing line\n");
   printf("Press S to show and move the square through each of the points in your path\n");
   glutMainLoop();
   return 0;
}