#include "Pyramid.hpp"

Pyramid::Pyramid()
{
	// set set cordinate values for all vertices
    GLfloat v[5][3] = { /* declare array and initialize vertices of cube */
    {0.0, 0.0, 1.0 },
    {-1.0, -1.0, -1.0 },
    {-1.0, 1.0, -1.0 },
    {1.0, 1.0, -1.0 },
    {1.0, -1.0, -1.0 }
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            vertex[i][j] = v[i][j];
        }
    }
    // other faces
    GLint faces[3][3] = {
    { 0, 1, 2 },
    { 0, 2, 3 },
    { 0, 3, 4 }
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            face[i][j] = faces[i][j];
        }
    }

    bottom[0][0] = 1;
    bottom[0][1] = 2;
    bottom[0][2] = 3;
    bottom[0][3] = 4;

    r = 1.0;
    g = 1.0;
    b = 0.0;
}

void Pyramid::drawFaceSide(int i)
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertex[face[i][0]]);
    glVertex3fv(vertex[face[i][1]]);
    glVertex3fv(vertex[face[i][2]]);
    glEnd();
}

void Pyramid::drawFaceBot()
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertex[bottom[0][0]]);
    glVertex3fv(vertex[bottom[0][1]]);
    glVertex3fv(vertex[bottom[0][2]]);
    glVertex3fv(vertex[bottom[0][3]]);
    glEnd();
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    // set color
    glColor3f(r,g,b);
    glScalef(s,s,s);
    // draw all faces
    for (int i =0; i < 3; i++) {
        drawFaceSide(i);
    }
    drawFaceBot();
    glPopMatrix();
}

