/**
 * figuras.c
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

#include <stdio.h>
#include <stdlib.h>

#include "vgl.h"
#include "LoadShaders.h"

#include "poligono_regular.h"

int main(int argc, char** argv);
void Graficar(void);
void Init(void);
void Display(void);

enum VAO_IDs {Circulo, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers = 1};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLuint NumVertices;
GLuint LineaPorFrame;

//----------------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv) {
  if (argc > 1) {
    NumVertices = 2 * atoi(*(argv + 1));
    LineaPorFrame = atoi(*(argv + 2));

    if (NumVertices < 3) {
      NumVertices = 2 * 3;
    }
    if (LineaPorFrame <= 0) {
      LineaPorFrame = 100;
    }
  }
  else {
    NumVertices = 2 * 3;
    LineaPorFrame = 100;
  }

  Graficar();

  return 0;
}

//-----------------------------------------------------------------------------
//
// graficar
//

void Graficar(void) {
  glfwInit();

  GLFWwindow* window = glfwCreateWindow(600, 600, "Figuras", NULL, NULL);

  glfwMakeContextCurrent(window);
  glewInit();

  Init();

  while (!glfwWindowShouldClose(window)) {
    Display();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
}

//-----------------------------------------------------------------------------
//
// init
//

void Init(void) {
  ShaderInfo  shaders[] = {
      {GL_VERTEX_SHADER, "figuras.vert"},
      {GL_FRAGMENT_SHADER, "figuras.frag"},
      {GL_NONE, NULL}};

  GLuint program = LoadShaders(shaders);
  glUseProgram(program);

  GLfloat* vertices_poligono;
  Punto2D P0;
  Punto2D C;

  glGenVertexArrays(NumVAOs, VAOs);
  glCreateBuffers(NumBuffers, Buffers);

  //
  //  Circulo
  //

  P0.x = 0.0f;    P0.y = 0.6f;
  C.x = 0.0f;     C.y = 0.0f;
  vertices_poligono = obtener_vertices_poligono(NumVertices / 2, C, P0);

  glBindVertexArray(VAOs[Circulo]);
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
  glBufferStorage(GL_ARRAY_BUFFER, 2 * NumVertices * sizeof(GLfloat),
                  vertices_poligono, 0);

  glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(vPosition);

  free(vertices_poligono);
}

//-----------------------------------------------------------------------------
//
// display
//

void Display(void) {
  static const float bcolor[] = {0.13f, 0.13f, 0.13f, 1.0f};
  static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
  static const float white[] = {1.0f, 1.0f, 1.0f, 1.0f};

  static GLuint frames = 0;
  static GLuint actual = 2;
  static GLboolean animado = GL_TRUE;

  glClearBufferfv(GL_COLOR, 0, bcolor);

  if (frames++ >= LineaPorFrame && animado) {
    actual += 2;
    frames = 0;

    if (actual > NumVertices) {
      animado = GL_FALSE;
    }
  }
  
  glBindVertexArray(VAOs[Circulo]);
  glDrawArrays(GL_LINES, 0, actual);
}