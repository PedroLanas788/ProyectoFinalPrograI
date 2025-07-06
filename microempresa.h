#ifndef MICROEMPRESA_H
#define MICROEMPRESA_H

#define MAX_TRANSACCIONES 100
#define MAX_PRODUCTOS 50

typedef enum {
    VENTA,
    COMPRA,
    GASTO
} TipoTransaccion;

typedef struct {
    char nombre[50];
    float precio;
    int cantidad;
} Producto;

typedef struct {
    char descripcion[100];
    float monto;
    TipoTransaccion tipo;
    int dia;
    int mes;
    int anio;
} Transaccion;

void registrarTransaccion(Transaccion transacciones[], int *total);
void consultarFlujoCaja(Transaccion transacciones[], int total);
void mostrarBalance(Transaccion transacciones[], int total);
void gestionarInventario(Producto inventario[], int *totalProductos);
const char* obtenerNombreTipo(TipoTransaccion tipo);

#endif