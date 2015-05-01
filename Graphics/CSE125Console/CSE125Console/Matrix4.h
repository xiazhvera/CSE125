#include "stdafx.h"

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define M_PI 3.14159265358979323846

#include "Vector4.h"
#include "Vector3.h"
#include <iostream>
#include <string>

class Matrix4
{

public:
	float f_m[4][4];
	double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
	Matrix4();
	Matrix4(double);
	Matrix4(Vector3, Vector3, Vector3, Vector3);
	Matrix4& operator=(const Matrix4&);
	float* getFloatPointer();

	double* getPointer();
	void identity();
	void transpose();

	void resetTranslate();

	Matrix4 operator*(const Matrix4& m2);//multiply matrix with matrix
	Vector4 operator*(const Vector4& v);//multiply matrix with vector
	Vector3 transform(const Vector3& v);//multiply matrix with vector
	void makeRotateX(double angle);// make rotation matrix about X axis with angle in degrees (note that the sin/cos functions in C++ expect radians so you need to convert to radians within the fmakeRotateZ(double angle);// make rotation matrix about Z axis with angle in degrees
	void makeRotateY(double);
	void makeRotateZ(double angle);
	void makeRotate(double angle, const Vector3& axis);// Make a rotation matrix about an arbitrary axis
	void makeScale(double sx, double sy, double sz);// make a non-uniform scaling matrix
	void makeTranslate(double tx, double ty, double tz);// make a translation matrix
	void print(string comment);// print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
	Matrix4 inverseMatrix4x4(const float *m);
};

#endif