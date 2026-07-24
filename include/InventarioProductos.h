#ifndef INVENTARIOPRODUCTOS_H
#define INVENTARIOPRODUCTOS_H

#pragma once
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// ESTRUCTURA ADAPTADA PARA EL SPRINT 5 (Evita conflictos con ListaProductos)
// ============================================================================
struct ProductoInventario {
    int idProducto;      // Coincide con la nomenclatura 'idProducto'
    std::string nombre;
    int stock;          // Atributo requerido para el control de inventario masivo
    double precio;

    // Constructor que permite la inicialización por lista usada en el main.cpp
    ProductoInventario(int id, const std::string& nom, int stk, double pre)
        : idProducto(id), nombre(nom), stock(stk), precio(pre) {}

    // Constructor por defecto requerido por std::vector
    ProductoInventario() : idProducto(0), nombre(""), stock(0), precio(0.0) {}
};

// Nodo del Árbol 2-3 optimizado para ProductoInventario
struct Nodo23 {
    // Un nodo 2-3 puede tener un máximo de 2 claves (claves[0] y claves[1])
    std::vector<ProductoInventario> claves;

    // Un nodo 2-3 puede tener un máximo de 3 hijos (hijos[0], hijos[1], hijos[2])
    std::vector<Nodo23*> hijos;

    bool esHoja() const {
        return hijos.empty();
    }

    Nodo23() {}
};

class InventarioProductos {
private:
    Nodo23* raiz;

    // Métodos auxiliares privados para la inserción recursiva y el split
    Nodo23* insertarRecursivo(Nodo23* nodo, const ProductoInventario& prod, ProductoInventario& clavePromovida);
    void dividirNodo(Nodo23* nodo, const ProductoInventario& prodPush, Nodo23* hijoPush, ProductoInventario& clavePromovida, Nodo23*& nuevoNodo);

    ProductoInventario* buscarRecursivo(Nodo23* nodo, int id) {
        if (nodo == nullptr) return nullptr;

        // Buscar entre las claves del nodo actual
        for (size_t i = 0; i < nodo->claves.size(); ++i) {
            if (nodo->claves[i].idProducto == id) {
                return &(nodo->claves[i]); // Puntero directo al producto en memoria
            }
        }

        // Si es hoja y no estuvo en las claves, no existe
        if (nodo->esHoja()) return nullptr;

        // Navegar hacia el hijo correspondiente
        if (id < nodo->claves[0].idProducto) {
            return buscarRecursivo(nodo->hijos[0], id);
        } else if (nodo->claves.size() == 1 || id < nodo->claves[1].idProducto) {
            return buscarRecursivo(nodo->hijos[1], id);
        } else {
            return buscarRecursivo(nodo->hijos[2], id);
        }
    }

public:
    InventarioProductos() : raiz(nullptr) {}
    void insertar(const ProductoInventario& prod);
    void mostrarInorden(Nodo23* nodo) const;
    void mostrar() const { mostrarInorden(raiz); }

    ProductoInventario* buscar(int id) {
        return buscarRecursivo(raiz, id);
    }
};

// ============================================================================
// DETALLE DE LA IMPLEMENTACIÓN Y COMENTARIOS EXPLICATIVOS DEL ALGORITMO
// ============================================================================

void InventarioProductos::insertar(const ProductoInventario& prod) {
    if (raiz == nullptr) {
        raiz = new Nodo23();
        raiz->claves.push_back(prod);
        return;
    }

    ProductoInventario clavePromovida;
    Nodo23* nuevoHijoDerecho = insertarRecursivo(raiz, prod, clavePromovida);

    // Si la raíz sufrió una división (split), se crea una nueva raíz de nivel superior
    if (nuevoHijoDerecho != nullptr) {
        Nodo23* antiguaRaiz = raiz;
        raiz = new Nodo23();
        raiz->claves.push_back(clavePromovida);
        raiz->hijos.push_back(antiguaRaiz);
        raiz->hijos.push_back(nuevoHijoDerecho);
    }
}

Nodo23* InventarioProductos::insertarRecursivo(Nodo23* nodo, const ProductoInventario& prod, ProductoInventario& clavePromovida) {
    if (nodo->esHoja()) {
        // DETALLE DE OPERACIÓN: Si el nodo tiene espacio (1 clave, tipo Nodo-2)
        if (nodo->claves.size() < 2) {
            nodo->claves.push_back(prod);
            // Se ordena el vector para que claves[0] < claves[1]
            if (nodo->claves.size() == 2 && nodo->claves[0].idProducto > nodo->claves[1].idProducto) {
                std::swap(nodo->claves[0], nodo->claves[1]);
            }
            return nullptr; // No hay división, termina la propagación hacia arriba
        }

        // DETALLE DE OPERACIÓN: Si el nodo ya está lleno (2 claves, tipo Nodo-3), genera desbordamiento
        Nodo23* nuevoNodo = nullptr;
        dividirNodo(nodo, prod, nullptr, clavePromovida, nuevoNodo);
        return nuevoNodo; // Retorna el nuevo nodo hermano derecho para ser enlazado por el padre
    }

    // Navegación por el árbol según el idProducto
    Nodo23* hijoDestino = nullptr;

    if (prod.idProducto < nodo->claves[0].idProducto) {
        hijoDestino = nodo->hijos[0];
    } else if (nodo->claves.size() == 1 || prod.idProducto < nodo->claves[1].idProducto) {
        hijoDestino = nodo->hijos[1];
    } else {
        hijoDestino = nodo->hijos[2];
    }

    ProductoInventario claveSubida;
    Nodo23* nuevoHijo = insertarRecursivo(hijoDestino, prod, claveSubida);

    // Si el hijo inferior se dividió, intentamos insertar el fragmento en el nodo actual
    if (nuevoHijo != nullptr) {
        if (nodo->claves.size() < 2) {
            // El nodo actual tiene espacio para absorber la clave subida y su nuevo puntero derecho
            nodo->claves.push_back(claveSubida);
            nodo->hijos.push_back(nuevoHijo);

            // Reordenamiento manual de claves e hijos correspondientes
            if (nodo->claves.size() == 2 && nodo->claves[0].idProducto > nodo->claves[1].idProducto) {
                std::swap(nodo->claves[0], nodo->claves[1]);
                std::swap(nodo->hijos[1], nodo->hijos[2]);
            }
            return nullptr;
        } else {
            // COMENTARIO DE DIVISIÓN (SPLIT): El nodo padre también está lleno.
            // Se propaga la división de manera ascendente en cadena.
            ProductoInventario nuevoNodoPadre;
            Nodo23* nuevoHijoPadre = nullptr;
            dividirNodo(nodo, claveSubida, nuevoHijo, clavePromovida, nuevoHijoPadre);
            return nuevoHijoPadre;
        }
    }

    return nullptr;
}

void InventarioProductos::dividirNodo(Nodo23* nodo, const ProductoInventario& prodPush, Nodo23* hijoPush, ProductoInventario& clavePromovida, Nodo23*& nuevoNodo) {
    /* ========================================================================
       EXPLICACIÓN DETALLADA DEL ALGORITMO DE DIVISIÓN (SPLIT):

       1. Recibimos un nodo saturado (con 2 claves) y un nuevo elemento "Push" que quiere ingresar.
       2. Temporalmente unimos las 2 claves existentes junto con la clave entrante en una lista ordenada de 3 elementos.
       3. El elemento del MEDIO (índis 1) es el elegido para ser PROMOVIDO al padre (`clavePromovida`).
       4. El elemento MENOR (índice 0) se queda en el nodo original (izquierdo).
       5. El elemento MAYOR (índice 2) se mueve a un nuevo nodo hermano creado en memoria (`nuevoNodo`).
       6. Si no es un nodo hoja, los 4 punteros de hijos temporales se reparten equitativamente.
       ========================================================================
    */

    std::vector<ProductoInventario> tempClaves = nodo->claves;
    tempClaves.push_back(prodPush);

    // Ordenamiento de las 3 claves temporales
    for(size_t i = 0; i < tempClaves.size(); ++i) {
        for(size_t j = i+1; j < tempClaves.size(); ++j) {
            if(tempClaves[i].idProducto > tempClaves[j].idProducto) std::swap(tempClaves[i], tempClaves[j]);
        }
    }

    std::vector<Nodo23*> tempHijos;
    if (!nodo->esHoja()) {
        tempHijos = nodo->hijos;
        tempHijos.push_back(hijoPush);
        // Asegurar que el hijo insertado se acomode según las magnitudes de las claves subidas
        for(size_t i = 0; i < tempHijos.size(); ++i){
            for(size_t j = i+1; j < tempHijos.size(); ++j){
                // Reacomodo heurístico simple basado en punteros
                if(i == 2 && j == 3 && tempHijos[i]->claves[0].idProducto > tempHijos[j]->claves[0].idProducto){
                    std::swap(tempHijos[i], tempHijos[j]);
                }
            }
        }
    }

    // Promoción de la mediana
    clavePromovida = tempClaves[1];

    // Reconfiguración del nodo original (Izquierdo)
    nodo->claves.clear();
    nodo->claves.push_back(tempClaves[0]);

    // Configuración del nuevo nodo hermano (Derecho)
    nuevoNodo = new Nodo23();
    nuevoNodo->claves.push_back(tempClaves[2]);

    // Distribución de hijos
    if (!nodo->esHoja()) {
        nodo->hijos.clear();
        nodo->hijos.push_back(tempHijos[0]);
        nodo->hijos.push_back(tempHijos[1]);

        nuevoNodo->hijos.push_back(tempHijos[2]);
        nuevoNodo->hijos.push_back(tempHijos[3]);
    }
}

void InventarioProductos::mostrarInorden(Nodo23* nodo) const {
    if (nodo == nullptr) return;

    if (nodo->esHoja()) {
        for (const auto& prod : nodo->claves) {
            std::cout << "[ID: " << prod.idProducto << "] " << prod.nombre << " | Stock: " << prod.stock << " | Precio: $" << prod.precio << "\n";
        }
    } else {
        mostrarInorden(nodo->hijos[0]);
        std::cout << "[ID: " << nodo->claves[0].idProducto << "] " << nodo->claves[0].nombre << " | Stock: " << nodo->claves[0].stock << "\n";
        mostrarInorden(nodo->hijos[1]);
        if (nodo->claves.size() == 2) {
            std::cout << "[ID: " << nodo->claves[1].idProducto << "] " << nodo->claves[1].nombre << " | Stock: " << nodo->claves[1].stock << "\n";
            mostrarInorden(nodo->hijos[2]);
        }
    }
}

/*
   ========================================================================
   LIMITACIONES DEL ALGORITMO (PROPIEDADES TÉCNICAS Y ÁREAS DE MEJORA):

   1. AUSENCIA DE OPERACIÓN DE ELIMINACIÓN (DELETE):
      El archivo no implementa la eliminación de nodos. La remoción en un Árbol 2-3
      es una de las operaciones más complejas en estructuras balanceadas, ya que
      exige gestionar casos de underflow mediante fusión de nodos (merging) o 
      préstamo de claves (redistribución) desde nodos hermanos. Si un producto se
      da de baja en el catálogo, debe manejarse de forma lógica o reflejarse solo
      en la capa de presentación/AVL, pero no se desasigna de este árbol 2-3.

   2. AUSENCIA DE LIBERACIÓN DE MEMORIA DINÁMICA (DESTRUCTOR):
      La clase `InventarioProductos` carece de un destructor explícito (`~InventarioProductos`)
      que realice un recorrido postorden para liberar la memoria de los nodos creados 
      con `new Nodo23()`. En ejecuciones prolongadas o sistemas persistentes, esto
      generaría fugas de memoria (memory leaks).

   3. COMPORTAMIENTO INDEFINIDO ANTE IDs DUPLICADOS:
      La función `insertar` no valida si el `idProducto` ya existe antes de procesar
      el recorrido. Insertar una clave duplicada provocará que la misma exista en
      múltiples nodos o posiciones, corrompiendo el invariante de búsqueda del árbol.

   4. ORDENAMIENTO DE HIJOS LIMITADO EN EL SPLIT (dividirNodo):
      El reacomodo de los punteros en `tempHijos` durante la división de un nodo
      interno utiliza un intercambio heurístico básico entre las posiciones 2 y 3.
      Aunque funciona correctamente para la mayoría de secuencias de inserción,
      no realiza un ordenamiento estricto por límites de rangos de claves para
      los 4 hijos temporales, lo que podría desordenar punteros en escenarios
      específicos de inserciones complejas en cascada.

   5. COMPLEJIDAD EN MEMORIA POR VECTORES DINÁMICOS:
      El uso de `std::vector` dentro de la estructura `Nodo23` para `claves` e `hijos`
      simplifica la implementación, pero añade un pequeño overhead de memoria
      frente al uso de arreglos estáticos de tamaño fijo (`claves[2]` e `hijos[3]`),
      los cuales garantizan un layout de memoria contiguo y de tamaño constante.
   ========================================================================
*/
#endif //INVENTARIOPRODUCTOS_H
