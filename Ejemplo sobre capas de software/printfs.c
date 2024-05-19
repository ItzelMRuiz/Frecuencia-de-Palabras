/**
 * printfs.c
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

int __mingw_vprintf(const char *, __builtin_va_list);

static __cdecl __attribute__((__nothrow__))
int printf(const char *__format, ...) {
  register int __retval;
  __builtin_va_list __local_argv; __builtin_va_start(__local_argv, __format);
  __retval = __mingw_vprintf(__format, __local_argv);
  __builtin_va_end(__local_argv);
  return __retval;
}

int main(int argc, char* argv[]) {
  printf("%s %X %X %X %X %X %X %X %X %X %X\n", "10 numeros primos: ", 1, 2, 3, 5, 7, 11, 13, 17, 19, 23);
  return 0;
}