//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

//**************************************************************************
// Funcion para dibujar modo solido
//**************************************************************************

void dibujar_solido(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos) {
    glColor3f(1,0,0);
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
// Funcion para dibujar modo solido 2
//**************************************************************************

void dibujar_solido2(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos) {
    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        if(Vertices[Triangulos[i]._0].x>0 && Vertices[Triangulos[i]._0].z>0 &&
           Vertices[Triangulos[i]._1].x>0 && Vertices[Triangulos[i]._1].z>0 &&
           Vertices[Triangulos[i]._2].x>0 && Vertices[Triangulos[i]._2].z>0)
        {
            glColor3f(1,0,0);
        }
        else if (Vertices[Triangulos[i]._0].x>0 && Vertices[Triangulos[i]._0].z<0 &&
                 Vertices[Triangulos[i]._1].x>0 && Vertices[Triangulos[i]._1].z<0 &&
                 Vertices[Triangulos[i]._2].x>0 && Vertices[Triangulos[i]._2].z<0)
        {
            glColor3f(1,1,0);
        }
        else if (Vertices[Triangulos[i]._0].x<0 && Vertices[Triangulos[i]._0].z>0 &&
                 Vertices[Triangulos[i]._1].x<0 && Vertices[Triangulos[i]._1].z>0 &&
                 Vertices[Triangulos[i]._2].x<0 && Vertices[Triangulos[i]._2].z>0)
        {
            glColor3f(0,0,1);
        }
        else if (Vertices[Triangulos[i]._0].x<0 && Vertices[Triangulos[i]._0].z<0 &&
                 Vertices[Triangulos[i]._1].x<0 && Vertices[Triangulos[i]._1].z<0 &&
                 Vertices[Triangulos[i]._2].x<0 && Vertices[Triangulos[i]._2].z<0)
        {
            glColor3f(0,1,0);
        } else {
            glColor3f(1,0,1);
        }
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar modo ajedrez
//**************************************************************************

void dibujar_ajedrez(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos) {
    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        switch (i%2) {
            case 0:glColor3f(1,0,0);break;
            case 1:glColor3f(0,1,0);break;
        }
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para dibujar modo alambre
//**************************************************************************

void dibujar_alambre(const vector<_vertex3f> &Vertices, const vector<_vertex3i> &Triangulos) {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1,0,0);

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

void dibujar_puntos(const vector<_vertex3f> &Vertices) {
    glColor3f(1,0,0);

    glBegin(GL_POINTS);
    for(unsigned int i=0;i< Vertices.size();i++){
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    }
    glEnd();
}

//**************************************************************************
// Funcion para modelar un cubo unidad
//**************************************************************************

void model_cubo(vector<_vertex3f> &v, vector<_vertex3i> &t) {
    vector<_vertex3f> Vertices(8);
    vector<_vertex3i> Triangulos(12);

    Vertices[0].x=-0.5;
    Vertices[0].y=-0.5;
    Vertices[0].z=-0.5;

    Vertices[1].x=0.5;
    Vertices[1].y=-0.5;
    Vertices[1].z=-0.5;

    Vertices[2].x=0.5;
    Vertices[2].y=0.5;
    Vertices[2].z=-0.5;

    Vertices[3].x=-0.5;
    Vertices[3].y=0.5;
    Vertices[3].z=-0.5;

    Vertices[4].x=-0.5;
    Vertices[4].y=-0.5;
    Vertices[4].z=0.5;

    Vertices[5].x=0.5;
    Vertices[5].y=-0.5;
    Vertices[5].z=0.5;

    Vertices[6].x=0.5;
    Vertices[6].y=0.5;
    Vertices[6].z=0.5;

    Vertices[7].x=-0.5;
    Vertices[7].y=0.5;
    Vertices[7].z=0.5;


    Triangulos[0]._0=0;
    Triangulos[0]._1=3;
    Triangulos[0]._2=1;

    Triangulos[1]._0=1;
    Triangulos[1]._1=3;
    Triangulos[1]._2=2;

    Triangulos[2]._0=1;
    Triangulos[2]._1=2;
    Triangulos[2]._2=5;

    Triangulos[3]._0=5;
    Triangulos[3]._1=2;
    Triangulos[3]._2=6;

    Triangulos[4]._0=5;
    Triangulos[4]._1=6;
    Triangulos[4]._2=4;

    Triangulos[5]._0=4;
    Triangulos[5]._1=6;
    Triangulos[5]._2=7;

    Triangulos[6]._0=4;
    Triangulos[6]._1=7;
    Triangulos[6]._2=0;

    Triangulos[7]._0=0;
    Triangulos[7]._1=7;
    Triangulos[7]._2=3;

    Triangulos[8]._0=4;
    Triangulos[8]._1=0;
    Triangulos[8]._2=5;

    Triangulos[9]._0=5;
    Triangulos[9]._1=0;
    Triangulos[9]._2=1;

    Triangulos[10]._0=3;
    Triangulos[10]._1=7;
    Triangulos[10]._2=2;

    Triangulos[11]._0=2;
    Triangulos[11]._1=7;
    Triangulos[11]._2=6;

    v = Vertices;
    t = Triangulos;
}

//**************************************************************************
// Funcion para modelar un tetraedro
//**************************************************************************

void model_tetraedro(vector<_vertex3f> &v, vector<_vertex3i> &t) {
    vector<_vertex3f> Vertices(4);
    vector<_vertex3i> Triangulos(4);

    Vertices[0].x=0;
    Vertices[0].y=1;
    Vertices[0].z=0;

    Vertices[1].x=0.5;
    Vertices[1].y=0;
    Vertices[1].z=-0.37;

    Vertices[2].x=0;
    Vertices[2].y=0;
    Vertices[2].z=0.5;

    Vertices[3].x=-0.5;
    Vertices[3].y=0;
    Vertices[3].z=-0.37;

    Triangulos[0]._0=1;
    Triangulos[0]._1=2;
    Triangulos[0]._2=3;

    Triangulos[1]._0=1;
    Triangulos[1]._1=0;
    Triangulos[1]._2=2;

    Triangulos[2]._0=2;
    Triangulos[2]._1=0;
    Triangulos[2]._2=3;

    Triangulos[3]._0=3;
    Triangulos[3]._1=0;
    Triangulos[3]._2=1;

    v = Vertices;
    t = Triangulos;
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
// Funcion para importar y modelar medio .ply
//**************************************************************************

void model_ply2(const char *file_name, vector<_vertex3f> &v, vector<_vertex3i> &t) {
    vector<float> v_aux; vector<int> t_aux;

    ply::read(file_name,v_aux,t_aux);
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Triangulos;

    _vertex3f ver;
    _vertex3i tri;
    vector<int> aux(v_aux.size()/3,-1);
    int c = 0;

    for(unsigned int i=0; i<v_aux.size(); i+=3) {
        if(v_aux[i+1]>=0) {
            ver.x = v_aux[i];
            ver.y = v_aux[i+1];
            ver.z = v_aux[i+2];
            Vertices.push_back(ver);
            aux[i/3] = c;
            c++;
        }
    }

    for(unsigned int i=0; i<t_aux.size(); i+=3) {
        if(aux[t_aux[i]]!=-1 && aux[t_aux[i+1]]!=-1 && aux[t_aux[i+2]]!=-1) {
            tri._0 = aux[t_aux[i]];
            tri._1 = aux[t_aux[i+1]];
            tri._2 = aux[t_aux[i+2]];
            Triangulos.push_back(tri);
        }
    }

    v = Vertices;
    t = Triangulos;
}

//**************************************************************************
// Lector de vector de flotantes
//**************************************************************************

void leer_puntos(const vector<float> &vec, vector<_vertex3f> &v) {
    if(vec.size()%3!=0) {
        cout << "Error. Número de coordenadas incorrectas, el tamaño del vector ha de ser divisible entre 3" << endl;
        exit(1);
    }

    vector<_vertex3f> Vertices(vec.size()/3);

    for(unsigned int i=0; i<Vertices.size(); i++) {
        Vertices[i].x = vec[i*3];
        Vertices[i].y = vec[i*3+1];
        Vertices[i].z = vec[i*3+2];
    }
    v = Vertices;
}
