#ifndef CATALOGO_PRODUCTOS_H
#define CATALOGO_PRODUCTOS_H

#include <iostream>
#include <string>
#include <algorithm>

// Estructura del Nodo del Catálogo
struct NodoProducto {
    int idProducto;
    std::string nombre;
    double precio;
    NodoProducto* izquierdo;
    NodoProducto* derecho;
    int altura;

    NodoProducto(int id, std::string nom, double prec)
        : idProducto(id), nombre(nom), precio(prec), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Clase CatalogoProductos utilizando Árbol AVL
class CatalogoProductos {
private:
    NodoProducto* raiz;

    // Funciones auxiliares de utilidad
    int obtenerAltura(NodoProducto* n) {
        return n == nullptr ? 0 : n->altura;
    }

    int obtenerBalance(NodoProducto* n) {
        return n == nullptr ? 0 : obtenerAltura(n->izquierdo) - obtenerAltura(n->derecho);
    }

    // Rotaciones AVL
    NodoProducto* rotacionDerecha(NodoProducto* y) {
        NodoProducto* x = y->izquierdo;
        NodoProducto* T2 = x->derecho;

        // Rotación
        x->derecho = y;
        y->izquierdo = T2;

        // Actualizar alturas
        y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
        x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

        return x;
    }

    NodoProducto* rotacionIzquierda(NodoProducto* x) {
        NodoProducto* y = x->derecho;
        NodoProducto* T2 = y->izquierdo;

        // Rotación
        y->izquierdo = x;
        x->derecho = T2;

        // Actualizar alturas
        x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
        y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

        return y;
    }

    // Inserción Recursiva
    NodoProducto* insertar(NodoProducto* nodo, int id, std::string nombre, double precio) {
        // 1. Inserción BST Estándar
        if (nodo == nullptr) {
            return new NodoProducto(id, nombre, precio);
        }

        if (id < nodo->idProducto) {
            nodo->izquierdo = insertar(nodo->izquierdo, id, nombre, precio);
        } else if (id > nodo->idProducto) {
            nodo->derecho = insertar(nodo->derecho, id, nombre, precio);
        } else {
            // EDGE CASE: El ID ya existe. Logiix decide actualizar el precio y nombre.
            nodo->nombre = nombre;
            nodo->precio = precio;
            return nodo;
        }

        // 2. Actualizar altura del nodo ancestro
        nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

        // 3. Obtener factor de balance para verificar desequilibrio
        int balance = obtenerBalance(nodo);

        // Caso Izquierda - Izquierda (Rotación Derecha Simple)
        if (balance > 1 && id < nodo->izquierdo->idProducto) {
            return rotacionDerecha(nodo);
        }

        // Caso Derecha - Derecha (Rotación Izquierda Simple)
        if (balance < -1 && id > nodo->derecho->idProducto) {
            return rotacionIzquierda(nodo);
        }

        // Caso Izquierda - Derecha (Rotación Doble Izquierda-Derecha)
        if (balance > 1 && id > nodo->izquierdo->idProducto) {
            nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
            return rotacionDerecha(nodo);
        }

        // Caso Derecha - Izquierda (Rotación Doble Derecha-Izquierda)
        if (balance < -1 && id < nodo->derecho->idProducto) {
            nodo->derecho = rotacionDerecha(nodo->derecho);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    // Nodo con el valor mínimo (sucesor en in-order)
    NodoProducto* nodoValorMinimo(NodoProducto* nodo) {
        NodoProducto* actual = nodo;
        while (actual->izquierdo != nullptr) {
            actual = actual->izquierdo;
        }
        return actual;
    }

    // Eliminación Recursiva (Baja)
    NodoProducto* eliminar(NodoProducto* raizSub, int id, bool& eliminado) {
        if (raizSub == nullptr) return raizSub;

        if (id < raizSub->idProducto) {
            raizSub->izquierdo = eliminar(raizSub->izquierdo, id, eliminado);
        } else if (id > raizSub->idProducto) {
            raizSub->derecho = eliminar(raizSub->derecho, id, eliminado);
        } else {
            eliminado = true;
            // EDGE CASE: Nodo con un solo hijo o ninguno
            if ((raizSub->izquierdo == nullptr) || (raizSub->derecho == nullptr)) {
                NodoProducto* temp = raizSub->izquierdo ? raizSub->izquierdo : raizSub->derecho;

                if (temp == nullptr) { // Caso sin hijos
                    temp = raizSub;
                    raizSub = nullptr;
                } else { // Caso un hijo
                    *raizSub = *temp; // Copiar contenido
                }
                delete temp;
            } else {
                // EDGE CASE: Nodo con dos hijos (Sucesor In-order)
                NodoProducto* temp = nodoValorMinimo(raizSub->derecho);
                raizSub->idProducto = temp->idProducto;
                raizSub->nombre = temp->nombre;
                raizSub->precio = temp->precio;
                raizSub->derecho = eliminar(raizSub->derecho, temp->idProducto, eliminado);
            }
        }

        if (raizSub == nullptr) return raizSub;

        // Actualizar altura
        raizSub->altura = 1 + std::max(obtenerAltura(raizSub->izquierdo), obtenerAltura(raizSub->derecho));

        // Balancear el árbol
        int balance = obtenerBalance(raizSub);

        if (balance > 1 && obtenerBalance(raizSub->izquierdo) >= 0) return rotacionDerecha(raizSub);
        if (balance > 1 && obtenerBalance(raizSub->izquierdo) < 0) {
            raizSub->izquierdo = rotacionIzquierda(raizSub->izquierdo);
            return rotacionDerecha(raizSub);
        }
        if (balance < -1 && obtenerBalance(raizSub->derecho) <= 0) return rotacionIzquierda(raizSub);
        if (balance < -1 && obtenerBalance(raizSub->derecho) > 0) {
            raizSub->derecho = rotacionDerecha(raizSub->derecho);
            return rotacionIzquierda(raizSub);
        }

        return raizSub;
    }

    void inOrder(NodoProducto* raizSub) {
        if (raizSub != nullptr) {
            inOrder(raizSub->izquierdo);
            std::cout << "[ID: " << raizSub->idProducto << "] " << raizSub->nombre << " - $" << raizSub->precio << "\n";
            inOrder(raizSub->derecho);
        }
    }

public:
    CatalogoProductos() : raiz(nullptr) {}

    void insertarProducto(int id, std::string nombre, double precio) {
        raiz = insertar(raiz, id, nombre, precio);
    }

    bool darDeBaja(int id) {
        bool eliminado = false;
        raiz = eliminar(raiz, id, eliminado);
        return eliminado;
    }

    NodoProducto* buscar(int id) {
        NodoProducto* actual = raiz;
        while (actual != nullptr) {
            if (id == actual->idProducto) return actual;
            actual = (id < actual->idProducto) ? actual->izquierdo : actual->derecho;
        }
        return nullptr; // Devuelve nullptr si está vacío o no se encuentra
    }

    void mostrarCatalogo() {
        if (raiz == nullptr) {
            std::cout << "(El catálogo de inventario está vacío)\n";
            return;
        }
        inOrder(raiz);
    }
};

#endif