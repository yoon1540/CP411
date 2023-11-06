#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];  /* 2D array to store cube vertices */
	GLint face[3][3];      /* 2D array to store faces */
    GLint bottom[1][4];
	GLfloat r, g, b;       /* color cube */
public:
	Pyramid();
	void draw();
	void drawFaceSide(int);
    void drawFaceBot();
};

#endif
