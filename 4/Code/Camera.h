#pragma once
#include "Structs.h"

class Camera {
private:
	Point3 eye, look, up;
	Vector3 u, v, n;
	double viewAngle, aspect, nearDist, farDist; 
	void setModelviewMatrix(); 

public:
	void set(Point3 eye, Point3 look, Vector3 up);
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void slide(double delU, double delV, double delN);
	void setShape(float vAng, float asp, float nearD, float farD) {
		viewAngle = vAng; aspect = asp; nearDist = nearD; farDist = farD;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(viewAngle, aspect, nearDist, farDist);
	}
};