/*
 * Description: SimpleView reference design
 * Author: Andrew Yoon
 * Version: 2023-10-27
 */

#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"
#include <math.h>

bool DEBUG = false;

Camera::Camera(){
	eye.set(5.0, 5.0, 10.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::reset(void) { // make default camera
	eye.set(5.0, 5.0, 10.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, vangle = 40.0, dnear = 1.0, dfar = 15.0;
	setViewNorm();
}

void Camera::setViewNorm() {
	GLfloat x, y, z, sr;
	x = ref.x-eye.x;
	y = ref.y-eye.y;
	z = ref.z-eye.z;
	sr = sqrt(x*x + y*y + z*z);
	x = x/sr;
	y = y/sr;
	z = z/sr;
	viewNorm.set(x, y, z);
}

void Camera::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){
// rotate eye position in WCS
	GLfloat v[3][3];
	GLfloat r = angle * 3.1415926/180;
	GLfloat axisVectLength = sqrt(rx*rx+ry*ry+rz*rz);
	GLfloat cosA = cos(r);
	GLfloat oneC = 1 - cosA;
	GLfloat sinA = sin(r);
	GLfloat ux = (rx)/axisVectLength;
	GLfloat uy = (ry)/axisVectLength;
	GLfloat uz = (rz)/axisVectLength;
	v[0][0] = ux*ux*oneC + cosA;
	v[0][1] = ux*uy*oneC - uz*sinA;
	v[0][2] = ux*uz*oneC + uy*sinA;

	v[1][0] = uy*ux*oneC + uz*sinA;
	v[1][1] = uy*uy*oneC + cosA;
	v[1][2] = uy*uz*oneC - ux*sinA;

	v[2][0] = uz*ux*oneC - uy*sinA;
	v[2][1] = uz*uy*oneC + ux*sinA;
	v[2][2] = uz*uz*oneC + cosA;

	eye.x = eye.x * v[0][0] + eye.y * v[0][1] + eye.z * v[0][2];
	eye.y = eye.x * v[1][0] + eye.y * v[1][1] + eye.z * v[1][2];
	eye.z = eye.x * v[2][0] + eye.y * v[2][1] + eye.z * v[2][2];
}

void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
// translate eye position in WCS
	eye.x += tx;
	eye.y += ty;
	eye.z += tz;
}

void Camera::setProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, aspect, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x,viewup.y,viewup.z);
}

