#ifndef HISTORIAL_PAQUETE_HPP
#define HISTORIAL_PAQUETE_HPP

#include <iostream>
#include <string>

/**
 * Nodo para la estructura lineal de la Pila.
 */
struct NodoPila {
    std::string estado;
    NodoPila* siguiente;

    NodoPila(const std::string& est) : estado(est), siguiente(nullptr) {}
};

/**
 * Clase HistorialPaquete que implementa una Pila desde cero.
 * Gestiona los cambios de estado de un paquete individual de forma LIFO.
 */
class HistorialPaquete {
private:
    NodoPila* tope;

public:
    HistorialPaquete() : tope(nullptr) {}

    /**
     * Destructor para liberar la memoria dinámica utilizada por la pila.
     */
    ~HistorialPaquete() {
        while (!estaVacia()) {
            pop();
        }
    }

    /**
     * Registra un nuevo estado en el historial (Push).
     * nuevoEstado Texto que describe el estado actual (ej: "En Almacén").
     * No tiene límite de tamaño teórico (memoria dinámica), pero la inserción
     * es ciega; no valida si el estado lógico tiene sentido respecto al anterior.
     */
    void push(const std::string& nuevoEstado) {
        NodoPila* nuevoNodo = new NodoPila(nuevoEstado);
        nuevoNodo->siguiente = tope;
        tope = nuevoNodo;
    }

    /**
     * Elimina el último estado registrado (Pop) para simular un "deshacer".
     * Si la pila está vacía, imprime un mensaje de error en consola en lugar
     * de lanzar una excepción formal del lenguaje.
     */
    void pop() {
        if (estaVacia()) {
            std::cout << "[Error Pila] No hay estados en el historial para eliminar.\n";
            return;
        }
        NodoPila* temporal = tope;
        tope = tope->siguiente;
        delete temporal;
    }

    /**
     * Retorna el estado actual del paquete (Top).
     * El string del estado superior o un aviso de vacío.
     */
    std::string obtenerEstadoActual() const {
        if (estaVacia()) {
            return "Sin estados registrados";
        }
        return tope->estado;
    }

    /**
     * Verifica si el historial está vacío.
     */
    bool estaVacia() const {
        return tope == nullptr;
    }

    /**
     * Muestra todo el historial de estados de arriba hacia abajo.
     */
    void mostrarHistorial() const {
        if (estaVacia()) {
            std::cout << "Historial vacío.\n";
            return;
        }
        NodoPila* actual = tope;
        std::cout << "Historial (Más reciente primero):\n";
        while (actual != nullptr) {
            std::cout << " -> " << actual->estado << "\n";
            actual = actual->siguiente;
        }
    }
};

#endif
