GCC_OPTIONS=-Wall -pedantic -I include
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)

default: 
	g++ a3.cpp Common/InitShader.o $(OPTIONS) -o a3 
	g++ p2.cpp Common/InitShader.o $(OPTIONS) -o p2  
	./a3
run:
	./a3

run2:
	./p2 

clean:
	rm a3
	rm p2

