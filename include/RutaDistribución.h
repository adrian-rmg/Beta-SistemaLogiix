#ifndef RUTADISTRIBUCION_H
#define RUTADISTRIBUCION_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

// Estructura para representar una conexión (arista dirigida con peso)
struct Conexion {
    std::string destino;
    int distanciaKM; // Peso de la arista (ej. kilómetros entre ciudades)
};

class RutaDistribucion {
private:
    /*
       ========================================================================
       REPRESENTACIÓN ELEGIDA: LISTA DE ADYACENCIA (unordered_map de vectores)

       ¿Por qué esta representación?
       1. Flexibilidad de Nodos (Ciudades con nombres tipo string): En lugar de usar
          una matriz de adyacencia de tamaño fijo indexada por enteros, usamos un map.
          Esto permite registrar ciudades dinámicamente usando sus nombres ("Maturin", "Caracas").
       2. Eficiencia de Espacio: En logística, la red de carreteras suele ser un grafo
          "disperso" (un almacén o ciudad no se conecta directamente con todos los demás).
          La lista de adyacencia consume solo O(V + E) de memoria en lugar de O(V^2).
       ========================================================================
    */
    std::unordered_map<std::string, std::vector<Conexion>> listaAdyacencia;

public:
    RutaDistribucion() {}

    // Añade una ciudad a la red (vértice)
    void agregarCiudad(const std::string& ciudad) {
        if (listaAdyacencia.find(ciudad) == listaAdyacencia.end()) {
            listaAdyacencia[ciudad] = std::vector<Conexion>();
        }
    }

    // Añade una ruta entre dos ciudades (arista dirigida con peso)
    void agregarRuta(const std::string& origen, const std::string& destino, int distancia) {
        agregarCiudad(origen);
        agregarCiudad(destino);
        listaAdyacencia[origen].push_back({destino, distancia});
    }

    /*
       ========================================================================
       RECORRIDO ELEGIDO: BFS (Búsqueda en Anchura / Breadth-First Search)

       ¿Por qué BFS?
       Para un sistema logístico, BFS es ideal porque explora la red nivel por nivel.
       En un grafo no ponderado o para encontrar el camino con menor "número de escalas"
       (saltos de almacén), BFS garantiza encontrar la ruta más corta en saltos.
       ========================================================================
    */
    void mostrarRecorridoBFS(const std::string& inicio) {
        if (listaAdyacencia.find(inicio) == listaAdyacencia.end()) {
            std::cout << "[Grafo] La ciudad de inicio no existe en la red.\n";
            return;
        }

        std::unordered_set<std::string> visitados;
        std::queue<std::string> cola;

        cola.push(inicio);
        visitados.insert(inicio);

        std::cout << "Recorrido BFS de Distribucion desde '" << inicio << "':\n  ";
        while (!cola.empty()) {
            std::string actual = cola.front();
            cola.pop();

            std::cout << " -> " << actual;

            // Explorar todos los vecinos adyacentes de la ciudad actual
            for (const auto& conexion : listaAdyacencia[actual]) {
                if (visitados.find(conexion.destino) == visitados.end()) {
                    visitados.insert(conexion.destino);
                    cola.push(conexion.destino);
                }
            }
        }
        std::cout << " -> [Fin del Recorrido]\n";
    }

    // Muestra todas las conexiones de la red
    void mostrarRed() const {
        std::cout << "Red Logistica de Distribucion Actual:\n";
        for (const auto& par : listaAdyacencia) {
            std::cout << "  [" << par.first << "] se conecta con: ";
            if (par.second.empty()) std::cout << "(Sin salidas)";
            for (const auto& conexion : par.second) {
                std::cout << "-> " << conexion.destino << " (" << conexion.distanciaKM << " km) ";
            }
            std::cout << "\n";
        }
    }

    /*
       ========================================================================
       LIMITACIONES DE ESTA IMPLEMENTACIÓN:
       1. No maneja rutas bidireccionales por defecto: El método `agregarRuta` es
          unidireccional (dirigido). Si se desea que sea de ida y vuelta, se debe
          llamar dos veces o modificar el código para agregar la arista en ambos sentidos.
       2. No implementa algoritmos de camino mínimo ponderado (como Dijkstra): Aunque
          guardamos el peso (distanciaKM), el recorrido BFS solo optimiza el número
          de saltos, ignorando las distancias reales en kilómetros.
       ========================================================================
    */
};

#endif // RUTADISTRIBUCION_H
