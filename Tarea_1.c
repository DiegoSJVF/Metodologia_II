 
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
    printf("\n");
    return factores_primos;
}

void metodo_1(unsigned long long n)
{

    struct fp *f_p, *aux;
    unsigned long long int factorial;
    unsigned long long int *cifrado, *multi;
    unsigned int i, j=0, k, r;
    FILE *file;

    cifrado = (unsigned long long int*) malloc(sizeof(unsigned long long int));
    if (cifrado == NULL) {
        printf("No se pudo asignar memoria.\n");
        return;
    }

	multi = (unsigned long long int*) malloc(sizeof(unsigned long long int));
    if (multi == NULL) {
        printf("No se pudo asignar memoria.\n");
        return;
    }

    file = fopen("combinatoria.txt", "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }


    f_p = fp_algoritmo(n);

    factorial *= n; // Actualiza el valor del factorial

    cifrado[0] = 0;

	while(f_p)
	{
		factorial = 1;

		while(f_p && factorial <= max_int){
			factorial *= pow2(f_p->primo, f_p->apariciones);
			aux = f_p;
			f_p = f_p->sig;
			free(aux);
		}

		if(cifrado[0] == 0)
		{

			j=0;
			while(factorial)
			{
				cifrado = (unsigned long long int*) realloc(cifrado, j+1 * sizeof(unsigned long long int));
				if (cifrado == NULL)
				{
					printf("No se pudo asignar memoria.\n");
					return;
				}
				cifrado[j] = factorial % max_int; // Cifra el factorial en base 2^32
				printf("cifrado: %llu", cifrado[1]);
				factorial /= max_int;
				j++;
			}
		}
		else {
			k=0;
			while(factorial)
			{
				multi = (unsigned long long int*) realloc(multi, k+1 * sizeof(unsigned long long int));
				if (multi == NULL)
				{
					printf("No se pudo asignar memoria.\n");
					return;
				}
				multi[j] = factorial % max_int; // Cifra el factorial en base 2^32
				factorial /= max_int;
				k++;
			}


			for(r = 0; r < k; r++)
			{

				if(((cifrado[r] + multi[r]) % max_int) > 0 )
				{
					if(r+1 < j-1)
						cifrado[r+1] = cifrado[r+1] + ((cifrado[r] + multi[r]) % max_int);
					else if(r+1 == j-1)
					{
						cifrado = (unsigned long long int*) realloc(cifrado, j * sizeof(unsigned long long int));
						if (cifrado == NULL)
						{
							printf("No se pudo asignar memoria.\n");
							return;
						}
						cifrado[r+1] = cifrado[r+1]+ ((cifrado[r] + multi[r]) % max_int);
						j++;
						printf("\ncifrado[0]: %llu", cifrado[0]);
						printf("\ncifrado[1]: %llu", cifrado[1]);
					}
					cifrado[r] = (cifrado[r] + multi[r])/max_int;
				}
				else
					cifrado[r] = cifrado[r] + multi[r];
			}
		}
	}

	for (i = 0; i < j; i++){
		if(i == 0)
			fprintf(file, "%llu! = %llu", n, cifrado[i]);
		else if(cifrado[i])
			fprintf(file, " + %llu * (2^32)^%u", cifrado[i], i);
	}
    fprintf(file, "\n");

    free(cifrado);
    fclose(file);

    return;
}

int main(int argc,char *argv[]) {

	unsigned long long int n;
	n = strtoull(argv[1], NULL, 10);

	printf("n: %llu", n);
	metodo_1(n);
}







