//**************************************************************************
// Clase Luz
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/glut.h>
#include "vertex.h"

#ifndef _LUZ
#define _LUZ

class Luz {
    private:
        GLenum id;
        bool direccional;
        _vertex4f posicion;
        GLfloat alfa;
        GLfloat beta;
        _vertex4f ambiental;
        _vertex4f difuso;
        _vertex4f especular;
    public:
        Luz();
        void activar();
        void desactivar();
        void setID(const GLenum &i);
        void setDireccional(const bool &d);
        void setPosicion(const _vertex3f &p);
        void setDireccion(const GLfloat &a, const GLfloat &b);
        void setAmbiental(const _vertex4f &a);
        void setDifuso(const _vertex4f &d);
        void setEspecular(const _vertex4f &e);
};

#endif
