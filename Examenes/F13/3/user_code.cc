//**************************************************************************
// Examen Febrero 2013
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 3
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

//**************************************************************************
// Funcion para dibujar modo solido
//**************************************************************************

void dibujar(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos) {
    glColor3f(0.5,0.5,0.5);
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();    
}

//**************************************************************************
// Funcion para dibujar modo puntos
//**************************************************************************

void dibujar_puntos(const vector<_vertex3f> &Vertices, const unsigned int &resaltado) {
    glPointSize(5);
    glBegin(GL_POINTS);
    for(unsigned int i=0;i< Vertices.size();i++){
        if(resaltado==i) {
            glPointSize(5);
            glColor3f(1,0,0);
        } else {
            glPointSize(5);
            glColor3f(0,0,0);
        }
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar modo solido con nombres
//**************************************************************************

void dibujar_nombres(const vector<_vertex3f> &Vertices) {
    glPushName(1);
    glPolygonMode(GL_FRONT,GL_FILL);
    glPointSize(5);
    for(unsigned int i=0;i< Vertices.size();i++){
        glLoadName(i);
        glBegin(GL_POINTS);
            glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
        glEnd();
    }
    glPopName();
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
