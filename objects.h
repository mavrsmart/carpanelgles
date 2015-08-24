// objects.h
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
//           objects.h
//  Чт Август 21 23:36:30 2014
//  Copyright  2014  user
//  <user@host>

//#include <GL/gl.h>
//#include <GL/glut.h>
#include "opengles/esUtil.h"


#ifndef _OBJECTS_H_
#define _OBJECTS_H_

typedef struct
{
   // Handle to a program object
   GLuint programObject;

   // Attribute locations
   GLint  positionLoc;
   GLint  texCoordLoc;

   // Sampler location
   GLint samplerLoc;

   // Texture handle
   GLuint textureId;

} UserData;



extern void* imgPixels;  
extern int imgWidth;   // Width of the texture image.
extern int imgHeight;  // Height of the texture image.

extern void* dashPixels;  // Pointer to raw RGB data for texture.
extern int dashWidth;   // Width of the texture image.
extern int dashHeight;  // Height of the texture image.

extern ESContext* dashcontext;

GLuint loadTexture( char* fileName );
void str_cp(char **s1, char *s2,char *s3);
void drawquad(GLuint texture,int x,int y,int x1,int y1);
void drawtriangle(GLuint texture,int x,int y,int x1,int y1);
void drawdashboard(GLuint texture,int x,int y,int x1,int y1);
void drawspeedometr(float speed);
void drawtahometr(float speed);
void drawfuel(float speed);
void drawtemp(float speed);
void drawzn(GLuint texture,int x,int y,int lenx,int leny,int active);
void draw_zn_fuel(int active);
void draw_zn_dalnsvet(int active);
void draw_zn_imobilizer(int active);
void draw_zn_maslo(int active);
void draw_zn_opendoor(int active);
void draw_zn_peregrev(int active);
void draw_zn_povorlevo(int active);
void draw_zn_povorpravo(int active);
void draw_zn_power(int active);
void draw_zn_protivotuman(int active);
void draw_zn_torm(int active);

#endif // _OBJECTS_H_
