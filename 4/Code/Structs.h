#pragma once
#include <GL/freeglut.h>
#include <math.h>

#define TWOPI 2*3.14159265

class Point2
{
public:
	float x, y;
	void set(float dx, float dy) { x = dx; y = dy; }
	void set(Point2& p) { x = p.x; y = p.y; }
	Point2(float xx, float yy) { x = xx; y = yy; }
	Point2() { x = y = 0; }
};

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
	void set(Point3& p) { x = p.x; y = p.y; z = p.z; }
	Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
	Point3() { x = y = z = 0; }
};

class Vector3
{
public:
	float i, j, k;
	void set(float dx, float dy, float dz) { i = dx; j = dy; k = dz; }
	void set(Vector3& v) { i = v.i; j = v.j; k = v.k; }
	Vector3(float ii, float jj, float kk) { i = ii; j = jj; k = kk; }
	Vector3() { i = j = k = 0; }

	void normalize() {
		float d = sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2));
		i = i / d;
		j = j / d;
		k = k / d;
	}

	Vector3 cross(Vector3 other) {
		Vector3 res;
		res.i = j * other.k - k * other.j;
		res.j = k * other.i - i * other.k;
		res.k = i * other.j - j * other.i;
		return res;
	}

	float dot(Vector3 other) {
		return i * other.i + j * other.j + k * other.k;
	}
};

