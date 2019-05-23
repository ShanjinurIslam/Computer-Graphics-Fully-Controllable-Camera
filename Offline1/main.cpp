//
//  main.cpp
//  Offline1
//
//  Created by Shanjinur Islam on 5/23/19.
//  Copyright © 2019 Shanjinur Islam. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/GLUT.h>
#include <cmath>

double angle,height ;

class Point{
public:
    double x,y,z ;
    
    Point(){
        x = 0 ;
        y = 0 ;
        z = 0 ;
    }
    Point(double x,double y,double z){
        this->x = x ;
        this->y = y ;
        this->z = z ;
    }
    Point(const Point &p){
        this->x = p.x ;
        this->y = p.y ;
        this->z = p.z ;
    }
    void print(){
        printf("(%lf,%lf,%lf)",x,y,z) ;
    }
} pos,u,l,r ;

void drawAxes(){
    glPushMatrix();
    glBegin(GL_LINES);{
        glColor3f(1.0, 0, 0);
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);
        
        glColor3f(0, 1.0, 0);
        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);
        
        glColor3f(0, 0, 1.0);
        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();
    glPopMatrix() ;
}

void init(){
    pos = Point(100,100,0) ;
    u = Point(0,0,1) ; //z axis is up vector
    l = Point(-1/(sqrt(2)),-1/sqrt(2),0) ;
    r = Point(-1/(sqrt(2)),1/sqrt(2),0) ;
    angle = acos(-1.0)/4 ;
    height = 80 ;
    glClearColor(0,0,0,0) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluPerspective(80,1,1,1000.0) ;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    glClearColor(0,0,0,0) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
    gluLookAt(pos.x,pos.y,pos.z, pos.x + 10*l.x , pos.y + 10*l.y , pos.z + 10*l.z , u.x, u.y, u.z);
    
    glMatrixMode(GL_MODELVIEW) ;
    
    glPushMatrix();
    drawAxes() ;
    glPopMatrix();
    
    glutSwapBuffers() ;
}
void animate(){
    glutPostRedisplay() ;
}
void keyboardListener(unsigned char key,int x,int y){
    
}
void specialKeyListener(int key,int x,int y){
    
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Offline 1");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMainLoop();
    
    return 0;
}
