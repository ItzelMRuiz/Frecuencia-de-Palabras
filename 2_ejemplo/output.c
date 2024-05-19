/**
 * output.c
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

struct _iobuf
{
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
};
typedef struct _iobuf FILE;

FILE *__cdecl __acrt_iob_func(unsigned index);

int __cdecl _flsbuf(int _Ch, FILE *_File);

int main()
{
    FILE *_stream = __acrt_iob_func(1);
    _flsbuf('7', _stream);
    return 0;
}