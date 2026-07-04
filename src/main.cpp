#include <iostream>
#include "ColaPedidos.h"
#include "HistorialPaquete.h"
#include "ListaProductos.h"
#include "CatalogoProductos.h"

using namespace std;

int main() {
    cout << "==========================================================" << endl;
    cout << "        Bienvenido al Sistema de Logistica Logiix" << endl;
    cout << "==========================================================" << endl;

    // ====================================================
    // PRUEBA DE LA COLA (Módulo de Pedidos - FIFO)
    // ====================================================
    cout << "\n>>> [FASE 1] Registro y Control de Pedidos Entrantes <<<" << endl;
    ColaPedidos sistemaPedidos;

    cout << "Registrando pedidos en el sistema..." << endl;
    sistemaPedidos.enqueue(101, "Maturin, Monagas");
    sistemaPedidos.enqueue(102, "Caracas, DC");
    sistemaPedidos.enqueue(103, "Lecheria, Anzoategui");

    sistemaPedidos.mostrarCola();

    cout << "\nProcesando el primer pedido de la fila..." << endl;
    Pedido* proximo = sistemaPedidos.obtenerFrente();
    if (proximo != nullptr) {
        cout << "Atendiendo ID: " << proximo->idPedido << " con destino a " << proximo->destino << endl;
    }
    sistemaPedidos.dequeue();

    cout << "\nEstado de la cola tras procesar el primer elemento:" << endl;
    sistemaPedidos.mostrarCola();


    // ====================================================
    // PRUEBA DE LA PILA (Módulo de Envíos - LIFO)
    // ====================================================
    cout << "\n>>> [FASE 2] Rastreo de Historial de Estados (Paquete ID: 101) <<<" << endl;
    HistorialPaquete rastreoPaquete;

    cout << "Cambiando estados del paquete logistico..." << endl;
    rastreoPaquete.push("En Almacen Central (Maturin)");
    rastreoPaquete.push("Empaquetado y Clasificado");
    rastreoPaquete.push("En Ruta de Entrega Terrestre");

    cout << "Estado Actual: " << rastreoPaquete.obtenerEstadoActual() << "\n" << endl;
    rastreoPaquete.mostrarHistorial();

    cout << "\n[Accion Especial] Error en ruta detectado: Se requiere deshacer ultimo estado." << endl;
    rastreoPaquete.pop();

    cout << "\nNuevo Estado Actual: " << rastreoPaquete.obtenerEstadoActual() << "\n" << endl;
    rastreoPaquete.mostrarHistorial();


    // ====================================================
    // PRUEBA DE LA LISTA ENLAZADA (Sprint 3 - Inventario / Carrito)
    // ====================================================
    cout << "\n>>> [FASE 3] Desglose de Productos del Paquete (Lista Doble) <<<" << endl;
    ListaProductos carritoPaquete;

    cout << "Insertando productos al paquete..." << endl;
    carritoPaquete.insertarFinal(5001, "Laptop ASUS ZenBook", 1250.00);
    carritoPaquete.insertarFinal(5002, "Mouse Inalambrico Logitech", 45.50);
    carritoPaquete.insertarFinal(5003, "Teclado Mecanico RGB", 89.99);

    // Operación: Recorrido (Hacia adelante e Inverso)
    carritoPaquete.mostrarListaHaciaAdelante();
    cout << endl;
    carritoPaquete.mostrarListaHaciaAtras();

    // Operación: Búsqueda
    cout << "\nBuscando el producto con ID 5002..." << endl;
    Producto* encontrado = carritoPaquete.buscarPorID(5002);
    if (encontrado != nullptr) {
        cout << "[Encontrado] -> " << encontrado->nombre << " | Precio: $" << encontrado->precio << endl;
    } else {
        cout << "[Error] El producto no existe.\n";
    }

    // Operación: Eliminación
    cout << "\nEliminando el producto ID 5002 (Mouse) del paquete..." << endl;
    carritoPaquete.eliminarPorID(5002);

    cout << "\nEstado final del desglose de productos del paquete:" << endl;
    carritoPaquete.mostrarListaHaciaAdelante();

    cout << "==========================================================" << endl;
    cout << "   Sprint 3 finalizado: Listas Doblemente Enlazadas (OK)" << endl;
    cout << "==========================================================" << endl;

    // ====================================================
    // PRUEBA DEL ÁRBOL AVL (Sprint 4 - Catálogo General O(log n))
    // ====================================================
    cout << "\n>>> [FASE 4] Catálogo General de Inventario Optimizado (Árbol AVL) <<<" << endl;
    CatalogoProductos inventarioGeneral;

    cout << "Poblando el catálogo maestro con operaciones eficientes en O(log n)..." << endl;
    // Insertamos en un orden que forzaría desbalances en un árbol normal para validar las rotaciones
    inventarioGeneral.insertarProducto(300, "Servidor Rack Dell", 2500.00);
    inventarioGeneral.insertarProducto(200, "Switch Cisco 24 Puertos", 450.00);
    inventarioGeneral.insertarProducto(400, "Access Point Wi-Fi 6", 180.00);
    inventarioGeneral.insertarProducto(100, "Cable Utp Categoria 6 (305m)", 90.00); // Provoca rotación leve
    inventarioGeneral.insertarProducto(250, "Gabinete de Pared 9RU", 115.00);

    cout << "\nCatálogo General Autodepurado y Ordenado Automáticamente (In-order):" << endl;
    inventarioGeneral.mostrarCatalogo();

    // Operación Especial: Edge Case - Intento de Duplicado (Actualización)
    cout << "\n[Acción Especial] Detectado reajuste de precio para el ID 250 (Gabinete)..." << endl;
    inventarioGeneral.insertarProducto(250, "Gabinete de Pared 9RU (Premium)", 135.00);

    // Operación: Búsqueda de alta velocidad
    cout << "\nVerificando datos actualizados mediante búsqueda indexada:" << endl;
    NodoProducto* prodAVL = inventarioGeneral.buscar(250);
    if (prodAVL != nullptr) {
        cout << "[Consulta AVL Exitosa] -> " << prodAVL->nombre << " | Nuevo Precio: $" << prodAVL->precio << endl;
    }

    // Operación: Baja de Producto con Balanceo Estricto
    cout << "\nDando de baja del catálogo maestro el ID 300 por obsolescencia..." << endl;
    if (inventarioGeneral.darDeBaja(300)) {
        cout << "Producto removido. Estructura balanceada reajustada instantáneamente." << endl;
    }

    cout << "\nEstado final del Catálogo General de Logiix:" << endl;
    inventarioGeneral.mostrarCatalogo();

    cout << "==========================================================" << endl;
    cout << "    Sprint 4 finalizado: Árboles AVL Estructurados (OK)" << endl;
    cout << "==========================================================" << endl;
    return 0;
}
