
CC = g++
CXXFLAGS = -Wall -fpermissive
OBJECTS = nets.o dialgauge.o znak.o objects.o vars.o setings.o carpanel.o opengles/esShader.o opengles/esTransform.o opengles/esShapes.o opengles/esUtil.o
INCFLAGS = 
LDFLAGS =
#LIBS = -lGL -lGLU -lglut -lpng -lfreeimage -liniparser -lpthread
INCDIR=-I./Common
LIBS=-lGLESv2 -lEGL -lm -lX11 -lpng -lfreeimage -liniparser -lpthread

COMMONSRC=./opengles/esShader.c    \
          ./opengles/esTransform.c \
          ./opengles/esShapes.c    \
          ./opengles/esUtil.c
COMMONHRD=/opengles/esUtil.h

all: carpanel

carpanel: ${COMMONSRC} $(OBJECTS)
	$(CC) $(CXXFLAGS) -o carpanel $(OBJECTS) $(LDFLAGS) $(LIBS)

#carpanel: ${COMMONSRC} ${COMMONHDR} carpanel
#	gcc ${COMMONSRC} carpanel -o ./$@ ${INCDIR} ${LIBS}


.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o
	rm -f opengles/*.o
	rm carpanel

.PHONY: all
.PHONY: count
.PHONY: clean






