/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * shetchik.h
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

#ifndef _SHETCHIK_H_
#define _SHETCHIK_H_

class shetchik
{
public:
	int enable;
	int x;
	int y;
	int lenx;
	int leny;
	char* texturefile;
	GLuint texture;
	int active;
    int active_size;
	int cor;
	int cor_cur;
	float koef;
		
	void loadconfig(char* zn_name);
	void draw();
	void setactive(int tru);
	
protected:

private:

};

#endif // _SHETCHIK_H_

