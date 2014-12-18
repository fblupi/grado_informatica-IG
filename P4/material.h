//**************************************************************************
// Clase Material
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/glut.h>
#include "vertex.h"
#include "textura.h"

#ifndef _MATERIAL
#define _MATERIAL

class Material {
    private:
        _vertex4f ambiental;
        _vertex4f difusa;
        _vertex4f especular;
        GLfloat brillo;
        bool tieneTextura;
        Textura *textura;
    public:
        Material();
        void setAmbiental(const _vertex4f &a);
        void setDifusa(const _vertex4f &d);
        void setEspecular(const _vertex4f &e);
        void setBrillo(const GLfloat &b);
        void setTextura(const char *file_name,const bool &automatic);
        void activar();
};

#endif
