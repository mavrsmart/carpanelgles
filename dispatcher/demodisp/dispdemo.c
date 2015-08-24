#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define speed 0
#define tahometr 1
#define temp 2
#define fuel 3
#define zn_fuel 4
#define zn_dalnsvet 5
#define zn_imobilizer 6
#define zn_maslo 7 
#define zn_opendoor 8
#define zn_peregrev 9
#define zn_povorlevo 10
#define zn_povorpravo 11
#define zn_power 12
#define zn_protivotuman 13
#define zn_torm 14

float variables[128];

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int timertick,mode;
    float i=0;
    float i2=0;
    float i3=0;

//    for(i=0;i<128;i++){variables[i]=0.0;}

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port mode\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    mode = atoi(argv[3]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    timertick=0;
    while(1){

	    usleep(1000);//1ms
	    timertick++;
	    if (mode==1){
	    if(timertick==1){
		//Для демо режима
		if(i>=220){i=0;}else{i=i+0.1;}
		if(i2>=8000){i2=0;}else{i2=i2+1;}
		if(i3>=100){i3=0;}else{i3=i3+0.01;}
		timertick=0;
	    }

//Отображение знаков по порогам
if(variables[temp]>90){variables[zn_peregrev]=1;} else {variables[zn_peregrev]=0;};
if(variables[fuel]<5){variables[zn_fuel]=1;} else {variables[zn_fuel]=0;};

	    }


		//Для настройки
		if (mode==2){
		if(timertick==1000){
		    variables[speed]=variables[speed]+10;//speed
		    if(variables[speed]==220){variables[speed]=0;}
		    variables[tahometr]=variables[tahometr]+500;//tahometr
		    if(variables[tahometr]==8500){variables[tahometr]=0;}
		    variables[fuel]=variables[fuel]+25;
		    if(variables[fuel]==125){variables[fuel]=0;}
		    variables[temp]=variables[temp]+10;
		    if(variables[temp]==120){variables[temp]=0;}
		timertick=0;
		}
		}

//Эмуляция значений в деморежиме
if (mode==1){
    if(i<=70){variables[speed]=0;}else{variables[speed]=180;}

    if(i2<=4000){variables[tahometr]=0;variables[zn_maslo]=1;}else{variables[tahometr]=6000;variables[zn_maslo]=0;}
    variables[fuel]=i3;
    variables[temp]=i3;
}

    n = write(sockfd,variables,sizeof(variables));
    if (n < 0) 
         error("ERROR writing to socket");
    }

    close(sockfd);
    return 0;
}
