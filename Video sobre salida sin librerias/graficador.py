"""
Para renderizar:

manim -pqh graficador.py CodeFromString


________________________________________________________________________________
Márquez Ruíz Itzel Monserrat
Pérez Velázquez Leonardo Daniel

Sistemas Operativos
Escuela Superior de Cómputo del
Instituto Politécnico Nacional

                            ____________________________________________________
                            Sobre procedimientos de biblioteca
                            
                Profesor Salas Ramirez Israel

                  _______________________________________
                  Ciudad de México, a 17 de mayo de 2024
"""

from manim import *

class CodeFromString(Scene):
    def construct(self):
        code = '''
int printf(const char *__format, ...);

int main(int argc, char* argv[]) {
  printf("¡Hola Mundo!");
  return 0;
}
'''
        rendered_code = Code(code=code, tab_width=4, background="window",
                            language="C", font="Monospace")
        self.play(Write(rendered_code), run_time=5)
        self.wait(2)