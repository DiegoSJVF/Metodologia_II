#include <stdio.h>
#include <stdlib.h>

struct fp
{
    unsigned long long int primo;
    unsigned int apariciones;
    struct fp *sig;
};

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

void imprimir_lista(struct fp *top)
{
    struct fp *actual = top;

    while (actual != NULL)
    {
        printf("Primo: %llu\n", actual->primo);
        printf("Apariciones: %llu\n\n", actual->apariciones);

        struct fp *temporal = actual;
        actual = actual->sig;
        free(temporal);
    }
}

int main()
{
    unsigned long long int numero;

    printf("Ingresa el número: ");
    scanf("%llu", &numero);

    struct fp *factores_primos;

    for (unsigned long long int i = 1; i <= numero; i++)
    {
        factores_primos = factorizacion_primos(i);

    }
    printf("\n");
    imprimir_lista(factores_primos);


    return 0;
}

