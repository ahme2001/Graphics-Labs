#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
enum choice {ortho=1, prespective=2};
enum userInput {zoomIn='i', zoomOut='o', stopSpinning=' ', CCW=GLUT_LEFT_BUTTON, CW= GLUT_RIGHT_BUTTON};
int userChoice = 0;
float orthoLeft = -50;
float orthoRight = 50;
float orthoBottom = -50;
float orthoTop = 50;
float orthoNear = -5;
float orthoFar = 5;
float fruLeft = -5;
float fruRight = 5;
float fruBottom = -5;
float fruTop = 5;
float fruNear = 5;
float fruFar = 100;
float offsetX = 100;
float offsetY = 100;
float zOffset = -15;//zoom out/in
float windowWidth = 500;
float windowHeight = 500;
float spinY = 0;
float spinZ = 0;
float spinSpeed = 5;
float currentSpin = 0;
float prevTime = 0;
// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0); // Default line width.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	switch (userChoice) {
	case ortho:{
        glRotatef(currentSpin, 0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 10.0, 0.0);
        glVertex3f(-30.0, 0.0, 0.0);
        glVertex3f(30.0, 0.0, 0.0);
        glEnd();
        spinY = 1.0;}
		break;
	case prespective:{
	    glTranslatef(0.0, 0.0, zOffset);
        glRotatef(currentSpin, 0.0, 1.0, 0.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-5.0f, -5.0f, 5.0f);
        glVertex3f(5.0f, -5.0f, 5.0f);
        glVertex3f(0.0f, -5.0f, -5.0f);
        glVertex3f(-5.0f, -5.0f, 5.0f);
        glVertex3f(5.0f, -5.0f, 5.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);
        glVertex3f(5.0f, -5.0f, 5.0f);
        glVertex3f(0.0f, -5.0f, -5.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);
        glVertex3f(-5.0f, -5.0f, 5.0f);
        glVertex3f(0.0f, -5.0f, -5.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);
        glEnd();}
		break;
	default:
		break;
	}
	glFlush();
}
// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
//spin logic
void spinDisplay(void)
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - prevTime;
    currentSpin += spinSpeed * deltaTime / 1000.0;
    glutPostRedisplay();
    prevTime = currentTime;
}

void spinDisplayReverse(void)
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - prevTime;
    currentSpin -= spinSpeed * deltaTime / 1000.0;
    glutPostRedisplay();
    prevTime = currentTime;
}
//keyboard & mouse
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case CCW:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(spinDisplay);
        }
        break;
	case CW:
		if (state == GLUT_DOWN)
        {
            glutIdleFunc(spinDisplayReverse);
        }
	default:
		break;
	}
}
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case zoomIn:
		zOffset += 1.0;
		break;
	case zoomOut:
		zOffset -= 1.0;
		break;
	case stopSpinning:
		glutIdleFunc(NULL);
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
	switch (userChoice) {
	case ortho:
		glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);
		spinY = 1.0;
		break;
	case prespective:
		glFrustum(fruLeft, fruRight, fruBottom, fruTop, fruNear, fruFar);
		spinZ = 1.0;
		break;
	default:
		break;
	}
	glMatrixMode(GL_MODELVIEW);
}

void printUserInteraction() {
	std::cout << "Interaction:" << std::endl;
	std::cout << "clicks left mouse to  spin around specific axis in counter-clockwise" << std::endl;
	std::cout << "clicks right mouse to  spin around specific axis in clockwise" << std::endl;
	std::cout << "Press space " " to stop spinning" << std::endl;
	std::cout << "Press i to zoom in" << std::endl;
	std::cout << "Press o to zoom out" << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	printUserInteraction();
	std::cout << "Which projection type do you want\n1) parallel projection\n2) perspective projection\n>> ";
	std::cin >> userChoice;
	if(userChoice == 2)
        spinZ = 1.0;
    else
        spinY = 1.0;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(offsetX, offsetY);
	glutCreateWindow("Lab 2.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

