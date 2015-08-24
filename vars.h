// vars.h
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
//           vars.h
//  Чт Август 21 23:28:15 2014
//  Copyright  2014  user
//  <user@host>

#include "znak.h"
#include "dialgauge.h"
//#include <GL/gl.h>
//#include <GL/glut.h>
#include "opengles/esUtil.h"

#ifndef _VARS_H_
#define _VARS_H_

extern dictionary* ini;


struct obj
{
	dialgauge* dgp;
	znak* znp;
	int enable;
	int type;
	char* name;
};

extern float variables[128];

extern obj objects[128];


extern float speed;
extern float tahometr;
extern float fuel;
extern float temp;
extern int power;
extern int dalnsvet;
extern int imobilizer;
extern int maslo;
extern int opendoor;
extern int povorlevo;
extern int povorpravo;
extern int protivotuman;
extern int torm;


extern GLuint dashboard,textspeed,texttahometr,textfuel,texttemp;

extern dialgauge dg_speed,dg_tahometr,dg_fuel,dg_temp;
extern znak zn_fuel,zn_dalnsvet,zn_imobilizer,zn_maslo,zn_opendoor,zn_peregrev,zn_povorlevo,zn_povorpravo,zn_power,zn_protivotuman,zn_torm;

#endif // _VARS_H_
