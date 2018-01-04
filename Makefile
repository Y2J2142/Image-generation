CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`



img_generator : img_generator.cpp img_generator.hpp
	g++ -std=c++11 -pthread $(CFLAGS) $(LIBS) -o $@ $<
