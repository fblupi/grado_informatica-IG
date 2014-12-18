//**************************************************************************
// Clase Figura (Cabecera)
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "material.h"

#ifndef _FIGURA
#define _FIGURA

using namespace std;

class Figura {
private:
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Triangulos;
    vector<_vertex3f> Normales_triangulos;
    vector<_vertex3f> Normales_vertices;
    vector<_vertex2f> Map;
    vector<pair<_vertex3f,_vertex3f> > Normales_triangulos_dibujados;
    vector<pair<_vertex3f,_vertex3f> > Normales_vertices_dibujados;
    _vertex3f Color;
    Material Mat;
    bool Calcular_textura;
public:
    Figura();
    void model_ply(const char *file_name);
    void model_ply_vertices(const char *file_name);
    void barrido_circular(const unsigned int &n);
    void barrido_circular_texturado(const unsigned int &n);
    void barrido_circularV2(const unsigned int &n, const float &A, const float &B);

    void calcular_normales_triangulos();
    void calcular_normales_vertices();
    void mapear(const unsigned int &n, const unsigned int &m);

    void dibujar(const int &modo);
    void dibujar();
    void dibujar_puntos();
    void dibujar_alambre();
    void dibujar_solido();
    void dibujar_ajedrez();
    void dibujar_suavizado_plano();
    void dibujar_suavizado_gouraud();
    void dibujar_normales_triangulos();
    void dibujar_normales_vertices();

    vector<_vertex3f> getVertices();
    vector<_vertex3i> getTriangulos();
    vector<_vertex3f> getNormales_triangulos();
    vector<_vertex3f> getNormales_vertices();
    vector<pair<_vertex3f,_vertex3f> > getNormales_triangulos_dibujados();
    vector<pair<_vertex3f,_vertex3f> > getNormales_vertices_dibujados();
    int getModo();
    _vertex3f getColor();

    void setVertices(const vector<_vertex3f> &v);
    void setTriangulos(const vector<_vertex3i> &v);
    void setNormales_triangulos(const vector<_vertex3f> &v);
    void setNormales_vertices(const vector<_vertex3f> &v);
    void setNormales_triangulos_dibujados(const vector<pair<_vertex3f,_vertex3f> > &v);
    void setNormales_vertices_dibujados(const vector<pair<_vertex3f,_vertex3f> > &v);
    void setModo(int m);
    void setColor(const _vertex3f &c);
    void setAmbiental(const _vertex4f &a);
    void setDifusa(const _vertex4f &d);
    void setEspecular(const _vertex4f &e);
    void setBrillo(const GLfloat &b);
    void setTextura(const char *file_name,const bool &automatic);
};

#endif
