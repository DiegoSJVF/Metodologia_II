#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define max_value 9223372036854775807
#define max_int 4294967295

struct fp
{
    unsigned long long int primo;
    unsigned long long int apariciones;
    struct fp *sig;
};


int main() {
    unsigned long long int factorial = 1;
    unsigned long long int aux;
    unsigned long long int *cifrado;
    int i, j=0, k;
    FILE *file;

    cifrado = (unsigned long long int*) malloc(sizeof(unsigned long long int));
    if (cifrado == NULL) {
        printf("No se pudo asignar memoria.\n");
        return 1;
    }

    file = fopen("factoriales.txt", "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    for (i = 1; factorial*i < max_value ; i++) {

        factorial *= i; // Actualiza el valor del factorial

        //f_p
        aux = factorial;
        j=0;
        while(aux) {
            cifrado = (unsigned long long int*) realloc(cifrado, j+1 * sizeof(unsigned long long int));
            if (cifrado == NULL) {
                printf("No se pudo asignar memoria.\n");
                return 1;
            }
            cifrado[j] = aux % max_int; // Cifra el factorial en base 2^32
            aux /= max_int;
            j++;
        }
        for (k = 0; k < j; k++){
            if(k == 0)
                fprintf(file, "%d! = %llu", i, cifrado[k]);
            else if(cifrado[k])
                fprintf(file, " + %llu", cifrado[k]);
        }
        fprintf(file, "\n");
    }

    free(cifrado);
    fclose(file);

    return 0;
}












