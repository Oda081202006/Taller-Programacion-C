#include <stdio.h> 
#include <arreglo.h>

int main(){
    int arreglo[TAM_MAX]; 
    int n;

    printf("Cauntos elementos desea agrefar: "); 
    sanf("%d", &n);
    if(n<=0 || n>50){
        printf("Fuera del rango!\n");
        return 1;
    }else{
        leerArreglo(arreglo,n);
        leerArreglo(arreglo,n)
    }
}