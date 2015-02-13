//**************************************************************************
// Clase Textura
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(const char *file_name, const bool &automatic) {
    pimg = new jpg::Imagen(file_name);
    tamx = pimg->tamX();
    tamy = pimg->tamY();
    texels = pimg->leerPixels();
    if(automatic) {
        automatico = true;
    } else {
        automatico = false;
    }
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,tamx,tamy,GL_RGB,GL_UNSIGNED_BYTE,texels);
}

void Textura::activar() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,id);
    if(automatico) {
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
    } else {
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }
}
