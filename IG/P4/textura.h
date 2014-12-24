//**************************************************************************
// Clase Textura
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "vertex.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

#ifndef _TEXTURA
#define _TEXTURA

class Textura {
    private:
        jpg::Imagen * pimg;
        unsigned int tamx;
        unsigned int tamy;
        unsigned char * texels;
        unsigned int id;
        bool automatico;
    public:
        Textura(const char *file_name, const bool &automatic);
        void activar();
};

#endif
