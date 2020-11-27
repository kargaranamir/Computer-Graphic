#include "Structs.h"
#include <math.h>
#include "Camera.h"
#include "RGBpixmap.h"

Camera camera;
RGBpixmap pix[4];  


void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	pix[0].readBMPFile("grass.bmp");        
	pix[0].setTexture(2001);              	

	pix[1].readBMPFile("road.bmp"); 
	pix[1].setTexture(2002);		

	pix[2].readBMPFile("door.bmp");  
	pix[2].setTexture(2003);		 

	pix[3].readBMPFile("home.bmp"); 
	pix[3].setTexture(2004);


	camera.setShape(60, 640 / 480, .001f, 100);
	camera.set(Point3(-7, 6, 1), Point3(0, 0, 0), Vector3(0, 0, 1));

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void DrawGrass()
{
	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1, 0.0); glVertex3f(10.0f, 1.0f, 0.0f);
	glTexCoord2f(1, 1); glVertex3f(10.0f, 3.0f, 0.0f);
	glTexCoord2f(0.0, 1); glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 2001);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 7.0f, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(10.0f, 7.0f, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();


}

void DrawRoad()
{
	glBindTexture(GL_TEXTURE_2D, 2002); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0f, 3.0f, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(10.0f, 3.0f, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(10.0f, 7.0f, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0f, 7.0f, 0.0f);
	glEnd();
}

void DrawHome()
{
	glBindTexture(GL_TEXTURE_2D, 2004);
	//back wall
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);  glVertex3d(0, 0, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3d(1, 0, 0);
	glTexCoord2f(1.0, 1.0);  glVertex3d(1, 0, 1);
	glTexCoord2f(0.5, 1.5); glVertex3d(0.5, 0, 1.5);
	glTexCoord2f(0.0, 1.0); glVertex3d(0, 0, 1);
	glEnd();

	//front wall
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);  glVertex3d(0, 1, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3d(1, 1, 0);
	glTexCoord2f(1.0, 1.0);  glVertex3d(1, 1, 1);
	glTexCoord2f(0.5, 1.5); glVertex3d(0.5, 1, 1.5);
	glTexCoord2f(0.0, 1.0); glVertex3d(0, 1, 1);
	glEnd();

	//left wall
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3d(0, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3d(0, 1, 0);
	glTexCoord2f(1.0, 1.0); glVertex3d(0, 1, 1);
	glTexCoord2f(0.0, 1.0); glVertex3d(0, 0, 1);
	glEnd();

	//right wall
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3d(1, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3d(1, 1, 0);
	glTexCoord2f(1.0, 1.0); glVertex3d(1, 1, 1);
	glTexCoord2f(0.0, 1.0); glVertex3d(1, 0, 1);
	glEnd();

	//door
	glBindTexture(GL_TEXTURE_2D, 2003);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3d(0.3, 1.01, 0);
	glTexCoord2f(1.0, 0.0); glVertex3d(0.7, 1.01, 0);
	glTexCoord2f(1.0, 1.0); glVertex3d(0.7, 1.01, 0.6);
	glTexCoord2f(0.0, 1.0); glVertex3d(0.3, 1.01, 0.6);
	glEnd();

	// left roof
	glBindTexture(GL_TEXTURE_2D, 2004);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3d(0, 0, 1);
	glTexCoord2f(1.0, 0.0); glVertex3d(0.5, 0, 1.5);
	glTexCoord2f(1.0, 1.0); glVertex3d(0.5, 1, 1.5);
	glTexCoord2f(0.0, 1.0); glVertex3d(0, 1, 1);
	glEnd();


	//right roof
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3d(0.5, 0, 1.5);
	glTexCoord2f(1.0, 0.0); glVertex3d(1, 0, 1);
	glTexCoord2f(1.0, 1.0); glVertex3d(1, 1, 1);
	glTexCoord2f(0.0, 1.0); glVertex3d(0.5, 1, 1.5);
	glEnd();
}

void Keyboard(unsigned char key, int mouseX, int mouseY)
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (key) {
	case 'w':
		camera.slide(0, 0, -0.5);
		break;
	case 's':
		camera.slide(0, 0, 0.5);
		break;
	case 'd':
		camera.slide(0.5, 0, 0);
		break;
	case 'a':
		camera.slide(-0.5, 0, 0);
		break;
	case 'R':
		camera.roll(1.0);
		break;
	case 'r':
		camera.roll(-1.0);
		break;
	case 'P':
		camera.pitch(1.0);
		break;
	case 'p':
		camera.pitch(-1.0);
		break;
	case 'Y':
		camera.yaw(1.0);
		break;
	case 'y':
		camera.yaw(-1.0);
	default:
		break;
	}
	glutPostRedisplay();
}

void Arrow(int key, int x, int y)
{
	float a = 3.0;

	switch (key)
	{
	case GLUT_KEY_UP:
		camera.slide(0, 0, -0.5);
		break;
	case GLUT_KEY_DOWN:
		camera.slide(0, 0, 0.5);
		break;
	case GLUT_KEY_LEFT:
		camera.slide(-0.5, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		camera.slide(0.5, 0, 0);
		break;
	}

	glutPostRedisplay();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	DrawRoad();
	DrawGrass();

	glPushMatrix();
	glTranslated(1.0, 0, 0);
	DrawHome();	
	glTranslated(2.0, 0, 0);
	DrawHome();
	glTranslated(2.0, 0, 0);
	DrawHome();
	glTranslated(2.0, 0, 0);
	DrawHome();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 0, 1);
	glTranslated(-2.0, -11.0, 0);
	DrawHome();
	glTranslated(-2.0, 0, 0);
	DrawHome();
	glTranslated(-2.0, 0, 0);
	DrawHome();
	glTranslated(-2.0, 0, 0);
	DrawHome();
	glPopMatrix();
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(640, 480);
	glutCreateWindow("Amirhossein Kargaran 9429523 - HW4");

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Arrow);
	
	Init();
	glutMainLoop();
}