
## Created by Anjuta

CC = gcc
CXXFLAGS = -Wall
OBJECTS = dispdemo.o
INCFLAGS = 
LDFLAGS =
LIBS = 

all: dispdemo

dispdemo: $(OBJECTS)
	$(CC) $(CXXFLAGS) -o dispdemo $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
