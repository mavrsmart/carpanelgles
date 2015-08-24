// objects.c
//
// Copyright (C) 2014 mavrsmart <mavr@smarts.zp.ua>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//           objects.c
//  Чт Август 21 23:36:30 2014
//  Copyright  2014  user
//  <user@host>

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
//#include <GL/glut.h>
#include "opengles/esUtil.h"
#include "FreeImage.h"
  
#include <math.h>
#include <assert.h>

#include <zlib.h>
#include <unistd.h>
#include "setings.h"
#include "vars.h"
#include "objects.h"

using namespace std;

void* imgPixels;  
int imgWidth;   // Width of the texture image.
int imgHeight;  // Height of the texture image.

void* dashPixels;  // Pointer to raw RGB data for texture.
int dashWidth;   // Width of the texture image.
int dashHeight;  // Height of the texture image.

ESContext* dashcontext;




void str_cp(char **s1, char *s2,char *s3){
  *s1 = new char [strlen(s2)+strlen(s3)+1];
  char *temp = *s1;

  while (*s2)
  {
     *temp++ = *s2++;
  }
  while (*s3)
  {
     *temp++ = *s3++;
  }
  *temp = '\0';
}

GLuint loadTexture( char* fileName ) {
        // Loads a texture image using the FreeImage library, and stores
        // the required info in global variables imgPixels, imgWidth, imgHeight.
        // The parameter fileName is a string that contains the name of the
        // image file from which the image is to be loaded.  If the
        // image can't be loaded, then imgPixels will be set to be a null pointer.
        
    imgPixels = 0; // Null pointer to signal that data has not been read.
    
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(fileName);
         // FREE_IMAGE_FORMAT is a type defined by the FreeImage library.
         // Here, the format is determined from the file extension in
         // the file name, such as .png, .jpg, or .gif.  Many formats
         // are supported.
    
    if (format == FIF_UNKNOWN) {
        printf("Unknown file type for texture image file %s\n", fileName);
        return 0;
    }
    
    FIBITMAP* bitmap = FreeImage_Load(format, fileName, 0);
          // FIBITMAP is a type defined by the FreeImage library, representing
          // the raw image data plus some metadata such as width, height,
          // and the format of the image data.  This actually tries to
          // read the data from the specified file.
          
    if (!bitmap) {
        printf("Failed to load image %s\n", fileName);
        return 0;
    }
    
    FIBITMAP* bitmap2 = FreeImage_ConvertTo32Bits(bitmap);
          // This creates a copy of the image, with the data represented
          // in standard RGB (or BGR) format, for use with OpenGL.
    
    FreeImage_Unload(bitmap);
          // After finishing with a bitmap, it should be disposed.
          // We are finished with bitmap, but not with bitmap2, since
          // we will continue to use the data from bitmap2.
          
    imgPixels = FreeImage_GetBits(bitmap2);  // Get the data we need!
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    
    if (imgPixels) {
        printf("Texture image loaded from file %s, size %dx%d\n", 
                         fileName, imgWidth, imgHeight);
    }
    else {
        printf("Failed to get texture data from %s\n", fileName);
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgPixels);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	
	return texture;
	
} // end loadTexture


void drawquad(GLuint texture,int x,int y,int x1,int y1){
glBindTexture(GL_TEXTURE_2D, texture);
/*
glBegin(GL_QUADS);
        glTexCoord2f( 0, 1);
        glVertex2i(x, y1);
        glTexCoord2i( 0, 0);
        glVertex2i(x, y);
        glTexCoord2i( 1, 0);
        glVertex2i(x1, y);
        glTexCoord2i( 1, 1);
        glVertex2i(x1, y1);
        glEnd();
*/		
}

void drawtriangle(GLuint texture,int x,int y,int x1,int y1){
glBindTexture(GL_TEXTURE_2D, texture);
	/*
glBegin(GL_TRIANGLES);
        glTexCoord2f( 0, 1);
        glVertex2i(x, y1);
        glTexCoord2i( 0, 0);
        glVertex2i(x, y);
        glTexCoord2i( 1, 0);
        glVertex2i(x1, y);
        glTexCoord2i( 0, 1);
        glVertex2i(x, y1);
        glEnd();
		*/
}

void drawdashboard(GLuint texture,int x,int y,int x1,int y1){
if(sets.dashboardenable==1){
	
 //  glPushMatrix();
//glTranslated(0,250,0);



	
		glBindTexture(GL_TEXTURE_2D, texture);
	/*
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1);
        	glVertex2i(x, y1);
        	glTexCoord2i( 0, 0);
        	glVertex2i(x, y);
        	glTexCoord2i( 1, 0);
        	glVertex2i(x1, y);
        	glTexCoord2i( 1, 1);
        	glVertex2i(x1, y1);
        glEnd();
*/
			
//drawquad(texture,x,y,x1,y1);
//glPopMatrix();
}
}	

void drawzn(GLuint texture,int x,int y,int lenx,int leny,int active){
    //drawquad(texture,x,y,lenx,leny);
		glBindTexture(GL_TEXTURE_2D, texture);
	/*
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1);
        	glVertex2i(x, y+leny);
        	glTexCoord2i( 0, 0);
        	glVertex2i(x, y);
        	glTexCoord2i( 1, 0);
        	glVertex2i(x+lenx, y);
        	glTexCoord2i( 1, 1);
        	glVertex2i(x+lenx, y+leny);
        glEnd();
		*/
}

