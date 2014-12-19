//**************************************************************************
// Práctica 4
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
#include "luz.h"
#include "lata.h"
#include "torillo.h"
#include "cubo.h"

using namespace std;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// constantes globales y flags
int modo = 6;
int figura = 1;
bool activo = false;
bool practica4 = true;
bool modelado = false;
bool subiendo = true;
bool avanzando = true;
Figura *peon_madera;
Figura *peon_negro;
Figura *peon_blanco;
Lata *lata;
Cubo *cubo;
Torillo * torillo;
Figura *peon;
Figura *beethoven;
Luz luz0;
Luz luz1;
Luz luz2;
GLfloat alfa = 0;
GLfloat beta = 0;
GLfloat angulo = 0;
GLfloat elevadora;
GLfloat desplazamiento;
GLfloat volante;
GLfloat vel_elevadora = 5;
GLfloat vel_desplazamiento = 5;
GLfloat vel_volante = 5;

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
    if(practica4) { // MODO PRACTICA 4
        switch(figura) {
            case 1:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                lata->dibujar(modo);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(0.5,0.28,0.5);
                glScalef(0.2,0.2,0.2);
                peon_madera->dibujar(modo);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(0.5,0.28,-0.5);
                glScalef(0.2,0.2,0.2);
                peon_negro->dibujar(modo);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(0.5,0.28,0);
                glScalef(0.2,0.2,0.2);
                peon_blanco->dibujar(modo);
                glPopMatrix();
                break;
            case 2:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.005,0.005,0.005);
                torillo->dibujar(modo);
                glPopMatrix();
                break;
            case 3:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glTranslatef(0,0.25,0);
                glScalef(0.5,0.5,0.5);
                cubo->dibujar(modo);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(0.5,0.28,0.5);
                glScalef(0.2,0.2,0.2);
                peon_madera->dibujar(modo);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(0.5,0.28,-0.5);
                glScalef(0.2,0.2,0.2);
                peon_negro->dibujar(modo);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(0.5,0.28,0);
                glScalef(0.2,0.2,0.2);
                peon_blanco->dibujar(modo);
                glPopMatrix();
                break;
        }
    } else { // MODO PRACTICA 3
        switch(figura) {
            case 1:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.2,0.2,0.2);
                beethoven->dibujar(modo);
                glPopMatrix();
                break;
            case 2:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.5,0.5,0.5);
                peon->dibujar(modo);
                glPopMatrix();
                break;
            case 3:
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glScalef(0.005,0.005,0.005);
                torillo->dibujar(modo);
                glPopMatrix();
                break;
        }
    }
}

//**************************************************************************
// Funcion que anima los objetos
//**************************************************************************

void idle()
{
    if(!practica4) { // MODO PRACTICA 3
        if(activo) {
            // Obtenemos posiciones actuales
            elevadora = torillo->getElevadora();
            desplazamiento = torillo->getDesplazamiento();
            volante = torillo->getVolante();
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
                torillo->setElevadora(elevadora+=vel_elevadora);
            } else {
                torillo->setElevadora(elevadora-=vel_elevadora);
            }
            // Actualizamos desplazamiento
            if(avanzando) {
                torillo->setDesplazamiento(desplazamiento+=vel_desplazamiento);
            } else {
                torillo->setDesplazamiento(desplazamiento-=vel_desplazamiento);
            }
            // Actualizamos volante
            torillo->setVolante(volante+=vel_volante);
        }
    } else {
        if(activo) {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            angulo += 1;
            luz2.setPosicion(_vertex3f(-sin(angulo*M_PI/180),cos(angulo*M_PI/180),0));
            luz2.activar();
            glPopMatrix();
        } else {
            glDisable(GL_LIGHT2);
        }
    }

    glutPostRedisplay();
}

//**************************************************************************
// Luces
//**************************************************************************

void draw_lights(void)
{

    luz0.activar();
    luz1.activar();
}

//**************************************************************************
// Escena
//**************************************************************************

void draw_scene(void)
{
    clear_window();
    change_observer();
    draw_axis();
    draw_objects();
    if(practica4) { // MODO PRACTICA 4
        draw_lights();
    }
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
// Imprimir ayuda
//***************************************************************************

void imprimir_ayuda() {
    if(practica4) { // MODO PRACTICA 4
        cout << endl << endl << "********************************************************************" << endl;
        cout << "AYUDA ESCENA PRACTICA 4" << endl;
        cout << "********************************************************************" << endl << endl;
        cout << "Q: quitar" << endl;
        cout << "P: modo puntos" << endl;
        cout << "L: modo aristas" << endl;
        cout << "S: modo suavizado plano" << endl;
        cout << "G: modo suavizado gouraud" << endl;
        cout << "1: escena lata y peones" << endl;
        cout << "2: escena torillo" << endl;
        cout << "3: escena cubo" << endl;
        cout << "A: aumenta valor de beta" << endl;
        cout << "Z: disminuye valor de beta" << endl;
        cout << "X: aumenta valor de alfa" << endl;
        cout << "C: disminuye valor de alfa" << endl;
        cout << "W: activar animacion" << endl;
        cout << "E: desactivar animacion" << endl;
        cout << "4: descativar escena practica 4" << endl;
        cout << "H: imprimir ayuda" << endl;
    } else { // MODO PRACTICA 3
        cout << endl << endl << "********************************************************************" << endl;
        cout << "AYUDA ESCENA PRACTICA 3" << endl;
        cout << "********************************************************************" << endl << endl;
        cout << "Q: quitar" << endl;
        cout << "P: modo puntos" << endl;
        cout << "L: modo aristas" << endl;
        cout << "S: modo solido" << endl;
        cout << "A: modo ajedrez" << endl;
        cout << "1: cargar ply: beethoven" << endl;
        cout << "2: cargar ply por revolucion: peon" << endl;
        cout << "3: cargar modelo jerarquico: torillo" << endl;
        cout << "Z: subir elevadora" << endl;
        cout << "z: bajar elevadora" << endl;
        cout << "X: avanzar" << endl;
        cout << "x: retroceder" << endl;
        cout << "C: girar volante a la izquierda" << endl;
        cout << "c: girar volante a la derecha" << endl;
        cout << "B: aumentar velocidad elevadora" << endl;
        cout << "b: disminuir velocidad elevadora" << endl;
        cout << "N: aumentar velocidad desplazamiento" << endl;
        cout << "n: disminuir velocidad desplazamiento" << endl;
        cout << "M: aumentar velocidad volante" << endl;
        cout << "m: disminuir velocidad volante" << endl;
        cout << "W: activar animacion" << endl;
        cout << "E: desactivar animacion" << endl;
        cout << "4: acticar escena practica 4" << endl;
        cout << "H: imprimir ayuda" << endl;
    }
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
    if(practica4) { // MODO PRACTICA 4
        switch (toupper(Tecla1)) {
            // Quitar
            case 'Q':
                exit(0);
                break;
            // Modo de dibujo
            case 'P':
                modo = 1;
                break;
            case 'L':
                modo = 2;
                break;
            case 'S':
                modo = 5;
                break;
            case 'G':
                modo = 6;
                break;
            // Modelo de dibujo
            case '1':
                figura = 1;
                break;
            case '2':
                figura = 2;
                break;
            case '3':
                figura = 3;
                break;
            // Cambiar angulos luz direccional
            case 'A':
                beta += 5;
                if(beta<0) beta+=360;
                if(beta>360) beta-=360;
                break;
            case 'Z':
                beta -= 5;
                if(beta<0) beta+=360;
                if(beta>360) beta-=360;
                break;
            case 'X':
                alfa += 5;
                if(alfa<0) alfa+=360;
                if(alfa>360) alfa-=360;
                break;
            case 'C':
                alfa -= 5;
                if(alfa<0) alfa+=360;
                if(alfa>360) alfa-=360;
                break;
            case 'W':
                activo = true;
                break;
            case 'E':
                activo = false;
                break;
            // Cambiar de escena
            case '4':
                practica4=false;
                modo=4; figura=3;
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
                glDisable(GL_LIGHT1);
                break;
            // Imprimir ayuda
            case 'H':
                imprimir_ayuda();
                break;
        }
    } else { // MODO PRACTICA 3
        switch (Tecla1) {
            // Quitar
            case 'Q':
                exit(0);
                break;
            case 'q':
                exit(0);
                break;
            // Modo de dibujo
            case 'p':
                modo = 1;
                break;
            case 'P':
                modo = 1;
                break;
            case 'l':
                modo = 2;
                break;
            case 'L':
                modo = 2;
                break;
            case 's':
                modo = 3;
                break;
            case 'S':
                modo = 3;
                break;
            case 'a':
                modo = 4;
                break;
            case 'A':
                modo = 4;
                break;
            // Modelo de dibujo
            case '1':
                figura = 1;
                break;
            case '2':
                figura = 2;
                break;
            case '3':
                figura = 3;
                break;
            // Acciones
            case 'Z':
                elevadora = torillo->getElevadora();
                torillo->setElevadora(elevadora+=vel_elevadora);
                break;
            case 'z':
                elevadora = torillo->getElevadora();
                torillo->setElevadora(elevadora-=vel_elevadora);
                break;
            case 'X':
                desplazamiento = torillo->getDesplazamiento();
                torillo->setDesplazamiento(desplazamiento+=vel_desplazamiento);
                break;
            case 'x':
                desplazamiento = torillo->getDesplazamiento();
                torillo->setDesplazamiento(desplazamiento-=vel_desplazamiento);
                break;
            case 'C':
                volante = torillo->getVolante();
                torillo->setVolante(volante+=vel_volante);
                break;
            case 'c':
                volante = torillo->getVolante();
                torillo->setVolante(volante-=vel_volante);
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
                activo = true;
                break;
            case 'E':
                activo = false;
                break;
            // Cambiar de escena
            case '4':
                practica4 = true;
                modo=6;
                figura=1;
                activo = false;
                glEnable(GL_LIGHT0);
                glEnable(GL_LIGHT1);
                break;
            // Imprimir ayuda
            case 'H':
                imprimir_ayuda();
                break;
            case 'h':
                imprimir_ayuda();
                break;
        }
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

    // se declaran las luces
    luz0.setID(GL_LIGHT0);
    luz0.setDireccional(false);
    luz0.setPosicion(_vertex3f(10,-10,-5));
    luz0.setAmbiental(_vertex4f(0.5,0.5,0.5,1));
    luz0.setDifuso(_vertex4f(0.8,0.8,0.8,1));
    luz0.setEspecular(_vertex4f(0.9,0.9,0.9,1));

    luz1.setID(GL_LIGHT1);
    luz1.setDireccional(true);
    luz1.setPosicion(_vertex3f(1,1,1));
    luz1.setDireccion(alfa,beta);
    luz1.setAmbiental(_vertex4f(0.3,0.3,0.3,1));
    luz1.setDifuso(_vertex4f(0.7,0.7,0.7,1));
    luz1.setEspecular(_vertex4f(1,1,1,1));

    luz2.setID(GL_LIGHT2);
    luz2.setDireccional(true);
    luz2.setPosicion(_vertex3f(0,0,0));
    luz2.setAmbiental(_vertex4f(0.3,0.1,0.1,1));
    luz2.setDifuso(_vertex4f(0.7,0.2,0.2,1));
    luz2.setEspecular(_vertex4f(1,0.2,0.2,1));

    // se modelan los objetos
    // practica 4
    cubo = new Cubo();

    unsigned int barrido = 48;
    peon_madera = new Figura();
    peon_madera->model_ply_vertices("D://PLY//rev//peon");
    peon_madera->setTextura("D://TEXTURES//text-madera.jpg",true);
    peon_madera->barrido_circular(barrido);
    peon_madera->calcular_normales_triangulos();
    peon_madera->calcular_normales_vertices();

    peon_negro = new Figura();
    peon_negro->model_ply_vertices("D://PLY//rev//peon");
    peon_negro->barrido_circular(barrido);
    peon_negro->calcular_normales_triangulos();
    peon_negro->calcular_normales_vertices();

    peon_blanco = new Figura();
    peon_blanco->model_ply_vertices("D://PLY//rev//peon");
    peon_blanco->barrido_circular(barrido);
    peon_blanco->calcular_normales_triangulos();
    peon_blanco->calcular_normales_vertices();

    // se definen los materiales
    peon_madera->setAmbiental(_vertex4f(0.3,0.3,0.3,1));
    peon_madera->setDifusa(_vertex4f(0.5,0.5,0.5,1));
    peon_madera->setEspecular(_vertex4f(1,1,1,1));
    peon_madera->setBrillo(80);

    peon_blanco->setAmbiental(_vertex4f(0.6,0.6,0.5,1));
    peon_blanco->setDifusa(_vertex4f(0.6,0.6,0.5,1)); // Super difuso
    peon_blanco->setEspecular(_vertex4f(0,0,0,1)); // No hay brillos especulares
    peon_blanco->setBrillo(10);

    peon_negro->setAmbiental(_vertex4f(0,0,0,1));
    peon_negro->setDifusa(_vertex4f(0.2,0.2,0.2,1)); // Apenas reflectividad difusa
    peon_negro->setEspecular(_vertex4f(0.6,0.6,0.6,1)); // Especular
    peon_negro->setBrillo(20);

    lata = new Lata();

    // practica 3
    torillo = new Torillo();
    peon = new Figura();
    peon->model_ply_vertices("D://PLY//rev//peon");
    peon->barrido_circular(barrido);
    peon->calcular_normales_triangulos();
    peon->calcular_normales_vertices();
    beethoven = new Figura();
    beethoven->model_ply("D://PLY//beethoven");
    beethoven->calcular_normales_triangulos();
    beethoven->calcular_normales_vertices();

    glutIdleFunc(idle);
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
    glutCreateWindow("Practica 4");

    // asignación de icono a la ventana
    HWND hWnd = FindWindow(NULL,TEXT("Practica 4"));
    HICON hIconS = (HICON)LoadImage(NULL,TEXT("D://ICONS//iconGreen.ico"),IMAGE_ICON,64,64,LR_LOADFROMFILE);
    HICON hIconB = (HICON)LoadImage(NULL,TEXT("D://ICONS//iconGreen.ico"),IMAGE_ICON,16,16,LR_LOADFROMFILE);
    SendMessage(hWnd,WM_SETICON,ICON_BIG,(LPARAM)hIconS);
    SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIconB);

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
