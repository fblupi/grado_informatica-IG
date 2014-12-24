//**************************************************************************
// Clase Coche
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "coche.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

Coche::Coche() {
    cubo.model_ply("D:\\PLY\\cube");
    cilindro.model_ply_vertices("D:\\PLY\\rev\\prisma");
    cilindro.barrido_circular(24);
    cono.model_ply_vertices("D:\\PLY\\rev\\cono");
    cono.barrido_circular(24);
}

void Coche::dibujar(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    // Chasis
    glPushMatrix();
    glTranslatef(0,40,0);
    draw_chasis(modo);
    glPopMatrix();
    // Cubierta
    glPushMatrix();
    glTranslatef(0,80,0);
    draw_cabina(modo);
    glPopMatrix();
    // Rueda 1
    glPushMatrix();
    glTranslatef(-50,20,50);
    draw_rueda(modo);
    glPopMatrix();
    // Rueda 2
    glPushMatrix();
    glTranslatef(50,20,50);
    draw_rueda(modo);
    glPopMatrix();
    // Rueda 3
    glPushMatrix();
    glTranslatef(-50,20,-50);
    draw_rueda(modo);
    glPopMatrix();
    // Rueda 4
    glPushMatrix();
    glTranslatef(50,20,-50);
    draw_rueda(modo);
    glPopMatrix();
    // Faro 1
    glPushMatrix();
    glTranslatef(-40,50,80);
    draw_faro(modo);
    glPopMatrix();
    // Faro 2
    glPushMatrix();
    glTranslatef(40,50,80);
    draw_faro(modo);
    glPopMatrix();
}

void Coche::draw_rueda(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(40,15,40);
    cilindro.dibujar(modo);
    glPopMatrix();
}

void Coche::draw_cabina(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(100,40,60);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Coche::draw_chasis(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(100,40,160);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Coche::draw_faro(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(270,1,0,0);
    glScalef(10,10,10);
    cono.dibujar(modo);
    glPopMatrix();
}
