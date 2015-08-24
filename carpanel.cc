/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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

#include <stdio.h>
#include <stdlib.h>
//#include <GL/gl.h>
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
#include "znak.h"
#include "dialgauge.h"
#include "nets.h"
#include <pthread.h>

using namespace std;


 #define TEXTURE_LOAD_ERROR 0




float i=0;
float i2=0;
float i3=0;

int64_t timertick=0;

dialgauge* dgp; 
znak* znp; 



int Init ( ESContext *esContext )
{
  int w;
   esContext->userData = malloc(sizeof(UserData));      
   dashcontext = malloc(sizeof(ESContext));      
   dashcontext->userData = malloc(sizeof(UserData));      
   UserData *userData = esContext->userData;	
   UserData *dashuserData = dashcontext->userData;	
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
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );
   dashuserData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
   dashuserData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   dashuserData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
   
   // Get the sampler location
   userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );
   dashuserData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );



///////////////////////////////////////////////////
        dashboard=loadTexture(sets.dashboardtexture);

	// Load the texture
   userData->textureId = dashboard;
   dashuserData->textureId = dashboard;

	    dashPixels=imgPixels;
		dashWidth=imgWidth;
		dashHeight=imgHeight;

        for(w=0;w<127;w++){
			if(objects[w].enable==1){
				if(objects[w].type==0){
					//Создаем класс dialgauge
					objects[w].dgp=new dialgauge;
					objects[w].dgp->loadconfig(objects[w].name);
				}
				if(objects[w].type==1){
					//Создаем класс znak
					objects[w].znp=new znak;
					objects[w].znp->loadconfig(objects[w].name);
				}
			}
		}


	
  
   
//////////////////////////////////////////////////




   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}




///
// Initialize the shader and program object
//
/*int Init ( ESContext *esContext )
{
   esContext->userData = malloc(sizeof(UserData));      
   UserData *userData = esContext->userData;
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
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
   
   // Get the sampler location
   userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );

   // Load the texture
   userData->textureId = CreateSimpleTexture2D ();

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}*/


void drawdashboard()
{
}


///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
   int w;
   UserData *userData = esContext->userData;
   UserData *dashuserData = dashcontext->userData;


	GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
                            0.0f,  1.0f,        // TexCoord 0 
                           -1.0f, -1.0f, 0.0f,  // Position 1
                            0.0f,  0.0f,        // TexCoord 1
                            1.0f, -1.0f, 0.0f,  // Position 2
                            1.0f,  0.0f,        // TexCoord 2
                            1.0f,  1.0f, 0.0f,  // Position 3
                            1.0f,  1.0f         // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( dashuserData->programObject );

   // Load the vertex position
   glVertexAttribPointer ( dashuserData->positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( dashuserData->texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );

   glEnableVertexAttribArray ( dashuserData->positionLoc );
   glEnableVertexAttribArray ( dashuserData->texCoordLoc );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, dashuserData->textureId );

   // Set the sampler texture unit to 0
   glUniform1i ( dashuserData->samplerLoc, 0 );


   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );




//  	drawdashboard(dashboard,sets.dashboardtemp_x,sets.dashboardtemp_y,sets.dashboardtemp_x1,sets.dashboardtemp_y1);

			
        for(w=0;w<127;w++){
			if(objects[w].enable==1){
				if(objects[w].type==0){
					//Рисуем класс dialgauge
					objects[w].dgp->draw(variables[w]);
				}
				if(objects[w].type==1){
					//Рисуем класс znak
					objects[w].znp->setactive(variables[w]);
					objects[w].znp->draw();
				}
			}
		}


}




///
// Cleanup
//
void ShutDown ( ESContext *esContext )
{
   UserData *userData = esContext->userData;

   // Delete texture object
   glDeleteTextures ( 1, &userData->textureId );

   // Delete program object
   glDeleteProgram ( userData->programObject );
        
   free(esContext->userData);
}



int main(int argc, char * argv[])
{
   ESContext esContext;
   UserData  userData;

	int wh;
	
	pthread_t thread_sock;
        int  iret_sock;
	
	   for(wh=0;wh<128;wh++){variables[wh]=0;}
	   for(wh=0;wh<128;wh++){objects[wh].enable=0;}
       readini();

	//socket thread

	iret_sock =pthread_create( &thread_sock,NULL,startsocket, &iret_sock);
	     if(iret_sock)
	     {
	         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret_sock);
	         exit(EXIT_FAILURE);
	     }

   esInitContext ( &esContext );
   esContext.userData = &userData;

   esCreateWindow ( &esContext, "carpanel", sets.xres, sets.yres, ES_WINDOW_RGB );

   if ( !Init ( &esContext ) )
      return 0;

   esRegisterDrawFunc ( &esContext, Draw );

glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
   esMainLoop ( &esContext );

   ShutDown ( &esContext );
	
 
        return 0;
}



