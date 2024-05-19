/*
    Márquez Ruíz Itzel Monserrat
    Pérez Velázquez Leonardo Daniel
    16/Mayo/2024
    Versión 1.0
    Frecuencia de Palabras
*/
//--------------------------------------------------LIBRERIAS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
//--------------------------------------------------ESTRUCTURAS
typedef struct informacion {
    wchar_t *palabra;
    int frecuencia;
}informacion;
//--------------------------------------------------FUNCIONES DE USUARIO
int qsortcmp(const void *frecuenciaA, const void *frecuenciaB);
//--------------------------------------------------FUNCION PRINCIPAL
int main(void) {
//--------------------------------------------------
    const wchar_t nombreArchivoEntrada[] = L"archivo_entrada.txt", nombreArchivoSalida[] = L"contador_palabras.txt";
    FILE *apuntadorArchivo = NULL;
    wchar_t caracterPalabra = L'\0', *palabraIdentificada = NULL;
    size_t contadorCaracteres = 0, contadorPalabras = 0;
    informacion *registro = NULL;
    int indicador = 0;
//--------------------------------------------------
    setlocale(LC_ALL, "");
    system("cls");
//--------------------------------------------------
    apuntadorArchivo = _wfopen(nombreArchivoEntrada, L"r, ccs=UTF-8");
    if(apuntadorArchivo == NULL) {
        wprintf(L"\n ERROR: Archivo \"%ls\" no abierto.\n ", nombreArchivoEntrada);
        system("pause");
        system("cls");
        return 1;
    }

    while((caracterPalabra = fgetwc(apuntadorArchivo)) != WEOF) {

        if(iswalpha(caracterPalabra)) {
            palabraIdentificada = (wchar_t *)realloc(palabraIdentificada, ((contadorCaracteres + 2) * sizeof(wchar_t)));
            if(palabraIdentificada == NULL) {
                wprintf(L"\n ERROR: Abstracción de información incompleta.\n ");
                system("pause");
                system("cls");
                fclose(apuntadorArchivo);
                free(palabraIdentificada);
                return 1;
            }
            palabraIdentificada[contadorCaracteres] = towlower(caracterPalabra);
            palabraIdentificada[contadorCaracteres + 1] = L'\0';
            contadorCaracteres++;
        }else {
            
            if(contadorCaracteres > 0) {
                
                for(indicador = 0; indicador < contadorPalabras; indicador++) {
                    if(wcscmp(registro[indicador].palabra, palabraIdentificada) == 0) {
                        registro[indicador].frecuencia++;
                        break;
                    }
                }

                if(indicador == contadorPalabras) {
                    registro = (informacion *)realloc(registro, ((contadorPalabras + 1) * sizeof(informacion)));
                    if(registro == NULL) {
                        wprintf(L"\n ERROR: Memoria de registro no asignada.\n ");
                        system("pause");
                        system("cls");
                        fclose(apuntadorArchivo);
                        free(palabraIdentificada);
                        for(indicador = 0; indicador < contadorPalabras; indicador++) {
                            free(registro[indicador].palabra);
                        }
                        free(registro);
                        return 1;
                    }
                    registro[contadorPalabras].palabra = wcsdup(palabraIdentificada);
                    registro[contadorPalabras].frecuencia = 1;
                    contadorPalabras++;
                }
                
            }

            free(palabraIdentificada);
            palabraIdentificada = NULL;
            contadorCaracteres = 0;
            
        }

    }
    
    fclose(apuntadorArchivo);
    caracterPalabra = L'0';
//--------------------------------------------------
    if(palabraIdentificada != NULL) {
        
        if(contadorCaracteres > 0) {
            
            for(indicador = 0; indicador < contadorPalabras; indicador++) {
                if(wcscmp(registro[indicador].palabra, palabraIdentificada) == 0) {
                    registro[indicador].frecuencia++;
                    break;
                }
            }

            if(indicador == contadorPalabras) {
                registro = (informacion *)realloc(registro, ((contadorPalabras + 1) * sizeof(informacion)));
                if(registro == NULL) {
                    wprintf(L"\n ERROR: Memoria de registro no asignada.\n ");
                    system("pause");
                    system("cls");
                    fclose(apuntadorArchivo);
                    free(palabraIdentificada);
                    for(indicador = 0; indicador < contadorPalabras; indicador++) {
                        free(registro[indicador].palabra);
                    }
                    free(registro);
                    return 1;
                }
                registro[contadorPalabras].palabra = wcsdup(palabraIdentificada);
                registro[contadorPalabras].frecuencia = 1;
                contadorPalabras++;
            }
            
        }

        free(palabraIdentificada);
        palabraIdentificada = NULL;
        contadorCaracteres = 0;
        
    }
//--------------------------------------------------
    apuntadorArchivo = _wfopen(nombreArchivoSalida, L"w, ccs=UTF-8");
    if(apuntadorArchivo == NULL) {
        wprintf(L"\n ERROR: Archivo \"%ls\" no generado.\n ", nombreArchivoSalida);
        system("pause");
        system("cls");
        for(indicador = 0; indicador < contadorPalabras; indicador++) {
            free(registro[indicador].palabra);
        }
        free(registro);
        return 1;
    }

    qsort(registro, contadorPalabras, sizeof(*registro), qsortcmp);

    for(indicador = 0; indicador < contadorPalabras; indicador ++) {
        fwprintf(apuntadorArchivo, L"%d\t\t%ls\n", registro[indicador].frecuencia, registro[indicador].palabra);
    }

    fclose(apuntadorArchivo);
    contadorPalabras = 0;
    for(indicador = 0; indicador < contadorPalabras; indicador++) {
        free(registro[indicador].palabra);
    }
    free(registro);
//--------------------------------------------------
    wprintf(L"\n Funciones realizadas exitosamente.\n ");
    system("pause");
    system("cls");
//--------------------------------------------------
    return 0;
//--------------------------------------------------
}
//--------------------------------------------------FUNCIONES DE USUARIO IMPLEMENTADAS
int qsortcmp(const void *frecuenciaA, const void *frecuenciaB) {
    informacion *apuntadorA = (informacion *)frecuenciaA;
    informacion *apuntadorB = (informacion *)frecuenciaB;
    if(apuntadorA->frecuencia < apuntadorB->frecuencia) {
        return 1;
    }
    if(apuntadorA->frecuencia > apuntadorB->frecuencia) {
        return -1;
    }
    return wcscmp(apuntadorB->palabra, apuntadorA->palabra);
}