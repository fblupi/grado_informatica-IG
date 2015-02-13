#ifndef _SELECCION
#define _SELECCION

typedef struct {
    int tama;
    int names[MAXNAMES];
    float zmin;
    float zmax;
} Objeto;

class Seleccion
{
private:
    int tama;
    Objeto objeto[MAXOBJETOS];
public:
    Seleccion();
};

#endif
