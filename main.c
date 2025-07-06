#include <stdio.h>
#include "microempresa.h"

int main() {
    Transaccion transacciones[MAX_TRANSACCIONES];
    Producto inventario[MAX_PRODUCTOS];
    int totalTransacciones = 0;
    int totalProductos = 0;
    int opcion;

    do {
        printf("\n--- SIMULADOR ECONOMICO DE MICROEMPRESAS ---\n");
        printf("1. Registrar transaccion\n");
        printf("2. Consultar flujo de caja\n");
        printf("3. Mostrar balance general\n");
        printf("4. Gestionar inventario\n");
        printf("5. Salir\n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: 
                registrarTransaccion(transacciones, &totalTransacciones);
                break;
            case 2:
                consultarFlujoCaja(transacciones, totalTransacciones);
                break;
            case 3:
                mostrarBalance(transacciones, totalTransacciones);
                break;
            case 4:
                gestionarInventario(inventario, &totalProductos);
                break;
            case 5:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida!\n");
        }
    } while(opcion != 5);

    return 0;
}