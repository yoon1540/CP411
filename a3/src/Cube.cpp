/*
 * Description: SimpleView reference design
 * Author: Andrew Yoon
 * Version: 2023-10-27
 */

#include "Cube.hpp"

Cube::Cube()
{
	// set set cordinate values for all vertices
    // other faces
    GLfloat v[8][3] = {
    {-1.0, -1.0,  1.0 },
    {-1.0, -1.0, -1.0 },
    {-1.0,  1.0, -1.0 },
    {-1.0,  1.0,  1.0 },
    {1.0,  -1.0,  1.0 },
    {1.0,  -1.0, -1.0 },
    {1.0,   1.0, -1.0 },
    {1.0,   1.0,  1.0 }
    };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            vertex[i][j] = v[i][j];
        }
    }
    // other faces
    GLint faces[6][4] = { /* Vertex indices for the 6 faces */
    { 0, 3, 2, 1 },
    { 2, 3, 7, 6 },
    { 4, 5, 6, 7 },
    { 0, 1, 5, 4 },
    { 1, 2, 6, 5 },
    { 3, 0, 4, 7 }
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            face[i][j] = faces[i][j];
        }
    }

    r = 1.0;
    g = 1.0;
    b = 1.0;
}

void Cube::drawFace(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertex[face[i][0]]);
    glVertex3fv(vertex[face[i][1]]);
    glVertex3fv(vertex[face[i][2]]);
    glVertex3fv(vertex[face[i][3]]);
    glEnd();
}

void Cube::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    // set color
    glColor3f(r,g,b);
    glScalef(s,s,s);
    // draw all faces
    for (int i =0; i < 6; i++) {
        drawFace(i);
    }
    glPopMatrix();
}

