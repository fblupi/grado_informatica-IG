//**************************************************************************
// Examen Febrero 2014
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 2
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std;

void dibujar(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos, const vector<bool> &resaltado);
void dibujar_nombres(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos);
void model_ply(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t);
void calcular_vecinos(const vector<_vertex3i> &t, vector<vector<unsigned int> > &vecinos);
