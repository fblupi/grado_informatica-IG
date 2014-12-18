//**************************************************************************
// Clase Cubo
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include"cubo.h"
#include "file_ply_stl.h"


Cubo::Cubo() {
    model();
    Mat.setTextura("D://TEXTURES//text-lata-1.jpg",false);
    normales();
    map();
    Mat.setAmbiental(_vertex4f(0.2,0.2,0.2,1));
    Mat.setDifusa(_vertex4f(0.4,0.4,0.4,1));
    Mat.setEspecular(_vertex4f(0.6,0.6,0.6,1));
    Mat.setBrillo(10);
}

void Cubo::model() {
    vector<_vertex3f> v(14);
    vector<_vertex3i> t(12);

    v[0] = _vertex3f(-.5,-.5,-.5);
    v[1] = _vertex3f(-.5,.5,-.5);
    v[2] = _vertex3f(.5,-.5,-.5);
    v[3] = _vertex3f(.5,.5,-.5);
    v[4] = _vertex3f(.5,-.5,.5);
    v[5] = _vertex3f(.5,.5,.5);
    v[6] = _vertex3f(-.5,-.5,.5);
    v[7] = _vertex3f(-.5,.5,.5);
    v[8] = v[0];
    v[9] = v[1];
    v[10] = v[0];
    v[11] = v[6];
    v[12] = v[1];
    v[13] = v[7];

    t[0] = _vertex3i(1,2,0);
    t[1] = _vertex3i(2,1,3);
    t[2] = _vertex3i(3,4,2);
    t[3] = _vertex3i(4,3,5);
    t[4] = _vertex3i(5,6,4);
    t[5] = _vertex3i(6,5,7);
    t[6] = _vertex3i(7,8,6);
    t[7] = _vertex3i(8,7,9);
    t[8] = _vertex3i(2,11,10);
    t[9] = _vertex3i(11,2,4);
    t[10] = _vertex3i(12,5,3);
    t[11] = _vertex3i(5,12,13);

    Vertices = v;
    Triangulos = t;
}

void Cubo::normales() {
    // TRIANGULOS
    vector<_vertex3f> v_aux(Triangulos.size());
    _vertex3f P, Q, N;
    for(unsigned int i=0; i<v_aux.size(); i++) {
        P.x = Vertices[Triangulos[i]._1].x - Vertices[Triangulos[i]._0].x;
        P.y = Vertices[Triangulos[i]._1].y - Vertices[Triangulos[i]._0].y;
        P.z = Vertices[Triangulos[i]._1].z - Vertices[Triangulos[i]._0].z;
        Q.x = Vertices[Triangulos[i]._2].x - Vertices[Triangulos[i]._0].x;
        Q.y = Vertices[Triangulos[i]._2].y - Vertices[Triangulos[i]._0].y;
        Q.z = Vertices[Triangulos[i]._2].z - Vertices[Triangulos[i]._0].z;
        N.x = P.y*Q.z - P.z*Q.y;
        N.y = P.z*Q.x - P.x*Q.z;
        N.z = P.x*Q.y - P.y*Q.x;
        N.normalize();
        v_aux[i] = N;
    }
    Normales_triangulos = v_aux;

    // VERTICES
    vector<_vertex3f> v_aux2(Vertices.size());
    v_aux2[0].x = (Normales_triangulos[0].x + Normales_triangulos[6].x + Normales_triangulos[7].x + Normales_triangulos[8].x)/4;
    v_aux2[0].y = (Normales_triangulos[0].y + Normales_triangulos[6].y + Normales_triangulos[7].y + Normales_triangulos[8].y)/4;
    v_aux2[0].z = (Normales_triangulos[0].z + Normales_triangulos[6].z + Normales_triangulos[7].z + Normales_triangulos[8].z)/4;
    v_aux2[0].normalize();
    v_aux2[1].x = (Normales_triangulos[0].x + Normales_triangulos[1].x + Normales_triangulos[7].x + Normales_triangulos[10].x + Normales_triangulos[11].x)/5;
    v_aux2[1].y = (Normales_triangulos[0].y + Normales_triangulos[1].y + Normales_triangulos[7].y + Normales_triangulos[10].y + Normales_triangulos[11].y)/5;
    v_aux2[1].z = (Normales_triangulos[0].z + Normales_triangulos[1].z + Normales_triangulos[7].z + Normales_triangulos[10].z + Normales_triangulos[11].z)/5;
    v_aux2[1].normalize();
    v_aux2[2].x = (Normales_triangulos[0].x + Normales_triangulos[1].x + Normales_triangulos[2].x + Normales_triangulos[8].x + Normales_triangulos[9].x)/5;
    v_aux2[2].y = (Normales_triangulos[0].y + Normales_triangulos[1].y + Normales_triangulos[2].y + Normales_triangulos[8].y + Normales_triangulos[9].y)/5;
    v_aux2[2].z = (Normales_triangulos[0].z + Normales_triangulos[1].z + Normales_triangulos[2].z + Normales_triangulos[8].z + Normales_triangulos[9].z)/5;
    v_aux2[2].normalize();
    v_aux2[3].x = (Normales_triangulos[1].x + Normales_triangulos[2].x + Normales_triangulos[3].x + Normales_triangulos[10].x)/4;
    v_aux2[3].y = (Normales_triangulos[1].y + Normales_triangulos[2].y + Normales_triangulos[3].y + Normales_triangulos[10].y)/4;
    v_aux2[3].z = (Normales_triangulos[1].z + Normales_triangulos[2].z + Normales_triangulos[3].z + Normales_triangulos[10].z)/4;
    v_aux2[3].normalize();
    v_aux2[4].x = (Normales_triangulos[2].x + Normales_triangulos[3].x + Normales_triangulos[4].x + Normales_triangulos[9].x)/4;
    v_aux2[4].y = (Normales_triangulos[2].y + Normales_triangulos[3].y + Normales_triangulos[4].y + Normales_triangulos[9].y)/4;
    v_aux2[4].z = (Normales_triangulos[2].z + Normales_triangulos[3].z + Normales_triangulos[4].z + Normales_triangulos[9].z)/4;
    v_aux2[4].normalize();
    v_aux2[5].x = (Normales_triangulos[3].x + Normales_triangulos[4].x + Normales_triangulos[5].x + Normales_triangulos[10].x + Normales_triangulos[11].x)/5;
    v_aux2[5].y = (Normales_triangulos[3].y + Normales_triangulos[4].y + Normales_triangulos[5].y + Normales_triangulos[10].y + Normales_triangulos[11].y)/5;
    v_aux2[5].z = (Normales_triangulos[3].z + Normales_triangulos[4].z + Normales_triangulos[5].z + Normales_triangulos[10].z + Normales_triangulos[11].z)/5;
    v_aux2[5].normalize();
    v_aux2[6].x = (Normales_triangulos[4].x + Normales_triangulos[5].x + Normales_triangulos[6].x + Normales_triangulos[8].x + Normales_triangulos[9].x)/5;
    v_aux2[6].y = (Normales_triangulos[4].y + Normales_triangulos[5].y + Normales_triangulos[6].y + Normales_triangulos[8].y + Normales_triangulos[9].y)/5;
    v_aux2[6].z = (Normales_triangulos[4].z + Normales_triangulos[5].z + Normales_triangulos[6].z + Normales_triangulos[8].z + Normales_triangulos[9].z)/5;
    v_aux2[6].normalize();
    v_aux2[7].x = (Normales_triangulos[5].x + Normales_triangulos[6].x + Normales_triangulos[7].x + Normales_triangulos[11].x)/4;
    v_aux2[7].y = (Normales_triangulos[5].y + Normales_triangulos[6].y + Normales_triangulos[7].y + Normales_triangulos[11].y)/4;
    v_aux2[7].z = (Normales_triangulos[5].z + Normales_triangulos[6].z + Normales_triangulos[7].z + Normales_triangulos[11].z)/4;
    v_aux2[7].normalize();
    v_aux2[8] = v_aux2[0];
    v_aux2[9] = v_aux2[1];
    v_aux2[10] = v_aux2[0];
    v_aux2[11] = v_aux2[6];
    v_aux2[12] = v_aux2[1];
    v_aux2[13] = v_aux2[7];
    Normales_vertices = v_aux;
}

void Cubo::map(){
    vector<_vertex2f> m(Vertices.size());
    m[0].s=0; m[0].t=0.33;
    m[1].s=0; m[1].t=0.66;
    m[2].s=0.25; m[2].t=0.33;
    m[3].s=0.25; m[3].t=0.66;
    m[4].s=0.5; m[4].t=0.33;
    m[5].s=0.5; m[5].t=0.66;
    m[6].s=0.75; m[6].t=0.33;
    m[7].s=0.75; m[7].t=0.66;
    m[8].s=1; m[8].t=0.33;
    m[9].s=1; m[9].t=0.66;
    m[10].s=0.25; m[10].t=0;
    m[11].s=0.5; m[11].t=0;
    m[12].s=0.25; m[12].t=1;
    m[13].s=0.5; m[13].t=1;
    for(unsigned int i=0; i<m.size(); i++) {
        m[i].s = 1 - m[i].s;
        m[i].t = 1 - m[i].t;
    }
    Map = m;
}

void Cubo::dibujar(const int &modo) {
    switch(modo) {
        case 1: dibujar_puntos(); break;
        case 2: dibujar_alambre(); break;
        case 3: dibujar_solido(); break;
        case 4: dibujar_ajedrez(); break;
        case 5: Mat.activar(); dibujar_suavizado_plano(); break;
        case 6: Mat.activar(); dibujar_suavizado_gouraud(); break;
    }
}

void Cubo::dibujar_puntos() {
    glColor3f(1,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    for(unsigned int i=0;i< Vertices.size();i++){
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    }
    glEnd();
}

void Cubo::dibujar_alambre() {
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

void Cubo::dibujar_ajedrez() {
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

void Cubo::dibujar_solido() {
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

void Cubo::dibujar_suavizado_plano() {
    glColor3f(1,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glNormal3f(Normales_triangulos[i].x, Normales_triangulos[i].y, Normales_triangulos[i].z);
        glTexCoord2f(Map[Triangulos[i]._0].s,Map[Triangulos[i]._0].t);
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glTexCoord2f(Map[Triangulos[i]._1].s,Map[Triangulos[i]._1].t);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glTexCoord2f(Map[Triangulos[i]._2].s,Map[Triangulos[i]._2].t);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

void Cubo::dibujar_suavizado_gouraud() {
    glColor3f(1,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glTexCoord2f(Map[Triangulos[i]._0].s,Map[Triangulos[i]._0].t);
        glNormal3f(Normales_vertices[Triangulos[i]._0].x, Normales_vertices[Triangulos[i]._0].y, Normales_vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glTexCoord2f(Map[Triangulos[i]._1].s,Map[Triangulos[i]._1].t);
        glNormal3f(Normales_vertices[Triangulos[i]._1].x, Normales_vertices[Triangulos[i]._1].y, Normales_vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glTexCoord2f(Map[Triangulos[i]._2].s,Map[Triangulos[i]._2].t);
        glNormal3f(Normales_vertices[Triangulos[i]._2].x, Normales_vertices[Triangulos[i]._2].y, Normales_vertices[Triangulos[i]._2].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}
