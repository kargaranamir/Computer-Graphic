// In the Name of Allah
// Making a mesh for the Toroidal Spirals
#include "Mesh.h"

static float a = 2.0, b = 0.5;
static float R = 0.3;
static int p = 3, q = 8;  //1,7  3,8  2,5   1,3

GLfloat xOfCurve(float t){
	return ((a + b*cos(q*t))*cos(p*t));
}

GLfloat yOfCurve(float t){
	return ((a + b*cos(q*t))*sin(p*t));
}

GLfloat zOfCurve(float t){
	return (b*sin(q*t));
}

GLfloat dxOfCurve(float t){
	return -p * yOfCurve(t) - b*q*sin(q*t)*cos(p*t);
}

GLfloat dyOfCurve(float t){
	return p * xOfCurve(t) - b*q *sin(q*t) *sin(p*t);
}

GLfloat dzOfCurve(float t){
	return b * q * cos(q*t);
}

GLfloat ddxOfCurve(float t){
	return -p * dyOfCurve(t) + b *q * (p * sin(q*t) * sin(p*t) - q*cos(q*t)*cos(p*t));
}

GLfloat ddyOfCurve(float t){
	return p * dxOfCurve(t) - b*q*(p*sin(q*t)*cos(p*t) + q*cos(q*t)*sin(p*t));
}

GLfloat ddzOfCurve(float t){
	return -(q*q)*b*sin(q*t);
}

void normalize(GLdouble A[3]){
	GLdouble mag = sqrt(A[0] * A[0] + A[1] * A[1] + A[2] * A[2]);
	A[0] = A[0] / mag;
	A[1] = A[1] / mag;
	A[2] = A[2] / mag;
}


void cross(GLdouble A[3], GLdouble B[3], GLdouble C[3]){
	GLdouble a1 = A[0], a2 = A[1], a3 = A[2];
	GLdouble b1 = B[0], b2 = B[1], b3 = B[2];
	C[0] = a2*b3 - a3*b2;
	C[1] = a3*b1 - a1*b3;
	C[2] = a1*b2 - a2*b1;
}

Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}

void Mesh::draw(){
	for (int f=0; f<numFaces; f++){
		glBegin(GL_POLYGON); //GL_POLYGON |  GL_LINE_LOOP
			for (int v=0; v<face[f].numVerts; v++){
				int in = face[f].vert[v].normIndex;
				int iv = face[f].vert[v].vertIndex;


				glNormal3d(norm[in].x, norm[in].y, norm[in].z);
				glVertex3d(pt[iv].x, pt[iv].y, pt[iv].z);
			}
		glEnd();
	}
}


int Mesh::next(int v, int n)
{
	if ((v + 1) % n == 0)
		return v - (n - 1);
	else
		return (v + 1);

}

void Mesh::Niyovil(int i)
{
	int j, mx = 0, my = 0, mz = 0;
	for (j =0 ; j < 4; j++) {

		mx += ((pt[face[i].vert[j].vertIndex].y - pt[face[i].vert[(j + 1) % 4].vertIndex].y)*(pt[face[i].vert[j].vertIndex].z + pt[face[i].vert[(j + 1) % 4].vertIndex].z));
		my += ((pt[face[i].vert[j].vertIndex].z - pt[face[i].vert[(j + 1) % 4].vertIndex].z)*(pt[face[i].vert[j].vertIndex].x + pt[face[i].vert[(j + 1) % 4].vertIndex].x));
		mz += ((pt[face[i].vert[j].vertIndex].x - pt[face[i].vert[(j + 1) % 4].vertIndex].x)*(pt[face[i].vert[j].vertIndex].y + pt[face[i].vert[(j + 1) % 4].vertIndex].y));

	}
	norm[i].x = mx;
	norm[i].y = my;
	norm[i].z = mz;
}


GLdouble tube[TUBE_N+1][TUBE_M][3];
void Mesh::makeToroidalSpiral(void){

	float dt = 2 * M_PI / TUBE_N;
	float du = 2 * M_PI / TUBE_M;
	float t = 0.0;
	int i;
	for (i = 0, t = 0.0; i < TUBE_N + 1; i++, t += dt) {
		GLdouble C[3], T[3], A[3], B[3], N[3];
		C[0] = xOfCurve(t), C[1] = yOfCurve(t), C[2] = zOfCurve(t);
		T[0] = dxOfCurve(t), T[1] = dyOfCurve(t), T[2] = dzOfCurve(t);
		A[0] = ddxOfCurve(t), A[1] = ddyOfCurve(t), A[2] = ddzOfCurve(t);
		cross(T, A, B);
		normalize(T);
		normalize(B);
		cross(B, T, N);
		int j, k; float u;
		for (j = 0, u = 0.0; j < TUBE_M; j++, u += du){
			for (k = 0; k < 3; k++) {
				tube[i][j][k] = C[k] + R*cos(u)*B[k] + R *sin(u)*N[k];
 
			}
		}

	}

	numVerts = TUBE_M * (TUBE_N + 1);
	pt = new Point3d[numVerts];

	numNormals = TUBE_N * TUBE_M;
	norm = new Vector3d[numNormals];

	numFaces = TUBE_N * TUBE_M;
	face = new Face[numFaces];

	for (int i = 0; i < TUBE_N +1 ; i++) {
		for (int j = 0; j < TUBE_M; j++) {
			// create vetex list
			pt[TUBE_M * i + j].x = tube[i][j][0];
			pt[TUBE_M * i + j].y = tube[i][j][1];
			pt[TUBE_M * i + j].z = tube[i][j][2];
		}
	}

	for (int i = 0; i < TUBE_N  ; i++){
		for (int j = 0; j < TUBE_M; j++) {
			//create face list
			face[TUBE_M * i + j].numVerts = 4;
			face[TUBE_M * i + j].vert = new VertexID[numVerts];

			face[TUBE_M * i + j].vert[0].vertIndex = TUBE_M * i + j;
			face[TUBE_M * i + j].vert[1].vertIndex = next(TUBE_M * i + j, TUBE_M);
			face[TUBE_M * i + j].vert[2].vertIndex = next(TUBE_M * i + j + TUBE_M, TUBE_M);
			face[TUBE_M * i + j].vert[3].vertIndex = TUBE_M * i + j + TUBE_M;
					
		}
	}
	for (int i = 0; i < TUBE_N; i++) 
		for (int j = 0; j < TUBE_M; j++) 
			Niyovil(TUBE_M * i + j);

	for (int i = 0; i < TUBE_N; i++)
		for (int j = 0; j < TUBE_M; j++){
		face[TUBE_M * i + j].vert[0].normIndex = TUBE_M * i + j;
		face[TUBE_M * i + j].vert[1].normIndex = TUBE_M * i + j;
		face[TUBE_M * i + j].vert[2].normIndex = TUBE_M * i + j;
		face[TUBE_M * i + j].vert[3].normIndex = TUBE_M * i + j;

		}

}



