#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

int Choice = 0;
static unsigned int buffer[2];
bool flag = false;
vector<float> verticesLine(0);


void Bresenham(int x0, int y0, int x1, int y1)
{
    bool steep = false;
    if (abs(x1-x0) < abs(y1-y0)){
        swap(x0, y0);
        swap(x1, y1);
        steep = true;
    }
    if (x0 > x1){
        swap(x0, x1);
        swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
        if (steep){
            verticesLine.push_back(y);
            verticesLine.push_back(x);
            verticesLine.push_back(0.0);
        }
        else{
            verticesLine.push_back(x);
            verticesLine.push_back(y);
            verticesLine.push_back(0.0);
        }
        error2 += derror2;
        if (error2 > dx){
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}
void DDA(int x0, int y0, int x1, int y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = max(abs(dx), abs(dy));
    float xIncr = dx / steps;
    float yIncr = dy / steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i < steps; i++)
    {
        verticesLine.push_back(x);
        verticesLine.push_back(y);
        verticesLine.push_back(0.0);
        x += xIncr;
        y += yIncr;

    }
}

float color = 0.0f;
GLuint vaoID;
// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    float* bufferData = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	float incre = 0.0011526;
    for (int i = 0; i < verticesLine.size()/3; i++)
    {
        bufferData[verticesLine.size() + i*3] = color;
        color += incre;
        if (color >= 0.9f ) {
            color = 0.0f;
        }
    }

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindVertexArray(vaoID);
	glDrawArrays(GL_POINTS, 0, verticesLine.size() / 3);
	glutSwapBuffers();
}

void drawname()
{
    switch (Choice) {
        case 1:{
            // Letter A.
            Bresenham(0.0, 30.0, 12.5, 90.0);
            Bresenham(12.5, 90.0, 25.0, 30.0);
            Bresenham(6.25,60.0, 18.75, 60.0);
            // Letter H.
            Bresenham(30.0, 30.0, 30.0, 90.0);
            Bresenham(30.0, 60.0, 55.0, 60.0);
            Bresenham(55.0, 90.0,55.0, 30.0);
            // Letter M.
            Bresenham(60.0, 30.0, 60.0, 90.0);
            Bresenham(60.0, 90.0, 72.5, 60.0);
            Bresenham(72.5, 60.0, 85.0,90.0);
            Bresenham(85.0,30.0, 85.0,90.0);
            // Letter E.
            Bresenham(90.0,30.0, 90.0,90.0);
            Bresenham(90.0,30.0, 115.0,30.0);
            Bresenham(90.0,90.0, 115.0,90.0);
            Bresenham(90.0,60.0, 115.0,60.0);
            // Letter D.
            Bresenham(120.0, 30.0, 120.0, 90.0);
            Bresenham(120.0, 30.0, 145.0, 45.0);
            Bresenham(120.0, 90.0, 145.0, 45.0);
            break;
        }case 2:{
            // Letter A.
            DDA(0.0, 30.0, 12.5, 90.0);
            DDA(12.5, 90.0, 25.0, 30.0);
            DDA(6.25,60.0, 18.75, 60.0);
            // Letter H.
            DDA(30.0, 30.0, 30.0, 90.0);
            DDA(30.0, 60.0, 55.0, 60.0);
            DDA(55.0, 90.0,55.0, 30.0);
            // Letter M.
            DDA(60.0, 30.0, 60.0, 90.0);
            DDA(60.0, 90.0, 72.5, 60.0);
            DDA(72.5, 60.0, 85.0,90.0);
            DDA(85.0,30.0, 85.0,90.0);
            // Letter E.
            DDA(90.0,30.0, 90.0,90.0);
            DDA(90.0,30.0, 115.0,30.0);
            DDA(90.0,90.0, 115.0,90.0);
            DDA(90.0,60.0, 115.0,60.0);
            // Letter D.
            DDA(120.0, 30.0, 120.0, 90.0);
            DDA(120.0, 30.0, 145.0, 45.0);
            DDA(120.0, 90.0, 145.0, 45.0);
            break;
        }
    }
}

// Timer function.
void animate(int someValue)
{
	glutPostRedisplay();
	glutTimerFunc(60, animate, 1);
}

// Initialization routine.
void setup(void)
{
    drawname();
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    float colors[verticesLine.size()];
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glGenBuffers(2, buffer); // Generate buffer ids.
	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, verticesLine.size()*sizeof(float) + sizeof(colors), NULL, GL_STATIC_DRAW);
	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticesLine.size()*sizeof(float), &verticesLine[0]);
	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, verticesLine.size()*sizeof(float), sizeof(colors), colors);
	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (void *)(verticesLine.size()*sizeof(float)));

	glutTimerFunc(3, animate, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 150.0, 0.0, 150.0,-1.0,1.0);
}

void printInteraction(void)
{
	cout << "Which algorithm type do you want\n1) Bresenham algorithm\n2) DDA algorithm\n>> ";
}

int main(int argc, char **argv)
{
    printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(100, 100);
	cin >> Choice;

	glutCreateWindow("Write My Name.cpp");
	glutDisplayFunc(drawScene);
	glewInit();
    glutReshapeFunc(resize);
    setup();
	glewExperimental = GL_TRUE;


	glutMainLoop();
}
