//**************************************************************************
// Clase Lata
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "lata.h"
#include "vertex.h"
#include "file_ply_stl.h"

using namespace std;

Lata::Lata() {
    // Modelamos objetos
    unsigned int barrido = 48;
    Tapa_inferior.model_ply_vertices("D://PLY//rev//lata_tapainf");
    Tapa_inferior.barrido_circular(barrido);
    Tapa_inferior.calcular_normales_triangulos();
    Tapa_inferior.calcular_normales_vertices();
    Tapa_superior.model_ply_vertices("D://PLY//rev//lata_tapasup");
    Tapa_superior.barrido_circular(barrido);
    Tapa_superior.calcular_normales_triangulos();
    Tapa_superior.calcular_normales_vertices();
    Cuerpo.model_ply_vertices("D://PLY//rev//lata_cuerpo");
    Cuerpo.setTextura("D://TEXTURES//text-lata-1.jpg",false);
    Cuerpo.barrido_circular_texturado(barrido);
    Cuerpo.calcular_normales_triangulos();
    Cuerpo.calcular_normales_vertices();
    // Definimos materiales
    Tapa_inferior.setAmbiental(_vertex4f(0.5,0.5,0.5,1));
    Tapa_inferior.setDifusa(_vertex4f(0.7,0.6,0.6,1));
    Tapa_inferior.setEspecular(_vertex4f(1,1,1,1));
    Tapa_inferior.setBrillo(100);
    Tapa_superior.setAmbiental(_vertex4f(0.5,0.5,0.5,1));
    Tapa_superior.setDifusa(_vertex4f(0.7,0.6,0.6,1));
    Tapa_superior.setEspecular(_vertex4f(1,1,1,1));
    Tapa_superior.setBrillo(100);
    Cuerpo.setAmbiental(_vertex4f(0.5,0.5,0.5,1));
    Cuerpo.setDifusa(_vertex4f(0.6,0.6,0.6,1));
    Cuerpo.setEspecular(_vertex4f(1,1,1,1));
    Cuerpo.setBrillo(100);
}

void Lata::dibujar(const int &modo) {
    Cuerpo.dibujar(modo);
    Tapa_inferior.dibujar(modo);
    Tapa_superior.dibujar(modo);
}
