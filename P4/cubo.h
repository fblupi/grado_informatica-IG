//**************************************************************************
// Clase Cubo
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "material.h"

#ifndef _CUBO
#define _CUBO

class Cubo {
private:
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Triangulos;
    vector<_vertex3f> Normales_triangulos;
    vector<_vertex3f> Normales_vertices;
    vector<_vertex2f> Map;
    Material Mat;
public:
    Cubo();
    void model();
    void normales();
    void map();
    void dibujar(const int &modo);
    void dibujar_puntos();
    void dibujar_alambre();
    void dibujar_solido();
    void dibujar_ajedrez();
    void dibujar_suavizado_plano();
    void dibujar_suavizado_gouraud();
};

#endif
