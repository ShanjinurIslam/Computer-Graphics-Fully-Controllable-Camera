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
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <cmath>

class Point{
public:
    double x,y,z ;
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
    void Print(){
        printf("(%lf,%lf,%lf)",x,y,z) ;
    }
};

void init(){
    
}
void display(){
    
}
void animate(){
    
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
