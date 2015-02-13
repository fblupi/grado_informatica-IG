//**************************************************************************
// Práctica 3
//
// Francisco Javier Bolívar Lupiáñez
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "vertex.h"
#include <vector>
#include <windows.h>
//#include "coche.h"
#include "torilloV2.h"

using namespace std;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// constantes globales con los vertices y triangulos y flags
bool modelado = false;
bool subiendo = true;
bool avanzando = true;
int modo = 4;
int figura = 3;
float a;
Figura beethoven;
Figura peon;
//Coche coche;
TorilloV2 torillo;
GLfloat elevadora;
GLfloat desplazamiento;
GLfloat volante;

GLfloat vel_elevadora=5;
GLfloat vel_desplazamiento=5;
GLfloat vel_volante=5;

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
//**************************************************************************

void clear_window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//**************************************************************************

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
//**************************************************************************

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
//**************************************************************************

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
//**************************************************************************

void draw_objects()
{
    if(!modelado) {
        beethoven.model_ply("D://PLY//beethoven");
        peon.model_ply_vertices("D://PLY//rev//peon");
        peon.barrido_circular(24);
        modelado = true;
    }
    switch(figura) {
        case 1: beethoven.dibujar(modo); break;
        case 2: peon.dibujar(modo); break;
        case 3: torillo.dibujar(modo); break;
    }
}

//**************************************************************************
// Funcion que anima los objetos
//**************************************************************************

void idle() {
    // Obtenemos posiciones actuales
    elevadora = torillo.getElevadora();
    desplazamiento = torillo.getDesplazamiento();
    volante = torillo.getVolante();
    // Si llega a los topes, cambia el movimiento
    if(elevadora==130) {
        subiendo = false;
    } else if(elevadora==0) {
        subiendo = true;
    }
    // Si llega a los topes, cambia el movimiento
    if(desplazamiento>=300) {
        avanzando = false;
    } else if(desplazamiento<=-200) {
        avanzando = true;
    }
    // Actualizamos elevadora
    if(subiendo) {
        torillo.setElevadora(elevadora+=vel_elevadora);
    } else {
        torillo.setElevadora(elevadora-=vel_elevadora);
    }
    // Actualizamos desplazamiento
    if(avanzando) {
        torillo.setDesplazamiento(desplazamiento+=vel_desplazamiento);
    } else {
        torillo.setDesplazamiento(desplazamiento-=vel_desplazamiento);
    }
    // Actualizamos volante
    torillo.setVolante(volante+=vel_volante);

    glutPostRedisplay();
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
    switch (Tecla1) {
        // Quitar
        case 'Q': exit(0); break;
        case 'q': exit(0); break;
        // Modo de dibujo
        case 'p': modo = 1; break;
        case 'l': modo = 2; break;
        case 's': modo = 3; break;
        case 'a': modo = 4; break;
        // Modelo de dibujo
        case '1': figura = 1; break;
        case '2': figura = 2; break;
        case '3': figura = 3; break;
        // Acciones
        case 'Z':
            elevadora = torillo.getElevadora();
            torillo.setElevadora(elevadora+=vel_elevadora);
            break;
        case 'z':
            elevadora = torillo.getElevadora();
            torillo.setElevadora(elevadora-=vel_elevadora);
            break;
        case 'X':
            desplazamiento = torillo.getDesplazamiento();
            torillo.setDesplazamiento(desplazamiento+=vel_desplazamiento);
            break;
        case 'x':
            desplazamiento = torillo.getDesplazamiento();
            torillo.setDesplazamiento(desplazamiento-=vel_desplazamiento);
            break;
        case 'C':
            volante = torillo.getVolante();
            torillo.setVolante(volante+=vel_volante);
            break;
        case 'c':
            volante = torillo.getVolante();
            torillo.setVolante(volante-=vel_volante);
            break;
        case 'B':
            vel_elevadora+=1;
            if(vel_elevadora>10) vel_elevadora=10;
            break;
        case 'b':
            vel_elevadora-=1;
            if(vel_elevadora<1) vel_elevadora=1;
            break;
        case 'N':
            vel_desplazamiento+=1;
            if(vel_desplazamiento>10) vel_desplazamiento=10;
            break;
        case 'n':
            vel_desplazamiento-=1;
            if(vel_desplazamiento<1) vel_desplazamiento=1;
            break;
        case 'M':
            vel_volante+=1;
            if(vel_volante>10) vel_volante=10;
            break;
        case 'm':
            vel_volante-=1;
            if(vel_volante<1) vel_volante=1;
            break;
        case 'W':
            glutIdleFunc(idle);
            break;
        case 'w':
            glutIdleFunc(NULL);
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
    Front_plane=1;
    Back_plane=1000;

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
    glEnable(GL_LIGHTING);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Practica 3");

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
