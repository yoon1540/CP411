/*
 * menu.cpp
 *
 *  Created on: Oct 3, 2023
 *      Author: andre
 */

#include <GL/glut.h>
#include "menu.hpp"
#include "object.hpp"
#include "edit.hpp"
#include "file.hpp"


GLsizei  windowHeight = 600, windowWidth = 800;

extern GLint oprMode, objType, moveMode;
extern NODE *selectNode;
extern GLint strokeWidth;
extern GLfloat fillred, fillgreen, fillblue, sred, sgreen, sblue;


void clear(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mainMenu(GLint menuOption){
	switch (menuOption) {
	case 1:
		clear();
		break;
	case 2:
		exit(0);
	}
	glutPostRedisplay();
	}

void drawSubMenuFunc(GLint drawOption){
	switch (drawOption) {
		case 1:
			objType = RECTANGLE;
			break;
		case 2:
			objType = CIRCLE;
			break;
		}
	glutPostRedisplay();
}

void styleSubMenuFunc(GLint styleOption){

}

void editSubMenuFunc(GLint editOption){
	oprMode = 1;
	moveMode = 0;

	switch(editOption){
		case 1:
			break;
		case 2:
			Delete(&selectNode);
			break;
		case 3:
			moveFront(selectNode);
			break;
		case 4:
			moveBack(selectNode);
			break;
		case 5:
			moveMode = 1;
		}


		glutPostRedisplay();
}

void fileSubMenuFunc(GLint fileOption){
	switch(fileOption){
			case 1:
				saveSVG("output.svg",windowWidth, windowHeight);
				break;
			case 2:
				openSVG("output.svg");
				break;
			case 3:
				saveBitmap("output.bmp", 0, 0, windowWidth, windowHeight);
		}

		glutPostRedisplay( );
}

void fillSubMenuFunc(GLint fillOption){
	switch(fillOption){
			case 1://red
				fillred = 1.0;
				fillgreen = 0.0;
				fillblue = 0.0;
				break;
			case 2://green
				fillred = 0.0;
				fillgreen = 1.0;
				fillblue = 0.0;
				break;
			case 3://blue
				fillred = 0.0;
				fillgreen = 0.0;
				fillblue = 1.0;
				break;
			case 4://black
				fillred = 0.0;
				fillgreen = 0.0;
				fillblue = 0.0;
				break;
			case 5://white
				fillred = 1.0;
				fillgreen = 1.0;
				fillblue = 1.0;
		}

		glutPostRedisplay();
}

void strokeSubMenuFunc(GLint strokeOption){
	switch(strokeOption){
			case 1://red
				sred = 1.0;
				sgreen = 0.0;
				sblue = 0.0;
				break;
			case 2://green
				sred = 0.0;
				sgreen = 1.0;
				sblue = 0.0;
				break;
			case 3://blue
				sred = 0.0;
				sgreen = 0.0;
				sblue = 1.0;
				break;
			case 4://black
				sred = 0.0;
				sgreen = 0.0;
				sblue = 0.0;
				break;
			case 5://white
				sred = 1.0;
				sgreen = 1.0;
				sblue = 1.0;
		}
		glutPostRedisplay();
}

void widthSubMenuFunc(GLint widthOption){
	switch(widthOption){
			case 1:
				strokeWidth = 1;
				break;
			case 2:
				strokeWidth = 2;
				break;
			case 3:
				strokeWidth = 3;
				break;
			case 4:
				strokeWidth = 4;
				break;
			case 5:
				strokeWidth = 5;
		}
		glutPostRedisplay();
}

void menuInit(){

	GLint drawSubMenu, styleSubMenu, editSubMenu, fileSubMenu, fillSubMenu, strokeSubMenu, widthSubMenu;

	drawSubMenu = glutCreateMenu(drawSubMenuFunc);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);



	fillSubMenu = glutCreateMenu(fillSubMenuFunc);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);

	strokeSubMenu = glutCreateMenu(strokeSubMenuFunc);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);

	widthSubMenu = glutCreateMenu(widthSubMenuFunc);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);
	// sub - sub menu

	styleSubMenu = glutCreateMenu(styleSubMenuFunc);
	glutAddSubMenu("Fill Colour", fillSubMenu);
	glutAddSubMenu("Stroke Colour", strokeSubMenu);
	glutAddSubMenu("Stroke Width", widthSubMenu);

	editSubMenu = glutCreateMenu(editSubMenuFunc);
	glutAddMenuEntry("Select", 1);
	glutAddMenuEntry("Delete", 2);
	glutAddMenuEntry("Move front", 3);
	glutAddMenuEntry("Move back", 4);
	glutAddMenuEntry("Move around", 5);

	fileSubMenu = glutCreateMenu(fileSubMenuFunc);
	glutAddMenuEntry("Save SVG", 1);
	glutAddMenuEntry("Open SVG", 2);
	glutAddMenuEntry("Export Bitmap", 3);


	glutCreateMenu(mainMenu); // Create main pop-up menu
	glutAddMenuEntry("New", 1);
	glutAddSubMenu("Draw", drawSubMenu);
	glutAddSubMenu("Style", styleSubMenu);
	glutAddSubMenu("Edit", editSubMenu);
	glutAddSubMenu("File", fileSubMenu);
	glutAddMenuEntry("Quit", 6);
}


