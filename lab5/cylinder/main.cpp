#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static unsigned int aClyinderLeg;
static unsigned int aCircle;
static bool solidMode = false;
static float rotationAngleX = 0.0f;
static float rotationAngleY = 0.0f;
static float rotationAngleZ = 0.0f;

// Initialization routine.
void setup(void)
{
    aClyinderLeg = glGenLists(1); // Return a list index.
    // Begin create a display list.
    glNewList(aClyinderLeg, GL_COMPILE);
    glutSolidCylinder(3.0, 30.0, 10, 10);
    glEndList();
    // End create a display list.

    aCircle = glGenLists(1);
    glNewList(aCircle, GL_COMPILE);
    glutSolidCylinder(30.0, 2.0, 10, 10);
    glEndList();

    glClearColor(1.0, 1.0, 1.0, 0.0);
}
// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 5.0, -70.0);
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0, -5.0, 70.0);
    if (solidMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // Draw seat
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 6.0, -70.0);
    glRotatef(90.0, 1, 0, 0);
    glCallList(aCircle); // Execute display list.
    glPopMatrix();

    // Draw first leg
    glPushMatrix();
    glTranslatef(-20.0, 5.0, -70.0);
    glRotatef(90.0,1,0,0);
    glRotatef(-15.0,0,1,0);
    glCallList(aClyinderLeg); // Execute display list.
    glPopMatrix();

    // Draw second leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 4.0, -50.0);
    glRotatef(85.0,1,0,0);
    glCallList(aClyinderLeg); // Execute display list.
    glPopMatrix();

    // Draw third leg
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(20.0, 5.0, -70.0);
    glRotatef(90.0,1,0,0);
    glRotatef(15.0,0,1,0);
    glCallList(aClyinderLeg); // Execute display list.
    glPopMatrix();

    glFlush();
}


void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x':
            rotationAngleX -= 5.0f;
            break;
        case 'X':
            rotationAngleX += 5.0f;
            break;
        case 'y':
            rotationAngleY -= 5.0f;
            break;
        case 'Y':
            rotationAngleY += 5.0f;
            break;
        case 'z':
            rotationAngleZ -= 5.0f;
            break;
        case 'Z':
            rotationAngleZ += 5.0f;
            break;
        case ' ':
            // Toggle between solid and wireframe mode.
            solidMode = !solidMode;
            break;
        case 27: // ESC key
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press x, X, y, Y, z, Z to rotate the 3-legged stool." << std::endl;
	std::cout << "Press space to Toggle drawing mode of the 3-legged between drawing a wireframe object or a solid one.";
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3-legged stool.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
