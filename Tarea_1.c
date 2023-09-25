
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define max_value 9223372036854775807
#define max_int 4294967296

struct fp
{
    unsigned long long int primo;
    unsigned int apariciones;
    struct fp *sig;
};

unsigned long long pow2(unsigned long long base, unsigned int exponent) {
    unsigned long long result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

struct fp *ingreso_lista(struct fp *top, unsigned long long int j)
{
    struct fp *q = NULL;


    if (!top || top->primo > j)
    {
        q = malloc(sizeof(struct fp));
        q->primo = j;
        q->apariciones = 1;
        q->sig = top;
        top = q;
    }
    else if (top->primo == j)
    {
        top->apariciones += 1;
    }
    else
    {
        struct fp *temporal = top;
        while (temporal->sig && temporal->sig->primo < j)
        {
            temporal = temporal->sig;
        }

        if (temporal->sig && temporal->sig->primo == j)
        {
            temporal->sig->apariciones += 1;
        }
        else
        {
            q = malloc(sizeof(struct fp));
            q->primo = j;
            q->apariciones = 1;
            q->sig = temporal->sig;
            temporal->sig = q;
        }
    }

    return top;
}


struct fp *factorizacion_primos(unsigned long long int numero)
{
    struct fp *top = NULL;
    unsigned long long int n;

    for (unsigned long long int i = 1; i <= numero; i++)
    {
        n = i;
        unsigned long long int j = 2;

        while (j * j <= n)
        {
            if (n % j == 0)
            {
                top = ingreso_lista(top, j);
                n /= j;
            }
            else
            {
                j += 1;
            }
        }
        if (n > 1)
            top = ingreso_lista(top, n);
    }

    return top;
}

/*void imprimir_lista(struct fp *top)
{
    struct fp *actual = top;

    while (actual != NULL)
    {
        printf("Primo: %llu\n", actual->primo);
        printf("Apariciones: %u\n\n", actual->apariciones);

        struct fp *temporal = actual;
        actual = actual->sig;
        free(temporal);
    }
}*/

struct fp *fp_algoritmo(unsigned long long int numero)
{
    struct fp *factores_primos;

    for (unsigned long long int i = 1; i <= numero; i++)
    {
        factores_primos = factorizacion_primos(i);
    }
    return factores_primos;
}

void metodo_1(unsigned long long n)
{

    struct fp *f_p, *aux;
    unsigned long long int factorial, resto;
    unsigned long long int *cifrado, *multi_1, *multi_2;
    unsigned int i, j=0, k=0, y, z;

    cifrado = (unsigned long long int*) malloc(sizeof(unsigned long long int));
    if (cifrado == NULL) {
        printf("No se pudo asignar memoria.\n");
        return;
    }

    multi_1 = (unsigned long long int*) malloc(sizeof(unsigned long long int));
    if (multi_1 == NULL) {
        printf("No se pudo asignar memoria.\n");
        return;
    }

    multi_2 = (unsigned long long int*) malloc(sizeof(unsigned long long int));
    if (multi_2 == NULL) {
        printf("No se pudo asignar memoria.\n");
        return;
    }




    f_p = fp_algoritmo(n);

    factorial *= n; // Actualiza el valor del factorial

    cifrado[0] = 0;
    multi_1[0] = 0;
    multi_2[0] = 0;

    while(f_p)
    {
        factorial = 1;

        while(f_p && factorial <= max_int){
            factorial *= pow2(f_p->primo, f_p->apariciones);
            aux = f_p;
            f_p = f_p->sig;
            free(aux);
        }
        if(multi_1[0] == 0)
        {
            j=0;
            while(factorial)
            {
                multi_1 = (unsigned long long int*) realloc(multi_1, j+1 * sizeof(unsigned long long int));
                if (multi_1 == NULL)
                {
                    printf("No se pudo asignar memoria.\n");
                    return;
                }
                multi_1[j] = factorial % max_int; // Cifra el factorial en base 2^32
                factorial /= max_int;
                j++;
            }
        }
        else
		{
			k=0;
			while(factorial)
			{
				multi_2 = (unsigned long long int*) realloc(multi_2, k+1 * sizeof(unsigned long long int));
				if (multi_2 == NULL)
				{
					printf("No se pudo asignar memoria.\n");
					return;
				}
				multi_2[k] = factorial % max_int; // Cifra el factorial en base 2^32
				factorial /= max_int;
				k++;
			}
			resto = 0;
			for(y = 0; y < j; y++)
			{
				for (z = 0; z < k ; z++)
				{
					cifrado = (unsigned long long int*) realloc(cifrado, j+k * sizeof(unsigned long long int));
					cifrado[z+y] += (((multi_1[y] * multi_2[z]) + resto) % max_int);
					resto = ((multi_1[y] * multi_2[z]) / max_int);
				}
			}
        }
    }

    if(multi_2[0] == 0)
		cifrado = multi_1;

    for (i = 0; i < j+k; i++){
        if(i == 0)
			{
				printf("\n%llu! = %llu", n, cifrado[i]);
			}
        else if(cifrado[i])
		{
			printf(" + %llu * (2^32)^%u", cifrado[i], i);
		}
    }

    free(cifrado);

    return;
}

int main(int argc,char *argv[]) {

    unsigned long long int n;
    n = strtoull(argv[1], NULL, 10);
    metodo_1(n);
}







