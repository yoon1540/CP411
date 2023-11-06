#include "House.hpp"

House::House()
{
	// set set cordinate values for all vertices
    GLfloat v1[8][3] = { /* declare array and initialize vertices of cube */
    {-1.0, -1.0,  1.0  },
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
            vertexCube[i][j] = v1[i][j];
        }
    }
    // other faces
    GLint faces1[6][4] = { /* Vertex indices for the 6 faces */
    { 0, 3, 2, 1 },
    { 2, 3, 7, 6 },
    { 4, 5, 6, 7 },
    { 0, 1, 5, 4 },
    { 1, 2, 6, 5 },
    { 3, 0, 4, 7 }
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            faceCube[i][j] = faces1[i][j];
        }
    }

    GLfloat v2[5][3] = { /* declare array and initialize vertices of cube */
    {0.0, 0.0, 2.0 },
    {-1.0, -1.0, 1.0 },
    {-1.0, 1.0, 1.0 },
    {1.0, 1.0, 1.0 },
    {1.0, -1.0, 1.0 }
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            vertexP[i][j] = v2[i][j];
        }
    }
    // other faces
    GLint faces2[3][3] = {
    { 0, 1, 2 },
    { 0, 2, 3 },
    { 0, 3, 4 }
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            faceP[i][j] = faces2[i][j];
        }
    }

    bottom[0][0] = 1;
    bottom[0][1] = 2;
    bottom[0][2] = 3;
    bottom[0][3] = 4;

    r = 1.0;
    g = 0.0;
    b = 0.0;
}

void House::drawFaceCube(int i)
{
// draw face i
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertexCube[faceCube[i][0]]);
    glVertex3fv(vertexCube[faceCube[i][1]]);
    glVertex3fv(vertexCube[faceCube[i][2]]);
    glVertex3fv(vertexCube[faceCube[i][3]]);
    glEnd();
}

void House::drawFaceP(int i)
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertexP[faceP[i][0]]);
    glVertex3fv(vertexP[faceP[i][1]]);
    glVertex3fv(vertexP[faceP[i][2]]);
    glEnd();
}

void House::drawBotP()
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertexP[bottom[0][0]]);
    glVertex3fv(vertexP[bottom[0][1]]);
    glVertex3fv(vertexP[bottom[0][2]]);
    glVertex3fv(vertexP[bottom[0][3]]);
    glEnd();
}

void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    // set color
    glColor3f(r,g,b);
    glScalef(s,s,s);
    // draw all faces
    for (int i =0; i < 6; i++) {
        drawFaceCube(i);
    }
    glColor3f(1,1,0);
    for (int i =0; i < 3; i++) {
        drawFaceP(i);
    }
    drawBotP();
    glPopMatrix();
}

