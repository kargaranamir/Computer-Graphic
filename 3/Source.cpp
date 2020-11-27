// Amirhossein Kargaran 9429523
// In the Name of Allah
// Making a mesh for the Toroidal Spirals

#include "Mesh.h"

Mesh cube;

bool first = 1;

GLfloat alpha = 30.0;
GLfloat High = 5.0;



GLfloat H = High, x0_ball = -(4.0 + cos(alpha*M_PI / 180)), y0_ball = High + sin(alpha*M_PI / 180);
GLfloat x = x0_ball + 0.2, y = y0_ball + 0.2, v, v0;

double t1, t2, t = 0.0;
bool isAnimate = FALSE;

static int animationPeriod = 50;
GLfloat x_eye = 0, y_eye = High / 2, z_eye = 10;




void Init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 50);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	GLfloat amb[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat spec[] = { 1.0, 5.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);


}

//Cooper material
void cooper_setLight() {
	GLfloat position[] = { -3.0f, 4.1, 2.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	GLfloat mat_amb[] = { 0.19125f, 0.0735f, 0.0225f };
	GLfloat mat_diff[] = { 0.7038f, 0.27048f, 0.0828f };
	GLfloat mat_spec[] = { 0.256777f, 0.137622f, 0.086014f };
	GLfloat mat_phong[] = { 12.8f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_phong);

}

//Silver material
void silver_setLight() {
	GLfloat position[] = { 0.0f, High / 2, 2.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	GLfloat mat_amb[] = { 0.19225f, 0.19225f, 0.19225f };
	GLfloat mat_diff[] = { 0.50754f, 0.50754f, 0.50754f };
	GLfloat mat_spec[] = { 0.508273f, 0.508273f, 0.508273f };
	GLfloat mat_phong[] = { 51.2f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_phong);

}

//Gold material
void gold_setLight() {
	GLfloat position[] = { 2.0f, 6.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	GLfloat mat_amb[] = { 0.24725f, 0.1995f, 0.0745f };
	GLfloat mat_diff[] = { 0.75164f, 0.60648f, 0.022648f };
	GLfloat mat_spec[] = { 0.628281f, 0.555802f, 0.366065f };
	GLfloat mat_phong[] = { 51.2f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_phong);
}


void myKeyboard(unsigned char key, int mouseX, int mouseY)
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (key) {
	case 'f':
		x_eye = 0.0; y_eye = High / 2; z_eye = 10;		
		break;
	case 'o':
		x_eye = 10.0; y_eye = High / 2; z_eye = 0;		 
		break;
	case 's':
		isAnimate = TRUE;						
		break;
	case 'e':
		exit(0);									
		break;
	}
	glutPostRedisplay();
}

void animate() {
	if (isAnimate) {
		if (y > 0) {
			if (x < x0_ball + 2 * cos(alpha*M_PI / 180)) {
				x += 0.5 * (9.8 * sin(alpha*M_PI / 180)) * t * t * cos(alpha*M_PI / 180);
				y -= 0.5 * (9.8 * sin(alpha*M_PI / 180)) * t * t * sin(alpha*M_PI / 180);
				t1 = t;
			}
			else if (!(x < x0_ball + 2 * cos(alpha*M_PI / 180)))
			{
				v0 = 9.8 * sin(alpha*M_PI / 180) * t1;

				x += (0.5 * (9.8) * t * t + v0 * t) * sin(alpha*M_PI / 180);
				y -= (0.5 * (9.8) * t * t + v0 * t) * cos(alpha*M_PI / 180);

				if (y <= 0) {
					H /= 2;
					y = H;
				}
			}
		}

		t += 0.005;
		glutPostRedisplay();
		Sleep(animationPeriod);
	}
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x_eye, y_eye, z_eye, 0.0, High / 2, 0.0, 0.0, 1.0, 0.0);

	gold_setLight();
	if (first){
		cube.makeToroidalSpiral();
		first = 0;
	}
	glPushMatrix();
	glTranslated(3.2, 6, 0.0);
	glScaled(0.3, 0.3, 0.3);
	cube.draw();
	glPopMatrix();


	cooper_setLight();
	glColor3f(0.0, 0.6, 0.0);
	glPushMatrix();
	glScaled(8.0, 0.1, 3.0);
	glutSolidCube(1.0);
	glPopMatrix();

	cooper_setLight();
	glColor3f(0.3, 0.8, 0.6);
	glPushMatrix();
	glTranslated(-4.0, High, 0.0);
	glRotatef(-alpha, 0.0, 0.0, 1.0);
	glScaled(2.0, 0.1, 2.0);

	glutSolidCube(1.0);
	glPopMatrix();

	silver_setLight();
	glColor3f(0.0, 0.0, 0.6);
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glutSolidSphere(0.2, 15, 15);

	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(600, 500);
	glutCreateWindow("Toroidal Spirals");
	glutDisplayFunc(render);
	glutKeyboardFunc(myKeyboard);

	glutIdleFunc(animate);

	Init();
	glutMainLoop();
}

