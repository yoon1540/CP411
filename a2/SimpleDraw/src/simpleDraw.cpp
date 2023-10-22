/*
 * simpleDraw.cpp
 *
 *  Created on: Oct 3, 2023
 *      Author: andre
 */

#include <stdio.h>
#include <GL/glut.h>
#include "object.hpp"
#include "menu.hpp"
#include "edit.hpp"
#include "file.hpp"

GLint oprMode = 0,
	  drawMode = 0,
	  menuMode = 0,
	  moveMode = 0,
	  xbegin, ybegin;
extern GLsizei  windowHeight, windowWidth;



SHAPE objType = CIRCLE;
GLfloat fillred = 1.0, fillgreen = 0.0, fillblue = 0.0,
		sred = 1.0, sgreen = 0.0, sblue = 0.0;
GLint strokeWidth = 1;
LIST objlist = {0};
NODE *selectNode;
OBJECT tempObject;

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("SimpleDraw by Andrew Yoon");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800, 600, 0.0);
}

void drawObjectList() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (objlist.start != NULL)
		drawList(&objlist);


	if (oprMode == 0 && drawMode == 1)
		drawShape(&tempObject);


	if (oprMode == 1 && moveMode == 0 && selectNode != NULL)
		drawShapeHighLight(selectNode->object);

	glFlush();
	glutSwapBuffers();
}

void mouseActionFunc(GLint button, GLint action, GLint xMouse, GLint yMouse) {

	if (oprMode == 0 && menuMode == 0) {
		if (button == GLUT_LEFT_BUTTON) {

			if (action == GLUT_DOWN) {
				tempObject.shape = objType;
				tempObject.fr = fillred;
				tempObject.fg = fillgreen;
				tempObject.fb = fillblue;
				tempObject.sr = sred;
				tempObject.sg = sgreen;
				tempObject.sb = sblue;
				tempObject.swidth = strokeWidth;
				tempObject.x1 = xMouse;
				tempObject.y1 = yMouse;

				drawMode = 1;
				if (objType == RECTANGLE) {
				   tempObject.x2 = xMouse;
				   tempObject.y2 = yMouse;
				}
				else if (objType == CIRCLE) {

					tempObject.x2 = xMouse;
					tempObject.y2 = yMouse;
				}

			} else if (action == GLUT_UP && drawMode == 1) {

				drawMode = 0;
				if (objType == RECTANGLE) {
				   tempObject.x2 = xMouse;
				   tempObject.y2 = yMouse;
				}
				else if (objType == CIRCLE) {

					tempObject.x2 = xMouse;
					tempObject.y2 = yMouse;

				}


				OBJECT *newObj = (OBJECT *) malloc(sizeof(OBJECT));
				*newObj = tempObject;
				insert(&objlist,newObj);

			}
		}

	}
	else if (moveMode == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			selectNode = select(xMouse, yMouse);
		}
	}


	else if (moveMode == 1) {
		if (button == GLUT_LEFT_BUTTON) {

			if (action == GLUT_DOWN) {
				selectNode = select(xMouse, yMouse);
				if (selectNode != NULL) {
					tempObject = *(selectNode->object);
					xbegin = xMouse;
					ybegin = yMouse;
				}

			} else if (action == GLUT_UP) {
				GLint x = xMouse - xbegin; GLint y = yMouse - ybegin;
				if(selectNode != NULL){
					selectNode->object->x1 += x; selectNode->object->x2 += x;
					selectNode->object->y1 += y; selectNode->object->y2 += y;
					selectNode = NULL;
				}
			}
		}
	}

	glutPostRedisplay();
	glFlush();
}

void mouseMotionFunc(GLint xMouse, GLint yMouse) {
	if(moveMode == 1){
			if(selectNode != NULL){
				selectNode->object->x1 += xMouse - xbegin; selectNode->object->x2 += xMouse - xbegin;
				selectNode->object->y1 += yMouse - ybegin; selectNode->object->y2 += yMouse - ybegin;
				xbegin = xMouse; ybegin = yMouse;
			}
		}


	else if(drawMode == 1){
		tempObject.x2 = xMouse;
		tempObject.y2 = yMouse;
	}


	glutPostRedisplay();
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {

	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), GLdouble(newHeight), 0.0);


	windowWidth = newWidth;
	windowHeight = newHeight;
	drawObjectList();
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	glutInit(&argc, argv);
	menuInit();
	init();
	glutReshapeFunc(winReshapeFcn);
	glutDisplayFunc(drawObjectList);
	glutMouseFunc(mouseActionFunc);
	glutMotionFunc(mouseMotionFunc);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

