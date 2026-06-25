#ifndef LISTA_PRODUCTOS_H
#define LISTA_PRODUCTOS_H

#include <iostream>
#include <string>

/**
 * Estructura que representa un producto individual (Nodo de la lista doble).
 */
struct Producto {
    int idProducto;
    std::string nombre;
    double precio;
    Producto* anterior;
    Producto* siguiente;

    Producto(int id, const std::string& nom, double pre)
        : idProducto(id), nombre(nom), precio(pre), anterior(nullptr), siguiente(nullptr) {}
};

/**
 * Clase ListaProductos que gestiona una Lista Doblemente Enlazada desde cero.
 * Ideal para el desglose de productos en paquetes o carritos de compra.
 */
class ListaProductos {
private:
    Producto* cabeza;
    Producto* cola;

public:
    ListaProductos() : cabeza(nullptr), cola(nullptr) {}

    /**
     * Destructor que libera recursivamente toda la memoria dinamica utilizada por la lista.
     * QUE NO HACE: No guarda datos en persistencia ni limpia archivos externos.
     */
    ~ListaProductos() {
        Producto* actual = cabeza;
        while (actual != nullptr) {
            Producto* temporal = actual->siguiente;
            delete actual;
            actual = temporal;
        }
    }

    /**
     * Inserta un nuevo producto al final de la lista (Complejidad: O(1)).
     * QUE NO HACE: No ordena los elementos de forma automatica tras la insercion.
     * QUE NO HACE: No valida si el ID del producto ya existe (permite duplicados).
     */
    void insertarFinal(int id, const std::string& nombre, double precio) {
        Producto* nuevo = new Producto(id, nombre, precio);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
    }

    /**
     * Elimina un producto de la lista mediante su identificador unico (Complejidad: O(n)).
     * QUE NO HACE: No lanza excepciones si el elemento no existe (solo imprime advertencia).
     * QUE NO HACE: Si hay duplicados, solo elimina la primera ocurrencia encontrada.
     */
    void eliminarPorID(int id) {
        if (cabeza == nullptr) {
            std::cout << "[Error Lista] Intento de eliminar en lista vacia.\n";
            return;
        }

        Producto* actual = cabeza;
        while (actual != nullptr && actual->idProducto != id) {
            actual = actual->siguiente;
        }

        if (actual == nullptr) {
            std::cout << "[Advertencia] Producto con ID " << id << " no encontrado.\n";
            return;
        }

        // Desenlace del nodo
        if (actual == cabeza) {
            cabeza = cabeza->siguiente;
            if (cabeza != nullptr) cabeza->anterior = nullptr;
            else cola = nullptr; // La lista quedo vacia
        } else if (actual == cola) {
            cola = cola->anterior;
            if (cola != nullptr) cola->siguiente = nullptr;
            else cabeza = nullptr;
        } else {
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
        }

        delete actual;
        std::cout << "[Lista] Producto " << id << " eliminado exitosamente.\n";
    }

    /**
     * Busca un producto por su ID en forma secuencial (Complejidad: O(n)).
     * Devuelve el puntero al nodo si lo encuentra, de lo contrario devuelve nullptr.
     * QUE NO HACE: No soporta busqueda binaria (las listas enlazadas carecen de acceso indexado directo).
     * QUE NO HACE: No busca por coincidencia parcial de texto en el nombre.
     */
    Producto* buscarPorID(int id) const {
        Producto* actual = cabeza;
        while (actual != nullptr) {
            if (actual->idProducto == id) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    /**
     * Recorre e imprime los elementos desde el inicio hasta el final (Complejidad: O(n)).
     * QUE NO HACE: No altera ni modifica el orden original de almacenamiento de los nodos.
     * QUE NO HACE: No formatea la salida en interfaces graficas o archivos CSV.
     */
    void mostrarListaHaciaAdelante() const {
        if (cabeza == nullptr) {
            std::cout << "La lista de productos esta vacia.\n";
            return;
        }
        Producto* actual = cabeza;
        std::cout << "Desglose de Productos (Orden Directo):\n";
        while (actual != nullptr) {
            std::cout << "  -> [ID: " << actual->idProducto
                      << " | " << actual->nombre
                      << " | Precio: $" << actual->precio << "]\n";
            actual = actual->siguiente;
        }
    }

    /**
     * Recorre e imprime los elementos en sentido inverso (Aprovecha las ventajas de la lista doble).
     * QUE NO HACE: No ordena los elementos de mayor a menor precio.
     */
    void mostrarListaHaciaAtras() const {
        if (cola == nullptr) {
            std::cout << "La lista de productos esta vacia.\n";
            return;
        }
        Producto* actual = cola;
        std::cout << "Desglose de Productos (Orden Inverso):\n";
        while (actual != nullptr) {
            std::cout << "  -> [ID: " << actual->idProducto
                      << " | " << actual->nombre
                      << " | Precio: $" << actual->precio << "]\n";
            actual = actual->anterior;
        }
    }
};

#endif