//**************************************************************************
// Examen Febrero 2014
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 2
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

//**************************************************************************
// Funcion para dibujar modo solido
//**************************************************************************

void dibujar(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos, const vector<bool> &resaltado) {
    glColor3f(0.5,0.5,0.5);
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        if(resaltado[i]) {
            glColor3f(1,0,0);
        } else {
            glColor3f(0.5,0.5,0.5);
        }
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar modo solido con nombres
//**************************************************************************

void dibujar_nombres(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos) {
    glPushName(1);
    glPolygonMode(GL_FRONT,GL_FILL);
    for(unsigned int i=0;i<Triangulos.size();i++){
        glLoadName(i);
        glBegin(GL_TRIANGLES);
            glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
            glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
            glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
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

void calcular_vecinos(const vector<_vertex3i> &t, vector<vector<unsigned int> > &vecinos) {
    vector<vector<unsigned int> > v_aux(t.size());

    for(unsigned int i=0; i<t.size(); i++) {
        for(unsigned int j=0; j<t.size(); j++) {
            if(i!=j) {
                int n=0;
                if(t[i]._0==t[j]._0) n++;
                if(t[i]._0==t[j]._1) n++;
                if(t[i]._0==t[j]._2) n++;
                if(t[i]._1==t[j]._0) n++;
                if(t[i]._1==t[j]._1) n++;
                if(t[i]._1==t[j]._2) n++;
                if(t[i]._2==t[j]._0) n++;
                if(t[i]._2==t[j]._1) n++;
                if(t[i]._2==t[j]._2) n++;
                if(n==2) v_aux[i].push_back(j);
            }
        }
    }

    vecinos = v_aux;
}
