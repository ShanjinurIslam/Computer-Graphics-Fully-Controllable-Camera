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

double angle,height,increment ;

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
        printf("(%lf,%lf,%lf)\n\n",x,y,z) ;
    }
} pos,u,l,r ;


Point generateCrossProduct(Point a, Point b){
    Point p ;
    p.x = a.y*b.z - a.z*b.y ;
    p.y = a.z*b.x - a.x*b.z ;
    p.z = a.x*b.y - a.y*b.x ;
    
    return p ;
}

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
    angle = acos(-1.0)/30 ; //3 degree angle change
    height = 80 ;
    increment = 5 ;
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
    gluLookAt(pos.x,pos.y,pos.z, pos.x + l.x , pos.y + l.y , pos.z + l.z , u.x, u.y, u.z);
    
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
    
    /*
    U
    |
    |
    |
    L ______ R
     
    1. Rotating will not change the UP vector but will change the LOOK Vector and RIGHT Vector.
    2. Looking up/down not change the RIGHT vector but will change the LOOK Vector and RIGHT Vector.
    3. Tilt not change the LOOK vector but will change the UP Vector and RIGHT Vector.
    */
    switch (key) {
        case '1':
            r.x = r.x*cos(-1.0*angle) + l.x*sin(-1.0*angle) ;
            r.y = r.y*cos(-1.0*angle) + l.y*sin(-1.0*angle) ;
            r.z = r.z*cos(-1.0*angle) + l.z*sin(-1.0*angle) ;
            l = generateCrossProduct(u,r) ;
            break;
        case '2':
            r.x = r.x*cos(angle) + l.x*sin(angle) ;
            r.y = r.y*cos(angle) + l.y*sin(angle) ;
            r.z = r.z*cos(angle) + l.z*sin(angle) ;
            l = generateCrossProduct(u,r) ;
            break;
        case '3':
            l.x = l.x*cos(angle) + u.x*sin(angle) ;
            l.y = l.y*cos(angle) + u.y*sin(angle) ;
            l.z = l.z*cos(angle) + u.z*sin(angle) ;
            u = generateCrossProduct(r,l) ;
            break;
        case '4':
            l.x = l.x*cos(-1.0*angle) + u.x*sin(-1.0*angle) ;
            l.y = l.y*cos(-1.0*angle) + u.y*sin(-1.0*angle) ;
            l.z = l.z*cos(-1.0*angle) + u.z*sin(-1.0*angle) ;
            u = generateCrossProduct(r,l) ;
            break;
        case '5':
            u.x = u.x*cos(angle) + r.x*sin(angle) ;
            u.y = u.y*cos(angle) + r.y*sin(angle) ;
            u.z = u.z*cos(angle) + r.z*sin(angle) ;
            r = generateCrossProduct(l,u) ;
            break;
        case '6':
            u.x = u.x*cos(-1.0*angle) + r.x*sin(-1.0*angle) ;
            u.y = u.y*cos(-1.0*angle) + r.y*sin(-1.0*angle) ;
            u.z = u.z*cos(-1.0*angle) + r.z*sin(-1.0*angle) ;
            r = generateCrossProduct(l,u) ;
            break;
            
        default:
            break;
    }
}
void specialKeyListener(int key,int x,int y){
    switch (key) {
        case GLUT_KEY_UP:
            pos.x += l.x * increment ; //as l.x is negative incrementing value linearly will change position of eye
            pos.y += l.y * increment ; //as l.x is negative incrementing value linearly will change position of eye
            pos.z += l.z * increment ;
            break;
        case GLUT_KEY_DOWN:
            pos.x -= l.x * increment ;
            pos.y -= l.y * increment ;
            pos.z -= l.z * increment ;
            break;
        
        case GLUT_KEY_LEFT:
            pos.x -= r.x * increment ; //as right vector is perpendicular to up vector linear shifting with negative incrementing value linearly will change position of eye left side
            pos.y -= r.y * increment ;
            pos.z -= r.z * increment ;
            break;
        case GLUT_KEY_RIGHT:
            pos.x += r.x * increment ; //as right vector is perpendicular to up vector linear shifting with positive incrementing value linearly will change position of eye right side
            pos.y += r.y * increment ;
            pos.z += r.z * increment ;
            break;
            
        case GLUT_KEY_PAGE_UP:
            pos.x += u.x * increment ;
            pos.y += u.y * increment ;
            pos.z += u.z * increment ; // shifting of position of eye on in z axis
            break;
        case GLUT_KEY_PAGE_DOWN:
            pos.x -= u.x * increment ;
            pos.y -= u.y * increment ;
            pos.z -= u.z * increment ; // shifting of position of eye on in z axis
            break;
            
        default:
            break;
    }
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
