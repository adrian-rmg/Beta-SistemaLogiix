#include <iostream>
#include "ColaPedidos.h"
#include "HistorialPaquete.h"

using namespace std;

int main() {
    cout << "==========================================================" << endl;
    cout << "        Bienvenido al Sistema de Logistica Logiix" << endl;
    cout << "==========================================================" << endl;

    // ==========================================
    // PRUEBA DE LA COLA (Módulo de Pedidos - FIFO)
    // ==========================================
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
    sistemaPedidos.dequeue(); // Sale de la cola

    cout << "\nEstado de la cola tras procesar el primer elemento:" << endl;
    sistemaPedidos.mostrarCola();


    // ==========================================
    // PRUEBA DE LA PILA (Módulo de Envíos - LIFO)
    // ==========================================
    cout << "\n>>> [FASE 2] Rastreo de Historial de Estados (Paquete ID: 101) <<<" << endl;
    HistorialPaquete rastreoPaquete;

    cout << "Cambiando estados del paquete logistico..." << endl;
    rastreoPaquete.push("En Almacen Central (Maturin)");
    rastreoPaquete.push("Empaquetado y Clasificado");
    rastreoPaquete.push("En Ruta de Entrega Terrestre");

    cout << "Estado Actual: " << rastreoPaquete.obtenerEstadoActual() << "\n" << endl;
    rastreoPaquete.mostrarHistorial();

    cout << "\n[Accion Especial] Error en ruta detectado: Se requiere deshacer ultimo estado." << endl;
    rastreoPaquete.pop(); // Revierte "En Ruta"

    cout << "\nNuevo Estado Actual: " << rastreoPaquete.obtenerEstadoActual() << "\n" << endl;
    rastreoPaquete.mostrarHistorial();

    cout << "==========================================================" << endl;
    cout << "    Sprint 1 finalizado: Pilas y Colas operativas (OK)" << endl;
    cout << "==========================================================" << endl;

    return 0;
}
