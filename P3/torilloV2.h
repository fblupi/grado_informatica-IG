//**************************************************************************
// Clase TorilloV2
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include <GL/gl.h>
#include "figura.h"

using namespace std;

class TorilloV2 {
private:
    Figura cubo;
    Figura cilindro;
    Figura prisma_triangular;
    Figura cono;
    Figura beethoven;
    GLfloat min_elevadora;
    GLfloat max_elevadora;
    GLfloat elevadora;
    GLfloat volante;
    GLfloat desplazamiento;
    GLfloat ruedas;
public:
    TorilloV2();

    void setElevadora(const GLfloat &num);
    void setVolante(const GLfloat &num);
    void setDesplazamiento(const GLfloat &num);
    GLfloat getElevadora();
    GLfloat getDesplazamiento();
    GLfloat getVolante();

    void dibujar(const int &modo);
    void draw_rueda(const int &modo);
    void draw_ruedas(const int &modo);
    void draw_palo_cabina(const int &modo);
    void draw_techo(const int &modo);
    void draw_cabina(const int &modo);
    void draw_asiento(const int &modo);
    void draw_espaldera(const int &modo);
    void draw_banco(const int &modo);
    void draw_interior(const int &modo);
    void draw_chasis(const int &modo);
    void draw_chasis_trasero(const int &modo);
    void draw_chasis_delantero(const int &modo);
    void draw_chasis_mandos(const int &modo);
    void draw_chasis_base(const int &modo);
    void draw_soporte(const int &modo);
    void draw_soporte_individual(const int &modo);
    void draw_palo_soporte(const int &modo);
    void draw_tope_soporte(const int &modo);
    void draw_tope_inferior(const int &modo);
    void draw_soporte_volante(const int &modo);
    void draw_volante(const int &modo);
    void draw_volante_completo(const int &modo);
    void draw_elevadora(const int &modo);
    void draw_soporte_pala(const int &modo);
    void draw_pala(const int &modo);
    void draw_palo_pala(const int &modo);
    void draw_cuerpo_pala(const int &modo);
    void draw_extremo_pala(const int &modo);
    void draw_union_palas(const int &modo);
    //void draw_faro(const int &modo);
};
