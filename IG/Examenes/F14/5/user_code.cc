//**************************************************************************
// Examen Febrero 2014
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 5
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

void draw_a() {
    glMatrixMode(GL_MODELVIEW);
    glColor3f(.3,.3,.3);
    glPushMatrix();
        glTranslatef(0,-.5,0);
        glScalef(.2,1,.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(.4,-1.1,0);
        glScalef(1,.2,.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(.8,-1.7,0);
        glScalef(.2,1,.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(.2,-2.1,0);
        glScalef(1,.2,.2);
        glutSolidCube(1);
    glPopMatrix();
}

void draw_b() {
    glMatrixMode(GL_MODELVIEW);
    glColor3f(.4,.4,.4);
    glPushMatrix();
        glScalef(12,.2,.2);
        glutSolidCube(1);
    glPopMatrix();
}

void draw_c() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(180,0,1,0);
        draw_a();
    glPopMatrix();
}

void draw_d() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glColor3f(.5,.5,.5);
        glTranslatef(0,-.5,0);
        glScalef(.2,1,.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glColor3f(.3,.3,.3);
        glTranslatef(0,-1.6,0);
        glScalef(1.2,1.2,1.2);
        glutSolidCube(1);
    glPopMatrix();
}
