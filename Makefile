CFLAGS = `pkg-config --cflags opencv `
LIBS = `pkg-config --static opencv --libs opencv`



img_generator : img_generator.cpp img_generator.hpp
	g++  -std=c++11 -Ofast -lpthread $(CFLAGS) $(LIBS) -o $@ $<
