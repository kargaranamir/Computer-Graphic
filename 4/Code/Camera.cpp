#pragma once
#include "Camera.h"
void Camera::setModelviewMatrix(void) {
	float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z);
	m[0] = u.i; m[4] = u.j; m[8] = u.k; m[12] = -eVec.dot(u);
	m[1] = v.i; m[5] = v.j; m[9] = v.k; m[13] = -eVec.dot(v);
	m[2] = n.i; m[6] = n.j; m[10] = n.k; m[14] = -eVec.dot(n);
	m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}
void Camera::set(Point3 Eye, Point3 Look, Vector3 Up) {
	eye.set(Eye);
	look.set(Look);
	up.set(Up.i, Up.j, Up.k);
	n.set(eye.x - Look.x, eye.y - Look.y, eye.z - Look.z);
	Vector3 upCross = Up.cross(n);
	u.set(upCross);
	n.normalize(); u.normalize();
	Vector3 nCross = n.cross(u);
	v.set(nCross);
	setModelviewMatrix();
}
void Camera::slide(double delU, double delV, double delN) {
	eye.x += delU * u.i + delV * v.i + delN * n.i;
	eye.y += delU * u.j + delV * v.j + delN * n.j;
	eye.z += delU * u.k + delV * v.k + delN * n.k;
	look.x += delU * u.i + delV * v.i + delN * n.i;
	look.y += delU * u.j + delV * v.j + delN * n.j;
	look.z += delU * u.k + delV * v.k + delN * n.k;
	setModelviewMatrix();
}
void Camera::roll(float angle) {
	double PI = 3.141592654;
	double radangle = PI * angle / 180.0;
	double cs, sn;
	cs = cos(radangle);
	sn = sin(radangle);
	Vector3 t(u.i, u.j, u.k);
	u.set(t.i * cs + v.i * sn, t.j * cs + v.j * sn, t.k * cs + v.k * sn);
	v.set(-t.i * sn + v.i * cs, -t.j * sn + v.j * cs, -t.k * sn + v.k * cs);
	setModelviewMatrix();
}
void Camera::pitch(float angle) {
	double PI = 3.141592654; 
	double radangle = PI * angle / 180.0;
	double cs, sn;
	cs = cos(radangle);
	sn = sin(radangle);
	Vector3 t(n.i, n.j, n.k);
	n.set(t.i * cs - v.i * sn, t.j * cs - v.j * sn, t.k * cs - v.k * sn);
	v.set(t.i * sn + v.i * cs, t.j * sn + v.j * cs, t.k * sn + v.k * cs);
	setModelviewMatrix();
}
void Camera::yaw(float angle) {
	double PI = 3.141592654;
	double radangle = PI * angle / 180.0;
	double cs, sn;
	cs = cos(radangle);
	sn = sin(radangle);
	Vector3 t(n.i, n.j, n.k);
	n.set(t.i * cs + u.i * sn, t.j * cs + u.j * sn, t.k * cs + u.k * sn);
	u.set(-t.i * sn + u.i * cs, -t.j * sn + u.j * cs, -t.k * sn + u.k * cs);
	setModelviewMatrix();
}