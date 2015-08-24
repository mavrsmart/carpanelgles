/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * znak.cc
 * Copyright (C) 2014 mavrsmart <mavr@smarts.zp.ua>
 *
 * carpanel is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * carpanel is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "znak.h"
#include "iniparser.h"
#include "vars.h"
#include "objects.h"
#include "setings.h"
//#include <GL/gl.h>
//#include <GL/glut.h>
#include "opengles/esUtil.h"



void znak::setactive(int tru){
	enable=tru;
	if((enable==0)&&(cor<=0)){cor=0;cor_cur=0;}
	if(enable==1){
		if(cor_cur==0){
			cor=cor+koef;
			if(cor>=active_size){cor_cur=1;}
		}else{
			cor=cor-koef;
			if(cor<=0){cor_cur=0;}
		}
	}else{
			cor=cor-koef;
			if(cor<=0){cor_cur=0;}
		}
	
}



void znak::loadconfig(char* zn_name){
	char* st;
	str_cp(&st,zn_name,":enable");
	enable=iniparser_getint(ini,st,0);
	str_cp(&st,zn_name,":texture");
	texturefile=iniparser_getstring(ini,st,"");
	str_cp(&st,zn_name,":x");
	x=iniparser_getdouble(ini,st,0);
	x=x/(sets.xres/2)-1;
	str_cp(&st,zn_name,":y");
	y=iniparser_getdouble(ini,st,0);
	y=y/(sets.yres/2)-1;
	str_cp(&st,zn_name,":lenx");
	lenx=iniparser_getdouble(ini,st,0);
	lenx=lenx/(sets.xres/2);
	str_cp(&st,zn_name,":leny");
	leny=iniparser_getdouble(ini,st,0);
	leny=leny/(sets.yres/2);

	str_cp(&st,zn_name,":active_size");
	active_size=iniparser_getint(ini,st,0);

	str_cp(&st,zn_name,":koef");
	koef=iniparser_getint(ini,st,0);
	
	texture=loadTexture(texturefile);
	cor=0;
	cor_cur=0;

//init es
   escontext_fon=malloc(sizeof(ESContext));      
   escontext_fon->userData = malloc(sizeof(UserData));      
   UserData *esfon = escontext_fon->userData;	
   GLbyte vShaderStr[] =  
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "   v_texCoord = a_texCoord;  \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;                            \n"
      "varying vec2 v_texCoord;                            \n"
      "uniform sampler2D s_texture;                        \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   esfon->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   esfon->positionLoc = glGetAttribLocation ( esfon->programObject, "a_position" );
   esfon->texCoordLoc = glGetAttribLocation ( esfon->programObject, "a_texCoord" );
   
   // Get the sampler location
   esfon->samplerLoc = glGetUniformLocation ( esfon->programObject, "s_texture" );


	// Load the texture
   esfon->textureId = texture;

	
}; 

void znak::draw(){
	if(enable==0){
/*		glColor3f(0.2,0.2,0.2);*/
	}
	//	drawzn(texture,x-cor/2,y-cor/2,lenx+cor,leny+cor,active);


    UserData *esfon = escontext_fon->userData;
	GLfloat vVertices2[] = { x,  y+leny, 0.0f,  // Position 0
                            0.0f,  1.0f,        // TexCoord 0 
                            x, y, 0.0f,  // Position 1
                            0.0f,  0.0f,        // TexCoord 1
                            x+lenx, y, 0.0f,  // Position 2
                            1.0f,  0.0f,        // TexCoord 2
                            x+lenx,  y+leny, 0.0f,  // Position 3
                            1.0f,  1.0f         // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
   // Set the viewport
//   glViewport ( 0, 0, esfon->width, esfon->height );
   
   // Clear the color buffer
  // glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( esfon->programObject );

   // Load the vertex position
   glVertexAttribPointer ( esfon->positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices2 );
   // Load the texture coordinate
   glVertexAttribPointer ( esfon->texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices2[3] );

   glEnableVertexAttribArray ( esfon->positionLoc );
   glEnableVertexAttribArray ( esfon->texCoordLoc );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, esfon->textureId );

   // Set the sampler texture unit to 0
   glUniform1i ( esfon->samplerLoc, 0 );

   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
	

	/*glColor3f(1,1,1);*/
}
