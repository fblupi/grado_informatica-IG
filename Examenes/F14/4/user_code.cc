//**************************************************************************
// Examen Febrero 2014
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 4
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

//**************************************************************************
// Funcion para dibujar modo solido
//**************************************************************************

void dibujar(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos, const vector<_vertex3f> &Normales_vertices) {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glNormal3f(Normales_vertices[Triangulos[i]._0].x, Normales_vertices[Triangulos[i]._0].y, Normales_vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glNormal3f(Normales_vertices[Triangulos[i]._1].x, Normales_vertices[Triangulos[i]._1].y, Normales_vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glNormal3f(Normales_vertices[Triangulos[i]._2].x, Normales_vertices[Triangulos[i]._2].y, Normales_vertices[Triangulos[i]._2].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para importar y modelar un .ply
//**************************************************************************

void model_ply(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t) {
    vector<float> v_aux; vector<int> t_aux;

    ply::read(file_name,v_aux,t_aux);
    vector<_vertex3f> Vertices(v_aux.size()/3);
    vector<_vertex3i> Triangulos(t_aux.size()/3);

    for(unsigned int i=0; i<Vertices.size(); i++) {
        Vertices[i].x = v_aux[i*3];
        Vertices[i].y = v_aux[i*3+1];
        Vertices[i].z = v_aux[i*3+2];
    }

    for(unsigned int i=0; i<Triangulos.size(); i++) {
        Triangulos[i]._0 = t_aux[i*3];
        Triangulos[i]._1 = t_aux[i*3+1];
        Triangulos[i]._2 = t_aux[i*3+2];
    }

    v = Vertices;
    t = Triangulos;
}

//**************************************************************************
// Funcion para calcular normales
//**************************************************************************

void calcular_normales(const vector<_vertex3f> &v, const vector<_vertex3i> &t, vector<_vertex3f> &nv) {
    vector<_vertex3f> nt(t.size());
    _vertex3f P,Q,N;  // Vectores P(V0->V1), Q(V0->V2) y normal N(P x Q)
    for(unsigned int i=0; i<nt.size(); i++) {
        // Calculo vector V0 -> V1
        P.x = v[t[i]._1].x - v[t[i]._0].x;
        P.y = v[t[i]._1].y - v[t[i]._0].y;
        P.z = v[t[i]._1].z - v[t[i]._0].z;
        // Calculo vector V0 -> V2
        Q.x = v[t[i]._2].x - v[t[i]._0].x;
        Q.y = v[t[i]._2].y - v[t[i]._0].y;
        Q.z = v[t[i]._2].z - v[t[i]._0].z;
        // Calculo vector normal = P x Q
        N.x = P.y*Q.z - P.z*Q.y;
        N.y = P.z*Q.x - P.x*Q.z;
        N.z = P.x*Q.y - P.y*Q.x;
        // Normalizo
        N.normalize();
        // Asigno valor
        nt[i] = N;
    }

    vector<_vertex3f> nv_aux(v.size(),_vertex3f(0,0,0));
    vector<int> num_triangulos(v.size(),0);  // Contador de número de triangulos que ayuda a formar un vértice
    unsigned int id0,id1,id2;
    for(unsigned int i=0; i<t.size(); i++) {
        id0 = t[i]._0; // Vértice 0 del triángulo i
        id1 = t[i]._1; // Vértice 1 del triángulo i
        id2 = t[i]._2; // Vértice 2 del triángulo i
        // Aumento la suma de coordenadas del vértice 0 del triángulo i
        nv_aux[id0].x += nt[i].x;
        nv_aux[id0].y += nt[i].y;
        nv_aux[id0].z += nt[i].z;
        num_triangulos[id0]++;  // Aumento contador del vértice 0 del triangulo i
        // Aumento la suma de coordenadas del vértice 1 del triángulo i
        nv_aux[id1].x += nt[i].x;
        nv_aux[id1].y += nt[i].y;
        nv_aux[id1].z += nt[i].z;
        num_triangulos[id1]++;  // Aumento contador del vértice 1 del triangulo i
        // Aumento la suma de coordenadas del vértice 2 del triángulo i
        nv_aux[id2].x += nt[i].x;
        nv_aux[id2].y += nt[i].y;
        nv_aux[id2].z += nt[i].z;
        num_triangulos[id2]++;  // Aumento contador del vértice 2 del triangulo i
    }
    for(unsigned int i=0; i<nv_aux.size(); i++) {
        // Divido cada coordenada para obtener la media
        nv_aux[i].x /= num_triangulos[i];
        nv_aux[i].y /= num_triangulos[i];
        nv_aux[i].z /= num_triangulos[i];
        // Normalizo
        nv_aux[i].normalize();
   }
   nv = nv_aux;
}

