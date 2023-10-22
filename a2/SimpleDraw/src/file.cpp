/*
 * file.cpp
 *
 *  Created on: Oct 3, 2023
 *      Author: andre
 */


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "file.hpp"
#include "object.hpp"
#include "edit.hpp"

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

extern LIST objlist;

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight) {
	FILE *fp = fopen(ptrcFileName, "wb");
		if (fp == NULL)
			return 0;

		int bitsize = nWidth*nHeight*3 +  ((3*nWidth)%4 == 0 ? 0 : (4-(3*nWidth)%4)*nHeight);

		printf("step 0 %d\n", bitsize);

		unsigned char *ptrImage = (unsigned char*) malloc(bitsize);
		if (ptrImage == NULL) {
			fclose(fp);
			return 0;
		}

		glReadPixels(nX, nY, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, ptrImage);

		printf("step 1\n");

		BITMAPFILEHEADER bfh;
		BITMAPINFOHEADER bih;
		memset(&bfh, 0, sizeof(bfh));
		memset(&bih, 0, sizeof(bih));


		bfh.bfType = 0x4d42;
		bfh.bfSize = sizeof(bfh) + sizeof(bih) + bitsize;
		bfh.bfOffBits = sizeof(bfh) + sizeof(bih);


		bih.biSize = sizeof(bih);
		bih.biWidth = nWidth + nWidth%4;
		bih.biHeight = nHeight;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		bih.biSizeImage = bitsize;


		if (fwrite(&bfh, sizeof(bfh), 1, fp) < 1) {
			free(ptrImage);
			fclose(fp);
			return 0;
		};

		if (fwrite(&bih, sizeof(bih), 1, fp)<1) {
			free(ptrImage);
			fclose(fp);
			return 0;
		}


		if (fwrite(ptrImage, 1, bitsize, fp) < bitsize ) {
			free(ptrImage);
			fclose(fp);
			return 0;
		}

		fclose(fp);
		free(ptrImage);

		return 1;
}

int saveSVG(const char *filename, int winWidth, int winHeight) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)  return EXIT_FAILURE;

	char line[255];
	int width, height; //store calculated height and width

	//write header data for SVG
	sprintf(line, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(line, fp);
	sprintf(line, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(line, fp);
	sprintf(line, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(line, fp);
	sprintf(line,
			"<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			winWidth, winHeight);
	fputs(line, fp);

	NODE *curr = objlist.start;
	int fr,fb,fg,sr,sb,sg;


	while(curr){
		OBJECT *object = curr->object;

		fr = (int) (curr->object->fr * 255); fb = (int) (curr->object->fb * 255); fg = (int) (curr->object->fg * 255);
		sr = (int) (curr->object->sr * 255); sb = (int) (curr->object->sb * 255); sg = (int) (curr->object->sg * 255);

		if(object->shape == 1)//Rectangle
			sprintf(line,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" storke-width=\"%d\" />\n",
					min(object->x1,object->x2),min(object->y1,object->y2), abs(object->x1-object->x2), abs(object->y1-object->y2),fr,fg,fb,sr,sg,sb,object->swidth);

		else if(object->shape == 2) //Circle
			sprintf(line,"<circle cx=\"%d\" cy=\"%d\" r=\"%f\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\" />\n",
					object->x1,object->y1,sqrt((object->x2-object->x1)*(object->x2-object->x1)+(object->y2-object->y1)*(object->y2-object->y1)),fr,fg,fb,sr,sg,sb,object->swidth);


		fputs(line,fp);
		curr = curr->next;
	}

	sprintf(line, "</svg>\n");
	fputs(line, fp);
	fclose(fp);

	return EXIT_SUCCESS;
}

int openSVG(const char *filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) return EXIT_FAILURE;

	int lineLength = 255;
	char line[lineLength];
	int x1, y1, w, h, fr, fg, fb, sr, sg, sb, sw;

	while ( fgets(line, lineLength, fp)) {

		OBJECT *shapeObj;
		if (line[0] == '<' && line[1] == 'r' ) { // rectangle
			sscanf(line,
					"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
					&x1, &y1, &w, &h, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

			shapeObj = (OBJECT*) malloc(sizeof(OBJECT));
			shapeObj->shape = RECTANGLE;
			shapeObj->x1 = x1;
			shapeObj->y1 = y1;
			shapeObj->x2 = x1 + w;
			shapeObj->y2 = y1 + h;
			shapeObj->fr = fr / 255;
			shapeObj->fg = fg / 255;
			shapeObj->fb = fb / 255;
			shapeObj->sr = sr / 255;
			shapeObj->sg = sg / 255;
			shapeObj->sb = sb / 255;
			shapeObj->swidth = sw;
			insert(&objlist, shapeObj);

		} else if (line[0] == '<' && line[1] == 'c' )  {

		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
