#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define PI 3.14159265359

// Globals.
static float R = 5.0; // Radius of hemisphere.
static int p = 10; // Number of longitudinal slices.
static int q = 4; // Number of latitudinal slices.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static float offset = -10;
static float spinSpeed = 5;
static float prev_time = 0;


int numVertices = 200;
double radius = 1.5;
double pitch = 1.5;
enum choice {helix=1, sphere=2};
int userChoice = 0;
bool isWireframe = true;

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
	int  i, j;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Command to push the hemisphere, which is drawn centered at the origin,
	// into the viewing frustum.
	glTranslatef(0.0, 0.0, offset);

	// Commands to turn the hemisphere.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);


	glColor3f(0.0, 0.0, 0.0);

	// Array of latitudinal triangle strips, each parallel to the equator, stacked one
	// above the other from the equator to the north pole.
	switch (userChoice) {
        case sphere:{
            if (isWireframe) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            for (j = 0; j < q; j++)
            {
                // One latitudinal triangle strip.
                glBegin(GL_TRIANGLE_STRIP);
                for (i = 0; i <= p; i++)
                {
                    glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
                        R * sin((float)(j + 1) / q * M_PI / 2.0),
                        -R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
                    glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
                        R * sin((float)j / q * M_PI / 2.0),
                        -R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
                }
                glEnd();
            }
            for (j = 0; j < q; j++)
            {
                // One latitudinal triangle strip.
                glBegin(GL_TRIANGLE_STRIP);
                for (i = 0; i <= p; i++)
                {
                    glVertex3f(R * cos(-1*((float)(j + 1) / q * M_PI / 2.0)) * cos(-1*(2.0 * (float)i / p * M_PI)),
                        R * sin(-1*((float)(j + 1) / q * M_PI / 2.0)),
                        -R * cos(-1*((float)(j + 1) / q * M_PI / 2.0)) * sin(-1*(2.0 * (float)i / p * M_PI)));
                    glVertex3f(R * cos(-1*((float)j / q * M_PI / 2.0)) * cos(-1*(2.0 * (float)i / p * M_PI)),
                        R * sin(-1*((float)j / q * M_PI / 2.0)),
                        -R * cos(-1*((float)j / q * M_PI / 2.0)) * sin(-1*(2.0 * (float)i / p * M_PI)));
                }
                glEnd();
            }
            break;
        }case helix:{
            glScalef(2.0, 2.0, 2.0);
            glLineWidth(5.0f);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= numVertices * 5; i++) {
                double t = (double)i / numVertices * 2.0 * M_PI;
                double x = radius * cos(t);
                double y = radius * sin(t);
                double z = pitch * t / (2 * M_PI * 5);
                glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
                glVertex3f(x, y, z);
            }
            glEnd();
            break;
        }
	}
	glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void spinDisplay() {
	Yangle += spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void spinDisplayReverse() {

	Yangle -= spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	std::cout << Yangle << std::endl;
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplayReverse);

		break;
	default:
		break;
	}
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
    case 'r':
        radius += 0.1;
        glutPostRedisplay();
        break;
    case 'R':
        radius -= 0.1;
        glutPostRedisplay();
        break;
    case 'N':
        numVertices += 10;
        glutPostRedisplay();
        break;
    case 'n':
        numVertices -= 10;
        glutPostRedisplay();
        break;
    case 'H':
        pitch += 1.0;
		glutPostRedisplay();
		break;
    case 'h':
        pitch -= 1.0;
		glutPostRedisplay();
		break;
    case 'W':
        isWireframe = true;
        glutPostRedisplay();
        break;
    case 'w':
        isWireframe = false;
        glutPostRedisplay();
        break;
    case 'P':
		p += 1;
		glutPostRedisplay();
		break;
    case 'p':
		if (p > 3) p -= 1;
		glutPostRedisplay();
		break;
	case 'Q':
		q += 1;
		glutPostRedisplay();
		break;
	case 'q':
		if (q > 3) q -= 1;
		glutPostRedisplay();
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	case 'O':
		offset += 1;
		glutPostRedisplay();
		break;
	case 'o':
		offset -= 1;
		glutPostRedisplay();
		break;
	case ' ':
		glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press x, X, y, Y, z, Z to turn the hemisphere." << std::endl;
	std::cout << "Which projection type do you want\n1) helix\n2) sphere\n>> ";
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	std::cin >> userChoice;
	if(userChoice == 2){
        std::cout << "Press P/p to increase/decrease the number of longitudinal slices." << std::endl
		<< "Press Q/q to increase/decrease the number of latitudinal slices." << std::endl
		<< "press W/w, draw sphere in wireframe / draw filled sphere." << std::endl;
	}else{
        std::cout << "press R/r to increase/decrease radius of the helix." << std::endl
		<< "press H/h to increase/decrease pitch of helix." << std::endl
		<< "press N/n to increase/decrease number of vertices used to draw the helix." << std::endl;
	}
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hemisphere.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
