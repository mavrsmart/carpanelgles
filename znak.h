/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * znak.h
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


#ifndef _ZNAK_H_
#define _ZNAK_H_

class znak
{
public:
    ESContext *escontext_fon;
	 
	int enable;
	float x;
	float y;
	float lenx;
	float leny;
	char* texturefile;
	GLuint texture;
	int active;
    int active_size;
	float cor;
	float cor_cur;
	float koef;
		
	void loadconfig(char* zn_name);
	void draw();
	void setactive(int tru);
protected:

private:

};

#endif // _ZNAK_H_
