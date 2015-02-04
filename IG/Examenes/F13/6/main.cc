//**************************************************************************
// Examen Febrero 2013
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 6: Se ha creado una retícula de 4x4 cuadrados. Indicar las
//              coordenadas de textura de las esquinas de cada uno de ellos
//              para obtener las dos composiciones siguientes con la textura
//              de la izquierda
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "vertex.h"
#include <vector>
#include <windows.h>
#include <jpg_imagen.hpp>

using namespace std;


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables textura
unsigned int tamx, tamy, id;
unsigned char *texels;
unsigned int composicion=1;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
    //  Front_plane>0  Back_plane>PlanoDelantero)
    glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1,0,0);
    glVertex3f(-AXIS_SIZE,0,0);
    glVertex3f(AXIS_SIZE,0,0);
    // eje Y, color verde
    glColor3f(0,1,0);
    glVertex3f(0,-AXIS_SIZE,0);
    glVertex3f(0,AXIS_SIZE,0);
    // eje Z, color azul
    glColor3f(0,0,1);
    glVertex3f(0,0,-AXIS_SIZE);
    glVertex3f(0,0,AXIS_SIZE);
    glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    if(composicion==1) {
        // QUAD 1
        glVertex3f(-1,-1,0);
        glVertex3f(-.5,-1,0);
        glVertex3f(-.5,-.5,0);
        glVertex3f(-1,-.5,0);
        // QUAD 2
        glTexCoord2f(0,1);
        glVertex3f(-.5,-1,0);
        glTexCoord2f(.33,1);
        glVertex3f(0,-1,0);
        glTexCoord2f(.33,.66);
        glVertex3f(0,-.5,0);
        glTexCoord2f(0,.66);
        glVertex3f(-.5,-.5,0);
        // QUAD 3
        glTexCoord2f(.33,1);
        glVertex3f(0,-1,0);
        glTexCoord2f(.66,1);
        glVertex3f(.5,-1,0);
        glTexCoord2f(.66,.66);
        glVertex3f(.5,-.5,0);
        glTexCoord2f(.33,.66);
        glVertex3f(0,-.5,0);
        // QUAD 4
        glTexCoord2f(.66,1);
        glVertex3f(.5,-1,0);
        glTexCoord2f(1,1);
        glVertex3f(1,-1,0);
        glTexCoord2f(1,.66);
        glVertex3f(1,-.5,0);
        glTexCoord2f(.66,.66);
        glVertex3f(.5,-.5,0);
        // QUAD 5
        glVertex3f(-1,-.5,0);
        glVertex3f(-.5,-.5,0);
        glVertex3f(-.5,0,0);
        glVertex3f(-1,0,0);
        // QUAD 6
        glTexCoord2f(0,.66);
        glVertex3f(-.5,-.5,0);
        glTexCoord2f(.33,.66);
        glVertex3f(0,-.5,0);
        glTexCoord2f(.33,.33);
        glVertex3f(0,0,0);
        glTexCoord2f(0,.33);
        glVertex3f(-.5,0,0);
        // QUAD 7
        glTexCoord2f(.33,.66);
        glVertex3f(0,-.5,0);
        glTexCoord2f(.66,.66);
        glVertex3f(.5,-.5,0);
        glTexCoord2f(.66,.33);
        glVertex3f(.5,0,0);
        glTexCoord2f(.33,.33);
        glVertex3f(0,0,0);
        // QUAD 8
        glTexCoord2f(.66,.66);
        glVertex3f(.5,-.5,0);
        glTexCoord2f(1,.66);
        glVertex3f(1,-.5,0);
        glTexCoord2f(1,.33);
        glVertex3f(1,0,0);
        glTexCoord2f(.66,.33);
        glVertex3f(.5,0,0);
        // QUAD 9
        glVertex3f(-1,0,0);
        glVertex3f(-.5,0,0);
        glVertex3f(-.5,.5,0);
        glVertex3f(-1,.5,0);
        // QUAD 10
        glTexCoord2f(0,.33);
        glVertex3f(-.5,0,0);
        glTexCoord2f(.33,.33);
        glVertex3f(0,0,0);
        glTexCoord2f(.33,0);
        glVertex3f(0,.5,0);
        glTexCoord2f(0,0);
        glVertex3f(-.5,.5,0);
        // QUAD 11
        glTexCoord2f(.33,.33);
        glVertex3f(0,0,0);
        glTexCoord2f(.66,.33);
        glVertex3f(.5,0,0);
        glTexCoord2f(.66,0);
        glVertex3f(.5,.5,0);
        glTexCoord2f(.33,0);
        glVertex3f(0,.5,0);
        // QUAD 12
        glTexCoord2f(.66,.33);
        glVertex3f(.5,0,0);
        glTexCoord2f(1,.33);
        glVertex3f(1,0,0);
        glTexCoord2f(1,0);
        glVertex3f(1,.5,0);
        glTexCoord2f(.66,0);
        glVertex3f(.5,.5,0);
        // QUAD 13
        glVertex3f(-1,.5,0);
        glVertex3f(-.5,.5,0);
        glVertex3f(-.5,1,0);
        glVertex3f(-1,1,0);
        // QUAD 14
        glVertex3f(-.5,.5,0);
        glVertex3f(0,.5,0);
        glVertex3f(0,1,0);
        glVertex3f(-.5,1,0);
        // QUAD 15
        glVertex3f(0,.5,0);
        glVertex3f(.5,.5,0);
        glVertex3f(.5,1,0);
        glVertex3f(0,1,0);
        // QUAD 16
        glVertex3f(.5,.5,0);
        glVertex3f(1,.5,0);
        glVertex3f(1,1,0);
        glVertex3f(.5,1,0);
    } else {
        // QUAD 1
        glVertex3f(-1,-1,0);
        glVertex3f(-.5,-1,0);
        glVertex3f(-.5,-.5,0);
        glVertex3f(-1,-.5,0);
        // QUAD 2
        glVertex3f(-.5,-1,0);
        glVertex3f(0,-1,0);
        glVertex3f(0,-.5,0);
        glVertex3f(-.5,-.5,0);
        // QUAD 3
        glVertex3f(0,-1,0);
        glVertex3f(.5,-1,0);;
        glVertex3f(.5,-.5,0);;
        glVertex3f(0,-.5,0);
        // QUAD 4
        glVertex3f(.5,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(1,-.5,0);
        glVertex3f(.5,-.5,0);
        // QUAD 5
        glTexCoord2f(0,0);
        glVertex3f(-1,-.5,0);
        glTexCoord2f(0,.33);
        glVertex3f(-.5,-.5,0);
        glTexCoord2f(.33,.33);
        glVertex3f(-.5,0,0);
        glTexCoord2f(.33,0);
        glVertex3f(-1,0,0);
        // QUAD 6
        glTexCoord2f(0,.33);
        glVertex3f(-.5,-.5,0);
        glTexCoord2f(0,.66);
        glVertex3f(0,-.5,0);
        glTexCoord2f(.33,.66);
        glVertex3f(0,0,0);
        glTexCoord2f(.33,.33);
        glVertex3f(-.5,0,0);
        // QUAD 7
        glTexCoord2f(0,.66);
        glVertex3f(0,-.5,0);
        glTexCoord2f(0,1);
        glVertex3f(.5,-.5,0);
        glTexCoord2f(.33,1);
        glVertex3f(.5,0,0);
        glTexCoord2f(.33,.66);
        glVertex3f(0,0,0);
        // QUAD 8
        glVertex3f(.5,-.5,0);
        glVertex3f(1,-.5,0);
        glVertex3f(1,0,0);
        glVertex3f(.5,0,0);
        // QUAD 9
        glTexCoord2f(.33,0);
        glVertex3f(-1,0,0);
        glTexCoord2f(.33,.33);
        glVertex3f(-.5,0,0);
        glTexCoord2f(.66,.33);
        glVertex3f(-.5,.5,0);
        glTexCoord2f(.66,0);
        glVertex3f(-1,.5,0);
        // QUAD 10
        glTexCoord2f(.33,.33);
        glVertex3f(-.5,0,0);
        glTexCoord2f(.33,.66);
        glVertex3f(0,0,0);
        glTexCoord2f(.66,.66);
        glVertex3f(0,.5,0);
        glTexCoord2f(.66,.33);
        glVertex3f(-.5,.5,0);
        // QUAD 11
        glTexCoord2f(.33,.66);
        glVertex3f(0,0,0);
        glTexCoord2f(.33,1);
        glVertex3f(.5,0,0);
        glTexCoord2f(.66,1);
        glVertex3f(.5,.5,0);
        glTexCoord2f(.66,.66);
        glVertex3f(0,.5,0);
        // QUAD 12
        glVertex3f(.5,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,.5,0);
        glVertex3f(.5,.5,0);
        // QUAD 13
        glTexCoord2f(.66,0);
        glVertex3f(-1,.5,0);
        glTexCoord2f(.66,.33);
        glVertex3f(-.5,.5,0);
        glTexCoord2f(1,.33);
        glVertex3f(-.5,1,0);
        glTexCoord2f(1,0);
        glVertex3f(-1,1,0);
        // QUAD 14
        glTexCoord2f(.66,.33);
        glVertex3f(-.5,.5,0);
        glTexCoord2f(.66,.66);
        glVertex3f(0,.5,0);
        glTexCoord2f(1,.66);
        glVertex3f(0,1,0);
        glTexCoord2f(1,.33);
        glVertex3f(-.5,1,0);
        // QUAD 15
        glTexCoord2f(.66,.66);
        glVertex3f(0,.5,0);
        glTexCoord2f(.66,1);
        glVertex3f(.5,.5,0);
        glTexCoord2f(1,1);
        glVertex3f(.5,1,0);
        glTexCoord2f(1,.66);
        glVertex3f(0,1,0);
        // QUAD 16
        glVertex3f(.5,.5,0);
        glVertex3f(1,.5,0);
        glVertex3f(1,1,0);
        glVertex3f(.5,1,0);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
    clear_window();
    change_observer();
    draw_axis();
    draw_objects();
    glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
    change_projection();
    glViewport(0,0,Ancho1,Alto1);
    glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
    // Para resolver el problema de ver si num==0, hago num-0.05>0
    switch (Tecla1) {
        case 'Q': exit(0); break;
        case 'q': exit(0); break;
        case '1': composicion=1; break;
        case '2': composicion=2; break;
    }
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{
    switch (Tecla1) {
        case GLUT_KEY_LEFT:Observer_angle_y--;break;
        case GLUT_KEY_RIGHT:Observer_angle_y++;break;
        case GLUT_KEY_UP:Observer_angle_x--;break;
        case GLUT_KEY_DOWN:Observer_angle_x++;break;
        case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
        case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    }
    glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Window_width=.5;
    Window_height=.5;
    Front_plane=10;
    Back_plane=10000;

    // se inicia la posicion del observador, en el eje z
    Observer_distance=3*Front_plane;
    Observer_angle_x=0;
    Observer_angle_y=0;

    // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1,1,1,1);

    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0,0,UI_window_width,UI_window_height);

    // textura
    jpg::Imagen * pimg = NULL;
    pimg = new jpg::Imagen("D://TEXTURES//text-lata-1.jpg");
    tamx = pimg->tamX();
    tamy = pimg->tamY();
    texels = pimg->leerPixels();
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,tamx,tamy,GL_RGB,GL_UNSIGNED_BYTE,texels);

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Examen Feb. 2013 - Ejercicio 6");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
