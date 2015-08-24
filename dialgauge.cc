/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * dialgauge.cc
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

//#include <GL/gl.h>
//#include <GL/glut.h>
#include "opengles/esUtil.h"
#include "iniparser.h"
#include "dialgauge.h"
#include "objects.h"
#include "vars.h"
#include "setings.h"

//#include "vars.h"
//#include "objects.h"


void dialgauge::loadconfig(char* name){
	char* st;
	char st2 [250];
	int i;
	str_cp(&st,name,":enable");
	enable=iniparser_getint(ini,st,0);
	str_cp(&st,name,":texture_temp");
	texturefile_temp=iniparser_getstring(ini,st,"");

	str_cp(&st,name,":xtemp");
	xtemp=iniparser_getdouble(ini,st,0);
	xtemp=xtemp/(sets.xres/2)-1;
	str_cp(&st,name,":ytemp");
	ytemp=iniparser_getdouble(ini,st,0);
	ytemp=ytemp/(sets.yres/2)-1;
	str_cp(&st,name,":lenxtemp");
	lenxtemp=iniparser_getdouble(ini,st,0);
	lenxtemp=lenxtemp/(sets.xres/2);
	str_cp(&st,name,":lenytemp");
	lenytemp=iniparser_getdouble(ini,st,0);
	lenytemp=lenytemp/(sets.yres/2);
	
	str_cp(&st,name,":div_centr_arrow");
	div_centr_arrow=iniparser_getdouble(ini,st,6);
	str_cp(&st,name,":texture_arrow");
	texturefile_arrow=iniparser_getstring(ini,st,"");
	str_cp(&st,name,":xarrow");
	xarrow=iniparser_getdouble(ini,st,0);
	str_cp(&st,name,":yarrow");
	yarrow=iniparser_getdouble(ini,st,0);
	str_cp(&st,name,":lenxarrow");
	lenxarrow=iniparser_getdouble(ini,st,0);
	str_cp(&st,name,":lenyarrow");
	lenyarrow=iniparser_getdouble(ini,st,0);

	str_cp(&st,name,":triangle");
	triangle=iniparser_getint(ini,st,1);

	str_cp(&st,name,":speed");
	speed=iniparser_getdouble(ini,st,0);
	
	str_cp(&st,name,":startangle");
	startangle=iniparser_getdouble(ini,st,0);

	str_cp(&st,name,":minporog");
	minporog=iniparser_getdouble(ini,st,0);
	
	str_cp(&st,name,":maxporog");
	maxporog=iniparser_getdouble(ini,st,0);

	for(i=0;i<koeflenght;i++){
	sprintf(st2,":porog_%d",i);
	str_cp(&st,name,st2);
	porog[i]=iniparser_getdouble(ini,st,-100000);
	if(porog[i]!=-100000){nummaxporog=i;}

	sprintf(st2,":koef_%d",i);
	str_cp(&st,name,st2);
	koef[i]=iniparser_getdouble(ini,st,-100000);
		
	sprintf(st2,":defangle_%d",i);
	str_cp(&st,name,st2);
	defangle[i]=iniparser_getdouble(ini,st,-100000);
		
//	printf("%s\n",st);	
	}
	
	texture_arrow=loadTexture(texturefile_arrow);
	texture_temp=loadTexture(texturefile_temp);

	oldangle=startangle;

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
   esfon->textureId = texture_temp;
	

	
}; 

void dialgauge::drawstrela(GLuint texture,int x,int y,int xlen,int ylen,float angle,int triangle){
	int x1,y1;
   x1=x+xlen;
   y1=y+ylen;	
/*   glPushMatrix();
   glTranslated(x+((x1-x)/div_centr_arrow),y+((y1-y)/2),0);
   glRotatef(angle,0,0,1);
   glTranslated(-1*(x+((x1-x)/div_centr_arrow)),-1*(y+((y1-y)/2)),0);
   if(triangle==1){
   drawtriangle(0,x-2,y-0.5,x1+15,y1+2);
   drawtriangle(texture,x,y,x1,y1);
   }else{
	   drawquad(texture,x,y,x1,y1);
   }
   glPopMatrix();*/
}

void dialgauge::draw(float value){
	float valueangl=0;
	float korrektir=0;
	float korrektirvalue=0;
	int i;
	float values;
	
	if(enable==1){

	values=value;	

	if(values<=minporog){values=0;}else{values=values-minporog;}
	if(values>maxporog-minporog){values=maxporog-minporog;}
		
	
	for(i=0;i<=nummaxporog;i++){
	if(values<=porog[i]){
    	korrektirvalue=(values/koef[i]);
		korrektir=defangle[i];
	}
	}



	if(values>=porog[nummaxporog]){
		values=porog[nummaxporog];
    	korrektirvalue=(values/koef[nummaxporog]);
		korrektir=defangle[nummaxporog];
	}


	valueangl=korrektir-korrektirvalue;
	if(valueangl<oldangle-speed){valueangl=oldangle-speed;}
	if(valueangl>oldangle+speed){valueangl=oldangle+speed;}
	oldangle=valueangl;
	//printf("Value %f\n",speed);

//	drawdashboard(texture_temp,xtemp,ytemp,xtemp+lenxtemp,ytemp+lenytemp);


    UserData *esfon = escontext_fon->userData;
	GLfloat vVertices2[] = { xtemp,  ytemp+lenytemp, 0.0f,  // Position 0
                            0.0f,  1.0f,        // TexCoord 0 
                            xtemp, ytemp, 0.0f,  // Position 1
                            0.0f,  0.0f,        // TexCoord 1
                            xtemp+lenxtemp, ytemp, 0.0f,  // Position 2
                            1.0f,  0.0f,        // TexCoord 2
                            xtemp+lenxtemp,  ytemp+lenytemp, 0.0f,  // Position 3
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





		
	drawstrela(texture_arrow,xtemp+xarrow,ytemp+yarrow,lenxarrow,lenyarrow,valueangl,triangle);//Рисуем стрелу
	}


}


