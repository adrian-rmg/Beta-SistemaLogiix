#ifndef RUTADISTRIBUCION_H
#define RUTADISTRIBUCION_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <climits>
#include <map>

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

    // Algoritmo de Dijkstra para calcular distancias mínimas en KM desde un origen
    void calcularRutaDijkstra(const std::string& origen) {
        if (listaAdyacencia.find(origen) == listaAdyacencia.end()) {
            std::cout << "\n[X] Error: La ciudad origen '" << origen << "' no existe en la red de distribución.\n";
            return;
        }

        // Distancias mínimas
        std::map<std::string, int> distancias;
        for (const auto& par : listaAdyacencia) {
            distancias[par.first] = INT_MAX;
        }
        distancias[origen] = 0;

        // Predecesor para reconstruir la ruta
        std::unordered_map<std::string, std::string> predecesor;
        predecesor[origen] = "";  // indica inicio

        // Min-heap
        std::priority_queue<
            std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>,
            std::greater<std::pair<int, std::string>>
        > colaPrioridad;
        colaPrioridad.push({0, origen});

        while (!colaPrioridad.empty()) {
            int distActual = colaPrioridad.top().first;
            std::string u = colaPrioridad.top().second;
            colaPrioridad.pop();

            if (distActual > distancias[u]) continue;

            for (const auto& conexion : listaAdyacencia[u]) {
                std::string v = conexion.destino;
                int peso = conexion.distanciaKM;

                if (distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    predecesor[v] = u;          // guardamos de dónde venimos
                    colaPrioridad.push({distancias[v], v});
                }
            }
        }

        // ---------- IMPRESIÓN CON RUTAS ----------
        std::cout << "\n=======================================================\n";
        std::cout << " COBERTURA Y DISTANCIAS ÓPTIMAS DESDE: " << origen << "\n";
        std::cout << "=======================================================\n";

        for (const auto& par : distancias) {
            const std::string& destino = par.first;
            int dist = par.second;

            if (dist == INT_MAX) {
                std::cout << " -> Destino: " << destino << " | Estado: INALCANZABLE\n";
                continue;
            }

            // Reconstruir camino
            std::vector<std::string> camino;
            std::string actual = destino;
            while (actual != "" && actual != origen) {
                camino.push_back(actual);
                actual = predecesor[actual];
            }
            camino.push_back(origen);    // agregamos el origen
            std::reverse(camino.begin(), camino.end());

            // Mostrar distancia y ruta
            std::cout << " -> Destino: " << destino
                      << " | Distancia Mínima: " << dist << " KM"
                      << " | Ruta: ";
            for (size_t i = 0; i < camino.size(); ++i) {
                std::cout << camino[i];
                if (i != camino.size() - 1) std::cout << " -> ";
            }
            std::cout << "\n";
        }
        std::cout << "=======================================================\n";
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

    // Verifica si una ciudad existe actualmente en la red de distribución
    bool existeCiudad(const std::string& ciudad) const {
        return listaAdyacencia.find(ciudad) != listaAdyacencia.end();
    }
};

#endif // RUTADISTRIBUCION_H
