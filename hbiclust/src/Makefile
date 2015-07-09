# Makefile for building the C language shared library for the CalcMatrixAvg demonstration package.
CC = g++
OPTS = -c -fPIC -std=c++11
LOADER = g++

CPP_FILES := $(wildcard *.cpp)
OBJECTS := $(notdir $(CPP_FILES:.cpp=.o))

hbiclust.so: $(OBJECTS)
	R CMD SHLIB -std=c++11 $(OBJECTS) -o hbiclust.so 


%.o: %.cpp
	$(CC) $(OPTS) -c -o $@ $<
# .c.o: 
	# $(C) $(OPTS) -c $<

clean:
	-rm *.o *.so