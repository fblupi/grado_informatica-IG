//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"

using namespace std;

void dibujar_ajedrez(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos);
void dibujar_solido(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos);
void dibujar_solido2(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos);
void dibujar_alambre(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos);
void dibujar_puntos(const vector<_vertex3f> &Vertices);

void model_cubo(vector<_vertex3f> &v, vector<_vertex3i> &t);
void model_tetraedro(vector<_vertex3f> &v, vector<_vertex3i> &t);
void model_ply(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t);
void model_ply2(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t);
void leer_puntos(const vector<float> &vec, vector<_vertex3f> &v);


