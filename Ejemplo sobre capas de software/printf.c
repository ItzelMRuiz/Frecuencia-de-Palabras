/**
 * printf.c
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

#define __MINGW_NOTHROW __attribute__((__nothrow__))
#define __mingw_stdio_redirect__ static __cdecl __MINGW_NOTHROW

int __mingw_vprintf(const char *, __builtin_va_list);

int main(int argc, char* argv[]);
__mingw_stdio_redirect__
int atoi(char* s);

__mingw_stdio_redirect__
int printf(const char *__format, ...) {
  register int __retval;
  __builtin_va_list __local_argv; __builtin_va_start(__local_argv, __format);
  __retval = __mingw_vprintf(__format, __local_argv);
  __builtin_va_end(__local_argv);
  return __retval;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Error: No hay suficientes argumentos\n");
    return 1;
  }

  const int n = atoi(*(argv + 1));
  if (argc - 2 != n) {
    printf("Error: No hay suficientes argumentos\n");
    return 1;
  }
  int a[n];

  for (int i = 0; i < n; ++i) {
    a[i] = atoi(*(argv + 2 + i));
  }
  for (int i = 0; i < n; ++i) {
    printf("%X", a[i]);
    if (i + 1 < n) {
      printf(" ");
    }
  }

  return 0;
}

int atoi(char* s) {
  int numero = 0;

  int i = 0;
  while (s[i]) {
    numero *= 10;
    numero += s[i] - 48;
    ++i;
  }

  return numero;
}
