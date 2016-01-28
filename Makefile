GCC_OPTIONS=-Wall -pedantic -I include
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)

default: 
	g++ red_triangle.cpp Common/InitShader.o $(OPTIONS) -o red_triangle 
	g++ p2.cpp Common/InitShader.o $(OPTIONS) -o p2  
	./red_triangle
run:
	./red_triangle 

run2:
	./p2 

clean:
	rm red_triangle
	rm p2

