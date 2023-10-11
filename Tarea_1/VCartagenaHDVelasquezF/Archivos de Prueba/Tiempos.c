/*
 * Integrantes: Valentina Cartagena Henriquez - Diego Velasquez Figueroa
 *
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define max_value 9223372036854775807
//#define max_int 4294967296

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


struct fp *factorizacion_primos(unsigned long long int numero)  //O(n^2)
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

struct fp *fp_algoritmo(unsigned long long int numero)  //O(n^3)
{
    struct fp *factores_primos;

    for (unsigned long long int i = 1; i <= numero; i++)
    {
        factores_primos = factorizacion_primos(i);
    }
    return factores_primos;
}


void factorizacion(struct fp **primera, struct fp **segunda)
{
    struct fp *temp1 = *primera;
    struct fp *temp2 = *segunda;
    struct fp *prev1 = NULL, *prev2 = NULL;
    struct fp *aux;


    prev1 = temp1;
    prev2 = temp2;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->primo < temp2->primo)
        {
            prev1 = temp1;
            temp1 = temp1->sig;
        }
        else if (temp1->primo > temp2->primo)
        {
            prev2 = temp2;
            temp2 = temp2->sig;
        }
        else
        {
            if (temp1->apariciones > temp2->apariciones)
            {
                temp1->apariciones -= temp2->apariciones;
                temp2->apariciones = 0;
                prev2->sig = temp2->sig;
                aux = temp2;
                temp2 = temp2->sig;
            }
            else if (temp1->apariciones < temp2->apariciones)
            {
                temp2->apariciones -= temp1->apariciones;
                temp1->apariciones = 0;
                prev1->sig = temp1->sig;
                aux = temp1;
                temp1 = temp1->sig;
            }
            else
            {
                prev2->sig = temp2->sig;
                aux = temp2;
                temp2 = prev2->sig;

                prev1->sig = temp1->sig;
                aux = temp1;
                temp1 = prev1->sig;
            }
        }
    }
}


void metodo_1(unsigned int n, unsigned int k) //O(n^3)
{
    struct fp *n_p, *k_p, *n_k_p, *aux;
    unsigned long long int rn = 1, rk = 1, rnk = 1, resultado;


    n_p = fp_algoritmo(n);
    k_p = fp_algoritmo(k);
    n_k_p = fp_algoritmo(n-k);

    factorizacion(&n_p, &k_p);
    factorizacion(&n_p, &n_k_p);

    while(n_p)  //3n
    {
        rn *= pow2(n_p->primo, n_p->apariciones);
        aux = n_p;
        n_p = n_p->sig;
        free(aux);
    }

    while(k_p)
    {
        rk *= pow2(k_p->primo, k_p->apariciones);
        aux = k_p;
        k_p = k_p->sig;
        free(aux);
    }

    while(n_k_p)
    {
        rnk *= pow2(n_k_p->primo, n_k_p->apariciones);
        aux = n_k_p;
        n_k_p = n_k_p->sig;
        free(aux);
    }

    resultado = rn /(rk*rnk);

   // printf("resultado (%u %u): %llu\n", n, k, resultado);

    return;
}

int min(int a, int b) {
    if(a < b)
        return a;
    else
        return b;
}

void metodo_2(unsigned int n, unsigned int k) //O(n^2)
{
    unsigned long long int resultado[n+1][k+1];
    unsigned int i, j;

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i)
                resultado[i][j] = 1;
            else
                resultado[i][j] = resultado[i-1][j-1] + resultado[i-1][j];
        }
    }

    //printf("resultado (%u %u): %llu\n", n, k, resultado[n][k]);
    return;
}

void metodo_3(unsigned int n, unsigned int k) //O(n)
{
    unsigned long long int resultado = 1;
    unsigned int i;

    if (k > n - k) {
        k = n - k;
    }

    for (i = 0; i < k; i++) {
        resultado *= (n - i);
        resultado /= (i + 1);
    }
    //printf("resultado (%u %u): %llu\n", n, k, resultado);

}

int main(int argc,char *argv[]) {

    unsigned int n, k;  //
    float tiempo;

    if(argc == 4)
    {
		if(strcmp(argv[2], argv[3]) >= 0)
		{
            if(strcmp(argv[1], "-1") == 0)
            {
                if(strcmp(argv[3], "0") == 0)
                {
                    //printf("resultado (%u %u): 1", n, k);
	                printf("%f\n", tiempo);
                    return 1;
                }
                else if(strcmp(argv[2], argv[3]) == 0)
                {
                    //printf("resultado (%u %u): 1", n, k);
	                printf("%f\n", tiempo);

                    return 1;
                }
                n = strtoull(argv[2], NULL, 10);
                k = strtoull(argv[3], NULL, 10);

                clock_t inicio = clock();
                metodo_1(n, k);
                clock_t fin = clock();
                tiempo = ((float)(fin - inicio)) / CLOCKS_PER_SEC;

                printf("%f\n", tiempo);
            }
            else if (strcmp(argv[1], "-2") == 0)
            {
                if(strcmp(argv[3], "0") == 0)
                {
                    //printf("resultado (%u %u): 2", n, k);
	                printf("%f\n", tiempo);
                    return 1;
                }
                else if(strcmp(argv[2], argv[3]) == 0)
                {
                    //printf("resultado (%u %u): 2", n, k);
	                printf("%f\n", tiempo);
                    return 1;
                }
                n = strtoull(argv[2], NULL, 10);
                k = strtoull(argv[3], NULL, 10);

                clock_t inicio = clock();
                metodo_2(n, k);
                clock_t fin = clock();
                tiempo = ((float)(fin - inicio)) / CLOCKS_PER_SEC;
                printf("%f\n", tiempo);
            }
            else if (strcmp(argv[1], "-3") == 0)
            {
                if(strcmp(argv[3], "0") == 0)
                {
                    //printf("resultado (%u %u): 3", n, k);
	                printf("%f\n", tiempo);
					return 1;
                }
                else if(strcmp(argv[2], argv[3]) == 0)
                {
                    //printf("resultado (%u %u): 3", n, k);
	                printf("%f\n", tiempo);
					return 1;
                }
                n = strtoull(argv[2], NULL, 10);
                k = strtoull(argv[3], NULL, 10);
                clock_t inicio = clock();
                metodo_3(n, k);
                clock_t fin = clock();
                tiempo = ((float)(fin - inicio)) / CLOCKS_PER_SEC;
                printf("%f\n", tiempo);
            }
        }
    }
}
