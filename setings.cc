// setings.c
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
//           setings.c
//  Чт Август 21 21:55:09 2014
//  Copyright  2014  user
//  <user@host>


#include "iniparser.h"
#include "vars.h"

using namespace std;




struct sets
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


void readini(){
	char* st;
	char st2 [250];
	int i;
	ini=iniparser_load("carpanel.ini");
	sets.sleepu=iniparser_getint(ini,"system:sleepu",1000);
	sets.timerticks=iniparser_getint(ini,"system:timerticks",1000);
	sets.sockport=iniparser_getint(ini,"system:port",17000);
	
	sets.testmode=iniparser_getint(ini,"system:testmode",0);
	sets.xres=iniparser_getint(ini,"system:xres",1280);
	sets.yres=iniparser_getint(ini,"system:yres",800);
	sets.dashboardenable=iniparser_getint(ini,"dashboard:enable",1);
	sets.dashboardtexture=iniparser_getstring(ini,"dashboard:texture","textures/dashboard_carbon.png");
	sets.dashboardtemp_x=iniparser_getint(ini,"dashboard:temp_x",0);
	sets.dashboardtemp_y=iniparser_getint(ini,"dashboard:temp_y",0);
	sets.dashboardtemp_x1=iniparser_getint(ini,"dashboard:temp_x1",1280);
	sets.dashboardtemp_y1=iniparser_getint(ini,"dashboard:temp_y1",600);

	for(i=0;i<127;i++){
		sprintf(st2,"objects:enable_%d",i);
		objects[i].enable=iniparser_getint(ini,st2,0);
		sprintf(st2,"objects:type_%d",i);
		objects[i].type=iniparser_getint(ini,st2,0);
		sprintf(st2,"objects:name_%d",i);
		objects[i].name=iniparser_getstring(ini,st2,"");
	}
	

};
