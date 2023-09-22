#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define max_value 9223372036854775807


int main() {
    unsigned long long int factorial = 1;
    unsigned long long int aux;
    unsigned long long int *cifrado;
    int i, j=0;
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

    for (i = 1; ; i++) {
        if ((factorial * i) > 4294967295) { // Si el factorial va a superar 2^32

            while(aux) {
                j=0;
                cifrado = (unsigned long long int*) realloc(cifrado, i * sizeof(unsigned long long int));
                if (cifrado == NULL) {
                    printf("No se pudo asignar memoria.\n");
                    return 1;
                }
                cifrado[j] = aux % 4294967296; // Cifra el factorial en base 2^32
                aux /= 4294967296;
                j++;
            }
            for (j = 0; j < i; j++){
                if(j == 0)
                    fprintf(file, "%d! = %llu", i, cifrado[j]);
                else if(cifrado[j])
                    fprintf(file, " + %llu", cifrado[j]);
            }
            fprintf(file, "\n");
            factorial *= i; // Actualiza el valor del factorial
            aux = factorial;
        }
        else {
            factorial *= i;
            fprintf(file, "%d! = %llu\n", i, factorial);
        }

        if (factorial > max_value) { // Si el factorial va a superar 2^63
            printf("El número más grande cuyo factorial es menor o igual a 2^63 - 1 es: %d\n", i - 1);
            break;
        }
    }

    free(cifrado);
    fclose(file);

    return 0;
}












