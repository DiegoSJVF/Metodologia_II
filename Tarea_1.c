
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void factorizacion(struct fp **primera, struct fp **segunda)
{
    struct fp *temp1 = *primera;
    struct fp *temp2 = *segunda;
    struct fp *prev1 = NULL, *prev2 = NULL;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->primo < temp2->primo)
        {
            prev1 = temp1;
            temp1 = temp1->sig;
        }
        else if (temp1->primo > temp2->primo)
        {
            temp2 = temp2->sig;
        }
        else
        {
            if (temp1->apariciones > temp2->apariciones)
            {
                temp1->apariciones -= temp2->apariciones;
                temp2 = temp2->sig;
            }
            else if (temp1->apariciones < temp2->apariciones)
            {
                if (prev1 == NULL)
                {
                    *primera = temp1->sig;
                    free(temp1);
                    temp1 = *primera;
                }
                else
                {
                    prev1->sig = temp1->sig;
                    free(temp1);
                    temp1 = prev1->sig;
                }
                temp2->apariciones -= temp1->apariciones;
            }
            else
            {
                if (prev1 == NULL)
                {
                    *primera = temp1->sig;
                    free(temp1);
                    temp1 = *primera;
                }
                else
                {
                    prev1->sig = temp1->sig;
                    free(temp1);
                    temp1 = prev1->sig;
                }
                struct fp *temp3 = temp2;
                if (temp3 == *segunda)
                {
                    *segunda = (*segunda)->sig;
                    free(temp3);
                    temp2 = *segunda;
                }
                else
                {
                    prev2->sig = temp3->sig;
                    free(temp3);
                    temp2 = prev2->sig;
                }
            }
        }
    }
}


void metodo_1(unsigned int n, unsigned int k)
{

    struct fp *n_p, *k_p, *n_k_p, *aux;
    unsigned long long int rn = 1, rk = 1, rnk = 1, result;

    n_p = fp_algoritmo(n);
    k_p = fp_algoritmo(k);
    n_k_p = fp_algoritmo(n-k);

    //factorizacion(&n_p, &k_p);
    //factorizacion(&n_p, &n_k_p);

    while(n_p)
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

    result = rn /(rk*rnk);

    printf("resultado (%u %u): %llu\n", n, k, result);

    return;
}

void metodo_2(unsigned int n, unsigned int k)
{

}



void metodo_3(unsigned int n, unsigned int k)
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
}

int main(int argc,char *argv[]) {

    unsigned int n, k;
    double tiempo;
    if(argc == 4)
    {
        if(strcmp(argv[1], "-1") == 0)
        {
            n = strtoull(argv[2], NULL, 10);
            k = strtoull(argv[3], NULL, 10);

            clock_t inicio = clock(); // start time
            metodo_1(n, k);
            clock_t fin = clock(); // end time
            tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC; // calculate execution time

            printf("Tiempo tomado en metodo 1: %f\n", tiempo);
        }
        else if (strcmp(argv[1], "-2") == 0)
        {
            n = strtoull(argv[2], NULL, 10);
            k = strtoull(argv[3], NULL, 10);

            clock_t inicio = clock(); // start time
            metodo_2(n, k);
            clock_t fin = clock(); // end time
            tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC; // calculate execution time
            printf("Tiempo tomado en metodo 2: %f\n", tiempo);

        }
        else if (strcmp(argv[1], "-3") == 0)
        {
            n = strtoull(argv[2], NULL, 10);
            k = strtoull(argv[3], NULL, 10);
            clock_t inicio = clock(); // start time
            metodo_3(n, k);
            clock_t fin = clock(); // end time
            tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC; // calculate execution time
            printf("Tiempo tomado en metodo 3: %f\n", tiempo);



        }
    }

}







