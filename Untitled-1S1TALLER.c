/* 
  Programa: Gestión de Inventario (producto único)
  Autores: Nicoll Cedeño y Giuliana Cobos
  Curso: ISWZ1529 – Programación 1 (UDLA)
  Fecha: [01/09/2025]
  Descripción: Registro, venta con descuento, reabastecimiento, consulta y ganancias.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estructura para guardar la información del producto
struct Producto {
    int id;
    char nombre[50];
    int stock;
    float precio_unitario;
    float ganancias_totales;
};

// Prototipos de funciones
void inicializarProducto(struct Producto *producto);
void mostrarMenu(void);
void venderProducto(struct Producto *producto);
void reabastecerProducto(struct Producto *producto);
void mostrarInfoProducto(const struct Producto *producto);
int  validarEnteroPositivo(int valor);
float validarFlotantePositivo(float valor);
void limpiarBufferEntrada(void);

int main(void) {
    struct Producto producto;
    int opcion;

    // Registro inicial del producto
    inicializarProducto(&producto);

    // Menú principal
    do {
        mostrarMenu();
        printf("Ingresa una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Debe ser un numero entero.\n");
            limpiarBufferEntrada();
            opcion = 0; // fuerza repetir
            continue;
        }
        limpiarBufferEntrada();

        switch (opcion) {
            case 1:
                venderProducto(&producto);
                break;
            case 2:
                reabastecerProducto(&producto);
                break;
            case 3:
                mostrarInfoProducto(&producto);
                break;
            case 4:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("¡Opcion invalida! Intenta nuevamente.\n");
        }
        printf("\n");
    } while (opcion != 4);

    return 0;
}

void inicializarProducto(struct Producto *producto) {
    printf("=== Registro del Producto ===\n");

    printf("Ingresa el ID del producto: ");
    while (scanf("%d", &producto->id) != 1) {
        printf("Error: ingresa un entero positivo: ");
        limpiarBufferEntrada();
    }
    producto->id = validarEnteroPositivo(producto->id);
    limpiarBufferEntrada();

    printf("Ingresa el nombre del producto: ");
    if (!fgets(producto->nombre, sizeof(producto->nombre), stdin)) {
        printf("Error al leer el nombre. Intenta nuevamente.\n");
        producto->nombre[0] = '\0';
    }
    // Quitar salto de línea
    producto->nombre[strcspn(producto->nombre, "\n")] = 0;
    while (producto->nombre[0] == '\0') {
        printf("El nombre no puede estar vacio. Ingresa el nombre: ");
        if (!fgets(producto->nombre, sizeof(producto->nombre), stdin)) {
            printf("Error al leer el nombre.\n");
            continue;
        }
        producto->nombre[strcspn(producto->nombre, "\n")] = 0;
    }

    printf("Ingresa la cantidad inicial en stock: ");
    while (scanf("%d", &producto->stock) != 1) {
        printf("Error: ingresa un entero positivo: ");
        limpiarBufferEntrada();
    }
    producto->stock = validarEnteroPositivo(producto->stock);

    printf("Ingresa el precio unitario: ");
    while (scanf("%f", &producto->precio_unitario) != 1) {
        printf("Error: ingresa un numero positivo: ");
        limpiarBufferEntrada();
    }
    producto->precio_unitario = validarFlotantePositivo(producto->precio_unitario);

    producto->ganancias_totales = 0.0f;

    printf("¡Producto registrado con exito!\n");
    limpiarBufferEntrada();
}

void mostrarMenu(void) {
    printf("\n=== Sistema de Gestion de Inventario ===\n");
    printf("\t1. Vender producto\n");
    printf("\t2. Reabastecer producto\n");
    printf("\t3. Mostrar información del producto\n");
    printf("\t4. Salir\n");
}

void venderProducto(struct Producto *producto) {
    int cantidad;
    float descuento;

    printf("\n=== Vender Producto ===\n");
    printf("Stock actual: %d unidades\n", producto->stock);

    if (producto->stock <= 0) {
        printf("No hay stock disponible para vender.\n");
        return;
    }

    printf("Ingresa la cantidad a vender: ");
    while (scanf("%d", &cantidad) != 1) {
        printf("Error: ingresa un entero positivo: ");
        limpiarBufferEntrada();
    }
    cantidad = validarEnteroPositivo(cantidad);

    if (cantidad > producto->stock) {
        printf("Error: stock insuficiente. Disponible: %d unidades.\n", producto->stock);
        return;
    }

    printf("Ingresa el porcentaje de descuento (0-100; usa 0 si no hay): ");
    while (scanf("%f", &descuento) != 1) {
        printf("Error: ingresa un numero (0 a 100): ");
        limpiarBufferEntrada();
    }
    limpiarBufferEntrada();

    if (descuento < 0.0f) descuento = 0.0f;
    if (descuento > 100.0f) descuento = 100.0f;

    float precio_aplicado = producto->precio_unitario * (1.0f - descuento / 100.0f);
    float total_venta = precio_aplicado * (float)cantidad;

    // Actualizar estado
    producto->stock -= cantidad;
    producto->ganancias_totales += total_venta;

    // Resumen
    printf("\nResumen de la venta:\n");
    printf("\tUnidades vendidas: %d\n", cantidad);
    printf("\tPrecio unitario base: $%.2f\n", producto->precio_unitario);
    printf("\tDescuento aplicado: %.2f%%\n", descuento);
    printf("\tPrecio unitario aplicado: $%.2f\n", precio_aplicado);
    printf("\tTotal de la venta: $%.2f\n", total_venta);
    printf("\tStock restante: %d unidades\n", producto->stock);
}

void reabastecerProducto(struct Producto *producto) {
    int cantidad;

    printf("\n=== Reabastecer Producto ===\n");
    printf("Stock actual: %d unidades\n", producto->stock);

    printf("Ingresa la cantidad a agregar: ");
    while (scanf("%d", &cantidad) != 1) {
        printf("Error: ingresa un entero positivo: ");
        limpiarBufferEntrada();
    }
    cantidad = validarEnteroPositivo(cantidad);

    producto->stock += cantidad;

    printf("¡Stock actualizado con exito!\n");
    printf("Nuevo stock: %d unidades\n", producto->stock);
    limpiarBufferEntrada();
}

void mostrarInfoProducto(const struct Producto *producto) {
    printf("\n=== Informacion del Producto ===\n");
    printf("\tID: %d\n", producto->id);
    printf("\tNombre: %s\n", producto->nombre);
    printf("\tStock: %d unidades\n", producto->stock);
    printf("\tPrecio unitario: $%.2f\n", producto->precio_unitario);
    printf("\tGanancias totales: $%.2f\n", producto->ganancias_totales);
}

int validarEnteroPositivo(int valor) {
    while (valor <= 0) {
        printf("Error: ingresa un entero positivo: ");
        if (scanf("%d", &valor) != 1) {
            printf("Entrada invalida. ");
            limpiarBufferEntrada();
            continue;
        }
    }
    limpiarBufferEntrada();
    return valor;
}

float validarFlotantePositivo(float valor) {
    while (valor <= 0.0f) {
        printf("Error: ingresa un numero positivo: ");
        if (scanf("%f", &valor) != 1) {
            printf("Entrada invalida. ");
            limpiarBufferEntrada();
            continue;
        }
    }
    limpiarBufferEntrada();
    return valor;
}

void limpiarBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descartar */ }
}