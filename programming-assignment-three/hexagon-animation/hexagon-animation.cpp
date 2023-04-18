#include <GL/glut.h>  
#include <math.h>  
#include <stdlib.h>
#include <iostream>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500;	// Initial display window size.  GLuint regHex;	// Define name for display list.
static GLfloat rotTheta = 0.0;
static GLfloat initRotSpeed = 0.0;
GLuint regHex;

class scrPt {
public:
	GLint x, y;
};
static void init(void)
{
	"have to define a display list for a red regular hexagon";
	scrPt hexVertex;  GLdouble hexTheta;  GLint k;

	glClearColor(1.0, 1.0, 1.0, 0.0);

	/* Set up a display list for a red regular hexagon.
	Vertices for the hexagon are six equally spaced
	points around the circumference of a circle.
	*/
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);  glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);  for (k = 0; k < 6; k++) {
		hexTheta = TWO_PI * k / 6;
		hexVertex.x = 150 + 100 * cos(hexTheta);  hexVertex.y = 150 + 100 * sin(hexTheta);  glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();  glEndList();

	//prompt the user to enter the initial rotation speed
	std::cout << "Enter the initial rotation speed: ";
	std::cin >> initRotSpeed;
}
void displayHex(void)
{
	"clear all pixels, draw the hexagon, and swap the buffers";
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(rotTheta, 0.0, 0.0, 1.0);  glCallList(regHex);
	glPopMatrix();
	glutSwapBuffers();  glFlush();
}

void rotateHexAntiClockwise(void)
{
	"rotate the hexagon anti-clockwise at the user defined speed";
	
	//rotate the hexagon anti-clockwise
	rotTheta += initRotSpeed;
	if (rotTheta > 360)
		rotTheta -= 360;
	glutPostRedisplay();
}
void rotateHexDoubleSpeed(void)
{
	"double the anti-clockwise rotation speed";
	initRotSpeed *= 2;
	glutPostRedisplay();
}
void rotateHexClockwise(void)
{
	"rotate the hexagon clockwise at user defined speed";

	//rotate the hexagon clockwise
	rotTheta -= initRotSpeed;
	if (rotTheta < 0)
		rotTheta += 360;
	glutPostRedisplay();
}

void winReshapeFcn(int newWidth, int newHeight)
{
	"set the viewport and projection parameters";
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -320.0, 320.0);

	glMatrixMode(GL_MODELVIEW);  glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
}

void mouseFcn(int button, int action, int x, int y)
{
	"functions that control the anti-clockwise rotation of the hexagon";
	switch (button) {
	case GLUT_LEFT_BUTTON: //start rotating anti-clockwise at user defined speed
		if (action == GLUT_DOWN)
			glutIdleFunc(rotateHexAntiClockwise);
		break;
	case GLUT_RIGHT_BUTTON: //double the anti-clockwise rotation speed
		if (action == GLUT_DOWN)
			rotateHexDoubleSpeed();
		break;
	default:
		break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	"functions that control the clockwise rotation of the hexagon";
	switch (key) {
	case 'q': //rotate clockwise at user defined speed
		glutIdleFunc(rotateHexClockwise);
		break;
	case 'w': //double the clockwise rotation speed
		rotateHexDoubleSpeed();
		break;
	case 'x' : //stop rotating
		glutIdleFunc(NULL);
		std::cout << "The hexagon has stopped rotating, please enter a new initial rotation speed:";
		std::cin >> initRotSpeed;
		break;
	default:
		break;
	}
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
	glutInitWindowPosition(150, 150);  
	glutInitWindowSize(winWidth, winHeight);  
	glutCreateWindow("Animation Example");

	init();
	glutDisplayFunc(displayHex);  
	glutReshapeFunc(winReshapeFcn);  
	glutMouseFunc(mouseFcn);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}

