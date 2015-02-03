//**************************************************************************
// Examen Febrero 2014
//
// Francisco Javier Bolívar Lupiáñez
//
// Ejercicio 3: Se desea hacer una función para visualizar una imagen. La
//              función debe cargar la imagen como una textura y
//              visualizarla aplicándola sobre un quad. Indica usando
//              pseudocódigo cómo dibujarías el quad y como le aplicarías
//              la textura para permitir que se pueda hacer zoom y
//              desplazamientos de la imagen. Suponer que la imagen es
//              cuadrada.
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
_vertex2f mapsd, mapsi, mapid, mapii;

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
        glTexCoord2f(mapii.s,mapii.t);
        glVertex3f(-1,-1,0);
        glTexCoord2f(mapid.s,mapid.t);
        glVertex3f(1,-1,0);
        glTexCoord2f(mapsd.s,mapsd.t);
        glVertex3f(1,1,0);
        glTexCoord2f(mapsi.s,mapsi.t);
        glVertex3f(-1,1,0);
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
        case 'Z':
            if(mapsd.s-mapsi.s>.2 && mapid.s-mapii.s>.2 &&
               mapii.t-mapsi.t>.2 && mapid.t-mapsd.t>.2) {
                mapii.s+=0.1; mapii.t-=0.1;
                mapid.s-=0.1; mapid.t-=0.1;
                mapsi.s+=0.1; mapsi.t+=0.1;
                mapsd.s-=0.1; mapsd.t+=0.1;
            }
            break;
        case 'z':
            if(mapsd.s-mapsi.s<1.0 && mapid.s-mapii.s<1.0 &&
               mapii.t-mapsi.t<1.0 && mapid.t-mapsd.t<1.0 &&
               mapii.s-0.05>0 && mapii.t!=1.0 &&
               mapid.s!=1.0 && mapid.t!=1.0 &&
               mapsd.s!=1.0 && mapsd.t-0.05>0 &&
               mapsi.s-0.05>0 && mapsi.t-0.05>0) {
                mapii.s-=0.1; mapii.t+=0.1;
                mapid.s+=0.1; mapid.t+=0.1;
                mapsi.s-=0.1; mapsi.t-=0.1;
                mapsd.s+=0.1; mapsd.t-=0.1;
            }
            break;
        case 'X':
            if(mapsd.s!=1.0 && mapid.s!=1.0) {
                mapsd.s+=0.1; mapsi.s+=0.1;
                mapid.s+=0.1; mapii.s+=0.1;
            }
            break;
        case 'x':
            if(mapsi.s-0.05>0 && mapii.s-0.05>0) {
                mapsd.s-=0.1; mapsi.s-=0.1;
                mapid.s-=0.1; mapii.s-=0.1;
            }
            break;
        case 'Y':
            if(mapii.t!=1.0 && mapid.t!=1.0) {
                mapsd.t+=0.1; mapsi.t+=0.1;
                mapid.t+=0.1; mapii.t+=0.1;
            }
            break;
        case 'y':
            if(mapsi.t-0.05>0 && mapsd.t-0.05>0) {
                mapsd.t-=0.1; mapsi.t-=0.1;
                mapid.t-=0.1; mapii.t-=0.1;
            }
            break;
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

    // map inicial
    mapsd.s=1.0;
    mapsd.t=0.0;
    mapsi.s=0.0;
    mapsi.t=0.0;
    mapid.s=1.0;
    mapid.t=1.0;
    mapii.s=0.0;
    mapii.t=1.0;

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
    glutCreateWindow("Examen Feb. 2014 - Ejercicio 3");

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
