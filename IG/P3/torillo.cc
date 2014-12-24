//**************************************************************************
// Clase Torillo
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "torillo.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include <math.h>

using namespace std;

Torillo::Torillo() {
    cubo.model_ply("D:\\PLY\\cube");
    prisma_triangular.model_ply("D:\\PLY\\prisma_triangular");
    cilindro.model_ply_vertices("D:\\PLY\\rev\\prisma");
    cilindro.barrido_circular(24);

    min_elevadora = 0;
    max_elevadora = 130;

    elevadora = 30;
    volante = 0;
    desplazamiento = 0;
    ruedas = 0;
}

void Torillo::setElevadora(const GLfloat &num) {
    if(num>max_elevadora) {
        elevadora = max_elevadora;
    } else if(num<min_elevadora) {
        elevadora = min_elevadora;
    } else {
        elevadora = num;
    }
}

void Torillo::setVolante(const GLfloat &num) {
    volante = num;
}

void Torillo::setDesplazamiento(const GLfloat &num) {
    if(num>desplazamiento) ruedas += 15;
    else if(num<desplazamiento) ruedas -= 15;
    desplazamiento = num;
}

GLfloat Torillo::getElevadora() {
    return elevadora;
}

GLfloat Torillo::getDesplazamiento() {
    return desplazamiento;
}

GLfloat Torillo::getVolante() {
    return volante;
}

void Torillo::draw_chasis_base(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,55,0);
    glScalef(200,50,150);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_chasis_trasero(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(50,105,0);
    glScalef(100,50,150);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_chasis_delantero(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-75,105,0);
    glScalef(50,50,150);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_chasis_mandos(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-75,145,0);
    glScalef(50,30,150);
    prisma_triangular.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_chasis(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    draw_chasis_base(modo);
    glPopMatrix();
    glPushMatrix();
    draw_chasis_trasero(modo);
    glPopMatrix();
    glPushMatrix();
    draw_chasis_delantero(modo);
    glPopMatrix();
    glPushMatrix();
    draw_chasis_mandos(modo);
    glPopMatrix();
}

void Torillo::draw_ruedas(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(60,30,75);
    draw_rueda(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-60,30,75);
    draw_rueda(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(60,30,-75);
    draw_rueda(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-60,30,-75);
    draw_rueda(modo);
    glPopMatrix();

}

void Torillo::draw_cabina(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-96.5,180,71.5);
    draw_palo_cabina(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-96.5,180,-71.5);
    draw_palo_cabina(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(96.5,180,71.5);
    draw_palo_cabina(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(96.5,180,-71.5);
    draw_palo_cabina(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,232.5,0);
    draw_techo(modo);
    glPopMatrix();
}

void Torillo::draw_palo_cabina(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5,100,5);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_interior(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    draw_asiento(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-75,145,0);
    draw_volante_completo(modo);
    glPopMatrix();
}

void Torillo::draw_asiento(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    draw_espaldera(modo);
    draw_banco(modo);
    glPopMatrix();
}

void Torillo::draw_espaldera(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(55,165,0);
    glScalef(10,50,60);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_banco(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(30,135,0);
    glScalef(60,10,60);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_techo(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(198,5,148);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_rueda(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(ruedas,0,0,1);
    glRotatef(90,1,0,0);
    glScalef(60,30,60);
    cilindro.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_soporte(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-110,0,60);
    draw_soporte_individual(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-110,0,-60);
    draw_soporte_individual(modo);
    glPopMatrix();
}

void Torillo::draw_soporte_individual(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,130,0);
    draw_palo_soporte(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,32.5,0);
    draw_tope_soporte(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,232.5,0);
    draw_tope_soporte(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.5,85,0);
    draw_tope_inferior(modo);
    glPopMatrix();
}

void Torillo::draw_palo_soporte(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(10,200,10);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_tope_soporte(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(20,5,20);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_tope_inferior(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5,10,10);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_soporte_volante(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(10,40,10);
    cilindro.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_volante(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(volante,0,1,0);
    glTranslatef(0,22,0);
    glScalef(50,4,50);
    cilindro.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_volante_completo(const int &modo) {
    double alfa = atan(0.6) * 180 / M_PI;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-alfa,0,0,1);
    draw_soporte_volante(modo);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-alfa,0,0,1);
    draw_volante(modo);
    glPopMatrix();
}




void Torillo::draw_elevadora(const int &modo){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-115,0,-60);
    draw_soporte_pala(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-115,0,60);
    draw_soporte_pala(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-175,0,-60);
    draw_pala(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-175,0,60);
    draw_pala(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-175,0,0);
    draw_union_palas(modo);
    glPopMatrix();
}

void Torillo::draw_soporte_pala(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,95,0);
    glScalef(30,10,20);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_pala(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(47.5,47.5,0);
    draw_palo_pala(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,2.5,0);
    draw_cuerpo_pala(modo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-60,2.5,0);
    draw_extremo_pala(modo);
    glPopMatrix();
}

void Torillo::draw_palo_pala(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5,85,20);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_cuerpo_pala(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(100,5,20);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_extremo_pala(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(180,0,1,0);
    glScalef(20,5,20);
    prisma_triangular.dibujar(modo);
    glPopMatrix();
}

void Torillo::draw_union_palas(const int &modo) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(47.5,50,0);
    glScalef(5,10,100);
    cubo.dibujar(modo);
    glPopMatrix();
}

void Torillo::dibujar(const int &modo) {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(desplazamiento,0,0);
    draw_chasis(modo);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(desplazamiento,0,0);
    draw_ruedas(modo);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(desplazamiento,0,0);
    draw_cabina(modo);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(desplazamiento,0,0);
    draw_interior(modo);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(desplazamiento,0,0);
    draw_soporte(modo);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(desplazamiento,elevadora,0);
    draw_elevadora(modo);
    glPopMatrix();
}
