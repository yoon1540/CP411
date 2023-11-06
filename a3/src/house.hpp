#ifndef CHOUSE_H
#define CHOUSE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class House: public Shape {
protected:
	GLfloat vertexCube[8][3];
	GLint faceCube[6][4];
    GLfloat vertexP[5][3];
	GLint faceP[3][3];
    GLint bottom[1][4];
	GLfloat r, g, b;       /* color cube */
public:
	House();
	void draw();
	void drawFaceCube(int);
    void drawFaceP(int);
    void drawBotP();
};

#endif
