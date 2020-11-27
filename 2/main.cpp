//Amirhossein Kargaran khozzani 9429523

#include <windows.h>
#include <GL/freeglut.h> 
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.14159265

// Checked for alpha=-30 and High=5 too
GLdouble alpha = -20;
GLdouble High = 10;

GLdouble t1 = 0.0, t2 = 0.0;
GLdouble Value = alpha * PI / 180;


//First Position 
GLdouble Y = (0.6 / cos(Value)), Vy = 0;
GLdouble Z = 0 , Vz = 0;



GLint animationPeriod = 50;
GLint isAnimate = 0, flag = 0;

void resize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(64.0, 64.0 / 48.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (flag == 0)
		gluLookAt(10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (flag == 1)
		gluLookAt(0.0, 0.0, -25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void drawScene(){

	resize();

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//Fixed Floor 
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0, -1*High , 0);
	glScaled(2.0,0.03,3.5);   
	glutSolidCube(5);
	glPopMatrix();

	// Fixed Ramp
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glRotated(alpha, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.0);
	glScaled(0.5, 0.03, 1.0);
	glutWireCube(2.0);
	glPopMatrix();


	//Draw Ball 
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, Y, Z);
	glutWireSphere(0.3, 10, 10);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		isAnimate = 1;		
		break;

	case 'o':
		flag = 1;
		break;

	case 'f':
		flag = 0;
		break;

	case 'e':
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void specialKeyInput(int key , int x , int y)
{
	if (key == GLUT_KEY_DOWN) animationPeriod += 5;
	if (key == GLUT_KEY_UP) if (animationPeriod > 5) animationPeriod -= 5;
	glutPostRedisplay();
}


void animate() {
	if (isAnimate) {
		if (Y + High <= 0) {
			Y = -1*High;
			if (Z <= -8)
				Z = -8;
			else 
			Z -= 0.2;
		}
		else if (Y - ((0.6 / cos(Value)) - abs(sin(Value))) <= 0) {
			Y = -0.5 * 9.8 * t2 * t2 + (t2 * Vy) + -0.5 * 9.8 * t1 * t1 * sin(Value) * sin(Value) + (0.6 / cos(Value)) ;
			Z = Vz * t2 + 0.5 * 9.8 * t1 * t1 * sin(Value) * cos(Value);
			t2 += 0.02; 
		}
		else{
			Y = -0.5 * 9.8 * t1 * t1 * sin(Value) * sin(Value) + (0.6 / cos(Value));
			Z = 0.5 * 9.8 * t1 * t1 * sin(Value) * cos(Value);
			Vy = -t1 * 9.8 * sin(Value) * sin(Value);
			Vz = t1 * 9.8 * sin(Value) * cos(Value);

			t1 += 0.02;
		}
		glutPostRedisplay();
		Sleep(animationPeriod);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Ball and Plate");

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutIdleFunc(animate);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutMainLoop();

	return 0;
}