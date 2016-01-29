// First new GL program
// Just makes a red triangle

#include "Angel.h"
#include <stdio.h>

const int NumPoints = 6;
GLfloat spin = 0.0;
typedef vec3 color3;

color3 magicColor = color3(0, 1, 0);
color3 squareColor = color3(1, 1, 1);

int mainWindow, subWindow, secondWindow;
//--------------------------------------------------------------------------

void
init( void )
{
    color3 colors[300];
    vec2 points[300];
    
    int pointCount = 0;
    GLfloat rad45 = DegreesToRadians * 45;
    
    color3 base_colors[5] = {
	color3(1.0, 1.0, 1.0),
	color3(0.0, 0.0, 0.0),
	color3(1.0, 0.0, 0.0),
	color3(0.0, 1.0, 0.0),
	color3(0.0, 0.0, 1.0),
    };

    //This paints the squares 
    vec2 squareBase = vec2(cos(rad45), sin(rad45));
    GLfloat size = .85;    
    //make 6 squares
    for(int i = 0; i < 6; i ++) {
        color3 color = base_colors[1];

 	if(i % 2 == 0) {
	    color = squareColor;
	}

        points[pointCount] = vec2((squareBase.x * size), ((squareBase.y * size) - .3));
        colors[pointCount] = color;
	pointCount++;
        points[pointCount] = vec2(-(squareBase.x * size), ((squareBase.y * size) - .3));
        colors[pointCount] = color;
	pointCount++;
        points[pointCount] = vec2((squareBase.x * size), -((squareBase.y * size) + .3));
        colors[pointCount] = color;
	pointCount++;
        points[pointCount] = vec2(-(squareBase.x * size), -((squareBase.y * size) + .3));
        colors[pointCount] = color;
	pointCount++;
	
	size = size - .15;
    }
     
    //Ellipse
    GLfloat rad360 = DegreesToRadians * 360;
    GLfloat rad6 = DegreesToRadians * 6;
    GLfloat radius = .9;
    GLfloat h2 = 0;
    GLfloat k2 = 0;
    for(GLfloat i = 0.0; i < rad360; i= i + rad6) {
	points[pointCount] = vec2(( h2+(radius*cos(i)) ), ( k2+(radius*sin(i) )) * .6 );
        colors[pointCount] = base_colors[2];
	pointCount++;
    }


    //Circle
    //rad360 is 2pi
    radius = .4;
    GLfloat h1 = 0.5;
    GLfloat k1 = 0;
    //make circle1
    for(GLfloat i = 0.0; i < rad360; i= i + rad6) {
	points[pointCount] = vec2(( h1+(radius*cos(i)) ), ( k1+(radius*sin(i) )));
        colors[pointCount] = magicColor;//base_colors[2];
	pointCount++;
    }   

    GLfloat rad90 = DegreesToRadians * 90;
    GLfloat rad120 = DegreesToRadians * 120;
    radius = .5;
    h1 = -0.5;
    k1 = 0;
    //make triangle
    for(GLfloat i = rad90; i < rad360+rad90; i= i + rad120) {
	points[pointCount] = vec2(( h1+(radius*cos(i)) ), ( k1+(radius*sin(i) )));
        colors[pointCount] = magicColor;
	pointCount++;
    }

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

    glutSetWindow(mainWindow);
    glClearColor( 0, 0, 0, 0 ); // black background

    glutSetWindow(subWindow);
    glClearColor(1, 1, 1, 1);
    
    glutSetWindow(secondWindow);
    glClearColor( 0, 0, 0, 0 ); // black background
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
    //glDrawArrays( GL_TRIANGLE_FAN, 24, 60 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_FAN, 85, 60 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_FAN, 146, 3 );    // draw the points
    glutSwapBuffers();
}

void
subDisplay( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the windowi
    //glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_STRIP, 4, 4 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_STRIP, 8, 4 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_STRIP, 12, 4 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_STRIP, 16, 4 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_STRIP, 20, 4 );    // draw the points
    glDrawArrays( GL_TRIANGLE_FAN, 24, 60 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_FAN, 85, 60 );    // draw the points
    //glDrawArrays( GL_TRIANGLE_FAN, 146, 3 );    // draw the points
    glutSwapBuffers();
}

void
display2( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the windowi
    glDrawArrays( GL_TRIANGLE_FAN, 85, 60 );    // draw the points
    glDrawArrays( GL_TRIANGLE_FAN, 146, 3 );    // draw the points
    glutSwapBuffers();
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

void
keyboard2( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit(0);
	break;
    case 'r':
	magicColor = color3(1, 0, 0);
	init();	
	glutPostRedisplay();
	break;
    case 'g':
	magicColor = color3(0, 1, 0);
	init();	
	glutPostRedisplay();
	break;
    case 'b':
	magicColor = color3(0, 0, 1);
	init();	
	glutPostRedisplay();
	break;
    case 'y':
	magicColor = color3(1, 1, 0);
	init();	
	glutPostRedisplay();
	break;
    case 'o':
	magicColor = color3(1, .5, 0);
	init();	
	glutPostRedisplay();
	break;
    case 'p':
	magicColor = color3(1, 0, 1);
	init();	
	glutPostRedisplay();
	break;
    case 'w':
	magicColor = color3(1, 1, 1);
	init();	
	glutPostRedisplay();
	break;
    }
}

void menuCallback(int id)
{
    if(id == 1 ) {
	glClearColor(1, 0, 0, 1);
	glutPostRedisplay();
    } else if(id == 2) {
	glClearColor(0, 1, 0, 1);
	glutPostRedisplay();
    } else if(id == 3) {
	glClearColor(0, 0, 1, 1);
	glutPostRedisplay();
    } else if(id == 4) {
	glClearColor(1, 1, 0, 1);
	glutPostRedisplay();
    } else if(id == 5) {
	glClearColor(1, .5, 0, 1);
	glutPostRedisplay();
    } else if(id == 6) {
	glClearColor(1, 0, 1, 1);
	glutPostRedisplay();
    } else if(id == 7) {
	glClearColor(1, 1, 1, 1);
	glutPostRedisplay();
    }
}

void mainMenuCallback(int id)
{
    if(id == 1 ) {
    } else if(id == 2) {
    } else if(id == 3) {
	squareColor = color3(1, 1, 1);
	init();	
	glutPostRedisplay();
    } else if(id == 4) {
	squareColor = color3(1, 0, 0);
	init();	
	glutPostRedisplay();
    } else if(id == 5) {
	squareColor = color3(0, 1, 0);
	init();	
	glutPostRedisplay();
    }
}
//----------------------------------------------------------------------------
/*void spinCube() {
    theta[axis] += 2.0;
    if(theta[axis] > 360.0) {
        theta[axis] -= 360.0;
    }
    glutPostRedisplay();
}*/
int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowSize( 500, 500 );

    mainWindow = glutCreateWindow( "Assignment 3" );
    glewExperimental=GL_TRUE; 
    glewInit();    
    init();
    int mainSubMenu = glutCreateMenu(mainMenuCallback);
    glutAddMenuEntry("White", 3);
    glutAddMenuEntry("Red", 4);
    glutAddMenuEntry("Green", 5);
    int mainMenu = glutCreateMenu(mainMenuCallback);
    glutAddMenuEntry("Stop Animation", 1);
    glutAddMenuEntry("Start Animation", 2);
    glutAddSubMenu("Square Colors", mainSubMenu); 
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    subWindow = glutCreateSubWindow(mainWindow, 0, 0, 150, 150 );
    init();
    int subMenu = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Orange", 5);
    glutAddMenuEntry("Purple", 6);
    glutAddMenuEntry("White", 7);
    glutDisplayFunc( subDisplay );
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //glutKeyboardFunc( keyboard );
    
    glutInitWindowSize( 250, 250 );
    secondWindow = glutCreateWindow( "Window 2" );
    init();
    glutDisplayFunc( display2 );
    glutKeyboardFunc( keyboard2 ); 
    glutMainLoop();
    return 0;
}
