/**
 * poligono_regular.c
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * 
 * 17/05/2024
 * 
 * Sistemas Operativos
 * 
 * Verción 1
*/

#include <stdlib.h>
#include <math.h>

#include "poligono_regular.h"

GLfloat pi = 3.1415927f;

//----------------------------------------------------------------------------
//
//  obtener_vertices_poligono
//
//  Proposito:  Crear los vertices para un un poligono regular centrado en C,
//              donde el primer vertice es P0
//

GLfloat*
obtener_vertices_poligono( GLint lados, Punto2D C, Punto2D P0 )
{
    GLuint      vertices_n = 2 * lados;
    GLfloat*    vertices = (GLfloat*)malloc( sizeof(GLfloat) * (2 * vertices_n) );

    GLfloat     h = C.x;
    GLfloat     k = C.y;
    GLfloat     x1;
    GLfloat     y1;
    GLfloat     x0;
    GLfloat     y0;
    GLfloat     cos_theta = cosf(2 * pi / lados);
    GLfloat     sin_theta = sinf(2 * pi / lados);

    x1 = P0.x - h;
    y1 = P0.y - k;

    int i = 0;
    while( i < 2 * vertices_n ) {
        vertices[i] = x1 + h;
        vertices[i + 1] = y1 + k;
        i += 2;

        x0 = x1;
        y0 = y1;

        x1 = x0 * cos_theta + y0 * sin_theta;
        y1 = y0 * cos_theta - x0 * sin_theta;

        vertices[i] = x1 + h;
        vertices[i + 1] = y1 + k;
        i += 2;
    }

    return vertices;
}

//----------------------------------------------------------------------------
//
//  crear_arco_poligno
//
//  Proposito:  Crear los vertices para un segmento de un poligono regular
//              donde el segmento es menor o igual al segmento completo
//

PoliRegular
crear_arco_poligno( Punto2D C, Punto2D P0, Punto2D P1 )
{
    GLuint      n_circulo = 64;

    GLfloat     x = sqrtf( ((P0.x - C.x) * (P0.x - C.x) + (P0.y - C.y) * (P0.y - C.y)) / ((P1.x - C.x) * (P1.x - C.x) + (P1.y - C.y) * (P1.y - C.y)) ) * (P1.x - C.x) + C.x;
    GLfloat     y = sqrtf( ((P0.x - C.x) * (P0.x - C.x) + (P0.y - C.y) * (P0.y - C.y)) / ((P1.x - C.x) * (P1.x - C.x) + (P1.y - C.y) * (P1.y - C.y)) ) * (P1.y - C.y) + C.y;
    Punto2D     P = {x, y};

    Punto2D     P0_t = {P0.x - C.x, P0.y - C.y};    // Transformado
    Punto2D     P_t = {P.x - C.x, P.y - C.y};       // Transformado

    GLfloat     theta0 = obtener_angulo( P0_t );
    GLfloat     theta1 = obtener_angulo( P_t );
    GLint       n = (GLint)n_circulo * (theta0 - theta1) / (2 * pi);

    if( n < 0 ) {
        n = n_circulo + n;
    }

    PoliRegular arco_poligono;
    arco_poligono.vertices = obtener_vertices_poligono( n_circulo, C, P0 );
    arco_poligono.lados = (GLuint)n;

    return arco_poligono;
}

//----------------------------------------------------------------------------
//
//  obtener_cuadrante
//
//  Proposito:  Determina en que cuadrante esta un punto, el punto (0, 0) se
//              considera que esta en el cuadrante 1
//

GLuint
obtener_cuadrante( Punto2D P )
{
    GLuint cuadrante;
    if( P.x >= 0 && P.y >= 0 ) {
        cuadrante = 1;
    }
    else if( P.x < 0 && P.y >= 0 ) {
        cuadrante = 2;
    }
    else if( P.x < 0 && P.y < 0 ) {
        cuadrante = 3;
    }
    else if( P.x >= 0 && P.y < 0 ) {
        cuadrante = 4;
    }

    return cuadrante;
}

//----------------------------------------------------------------------------
//
//  obtener_angulo
//
//  Proposito:  Determina el angulo en radianes que hace el punto respecto al
//              eje x
//  Rango:      [-2 pi, 2 pi]
//

GLfloat
obtener_angulo( Punto2D P )
{
    GLfloat theta;
    GLfloat r = sqrtf(P.x * P.x + P.y * P.y);

    if( P.y >= 0 ) {
        theta = acosf( P.x / r );
    }
    else {
        theta = 2 * pi - acosf( P.x / r );
    }

    return theta;
}