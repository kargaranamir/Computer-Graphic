#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\freeglut.h>
#include <iostream>
#include <math.h>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define TUBE_N 64
#define TUBE_M 32

class Point3d{
public:
	double x,y,z;
};

class Vector3d{
public:
	double x,y,z;
};

class VertexID{
public:
	GLint vertIndex, normIndex;
};

class Face{
public:
	GLint numVerts;
	VertexID *vert;
};

class Mesh
{
private:
	GLint numVerts;
	Point3d *pt;
	GLint numNormals;
	Vector3d *norm;
	GLint numFaces;
	Face *face;


public:
	Mesh(void);
	~Mesh(void);

	void draw(void);
	void makeToroidalSpiral(void);
	void Niyovil(int );
	int next(int , int);
	
};

