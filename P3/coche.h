//**************************************************************************
// Clase Coche
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include "figura.h"

using namespace std;

class Coche {
private:
    Figura cubo;
    Figura cono;
    Figura cilindro;
public:
    Coche();
    void dibujar(const int &modo);
    void draw_rueda(const int &modo);
    void draw_cabina(const int &modo);
    void draw_chasis(const int &modo);
    void draw_faro(const int &modo);
};
