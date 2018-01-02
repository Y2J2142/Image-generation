CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

img_generator : img_generator.cpp
	g++ -std=c++11 $(CFLAGS) $(LIBS) -o $@ $<
