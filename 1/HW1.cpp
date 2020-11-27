#include <windows.h>  // For MS Windows
#include <gl/glut.h>  // GLUT, includes glu.h and gl.h

typedef struct {
	float    x;
	float    y;
} point; 

 point A[9] = { { -0.125f, -0.5f }, { -0.125f, 0.0f }, { -0.25f, 0.0f }, { -0.25f, 0.25f } 
, { 0.0f, 0.25f }, { 0.25f, 0.25f }, { 0.25f, 0.0f }, { 0.125f, 0.0f }, { 0.125f, -0.5f } };  // T Model

 point B[9] = { { -0.125f, 0 }, { -0.125f, -0.5f }, { -0.25f, -0.5f }, { -0.25f, 0.25f }
 , { 0.0f, 0.75f }, { 0.25f, 0.25f }, { 0.25f, -0.5f }, { 0.125f, -0.5f }, { 0.125f, 0 } }; // Home Model

 point C[9] = { { 0.0f, 1.0f }, { 0.643f, 0.766f }, { 0.985f, 0.174f }, { 0.866f, -0.5f }   // Regular 9-Sided Model 
 , { 0.342f, -0.940f }, { -0.342f, -0.940f }, { -0.866f, -0.5f }, { -0.985f, 0.174f }, { -0.643f, 0.766f }};

 point T[9]; // Showing Model

 int state = 0;  // State

 float t = 0.0;   // Counter
 float frame = 4800.0; // Number of frames for convert (order of interpolation)

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer


	glBegin(GL_LINES);              // Draw
	glColor3f(1.0f, 0.0f, 0.0f);   // Red

	for (int i = 0; i < 9; i++)

	{
		glVertex2f(T[i].x, T[i].y);
		if (i != 8)
			glVertex2f(T[i + 1].x, T[i + 1].y);
		else
			glVertex2f(T[0].x, T[0].y);

	}

	glEnd();
	glFlush();  // Render now
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:             // ESCAPE key for exit
		exit(0);
		break;

	case 't':
		t = 0;
		state = 0;
		break;
	case 'c':
		t = 0;
		state = 1;
		break;
	case 'd':
		t = 0;
		state = 2;
		break;
	case 'p':
		t = 0;
		state = 3;
		break;
	}
}

void AnimateScene(void)
{

	if (state == 0) {  // T Model
		for (int i = 0; i < 9; i++)
		{
			T[i].x = A[i].x;
			T[i].y = A[i].y;
		}
	}

	else if (state == 1){ // Home Model
		for (int i = 0; i < 9; i++)
		{
			T[i].x = B[i].x;
			T[i].y = B[i].y;
		}

	}

	else if (state == 2){ // Converting 
			t++;
			if (t > frame)
				t = frame;

		for (int i = 0; i < 9; i++)
		{
			T[i].x = A[i].x + (t / frame)*(B[i].x - A[i].x);
			T[i].y = A[i].y + (t / frame)*(B[i].y - A[i].y);
		}

	}
	else if (state == 3){  //Converting another 2 models ( Home to Regular 9-Sided Model)
		t++;
		if (t > frame)
			t = frame;

		for (int i = 0; i < 9; i++)
		{
			T[i].x = B[i].x + (t / frame)*(C[i].x *0.5f- B[i].x);
			T[i].y = B[i].y + (t / frame)*(C[i].y *0.5f- B[i].y);
		}
	}

	// Force redraw
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("Amirhossein Kargaran 9429523"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutKeyboardFunc(Keyboard); // Keuboard function
	glutIdleFunc(AnimateScene); // Update glut window continuously
	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}