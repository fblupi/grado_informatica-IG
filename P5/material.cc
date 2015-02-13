//**************************************************************************
// Clase Material
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "material.h"

Material::Material(){
    tieneTextura = false;
    textura = NULL;
}

void Material::setAmbiental(const _vertex4f &a) {
    ambiental = a;
}

void Material::setDifusa(const _vertex4f &d) {
    difusa = d;
}

void Material::setEspecular(const _vertex4f &e) {
    especular = e;
}

void Material::setBrillo(const GLfloat &b) {
    brillo = b;
}

void Material::setTextura(const char *file_name, const bool &automatic) {
    textura = new Textura(file_name,automatic);
    tieneTextura = true;
}

void Material::activar() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiental);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difusa);
    glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);
    glMaterialf(GL_FRONT,GL_SHININESS,brillo);
    if(tieneTextura) {
        textura->activar();
    } else {
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}
