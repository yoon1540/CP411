/*
 * Description: SimpleView reference design
 * Author: Andrew Yoon
 * Version: 2023-10-27
 */

#include "Matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

Matrix::Matrix() {
	loadIdentity();
}

// mat <- identity matrix
void Matrix::loadIdentity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrixPreMultiply(Matrix* m) {
	// add code here
	GLfloat temp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = m->mat[i][0] * mat[0][j] + m->mat[i][1] * mat[1][j] + m->mat[i][2] * mat[2][j] + m->mat[i][3] * mat[3][j];
			}
		}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = temp[i][j];
		}
	}
}

// transpose  mat <- mat'
void Matrix::transpose() {
	// add code here
	for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat[i][j] = -mat[i][j];
			}
		}
}

// normalize MC
void Matrix::normalize() {
	// add code here
	for (int i = 0; i < 4; i++) {
			GLfloat sum = 0;
			for (int j = 0; j < 4; j++) {
				sum += mat[j][i];
			}
			for (int j = 0; j < 4; j++) {
				mat[j][i] /= sum;
			}
		}
}

// v  <- mat * v
void Matrix::multiplyVector(GLfloat* v) {
	// add code here
	GLfloat temp[4];
		for (int i = 0; i < 4; i++) {
			temp[i] = mat[i][0] * v[0] + mat[i][1] * v[1] + mat[i][2] * v[2] + mat[i][3] * v[3];
		}
		for (int i = 0; i < 4; i++) {
			v[i] = temp[i];
		}
}

void Matrix::rotateMatrix(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
// add code here
	GLfloat r = angle * 3.1415926/180;
		GLfloat axisVectLength = sqrt(rx*rx+ry*ry+rz*rz);
		GLfloat cosA = cos(r);
		GLfloat oneC = 1 - cosA;
		GLfloat sinA = sin(r);
		GLfloat ux = (rx)/axisVectLength;
		GLfloat uy = (ry)/axisVectLength;
		GLfloat uz = (rz)/axisVectLength;

		mat[0][0] = ux*ux*oneC + cosA;
		mat[0][1] = ux*uy*oneC - uz*sinA;
		mat[0][2] = ux*uz*oneC + uy*sinA;
		mat[0][3] = 0;

		mat[1][0] = uy*ux*oneC + uz*sinA;
		mat[1][1] = uy*uy*oneC + cosA;
		mat[1][2] = uy*uz*oneC - ux*sinA;
		mat[1][3] = 0;

		mat[2][0] = uz*ux*oneC - uy*sinA;
		mat[2][1] = uz*uy*oneC + ux*sinA;
		mat[2][2] = uz*uz*oneC + cosA;
		mat[2][3] = 0;

		mat[3][0] = 0;
		mat[3][1] = 0;
		mat[3][2] = 0;
		mat[3][3] = 1;
}



