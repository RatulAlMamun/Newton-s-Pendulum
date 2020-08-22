#include <GL\glut.h>
#include <bits/stdc++.h>
const float DEG2RAD = 3.14159/180;

/*---------------------Lighting Circle Function---------------------------*/
void Circle(GLfloat x, GLfloat y, GLfloat radius){
    glBegin(GL_POLYGON);
    GLfloat R = 1, G = 1, B = 0;
    for (GLint i=150; i <= 360; i++){
        glColor3f(R,G,B);
        GLfloat degInRad = i*DEG2RAD;
        glVertex2f(x+cos(degInRad)*radius, y+sin(degInRad)*radius);
        R -= .01; G -= .01; B -= .01;
    }
    for (GLint i=0; i <= 150; i++){
        glColor3f(R,G,B);
        GLfloat degInRad = i*DEG2RAD;
        glVertex2f(x+cos(degInRad)*radius, y+sin(degInRad)*radius);
        R -= .02; G -= .02; B -= .02;
    }

    glEnd();
}

/*------------------------Cubic Box Function-----------------------------------*/
void Cube(GLfloat x, GLfloat y, GLfloat length, GLfloat height, GLfloat width, GLfloat DEGREE, GLfloat R, GLfloat G, GLfloat B){
    GLfloat degree = DEGREE*DEG2RAD;
    glColor3f(R, G, B); ///front
    glBegin(GL_POLYGON);
    glVertex2f(x+0, y+0);
    glVertex2f(x+length, y+0);
    glVertex2f(x+length, y-height);
    glVertex2f(x+0, y-height);
    glEnd();

    glColor3f(R+.2, G+.2, B+.2); ///top
    glBegin(GL_POLYGON);
    glVertex2f(x+0, y+0);
    glVertex2f(x+length, y+0);
    glVertex2f(x+length+width*cos(degree), y+width*sin(degree));
    glVertex2f(x+width*cos(degree), y+width*sin(degree));
    glEnd();

    glColor3f(R-0.13, G-0.13, B-0.13); ///side
    glBegin(GL_POLYGON);
    glVertex2f(x+length, y+0);
    glVertex2f(x+length, y-height);
    glVertex2f(x+length+width*cos(degree), y-height+width*sin(degree));
    glVertex2f(x+length+width*cos(degree), y+width*sin(degree));
    glEnd();
}

/*-----------------------Display Function----------------------------------*/
GLfloat rope1X = -47;
GLfloat rope1Y = -30.0;
GLfloat rope3X = 11.0;
GLfloat rope3Y = -30;
GLint rope1state = 1;
GLint rope3state = 1;

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    ///-----------------Table---------------------------
    Cube(-270, -85, 20, 200, 10, 40, .2, .3, .4);
    Cube(-200, -55, 20, 200, 10, 40, .2, .3, .4);
    Cube(160, -85, 20, 200, 10, 40, .2, .3, .4);
    Cube(230, -55, 20, 200, 10, 40, .2, .3, .4);
    Cube(-300, -100, 500, 15, 100, 40, .1, .5, .7);

    ///---------------Holding Joint----------------------
    Cube(-200, -70, 50, 5, 25, 40, .56, .46, .22);
    Cube(100, -70, 50, 5, 25, 40, .56, .46, .22);

    ///------------------Holder---------------------------
    Cube(125, 230, 14, 295, 7, 40, .56, .46, .22);
    Cube(-175, 230, 14, 295, 7, 40, .56, .46, .22);
    Cube(-175, 230, 314, 14, 7, 40, .56, .46, .22);

    ///--------------------Rope----------------------------
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(-18, 216);
    glVertex2f(-18, -30);
    glVertex2f(-47, 216);
    glVertex2f(rope1X, rope1Y);
    glVertex2f(11, 216);
    glVertex2f(rope3X, rope3Y);
    glEnd();

    ///--------------------Bob-----------------------------
    Circle(-18, -30, 15);
    Circle(rope1X, rope1Y, 15);
    Circle(rope3X, rope3Y, 15);

    glutSwapBuffers();
}
/*-------------------------Timer Function----------------------*/
GLint bob = 1;
GLfloat i = 0;
GLfloat j = 0;
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    ///Animation Logic
    if(bob){
        switch(rope1state){
            case 1:
                if(j<=20){
                    rope1X = -47 - 246*sin(j*DEG2RAD);
                    rope1Y = 216 -246*cos(j*DEG2RAD);
                } else rope1state = -1;
                j+=0.5;
                break;
            case -1:
                if(j>=0){
                    rope1X = -47 - 246*sin(j*DEG2RAD);
                    rope1Y = 216 -246*cos(j*DEG2RAD);
                } else{
                    rope1state = 1;
                    bob = 0;
                }
                j-=0.9;
                break;
        }
    } else {
        switch(rope3state){
            case 1:
                if(i<=23){
                    rope3X = 11+246*sin(i*DEG2RAD);
                    rope3Y = 216-246*cos(i*DEG2RAD);
                    i+=0.5;
                } else rope3state = -1;
                break;
            case -1:
                if(i>=0){
                    rope3X = 11+246*sin(i*DEG2RAD);
                    rope3Y = 216-246*cos(i*DEG2RAD);
                    i-=0.9;
                } else {
                    rope3state = 1;
                    bob = 1;
                }
                break;
        }
    }
}
/*-------------GL initialize Function-------------------*/
void init(void){
	glClearColor (0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500.0, 500.0, -325.0, 325.0, -100.0, 100.0);
}

/*-----------------Main Function-------------------------*/
int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000,650);
    glutInitWindowPosition(20,20);
    glutCreateWindow("Newton's Third law Pendulum");
    init();

    glutDisplayFunc(Display);
    glutTimerFunc(5000, timer, 0);
    glutMainLoop();
    return 0;
}
