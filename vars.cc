// vars.c
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
//           vars.c
//  Чт Август 21 23:28:15 2014
//  Copyright  2014  user
//  <user@host>

//#include <GL/gl.h>
//#include <GL/glut.h>
#include "opengles/esUtil.h"
#include "znak.h"
#include "dialgauge.h"
#include "iniparser.h"


dictionary* ini;

struct obj
{
	dialgauge* dgp;
	znak* znp;
	int enable;
	int type;
	char* name;
};

float variables[128];

obj objects[128];



GLuint dashboard;

