/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * dialgauge.h
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


#ifndef _DIALGAUGE_H_
#define _DIALGAUGE_H_

#define koeflenght 50 //Количество коэфициентов корректировки

class dialgauge
{
public:
ESContext *escontext_fon;
ESContext *escontext_arrow;

char* texturefile_arrow;
GLuint texture_arrow;//Текстура стрелки
char* texturefile_temp;	
GLuint texture_temp;//Текстура фона приборки
int enable;
float xtemp;
float ytemp;
float lenxtemp;
float lenytemp;
float div_centr_arrow;	
int xarrow;
int yarrow;
int lenxarrow;
int lenyarrow;
int triangle;
float speed;
float startangle;
float minporog;//Минимальный порог, для прибора 0
float koef[koeflenght];
float defangle[koeflenght];
float porog[koeflenght];
float maxporog;//Максимальное значение
int nummaxporog;//Последнее значение порога
float oldangle;	

		
	void loadconfig(char* name);
	void draw(float value);
    void drawstrela(GLuint texture,int x,int y,int xlen,int ylen,float angle,int triangle);
		
protected:

private:

};


#endif // _DIALGAUGE_H_

