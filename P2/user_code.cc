//**************************************************************************
// Codigo del usuario
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include <math.h>

using namespace std;

#define PI 3.1416

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
    glPointSize(3);

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

void model_ply_vertices(const char *file_name, vector<_vertex3f> &v) {
    vector<float> v_aux;

    ply::read_vertices(file_name,v_aux);
    vector<_vertex3f> Vertices(v_aux.size()/3);

    for(unsigned int i=0; i<Vertices.size(); i++) {
        Vertices[i].x = v_aux[i*3];
        Vertices[i].y = v_aux[i*3+1];
        Vertices[i].z = v_aux[i*3+2];
    }

    v = Vertices;
}

//**************************************************************************
// Barrido circular basico (eje y)
//**************************************************************************

void barrido_circular_basico(const vector<_vertex3f> &puntos, const unsigned int &n, vector<_vertex3f> &v, vector<_vertex3i> &t) {
    float alfa = 2*PI/n;
    unsigned int m = puntos.size();
    unsigned int n_puntos = m*n;
    unsigned int pos;
    unsigned int cnt = 0;

    vector<_vertex3f> Vertices(n_puntos);
    vector<_vertex3i> Triangulos(6*n);

    for(unsigned int i=0; i<puntos.size(); i++) {
        Vertices[i] = puntos[i];
    }

    for(unsigned int i=1; i<n; i++) {
        for(unsigned int j=0; j<m; j++) {
            Vertices[i*m+j].x = puntos[j].x*cos(alfa*i);
            Vertices[i*m+j].y = puntos[j].y;
            Vertices[i*m+j].z = puntos[j].x*sin(alfa*i);
        }
    }

    v = Vertices;

    for(unsigned int i=0; i<(m-1); i++) {
        for(unsigned int j=0; j<n; j++) {
            pos = m*j+i;

            Triangulos[cnt]._0 = (pos+1)%n_puntos;
            Triangulos[cnt]._1 = (pos+m)%n_puntos;
            Triangulos[cnt]._2 = (pos)%n_puntos;
            Triangulos[cnt+1]._0 = (pos+1)%n_puntos;
            Triangulos[cnt+1]._1 = (pos+m+1)%n_puntos;
            Triangulos[cnt+1]._2 = (pos+m)%n_puntos;

            cnt+=2;
        }
    }

    t = Triangulos;

}

//**************************************************************************
// Barrido circular (eje y)
//**************************************************************************

void barrido_circular(const vector<_vertex3f> &puntos, const unsigned int &n, vector<_vertex3f> &v, vector<_vertex3i> &t) {
    bool p_inf = false; // ¿Extremo inferior en eje de rotación?
    bool p_sup = false; // ¿Extremo superior en eje de rotación?

    if(puntos[0].x==0) p_inf = true;                // Extremo inferior en eje de rotación
    if(puntos[puntos.size()-1].x==0) p_sup = true;  // Extremo superior en eje de rotación

    float alfa = 2*PI/n;    // Ángulo entre un vértice y otro
    unsigned int m = puntos.size(); // Vértices interiores iniciales

    if(p_inf) m--;  // Si extremo inferior en eje de rotación, uno de los vértices no es interior
    if(p_sup) m--;  // Si extremo superior en eje de rotación, uno de los vértices no es interior

    unsigned int n_puntos = m*n;            // Vértices totales. Vértices interiores iniciales * n
    unsigned int n_puntos_interiores = m*n; // Vértices interiores. Vértices interiores iniciales * n

    if(p_inf) n_puntos++;   // Hay un vértice más además de los interiores
    if(p_sup) n_puntos++;   // Hay un vértice más además de los interiores

    unsigned int n_triangulos = 2*n*(m-1);  // Triangulos totales. 2 * n * (m-1)

    if(p_inf) n_triangulos+=n;   // Hay n triángulos más además de los interiores
    if(p_sup) n_triangulos+=n;   // Hay n triángulos más además de los interiores

    vector<_vertex3f> Vertices(n_puntos);
    vector<_vertex3i> Triangulos(n_triangulos);

    //***** 1. VERTICES ****************************************************
    // a. NO HAY EXTREMOS EN EL EJE DE ROTACIÓN
    if(!p_inf && !p_sup) {
        // 1.1a. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size(); i++) {   // Recorremos el vector entero
            Vertices[i] = puntos[i];
        }
        // 1.2a. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<m; j++) {
                Vertices[i*m+j].x = puntos[j].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                Vertices[i*m+j].y = puntos[j].y;                // Coor y no varía
                Vertices[i*m+j].z = puntos[j].x*sin(alfa*i);    // Coor z = R * sin(alfa)
            }
        }
    }
    // b. EXTREMO INFERIOR EN EL EJE DE ROTACIÓN
    else if(p_inf && !p_sup) {
        // 1.1b. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-1; i++) { // Nos saltamos el primer elemento
            Vertices[i] = puntos[i+1];
        }
        // 1.2b. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size(); j++) {
                Vertices[i*m+j].x = puntos[j+1].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                Vertices[i*m+j].y = puntos[j+1].y;                // Coor y no varía
                Vertices[i*m+j].z = puntos[j+1].x*sin(alfa*i);    // Coor z = R * sin(alfa
            }
        }
        // 1.3b. Guardamos vertices "tapa"
        Vertices[n_puntos-1] = puntos[0];   // Primer vértice
    }
    // c. EXTREMO SUPERIOR EN EL EJE DE ROTACIÓN
    else if(!p_inf && p_sup) {
        // 1.1c. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-1; i++) { // Nos saltamos el último elemento
            Vertices[i] = puntos[i];
        }
        // 1.2c. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size()-1; j++) {
                Vertices[i*m+j].x = puntos[j].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                Vertices[i*m+j].y = puntos[j].y;                // Coor y no varía
                Vertices[i*m+j].z = puntos[j].x*sin(alfa*i);    // Coor z = R * sin(alfa
            }
        }
        // 1.3c. Guardamos vertices "tapa"
        Vertices[n_puntos-1] = puntos[puntos.size()-1]; // Último vértice
    }
    // d. AMBOS EXTREMOS EN EL EJE DE ROTACIÓN
    else if (p_inf && p_sup) {
        // 1.1d. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-2; i++) { // Nos saltamos el primer y el último elemento
            Vertices[i] = puntos[i+1];
        }
        // 1.2d. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size()-1; j++) {
                Vertices[i*m+j].x = puntos[j+1].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                Vertices[i*m+j].y = puntos[j+1].y;                // Coor y no varía
                Vertices[i*m+j].z = puntos[j+1].x*sin(alfa*i);    // Coor z = R * sin(alfa
            }
        }
        // 1.3d. Guardamos vertices "tapa"
        Vertices[n_puntos-2] = puntos[0];               // Primer vértice
        Vertices[n_puntos-1] = puntos[puntos.size()-1]; // Último vértice
    }
    // 1.4. Guardamos en el vector salida
    v = Vertices;
    //**********************************************************************

    //***** 2. TRIANGULOS **************************************************
    unsigned int pos;       // Posición en la matriz de triangulos
    unsigned int pos_ext;   // Posición del vértice extremo al que van las tapas
    unsigned int cnt = 0;   // Índice del vector de triángulo actual
    // 2.1. Tapa inferior
    if(p_inf) { // Si hay vértice extremo inferior, se modela
        if(p_sup) pos_ext = n_puntos-2; // Si hay vértice extremo superior, el inferior estará en la penúltima posición
        else pos_ext = n_puntos-1;      // Si no hay vértice extremo superior, el inferior estará en la última posición
        for(unsigned int i=0; i<n; i++) {
            pos = i*m;  // Salto al siguiente primer vértice
            Triangulos[cnt]._0 = (pos)%n_puntos_interiores;     // Vértice actual
            Triangulos[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
            Triangulos[cnt]._2 = pos_ext;                       // Vértice extremo inferior
            cnt++;  // Siguiente índice del vector de triángulos
        }
    }
    // 2.2. Tapa superior
    if(p_sup) { // Si hay vértice extremo superior, se modela
        pos_ext = n_puntos-1;
        for(unsigned int i=0; i<n; i++) {
            pos = i*m+m-1;  // Salto al siguiente último vértice
            Triangulos[cnt]._0 = pos_ext;                       // Vértice extremo superior
            Triangulos[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
            Triangulos[cnt]._2 = (pos)%n_puntos_interiores;     // Vértice actual
            cnt++;  // Siguiente índice del vector de triángulos
        }
    }
    // 2.3. Triangulos intermedios
    for(unsigned int i=0; i<(m-1); i++) {
        for(unsigned int j=0; j<n; j++) {
            pos = m*j+i;    // Salto al siguiente vértice a la derecha
            // 2.3.1. Triangulo par
            Triangulos[cnt]._0 = (pos+1)%n_puntos_interiores;       // Vértice encima del actual
            Triangulos[cnt]._1 = (pos+m)%n_puntos_interiores;       // Vértice a la derecha del actual
            Triangulos[cnt]._2 = (pos)%n_puntos_interiores;         // Vértice actual
            // 2.3.3. Triangulo impar
            Triangulos[cnt+1]._0 = (pos+1)%n_puntos_interiores;     // Vértice encima del actual
            Triangulos[cnt+1]._1 = (pos+m+1)%n_puntos_interiores;   // Vértice a la derecha y encima del actual
            Triangulos[cnt+1]._2 = (pos+m)%n_puntos_interiores;     // Vértice a la derecha del actual
            cnt+=2;  // Siguientes dos índices del vector de triángulos
        }
    }
    // 2.4. Guardamos en el vector salida
    t = Triangulos;
    //**********************************************************************
}
