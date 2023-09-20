#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define max_value 9223372036854775807


int main() {
    uint64_t factorial = 1;
    uint64_t aux;
    uint64_t *cifrado;
    int i, j;
    FILE *file;

    cifrado = (uint64_t*) malloc(sizeof(uint64_t));
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
            if(0)
            cifrado = (uint64_t*) realloc(cifrado, i * sizeof(uint64_t));
            if (cifrado == NULL) {
                printf("No se pudo asignar memoria.\n");
                return 1;
            }
            cifrado[i - 1] = 0; // Inicializa el nuevo elemento a cero
            for (j = 0; j < i; j++) {
                cifrado[j] = aux % 4294967296; // Cifra el factorial en base 2^32
                aux /= 4294967296;
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
