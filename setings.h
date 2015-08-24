// setings.h
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
//           setings.h
//  Чт Август 21 21:55:09 2014
//  Copyright  2014  user
//  <user@host>

#ifndef _SETINGS_H_
#define _SETINGS_H_

#include "iniparser.h"


using namespace std;

extern struct
{
	int sleepu;
	int timerticks;
	int sockport;

	int testmode;
    int xres;
    int yres;
    int dashboardenable;
	char* dashboardtexture;
    int dashboardtemp_x;
    int dashboardtemp_y;
    int dashboardtemp_x1;
    int dashboardtemp_y1;
	
} sets;

extern	dictionary* ini;


void readini();

#endif // _SETINGS_H_
