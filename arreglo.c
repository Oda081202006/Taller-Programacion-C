#include <stdio.h> 
#include <arreglo.h>

void leerArreglo(int arreglo [TAM_MAX], int numero )

{
    printf("Ingrese los %d numemros enteros \n",numero); 
    for(int i=0; i<numero; i++){
        printf("Elemento %d: ",i+1);
        scanf("%d", &arreglo[i]);
    }

}

void leerArreglo(int arreglo [TAM_MAX], int numero )

{
    printf("\nImprimir todo el arreglo\n");
    for(int i=0; i<numero;i++){
        printf("%d\t", arreglo[i]);
    }
}