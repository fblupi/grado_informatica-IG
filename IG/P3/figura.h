//**************************************************************************
// Clase Figura (Cabecera)
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std;

class Figura {
private:
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Triangulos;
    vector<_vertex3f> Normales_triangulos;
    vector<_vertex3f> Normales_vertices;
    vector<pair<_vertex3f,_vertex3f> > Normales_triangulos_dibujados;
    vector<pair<_vertex3f,_vertex3f> > Normales_vertices_dibujados;
public:
    Figura();
    void model_ply(const char *file_name);
    void model_ply_vertices(const char *file_name);
    void barrido_circular(const unsigned int &n);
    void barrido_circularV2(const unsigned int &n, const float &A, const float &B);

    void calcular_normales_triangulos();
    void calcular_normales_vertices();

    void dibujar(const int &modo);
    void dibujar();
    void dibujar_puntos();
    void dibujar_alambre();
    void dibujar_solido();
    void dibujar_ajedrez();
    void dibujar_normales_triangulos();
    void dibujar_normales_vertices();

    vector<_vertex3f> getVertices();
    vector<_vertex3i> getTriangulos();
    vector<_vertex3f> getNormales_triangulos();
    vector<_vertex3f> getNormales_vertices();
    vector<pair<_vertex3f,_vertex3f> > getNormales_triangulos_dibujados();
    vector<pair<_vertex3f,_vertex3f> > getNormales_vertices_dibujados();
    int getModo();

    void setVertices(const vector<_vertex3f> &v);
    void setTriangulos(const vector<_vertex3i> &v);
    void setNormales_triangulos(const vector<_vertex3f> &v);
    void setNormales_vertices(const vector<_vertex3f> &v);
    void setNormales_triangulos_dibujados(const vector<pair<_vertex3f,_vertex3f> > &v);
    void setNormales_vertices_dibujados(const vector<pair<_vertex3f,_vertex3f> > &v);
    void setModo(int m);
};


