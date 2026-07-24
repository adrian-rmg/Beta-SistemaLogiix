/**
 * ============================================================================
 * PROYECTO LOGIIX - SISTEMA DE LOGÍSTICA Y DISTRIBUCIÓN
 * Archivo: src/main.cpp
 * Propósito: Punto de entrada principal e interfaz CLI integrada del sistema.
 * Integrantes: Adrián Márquez, Greicel Salas, Fernando Cedeño, Jesús Romero, Andrés Mata.
 * ============================================================================
 */

#include <iostream>
#include "Menus.h"
#include "TablaUsuarios.h"
#include "ColaPedidos.h"
#include "HistorialPaquete.h"
#include "CatalogoProductos.h"
#include "InventarioProductos.h"
#include "RutaDistribucion.h"

using namespace std;

// Menú Principal
int main() {
    // Instanciación de las estructuras principales
    TablaUsuarios tablaUsuarios;
    ColaPedidos colaPedidos;
    std::unordered_map<int, HistorialPaquete> mapaHistoriales;
    CatalogoProductos catalogo;
    InventarioProductos inventario;
    RutaDistribucion redRutas;

    int opcion = 0;

    do {
        mostrarEncabezado();
        cout << "SELECCIONE EL MÓDULO A GESTIONAR:\n\n";
        cout << "1. Módulo de Usuarios y Autenticación (Tabla Hash)\n";
        cout << "2. Módulo de Pedidos en Espera (Cola - FIFO)\n";
        cout << "3. Módulo de Rastreo de Envíos (Pila - LIFO)\n";
        cout << "4. Módulo de Catálogo e Inventario (Árboles AVL / 2-3)\n";
        cout << "5. Módulo de Red de Distribución (Grafo)\n";
        cout << "6. Salir del Sistema\n\n";
        cout << "Ingrese su opción (1-6): ";

        if (!(cin >> opcion)) {
            cout << "\n[!] Entrada inválida. Ingrese un número entre 1 y 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pausar();
            continue;
        }

        switch (opcion) {
            case 1:
                menuUsuarios(tablaUsuarios);
                break;
            case 2:
                menuPedidos(colaPedidos, tablaUsuarios, inventario, redRutas, mapaHistoriales);
                break;
            case 3:
                menuHistorial(mapaHistoriales);
                break;
            case 4:
                menuInventario(catalogo, inventario);
                break;
            case 5:
                menuRutas(redRutas);
                break;
            case 6:
                cout << "\n==========================================================\n";
                cout << " GRACIAS POR UTILIZAR EL SISTEMA DE LOGISTICA LOGIIX\n";
                cout << "==========================================================\n\n";
                break;
            default:
                cout << "\n[!] Opción fuera de rango (1-6).\n";
                pausar();
        }
    } while (opcion != 6);

    return 0;
}
