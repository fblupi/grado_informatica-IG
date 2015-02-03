//**************************************************************************
// Examen Febrero 2013
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 3
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std;

void dibujar(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos);
void dibujar_puntos(const vector<_vertex3f> &Vertices, const unsigned int &resaltado);
void dibujar_nombres(const vector<_vertex3f> &Vertices);
void model_ply(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t);
