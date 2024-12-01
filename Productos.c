#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 50

typedef struct {
    char nombre[MAX_NOMBRE];
    int tiempoFabricacion;
    int recursosRequeridos;
    int demanda;
} Producto;

Producto *productos[MAX_PRODUCTOS];
int totalProductos = 0;

void agregarProducto();
void editarProducto();
void eliminarProducto();
void calcularProduccion();
void listarProductos();
int buscarProducto(const char *nombre);

int main() {
    int opcion;

    printf("Optimización de Producción en Fábrica\n");
    
    do {
        printf("\nMenú de Opciones:\n");
        printf("1. Agregar Producto\n");
        printf("2. Editar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Calcular Producción\n");
        printf("5. Listar Productos\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                calcularProduccion();
                break;
            case 5:
                listarProductos();
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 6);

    for (int i = 0; i < totalProductos; i++) {
        free(productos[i]);
    }

    return 0;
}

void agregarProducto() {
    if (totalProductos >= MAX_PRODUCTOS) {
        printf("Error: No se pueden agregar más productos.\n");
        return;
    }

    productos[totalProductos] = (Producto *)malloc(sizeof(Producto));
    if (productos[totalProductos] == NULL) {
        printf("Error de memoria.\n");
        return;
    }

    printf("Ingrese el nombre del producto: ");
    scanf("%s", productos[totalProductos]->nombre);

    printf("Ingrese el tiempo de fabricación del producto: ");
    scanf("%d", &productos[totalProductos]->tiempoFabricacion);

    printf("Ingrese los recursos necesarios para el producto: ");
    scanf("%d", &productos[totalProductos]->recursosRequeridos);

    printf("Ingrese la cantidad demandada del producto: ");
    scanf("%d", &productos[totalProductos]->demanda);

    totalProductos++;
    printf("Producto agregado exitosamente.\n");
}

void editarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombre);

    int indice = buscarProducto(nombre);
    if (indice == -1) {
        printf("Error: Producto no encontrado.\n");
        return;
    }

    printf("Producto encontrado. Ingrese los nuevos valores.\n");
    printf("Nuevo tiempo de fabricación: ");
    scanf("%d", &productos[indice]->tiempoFabricacion);

    printf("Nuevos recursos necesarios: ");
    scanf("%d", &productos[indice]->recursosRequeridos);

    printf("Nueva cantidad demandada: ");
    scanf("%d", &productos[indice]->demanda);

    printf("Producto editado exitosamente.\n");
}

void eliminarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);

    int indice = buscarProducto(nombre);
    if (indice == -1) {
        printf("Error: Producto no encontrado.\n");
        return;
    }

    free(productos[indice]);
    for (int i = indice; i < totalProductos - 1; i++) {
        productos[i] = productos[i + 1];
    }
    totalProductos--;
    printf("Producto eliminado exitosamente.\n");
}

void calcularProduccion() {
    int tiempoTotal = 0, recursosTotales = 0;
    int tiempoDisponible, recursosDisponibles;

    printf("Ingrese el tiempo máximo de producción disponible (en minutos): ");
    scanf("%d", &tiempoDisponible);

    printf("Ingrese la cantidad máxima de recursos disponibles: ");
    scanf("%d", &recursosDisponibles);

    for (int i = 0; i < totalProductos; i++) {
        tiempoTotal += productos[i]->tiempoFabricacion * productos[i]->demanda;
        recursosTotales += productos[i]->recursosRequeridos * productos[i]->demanda;
    }

    printf("\nCálculo de Producción:\n");
    printf("Tiempo total requerido: %d minutos\n", tiempoTotal);
    printf("Recursos totales requeridos: %d\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("La fábrica puede cumplir con la demanda.\n");
    } else {
        printf("La fábrica NO puede cumplir con la demanda.\n");
    }
}

void listarProductos() {
    printf("\nLista de Productos:\n");
    for (int i = 0; i < totalProductos; i++) {
        printf("Producto %d:\n", i + 1);
        printf("  Nombre: %s\n", productos[i]->nombre);
        printf("  Tiempo de fabricación: %d\n", productos[i]->tiempoFabricacion);
        printf("  Recursos necesarios: %d\n", productos[i]->recursosRequeridos);
        printf("  Cantidad demandada: %d\n", productos[i]->demanda);
    }
}

int buscarProducto(const char *nombre) {
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productos[i]->nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}