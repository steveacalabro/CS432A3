// First new GL program
// Just makes a red triangle

#include "Angel.h"
#include <stdio.h>

const int NumPoints = 6;

//--------------------------------------------------------------------------

void
init( void )
{
    int pointCount = 0;
    GLfloat rad45 = DegreesToRadians * 45;
    
    typedef vec3 color3;
    color3 base_colors[5] = {
	color3(1.0, 1.0, 1.0),
	color3(0.0, 0.0, 0.0),
	color3(1.0, 0.0, 0.0),
	color3(0.0, 1.0, 0.0),
	color3(0.0, 0.0, 1.0),
    };

    color3 colors[200];
    vec2 points[200];
    
    //This paints the squares 
    vec2 squareBase = vec2(cos(rad45), sin(rad45));
    GLfloat size = .85;    
    //make 6 squares
    for(int i = 0; i < 6; i ++) {
        int color = 1;

 	if(i % 2 == 0) {
	    color = 0;
	}

        points[pointCount] = vec2((squareBase.x * size), ((squareBase.y * size) - .3));
        colors[pointCount] = base_colors[color];
	pointCount++;
        points[pointCount] = vec2(-(squareBase.x * size), ((squareBase.y * size) - .3));
        colors[pointCount] = base_colors[color];
	pointCount++;
        points[pointCount] = vec2((squareBase.x * size), -((squareBase.y * size) + .3));
        colors[pointCount] = base_colors[color];
	pointCount++;
        points[pointCount] = vec2(-(squareBase.x * size), -((squareBase.y * size) + .3));
        colors[pointCount] = base_colors[color];
	pointCount++;
	
	size = size - .15;
    }

    //Circle
    //rad360 is 2pi
    GLfloat rad360 = DegreesToRadians * 360;
    GLfloat rad6 = DegreesToRadians * 6;
    GLfloat radius = .2;
    GLfloat h1 = 0.55;
    GLfloat k1 = 0.7;
    //make circle1
    for(GLfloat i = 0.0; i < rad360; i= i + rad6) {
	points[pointCount] = vec2(( h1+(radius*cos(i)) ), ( k1+(radius*sin(i) )));
        colors[pointCount] = base_colors[2] * (i/5);
	pointCount++;
    }
     
     
    //Ellipse
    GLfloat h2 = -0.55;
    GLfloat k2 = 1.2;
    for(GLfloat i = 0.0; i < rad360; i= i + rad6) {
	points[pointCount] = vec2(( h2+(radius*cos(i)) ), ( k2+(radius*sin(i) )) * .6 );
        colors[pointCount] = base_colors[2];
	pointCount++;
    }

    GLfloat rad90 = DegreesToRadians * 90;
    GLfloat rad120 = DegreesToRadians * 120;
    radius = .3;
    h1 = 0.0;
    k1 = .7;
    int colorCount = 2;
    //make triangle
    for(GLfloat i = rad90; i < rad360+rad90; i= i + rad120) {
	points[pointCount] = vec2(( h1+(radius*cos(i)) ), ( k1+(radius*sin(i) )));
        colors[pointCount] = base_colors[colorCount];
	pointCount++;
	colorCount++;
    }
/*
    points[pointCount] = vec2(0, 1 );
    colors[pointCount] = base_colors[2];
    pointCount++;
    points[pointCount] = vec2(-.25, .55 );
    colors[pointCount] = base_colors[3];
    pointCount++;
    points[pointCount] = vec2(.25, .55);
    colors[pointCount] = base_colors[4];
    pointCount++;
*/
    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

    // Load shaders and use the resulting shader program
    GLuint program =  InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    //glLinkProgram(program);

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    GLuint loc2 = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc2);
    glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0,
			  BUFFER_OFFSET(sizeof(points)));

    glClearColor( 0, 0, 0, 0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_STRIP, 4, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_STRIP, 8, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_STRIP, 12, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_STRIP, 16, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_STRIP, 20, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_FAN, 24, 60 );    // draw the points
    glDrawArrays( GL_TRIANGLE_FAN, 85, 60 );    // draw the points
    glDrawArrays( GL_TRIANGLE_FAN, 146, 3 );    // draw the points
  glFlush();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 500, 500 );

    glutCreateWindow( "Assignment 2" );
    glewExperimental=GL_TRUE; 
    glewInit();    
    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
/*
static char* readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");
    
    if(fp == NULL)
    {
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
   
    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);
 
    return buf;
}*/
