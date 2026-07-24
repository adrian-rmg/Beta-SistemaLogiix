#ifndef COLA_PEDIDOS_HPP
#define COLA_PEDIDOS_HPP

#include <iostream>
#include <string>
#include "HistorialPaquete.h"

/**
 * Estructura que representa un pedido individual en el sistema.
 */
struct Pedido {
    int idPedido;
    std::string cedulaCliente;
    std::string destino;
    HistorialPaquete historial;
    Pedido* siguiente;

    Pedido(int id, const std::string& cedula, const std::string& dest)
        : idPedido(id), cedulaCliente(cedula), destino(dest), siguiente(nullptr) {
        historial.push(EstadoPaquete::Registrado);
    }
};

/**
 * Clase ColaPedidos que implementa una Cola desde cero.
 * Gestiona los pedidos entrantes pendientes por procesar de forma FIFO.
 */
class ColaPedidos {
private:
    Pedido* frente;
    Pedido* final;

public:
    ColaPedidos() : frente(nullptr), final(nullptr) {}

    /**
     * Destructor para liberar la memoria dinámica de la cola.
     */
    ~ColaPedidos() {
        while (!estaVacia()) {
            dequeue();
        }
    }

    /**
     * Inserta un nuevo pedido al final de la cola (Enqueue).
     * id Identificador único del pedido.
     * destino Dirección o ciudad destino.
     * No controla si existen IDs de pedidos duplicados dentro de la cola.
     */
    void enqueue(int id, const std::string& cedula, const std::string& destino) {
        Pedido* nuevoPedido = new Pedido(id, cedula, destino);
        if (estaVacia()) {
            frente = nuevoPedido;
            final = nuevoPedido;
        } else {
            final->siguiente = nuevoPedido;
            final = nuevoPedido;
        }
    }

    /**
     * Procesa (elimina) el pedido que está al frente de la cola (Dequeue).
     * Al igual que la pila, si la cola está vacía, solo emite una advertencia
     * por consola en lugar de un manejo formal de errores (Exceptions).
     */
    void dequeue() {
        if (estaVacia()) {
            std::cout << "[Error Cola] No hay pedidos pendientes por procesar.\n";
            return;
        }
        Pedido* temporal = frente;
        frente = frente->siguiente;
        
        if (frente == nullptr) {
            final = nullptr; // Si la cola quedó vacía
        }
        delete temporal;
    }

    /**
     * Consulta el pedido que está próximo a ser procesado (Front).
     * Si la cola está vacía, devuelve un puntero nulo (nullptr), obligando
     * al llamador a validar el resultado antes de acceder a sus propiedades.
     */
    Pedido* obtenerFrente() const {
        return frente;
    }

    // Método para bucar un pedido por ID y obtener su historial
    Pedido* buscarPedido(int id) {
        Pedido* actual = frente;
        while (actual != nullptr) {
            if (actual->idPedido == id) {
                return actual; // Retorna el pedido encontrado
            }
            actual = actual->siguiente;
        }
        return nullptr; // No se encontró
    }

    /**
     * Verifica si no hay pedidos en espera.
     */
    bool estaVacia() const {
        return frente == nullptr;
    }

    /**
     * Despliega la lista actual de pedidos en espera en la consola.
     */
    void mostrarCola() const {
        if (estaVacia()) {
            std::cout << "No hay pedidos pendientes en la cola.\n";
            return;
        }
        Pedido* actual = frente;
        std::cout << "Cola de Espera Activa:\n";
        while (actual != nullptr) {
            std::cout << " [ID: " << actual->idPedido << " | Destino: " << actual->destino << "]\n";
            actual = actual->siguiente;
        }
    }
};

#endif
