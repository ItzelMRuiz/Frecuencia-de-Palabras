"""
Para renderizar:

manim -pqh graficador2.py CodeFromString2


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

class CodeFromString2(Scene):
    def construct(self):
        code = '''
int __mingw_vprintf(const char *, __builtin_va_list);

static __cdecl __attribute__((__nothrow__))
int printf(const char *__format, ...) {
  register int __retval;
  __builtin_va_list __local_argv;
  __builtin_va_start(__local_argv, __format);
  __retval = __mingw_vprintf(__format, __local_argv);
  __builtin_va_end(__local_argv);
  return __retval;
}
'''
        rendered_code = Code(code=code, tab_width=4, background="window",
                            language="C", font="Monospace")
        self.play(Write(rendered_code), run_time=5)
        self.wait(2)