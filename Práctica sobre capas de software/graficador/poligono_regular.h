#ifndef POLI_REGULAR
#define POLI_REGULAR

#include "vgl.h"

typedef struct {
    GLuint      lados;
    GLfloat*    vertices;   // 2 vertices por cada lado
} PoliRegular;

typedef struct {
    GLfloat     x;
    GLfloat     y;
} Punto2D;

GLfloat*
obtener_vertices_poligono( GLint lados, Punto2D C, Punto2D P0 );
PoliRegular
crear_arco_poligno( Punto2D C, Punto2D P0, Punto2D P1 );
GLuint
obtener_cuadrante( Punto2D P );
GLfloat
obtener_angulo( Punto2D P );

#endif