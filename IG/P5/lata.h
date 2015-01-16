//**************************************************************************
// Clase Lata
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include "figura.h"

#ifndef _LATA
#define _LATA

class Lata {
    private:
        Figura Tapa_inferior;
        Figura Tapa_superior;
        Figura Cuerpo;
    public:
        Lata();
        void dibujar(const int &modo);
};

#endif
