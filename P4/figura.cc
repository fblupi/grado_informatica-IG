//**************************************************************************
// Clase Figura
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "figura.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include <math.h>

using namespace std;

//**************************************************************************
// CONSTRUCTORES, MODEL PLY Y BARRIDO
//**************************************************************************

Figura::Figura() {
    Color._0=1;
    Color._1=0;
    Color._2=0;
    Calcular_textura=false;
    setAmbiental(_vertex4f(0.5,0.5,0.5,1));
    setDifusa(_vertex4f(0.5,0.5,0.5,1));
    setEspecular(_vertex4f(0.5,0.5,0.5,1));
    setBrillo(30);
}

void Figura::model_ply(const char *file_name) {
    vector<float> v_aux;
    vector<int> t_aux;

    ply::read(file_name,v_aux,t_aux);
    vector<_vertex3f> v(v_aux.size()/3);
    vector<_vertex3i> t(t_aux.size()/3);

    for(unsigned int i=0; i<v.size(); i++) {
        v[i].x = v_aux[i*3];
        v[i].y = v_aux[i*3+1];
        v[i].z = v_aux[i*3+2];
    }

    for(unsigned int i=0; i<t.size(); i++) {
        t[i]._0 = t_aux[i*3];
        t[i]._1 = t_aux[i*3+1];
        t[i]._2 = t_aux[i*3+2];
    }

    Vertices = v;
    Triangulos = t;
}

void Figura::model_ply_vertices(const char *file_name) {
    vector<float> v_aux;

    ply::read_vertices(file_name,v_aux);
    vector<_vertex3f> v(v_aux.size()/3);

    for(unsigned int i=0; i<v.size(); i++) {
        v[i].x = v_aux[i*3];
        v[i].y = v_aux[i*3+1];
        v[i].z = v_aux[i*3+2];
    }

    Vertices = v;
}

void Figura::barrido_circular(const unsigned int &n) {
    vector<_vertex3f> puntos = Vertices;

    bool p_inf = false; // ¿Extremo inferior en eje de rotación?
    bool p_sup = false; // ¿Extremo superior en eje de rotación?

    bool aba_arr = false;   // ¿El primer punto esta abajo?

    if(puntos[0].x==0) p_inf = true;                // Extremo inferior en eje de rotación
    if(puntos[puntos.size()-1].x==0) p_sup = true;  // Extremo superior en eje de rotación

    if(puntos[0].y<puntos[puntos.size()-1].y) aba_arr = true;   // El primer punto está abajo

    float alfa = 2*M_PI/n;    // Ángulo entre un vértice y otro
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

    vector<_vertex3f> v_aux(n_puntos);
    vector<_vertex3i> t_aux(n_triangulos);

    //***** 1. VERTICES ****************************************************
    // a. NO HAY EXTREMOS EN EL EJE DE ROTACIÓN
    if(!p_inf && !p_sup) {
        // 1.1a. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size(); i++) {   // Recorremos el vector entero
            v_aux[i] = puntos[i];
        }
        // 1.2a. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<m; j++) {
                v_aux[i*m+j].x = puntos[j].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j].x*sin(alfa*i);    // Coor z = R * sin(alfa)
            }
        }
    }
    // b. EXTREMO INFERIOR EN EL EJE DE ROTACIÓN
    else if(p_inf && !p_sup) {
        // 1.1b. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-1; i++) { // Nos saltamos el primer elemento
            v_aux[i] = puntos[i+1];
        }
        // 1.2b. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size(); j++) {
                v_aux[i*m+j].x = puntos[j+1].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j+1].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j+1].x*sin(alfa*i);    // Coor z = R * sin(alfa
            }
        }
        // 1.3b. Guardamos vertices "tapa"
        v_aux[n_puntos-1] = puntos[0];   // Primer vértice
    }
    // c. EXTREMO SUPERIOR EN EL EJE DE ROTACIÓN
    else if(!p_inf && p_sup) {
        // 1.1c. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-1; i++) { // Nos saltamos el último elemento
            v_aux[i] = puntos[i];
        }
        // 1.2c. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size()-1; j++) {
                v_aux[i*m+j].x = puntos[j].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j].x*sin(alfa*i);    // Coor z = R * sin(alfa
            }
        }
        // 1.3c. Guardamos vertices "tapa"
        v_aux[n_puntos-1] = puntos[puntos.size()-1]; // Último vértice
    }
    // d. AMBOS EXTREMOS EN EL EJE DE ROTACIÓN
    else if (p_inf && p_sup) {
        // 1.1d. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-2; i++) { // Nos saltamos el primer y el último elemento
            v_aux[i] = puntos[i+1];
        }
        // 1.2d. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size()-1; j++) {
                v_aux[i*m+j].x = puntos[j+1].x*cos(alfa*i);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j+1].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j+1].x*sin(alfa*i);    // Coor z = R * sin(alfa
            }
        }
        // 1.3d. Guardamos vertices "tapa"
        v_aux[n_puntos-2] = puntos[0];               // Primer vértice
        v_aux[n_puntos-1] = puntos[puntos.size()-1]; // Último vértice
    }
    // 1.4. Guardamos en el vector salida
    Vertices = v_aux;

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
            if(aba_arr) {   // Si los puntos se presentan de abajo arriba
                t_aux[cnt]._0 = (pos)%n_puntos_interiores;     // Vértice actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = pos_ext;                       // Vértice extremo inferior
            } else {        // Si los puntos se presentan de arriba a abajo
                t_aux[cnt]._0 = pos_ext;                       // Vértice extremo inferior
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos)%n_puntos_interiores;     // Vértice actual
            }
            cnt++;  // Siguiente índice del vector de triángulos
        }
    }
    // 2.2. Tapa superior
    if(p_sup) { // Si hay vértice extremo superior, se modela
        pos_ext = n_puntos-1;
        for(unsigned int i=0; i<n; i++) {
            pos = i*m+m-1;  // Salto al siguiente último vértice
            if(aba_arr) {   // Si los puntos se presentan de abajo arriba
                t_aux[cnt]._0 = pos_ext;                       // Vértice extremo superior
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos)%n_puntos_interiores;     // Vértice actual
            } else {        // Si los puntos se presentan de arriba a abajo
                t_aux[cnt]._0 = (pos)%n_puntos_interiores;     // Vértice actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = pos_ext;                       // Vértice extremo superior
            }
            cnt++;  // Siguiente índice del vector de triángulos
        }
    }
    // 2.3. Triangulos intermedios
    for(unsigned int i=0; i<(m-1); i++) {
        for(unsigned int j=0; j<n; j++) {
            pos = m*j+i;    // Salto al siguiente vértice a la derecha
            if(aba_arr) {   // Si los puntos se presentan de abajo arriba
                // 2.3.1. Triangulo par
                t_aux[cnt]._0 = (pos+1)%n_puntos_interiores;       // Vértice encima del actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;       // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos)%n_puntos_interiores;         // Vértice actual
                // 2.3.3. Triangulo impar
                t_aux[cnt+1]._0 = (pos+1)%n_puntos_interiores;     // Vértice encima del actual
                t_aux[cnt+1]._1 = (pos+m+1)%n_puntos_interiores;   // Vértice a la derecha y encima del actual
                t_aux[cnt+1]._2 = (pos+m)%n_puntos_interiores;     // Vértice a la derecha del actual
            } else {        // Si los puntos se presentan de arriba a abajo
                // 2.3.1. Triangulo par
                t_aux[cnt]._0 = (pos)%n_puntos_interiores;         // Vértice actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;       // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos+1)%n_puntos_interiores;       // Vértice encima del actual
                // 2.3.3. Triangulo impar
                t_aux[cnt+1]._0 = (pos+m)%n_puntos_interiores;     // Vértice a la derecha del actual
                t_aux[cnt+1]._1 = (pos+m+1)%n_puntos_interiores;   // Vértice a la derecha y encima del actual
                t_aux[cnt+1]._2 = (pos+1)%n_puntos_interiores;     // Vértice encima del actual
            }
            cnt+=2;  // Siguientes dos índices del vector de triángulos
        }
    }
    // 2.4. Guardamos en el vector salida
    Triangulos = t_aux;
}

void Figura::barrido_circular_texturado(const unsigned int &n) {
    vector<_vertex3f> puntos = Vertices;

    float alfa = 2*M_PI/n;    // Ángulo entre un vértice y otro
    unsigned int m = puntos.size(); // Vértices interiores iniciales

    unsigned int n_puntos = m*(n+1);

    unsigned int n_triangulos = 2*n*(m-1);  // Triangulos totales. 2 * n * (m-1)

    vector<_vertex3f> v_aux(n_puntos);
    vector<_vertex3i> t_aux(n_triangulos);

    //***** 1. VERTICES ****************************************************
    // 1.1. Guardamos vertices iniciales
    for(unsigned int i=0; i<puntos.size(); i++) {   // Recorremos el vector entero
        v_aux[i] = puntos[i];
    }
    // 1.2. Guardamos vertices creados con el barrido
    for(unsigned int i=1; i<n+1; i++) {
        for(unsigned int j=0; j<m; j++) {
            v_aux[i*m+j].x = puntos[j].x*cos(alfa*i);    // Coor x = R * cos(alfa)
            v_aux[i*m+j].y = puntos[j].y;                // Coor y no varía
            v_aux[i*m+j].z = puntos[j].x*sin(alfa*i);    // Coor z = R * sin(alfa)
        }
    }
    // 1.3. Guardamos el vector de salida
    Vertices = v_aux;

    //***** 2. TRIANGULOS **************************************************
    unsigned int pos;       // Posición en la matriz de triangulos
    unsigned int cnt = 0;   // Índice del vector de triángulo actual

    // 2.1 Guaradamos los triangulos
    for(unsigned int i=0; i<(m-1); i++) {
        for(unsigned int j=0; j<n; j++) {
            pos = m*j+i;    // Salto al siguiente vértice a la derecha
            // 2.1.1. Triangulo par
            t_aux[cnt]._0 = (pos+1)%n_puntos;       // Vértice encima del actual
            t_aux[cnt]._1 = (pos+m)%n_puntos;       // Vértice a la derecha del actual
            t_aux[cnt]._2 = (pos)%n_puntos;         // Vértice actual
            // 2.1.2. Triangulo impar
            t_aux[cnt+1]._0 = (pos+1)%n_puntos;     // Vértice encima del actual
            t_aux[cnt+1]._1 = (pos+m+1)%n_puntos;   // Vértice a la derecha y encima del actual
            t_aux[cnt+1]._2 = (pos+m)%n_puntos;     // Vértice a la derecha del actual
            cnt+=2;  // Siguientes dos índices del vector de triángulos
        }
    }
    // 2.2. Guardamos en el vector salida
    Triangulos = t_aux;

    //***** 3. COORDS. TEXTURA *********************************************
    mapear(n,m);
}

void Figura::barrido_circularV2(const unsigned int &n, const float &A, const float &B) {
    vector<_vertex3f> puntos = Vertices;

    float alfa = (B-A)/(n-1);

    bool p_inf = false; // ¿Extremo inferior en eje de rotación?
    bool p_sup = false; // ¿Extremo superior en eje de rotación?

    bool aba_arr = false;   // ¿El primer punto esta abajo?

    if(puntos[0].x==0) p_inf = true;                // Extremo inferior en eje de rotación
    if(puntos[puntos.size()-1].x==0) p_sup = true;  // Extremo superior en eje de rotación

    if(puntos[0].y<puntos[puntos.size()-1].y) aba_arr = true;   // El primer punto está abajo
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

    vector<_vertex3f> v_aux(n_puntos);
    vector<_vertex3i> t_aux(n_triangulos);

    //***** 1. VERTICES ****************************************************
    // a. NO HAY EXTREMOS EN EL EJE DE ROTACIÓN
    if(!p_inf && !p_sup) {
        // 1.1a. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size(); i++) {   // Recorremos el vector entero
            v_aux[i].x = puntos[i].x*cos(A);
            v_aux[i].y = puntos[i].y;
            v_aux[i].z = puntos[i].x*sin(A);
        }
        // 1.2a. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<m; j++) {
                v_aux[i*m+j].x = puntos[j].x*cos(alfa*i+A);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j].x*sin(alfa*i+A);    // Coor z = R * sin(alfa)
            }
        }
    }
    // b. EXTREMO INFERIOR EN EL EJE DE ROTACIÓN
    else if(p_inf && !p_sup) {
        // 1.1b. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-1; i++) { // Nos saltamos el primer elemento
            v_aux[i].x = puntos[i+1].x*cos(A);
            v_aux[i].y = puntos[i+1].y;
            v_aux[i].z = puntos[i+1].x*sin(A);
        }
        // 1.2b. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size(); j++) {
                v_aux[i*m+j].x = puntos[j+1].x*cos(alfa*i+A);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j+1].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j+1].x*sin(alfa*i+A);    // Coor z = R * sin(alfa
            }
        }
        // 1.3b. Guardamos vertices "tapa"
        v_aux[n_puntos-1] = puntos[0];   // Primer vértice
    }
    // c. EXTREMO SUPERIOR EN EL EJE DE ROTACIÓN
    else if(!p_inf && p_sup) {
        // 1.1c. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-1; i++) { // Nos saltamos el último elemento
            v_aux[i].x = puntos[i].x*cos(A);
            v_aux[i].y = puntos[i].y;
            v_aux[i].z = puntos[i].x*sin(A);
        }
        // 1.2c. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size()-1; j++) {
                v_aux[i*m+j].x = puntos[j].x*cos(alfa*i+A);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j].x*sin(alfa*i+A);    // Coor z = R * sin(alfa
            }
        }
        // 1.3c. Guardamos vertices "tapa"
        v_aux[n_puntos-1] = puntos[puntos.size()-1]; // Último vértice
    }
    // d. AMBOS EXTREMOS EN EL EJE DE ROTACIÓN
    else if (p_inf && p_sup) {
        // 1.1d. Guardamos vertices iniciales
        for(unsigned int i=0; i<puntos.size()-2; i++) { // Nos saltamos el primer y el último elemento
            v_aux[i].x = puntos[i+1].x*cos(A);
            v_aux[i].y = puntos[i+1].y;
            v_aux[i].z = puntos[i+1].x*sin(A);
        }
        // 1.2d. Guardamos vertices creados con el barrido
        for(unsigned int i=1; i<n; i++) {
            for(unsigned int j=0; j<puntos.size()-1; j++) {
                v_aux[i*m+j].x = puntos[j+1].x*cos(alfa*i+A);    // Coor x = R * cos(alfa)
                v_aux[i*m+j].y = puntos[j+1].y;                // Coor y no varía
                v_aux[i*m+j].z = puntos[j+1].x*sin(alfa*i+A);    // Coor z = R * sin(alfa
            }
        }
        // 1.3d. Guardamos vertices "tapa"
        v_aux[n_puntos-2] = puntos[0];               // Primer vértice
        v_aux[n_puntos-1] = puntos[puntos.size()-1]; // Último vértice
    }
    // 1.4. Guardamos en el vector salida
    Vertices = v_aux;

    //***** 2. TRIANGULOS **************************************************
    unsigned int pos;       // Posición en la matriz de triangulos
    unsigned int pos_ext;   // Posición del vértice extremo al que van las tapas
    unsigned int cnt = 0;   // Índice del vector de triángulo actual
    // 2.1. Tapa inferior
    if(p_inf) { // Si hay vértice extremo inferior, se modela
        if(p_sup) pos_ext = n_puntos-2; // Si hay vértice extremo superior, el inferior estará en la penúltima posición
        else pos_ext = n_puntos-1;      // Si no hay vértice extremo superior, el inferior estará en la última posición
        for(unsigned int i=0; i<(n-1); i++) {
            pos = i*m;  // Salto al siguiente primer vértice
            if(aba_arr) {   // Si los puntos se presentan de abajo arriba
                t_aux[cnt]._0 = (pos)%n_puntos_interiores;     // Vértice actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = pos_ext;                       // Vértice extremo inferior
            } else {        // Si los puntos se presentan de arriba a abajo
                t_aux[cnt]._0 = pos_ext;                       // Vértice extremo inferior
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos)%n_puntos_interiores;     // Vértice actual
            }
            cnt++;  // Siguiente índice del vector de triángulos
        }
    }
    // 2.2. Tapa superior
    if(p_sup) { // Si hay vértice extremo superior, se modela
        pos_ext = n_puntos-1;
        for(unsigned int i=0; i<(n-1); i++) {
            pos = i*m+m-1;  // Salto al siguiente último vértice
            if(aba_arr) {   // Si los puntos se presentan de abajo arriba
                t_aux[cnt]._0 = pos_ext;                       // Vértice extremo superior
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos)%n_puntos_interiores;     // Vértice actual
            } else {        // Si los puntos se presentan de arriba a abajo
                t_aux[cnt]._0 = (pos)%n_puntos_interiores;     // Vértice actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;   // Vértice a la derecha del actual
                t_aux[cnt]._2 = pos_ext;                       // Vértice extremo superior
            }
            cnt++;  // Siguiente índice del vector de triángulos
        }
    }
    // 2.3. Triangulos intermedios
    for(unsigned int i=0; i<(m-1); i++) {
        for(unsigned int j=0; j<(n-1); j++) {
            pos = m*j+i;    // Salto al siguiente vértice a la derecha
            if(aba_arr) {   // Si los puntos se presentan de abajo arriba
                // 2.3.1. Triangulo par
                t_aux[cnt]._0 = (pos+1)%n_puntos_interiores;       // Vértice encima del actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;       // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos)%n_puntos_interiores;         // Vértice actual
                // 2.3.3. Triangulo impar
                t_aux[cnt+1]._0 = (pos+1)%n_puntos_interiores;     // Vértice encima del actual
                t_aux[cnt+1]._1 = (pos+m+1)%n_puntos_interiores;   // Vértice a la derecha y encima del actual
                t_aux[cnt+1]._2 = (pos+m)%n_puntos_interiores;     // Vértice a la derecha del actual
            } else {        // Si los puntos se presentan de arriba a abajo
                // 2.3.1. Triangulo par
                t_aux[cnt]._0 = (pos)%n_puntos_interiores;         // Vértice actual
                t_aux[cnt]._1 = (pos+m)%n_puntos_interiores;       // Vértice a la derecha del actual
                t_aux[cnt]._2 = (pos+1)%n_puntos_interiores;       // Vértice encima del actual
                // 2.3.3. Triangulo impar
                t_aux[cnt+1]._0 = (pos+m)%n_puntos_interiores;     // Vértice a la derecha del actual
                t_aux[cnt+1]._1 = (pos+m+1)%n_puntos_interiores;   // Vértice a la derecha y encima del actual
                t_aux[cnt+1]._2 = (pos+1)%n_puntos_interiores;     // Vértice encima del actual
            }
            cnt+=2;  // Siguientes dos índices del vector de triángulos
        }
    }
    // 2.4. Guardamos en el vector salida
    Triangulos = t_aux;
}

//**************************************************************************
// VECTORES NORMALES
//**************************************************************************

void Figura::calcular_normales_triangulos() {
    vector<_vertex3f> v_aux(Triangulos.size());
    vector<pair<_vertex3f,_vertex3f> > v_aux2(Triangulos.size());

    double M=0.5;   // variable para redimensionar vector normal dibujad

    _vertex3f P, Q, N;  // Vectores P(V0->V1), Q(V0->V2) y normal N(P x Q)

    for(unsigned int i=0; i<v_aux.size(); i++) {
        // Calculo vector V0 -> V1
        P.x = Vertices[Triangulos[i]._1].x - Vertices[Triangulos[i]._0].x;
        P.y = Vertices[Triangulos[i]._1].y - Vertices[Triangulos[i]._0].y;
        P.z = Vertices[Triangulos[i]._1].z - Vertices[Triangulos[i]._0].z;
        // Calculo vector V0 -> V2
        Q.x = Vertices[Triangulos[i]._2].x - Vertices[Triangulos[i]._0].x;
        Q.y = Vertices[Triangulos[i]._2].y - Vertices[Triangulos[i]._0].y;
        Q.z = Vertices[Triangulos[i]._2].z - Vertices[Triangulos[i]._0].z;
        // Calculo vector normal = P x Q
        N.x = P.y*Q.z - P.z*Q.y;
        N.y = P.z*Q.x - P.x*Q.z;
        N.z = P.x*Q.y - P.y*Q.x;
        // Normalizo
        N.normalize();
        // Asigno valor
        v_aux[i] = N;

        // Calculo centroide
        v_aux2[i].first.x = (Vertices[Triangulos[i]._0].x + Vertices[Triangulos[i]._1].x + Vertices[Triangulos[i]._2].x)/3;
        v_aux2[i].first.y = (Vertices[Triangulos[i]._0].y + Vertices[Triangulos[i]._1].y + Vertices[Triangulos[i]._2].y)/3;
        v_aux2[i].first.z = (Vertices[Triangulos[i]._0].z + Vertices[Triangulos[i]._1].z + Vertices[Triangulos[i]._2].z)/3;
        // Calculo punto que pase por la normal y el centroide
        v_aux2[i].second.x = v_aux2[i].first.x + M*v_aux[i].x;
        v_aux2[i].second.y = v_aux2[i].first.y + M*v_aux[i].y;
        v_aux2[i].second.z = v_aux2[i].first.z + M*v_aux[i].z;
    }
    Normales_triangulos = v_aux;
    Normales_triangulos_dibujados = v_aux2;
}

void Figura::calcular_normales_vertices() {
    _vertex3f aux(0,0,0);   // vertex nulo (posicionado en el origen)
    pair<_vertex3f,_vertex3f> aux2; aux2.first = aux; aux2.second = aux;    // par de vertex nulos

    vector<_vertex3f> v_aux(Vertices.size(),aux);
    vector<pair<_vertex3f,_vertex3f> > v_aux2(Vertices.size(),aux2);

    double M=0.5;   // variable para redimensionar vector normal dibujado

    vector<int> num_triangulos(Vertices.size(),0);  // Contador de número de triangulos que ayuda a formar un vértice
    unsigned int id0, id1, id2;

    for(unsigned int i=0; i<Triangulos.size(); i++) {
        id0 = Triangulos[i]._0; // Vértice 0 del triángulo i
        id1 = Triangulos[i]._1; // Vértice 1 del triángulo i
        id2 = Triangulos[i]._2; // Vértice 2 del triángulo i
        // Aumento la suma de coordenadas del vértice 0 del triángulo i
        v_aux[id0].x += Normales_triangulos[i].x;
        v_aux[id0].y += Normales_triangulos[i].y;
        v_aux[id0].z += Normales_triangulos[i].z;
        num_triangulos[id0]++;  // Aumento contador del vértice 0 del triangulo i
        // Aumento la suma de coordenadas del vértice 1 del triángulo i
        v_aux[id1].x += Normales_triangulos[i].x;
        v_aux[id1].y += Normales_triangulos[i].y;
        v_aux[id1].z += Normales_triangulos[i].z;
        num_triangulos[id1]++;  // Aumento contador del vértice 1 del triangulo i
        // Aumento la suma de coordenadas del vértice 2 del triángulo i
        v_aux[id2].x += Normales_triangulos[i].x;
        v_aux[id2].y += Normales_triangulos[i].y;
        v_aux[id2].z += Normales_triangulos[i].z;
        num_triangulos[id2]++;  // Aumento contador del vértice 2 del triangulo i
    }
    for(unsigned int i=0; i<v_aux.size(); i++) {
        // Divido cada coordenada para obtener la media
        v_aux[i].x /= num_triangulos[i];
        v_aux[i].y /= num_triangulos[i];
        v_aux[i].z /= num_triangulos[i];
        // Normalizo
        v_aux[i].normalize();

        // Calculo centroide, en caso de los puntos, el propio punto
        v_aux2[i].first.x = Vertices[i].x;
        v_aux2[i].first.y = Vertices[i].y;
        v_aux2[i].first.z = Vertices[i].z;
        // Calculo punto que pase por la normal y el centroide
        v_aux2[i].second.x = v_aux2[i].first.x + M*v_aux[i].x;
        v_aux2[i].second.y = v_aux2[i].first.y + M*v_aux[i].y;
        v_aux2[i].second.z = v_aux2[i].first.z + M*v_aux[i].z;
    }
    Normales_vertices = v_aux;
    Normales_vertices_dibujados = v_aux2;
}

//**************************************************************************
// DIBUJAR
//**************************************************************************

void Figura::dibujar(const int &modo) {
    switch(modo) {
        case 1: dibujar_puntos(); break;
        case 2: dibujar_alambre(); break;
        case 3: dibujar_solido(); break;
        case 4: dibujar_ajedrez(); break;
        case 5: Mat.activar(); dibujar_suavizado_plano(); break;
        case 6: Mat.activar(); dibujar_suavizado_gouraud(); break;
    }
}

void Figura::dibujar() {
    dibujar_ajedrez();
}

void Figura::dibujar_puntos() {
    glColor3f(Color._0,Color._1,Color._2);
    glPointSize(3);

    glBegin(GL_POINTS);
    for(unsigned int i=0;i< Vertices.size();i++){
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    }
    glEnd();
}

void Figura::dibujar_alambre() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(Color._0,Color._1,Color._2);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

void Figura::dibujar_ajedrez() {
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

void Figura::dibujar_solido() {
    glColor3f(Color._0,Color._1,Color._2);
    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

void Figura::dibujar_suavizado_plano() {
    glColor3f(Color._0,Color._1,Color._2);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        glNormal3f(Normales_triangulos[i].x, Normales_triangulos[i].y, Normales_triangulos[i].z);
        if(!Map.empty()) {
            glTexCoord2f(Map[Triangulos[i]._0].s,Map[Triangulos[i]._0].t);
        }
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        if(!Map.empty()) {
            glTexCoord2f(Map[Triangulos[i]._1].s,Map[Triangulos[i]._1].t);
        }
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        if(!Map.empty()) {
            glTexCoord2f(Map[Triangulos[i]._2].s,Map[Triangulos[i]._2].t);
        }
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

void Figura::dibujar_suavizado_gouraud() {
    glColor3f(Color._0,Color._1,Color._2);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_SMOOTH);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i< Triangulos.size();i++){
        if(!Map.empty()) {
            glTexCoord2f(Map[Triangulos[i]._0].s,Map[Triangulos[i]._0].t);
        }
        glNormal3f(Normales_vertices[Triangulos[i]._0].x, Normales_vertices[Triangulos[i]._0].y, Normales_vertices[Triangulos[i]._0].z);
        glVertex3f(Vertices[Triangulos[i]._0].x, Vertices[Triangulos[i]._0].y, Vertices[Triangulos[i]._0].z);
        if(!Map.empty()) {
            glTexCoord2f(Map[Triangulos[i]._1].s,Map[Triangulos[i]._1].t);
        }
        glNormal3f(Normales_vertices[Triangulos[i]._1].x, Normales_vertices[Triangulos[i]._1].y, Normales_vertices[Triangulos[i]._1].z);
        glVertex3f(Vertices[Triangulos[i]._1].x, Vertices[Triangulos[i]._1].y, Vertices[Triangulos[i]._1].z);
        if(!Map.empty()) {
            glTexCoord2f(Map[Triangulos[i]._2].s,Map[Triangulos[i]._2].t);
        }
        glNormal3f(Normales_vertices[Triangulos[i]._2].x, Normales_vertices[Triangulos[i]._2].y, Normales_vertices[Triangulos[i]._2].z);
        glVertex3f(Vertices[Triangulos[i]._2].x, Vertices[Triangulos[i]._2].y, Vertices[Triangulos[i]._2].z);
    }
    glEnd();
}

void Figura::dibujar_normales_triangulos() {
    glColor3f(0,0,1);

    glBegin(GL_LINES);
    for(unsigned int i=0;i< Normales_triangulos_dibujados.size();i++){
        glVertex3f(Normales_triangulos_dibujados[i].first.x,
                   Normales_triangulos_dibujados[i].first.y,
                   Normales_triangulos_dibujados[i].first.z);
        glVertex3f(Normales_triangulos_dibujados[i].second.x,
                   Normales_triangulos_dibujados[i].second.y,
                   Normales_triangulos_dibujados[i].second.z);
    }
    glEnd();
}

void Figura::dibujar_normales_vertices() {
    glColor3f(0,0,1);

    glBegin(GL_LINES);
    for(unsigned int i=0;i< Normales_vertices_dibujados.size();i++){
        glVertex3f(Normales_vertices_dibujados[i].first.x,
                   Normales_vertices_dibujados[i].first.y,
                   Normales_vertices_dibujados[i].first.z);
        glVertex3f(Normales_vertices_dibujados[i].second.x,
                   Normales_vertices_dibujados[i].second.y,
                   Normales_vertices_dibujados[i].second.z);
    }
    glEnd();
}

//**************************************************************************
// GET Y SET
//**************************************************************************

vector<_vertex3f> Figura::getVertices() {
    return Vertices;
}

vector<_vertex3i> Figura::getTriangulos() {
    return Triangulos;
}

vector<_vertex3f> Figura::getNormales_triangulos() {
    return Normales_triangulos;
}

vector<_vertex3f> Figura::getNormales_vertices() {
    return Normales_vertices;
}

vector<pair<_vertex3f,_vertex3f> > Figura::getNormales_triangulos_dibujados() {
    return Normales_triangulos_dibujados;
}

vector<pair<_vertex3f,_vertex3f> > Figura::getNormales_vertices_dibujados() {
    return Normales_vertices_dibujados;
}

_vertex3f Figura::getColor() {
    return Color;
}

void Figura::setVertices(const vector<_vertex3f> &v) {
    Vertices = v;
}

void Figura::setTriangulos(const vector<_vertex3i> &v) {
    Triangulos = v;
}

void Figura::setNormales_triangulos(const vector<_vertex3f> &v) {
    Normales_triangulos = v;
}

void Figura::setNormales_vertices(const vector<_vertex3f> &v) {
    Normales_vertices = v;
}

void Figura::setNormales_triangulos_dibujados(const vector<pair<_vertex3f,_vertex3f> > &v) {
    Normales_triangulos_dibujados = v;
}

void Figura::setNormales_vertices_dibujados(const vector<pair<_vertex3f,_vertex3f> > &v) {
    Normales_vertices_dibujados = v;
}

void Figura::setColor(const _vertex3f &c) {
    Color = c;
}

void Figura::setAmbiental(const _vertex4f &a) {
    Mat.setAmbiental(a);
}

void Figura::setDifusa(const _vertex4f &d) {
    Mat.setDifusa(d);
}

void Figura::setEspecular(const _vertex4f &e) {
    Mat.setEspecular(e);
}

void Figura::setBrillo(const GLfloat &b) {
    Mat.setBrillo(b);
}

void Figura::setTextura(const char *file_name, const bool &automatic) {
    Mat.setTextura(file_name,automatic);
    if(!automatic) {
        Calcular_textura = true;
    }
}

void Figura::mapear(const unsigned int &n, const unsigned int &m) {
    vector<_vertex2f> v_aux(Vertices.size());
    float var = 1.0/n;
    vector<float> distancia(m);
    float suma = 0.0;
    distancia[0] = suma;
    for(unsigned int i=1; i<m; i++) {
        suma += sqrt(pow(Vertices[i].x-Vertices[i-1].x,2)+pow(Vertices[i].y-Vertices[i-1].y,2));
        distancia[i] = suma;
    }
    for(unsigned int i=0; i<m; i++) {
        distancia[i] /= suma;
    }
    for(unsigned int i=0; i<n+1; i++) {
        for(unsigned int j=0; j<m; j++) {
            v_aux[i*m+j].s = 1-i*var;           // s = i*distancia horizontal entre dos puntos
            v_aux[i*m+j].t = 1-distancia[j];    // t = distancia entre j y j-1
        }
    }
    Map = v_aux;
}
