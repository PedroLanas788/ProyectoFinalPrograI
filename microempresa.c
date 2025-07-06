#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "microempresa.h"

const char* obtenerNombreTipo(TipoTransaccion tipo) {
    switch(tipo) {
        case VENTA: return "Venta";
        case COMPRA: return "Compra";
        case GASTO: return "Gasto";
        default: return "Desconocido";
    }
}

void registrarTransaccion(Transaccion transacciones[], int *total) {
    if (*total >= MAX_TRANSACCIONES) {
        printf("Error: Se ha alcanzado el maximo de transacciones (%d)\n", MAX_TRANSACCIONES);
        return;
    }

    printf("\nNueva Transaccion #%d\n", *total + 1);
    
    printf("Descripcion: ");
    scanf(" %[^\n]", transacciones[*total].descripcion);
    
    printf("Monto: ");
    scanf("%f", &transacciones[*total].monto);
    
    printf("Tipo (0-Venta, 1-Compra, 2-Gasto): ");
    scanf("%d", (int*)&transacciones[*total].tipo);
    
    printf("Fecha (dd mm aaaa): ");
    scanf("%d %d %d", &transacciones[*total].dia, 
                      &transacciones[*total].mes, 
                      &transacciones[*total].anio);
    
    (*total)++;
    printf("\nTransaccion registrada exitosamente!\n");
}

void consultarFlujoCaja(Transaccion transacciones[], int total) {
    if (total == 0) {
        printf("\nNo hay transacciones registradas.\n");
        return;
    }

    int mes, anio;
    printf("\nIngrese mes y año a consultar (mm aaaa): ");
    scanf("%d %d", &mes, &anio);

    printf("\n--- TRANSACCIONES DEL %d/%d ---\n", mes, anio);
    printf("%-10s %-50s %-10s %-15s\n", "Fecha", "Descripcion", "Monto", "Tipo");
    
    float totalVentas = 0, totalCompras = 0, totalGastos = 0;
    
    for (int i = 0; i < total; i++) {
        if (transacciones[i].mes == mes && transacciones[i].anio == anio) {
            printf("%02d/%02d/%04d %-50s %-10.2f %-15s\n", 
                  transacciones[i].dia,
                  transacciones[i].mes,
                  transacciones[i].anio,
                  transacciones[i].descripcion,
                  transacciones[i].monto,
                  obtenerNombreTipo(transacciones[i].tipo));
            
            switch(transacciones[i].tipo) {
                case VENTA: totalVentas += transacciones[i].monto; break;
                case COMPRA: totalCompras += transacciones[i].monto; break;
                case GASTO: totalGastos += transacciones[i].monto; break;
            }
        }
    }
    
    printf("\n--- RESUMEN ---\n");
    printf("Total Ventas: %.2f\n", totalVentas);
    printf("Total Compras: %.2f\n", totalCompras);
    printf("Total Gastos: %.2f\n", totalGastos);
    printf("Flujo Neto: %.2f\n", totalVentas - totalCompras - totalGastos);
}

void mostrarBalance(Transaccion transacciones[], int total) {
    if (total == 0) {
        printf("\nNo hay transacciones registradas.\n");
        return;
    }

    float ventas = 0, compras = 0, gastos = 0;
    
    for (int i = 0; i < total; i++) {
        switch(transacciones[i].tipo) {
            case VENTA: ventas += transacciones[i].monto; break;
            case COMPRA: compras += transacciones[i].monto; break;
            case GASTO: gastos += transacciones[i].monto; break;
        }
    }
    
    printf("\n--- BALANCE GENERAL ---\n");
    printf("Total Ingresos (Ventas): %.2f\n", ventas);
    printf("Total Egresos (Compras + Gastos): %.2f\n", compras + gastos);
    printf("Balance Neto: %.2f\n", ventas - compras - gastos);
    printf("Margen Bruto: %.2f\n", ventas - compras);
}

void gestionarInventario(Producto inventario[], int *totalProductos) {
    int opcion;
    do {
        printf("\n--- GESTION DE INVENTARIO ---\n");
        printf("1. Agregar producto\n");
        printf("2. Listar productos\n");
        printf("3. Volver al menu principal\n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: {
                if (*totalProductos >= MAX_PRODUCTOS) {
                    printf("Error: Inventario lleno (maximo %d productos)\n", MAX_PRODUCTOS);
                    break;
                }
                
                printf("\nNuevo Producto #%d\n", *totalProductos + 1);
                printf("Nombre: ");
                scanf(" %[^\n]", inventario[*totalProductos].nombre);
                printf("Precio: ");
                scanf("%f", &inventario[*totalProductos].precio);
                printf("Cantidad: ");
                scanf("%d", &inventario[*totalProductos].cantidad);
                
                (*totalProductos)++;
                printf("Producto agregado exitosamente!\n");
                break;
            }
            case 2: {
                if (*totalProductos == 0) {
                    printf("\nNo hay productos en el inventario.\n");
                    break;
                }
                
                printf("\n--- INVENTARIO ---\n");
                printf("%-30s %-10s %-10s %-10s\n", "Producto", "Precio", "Cantidad", "Valor Total");
                
                float valorTotalInventario = 0;
                for (int i = 0; i < *totalProductos; i++) {
                    float valorProducto = inventario[i].precio * inventario[i].cantidad;
                    printf("%-30s %-10.2f %-10d %-10.2f\n", 
                          inventario[i].nombre,
                          inventario[i].precio,
                          inventario[i].cantidad,
                          valorProducto);
                    valorTotalInventario += valorProducto;
                }
                
                printf("\nValor total del inventario: %.2f\n", valorTotalInventario);
                break;
            }
            case 3:
                printf("Volviendo al menu principal...\n");
                break;
            default:
                printf("Opcion invalida!\n");
        }
    } while(opcion != 3);
}