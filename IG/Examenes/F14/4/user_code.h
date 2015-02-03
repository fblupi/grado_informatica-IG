//**************************************************************************
// Examen Febrero 2014
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 4
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std;

void dibujar(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos, const vector<_vertex3f> &Normales_vertices);
void model_ply(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t);
void calcular_normales(const vector<_vertex3f> &v, const vector<_vertex3i> &t, vector<_vertex3f> &nv);
