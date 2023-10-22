/*
 * objects.hpp
 *
 *  Created on: Oct 3, 2023
 *      Author: andre
 */
#include <string>
#include <GL/gl.h>

#ifndef OBJECTS_HPP_
#define OBJECTS_HPP_

typedef enum shape {
	RECTANGLE = 1,
	CIRCLE
} SHAPE;

typedef struct object {
	SHAPE shape;
	int x1, x2, y1, y2;
	GLfloat fr, fg, fb;
	GLfloat sr, sg, sb;
	GLint swidth;

} OBJECT;

typedef struct node {
   OBJECT *object;
   struct node *prev, *next;
} NODE;

// Doubly linked list
typedef struct objectlist {
	NODE *start, *end;
} LIST;

void insert(LIST *list, OBJECT *object);
void deleteNode(LIST *list, NODE **selectp);
void clearList(LIST *list);
void drawShape(OBJECT *object);
void drawShapeHighLight(OBJECT *object);
void drawList(LIST *list);

void setPixel(GLint x, GLint y);
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x, const GLint& y);
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2);
void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y);
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2);


#endif /* OBJECTS_HPP_ */
