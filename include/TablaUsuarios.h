#ifndef TABLAUSUARIOS_H
#define TABLAUSUARIOS_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Enums.h"

// Datos del usuario a almacenar en la tabla Hash
struct Usuario {
    std::string cedula; // Clave única (Key)
    std::string nombre;
    RolUsuario rol;    // Administrador, Repartidor, etc.
};

class TablaUsuarios {
private:
    static const int TAMANIO_INICIAL = 11; // Tamaño de la tabla (preferiblemente un número primo)
    
    // El "Bucket" de la tabla hash. Cada celda contiene una lista enlazada para manejar colisiones.
    std::vector<std::list<Usuario>> tabla;

    /*
       ========================================================================
       FUNCIÓN HASH ELEGIDA: MÉTODO DE LA DIVISIÓN (MÓDULO) + HASH DE STRING (DJB2 simplificado)
       
       ¿Por qué esta función?
       Dado que la clave (cedula) es un string alfanumérico, primero aplicamos un 
       algoritmo polinomial simple para convertir los caracteres del string en un 
       número entero grande y evitar colisiones por anagramas. Luego, usamos el 
       operador módulo (%) con el tamaño de la tabla para ajustarlo al rango de índices.
       ========================================================================
    */
    int funcionHash(const std::string& clave) const {
        unsigned long hash = 5381; // Semilla del algoritmo DJB2
        for (char c : clave) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % TAMANIO_INICIAL;
    }

public:
    TablaUsuarios() {
        tabla.resize(TAMANIO_INICIAL);
    }

    // Inserta un usuario en la tabla
    void insertar(const std::string& cedula, const std::string& nombre, const RolUsuario& rol) {
        int indice = funcionHash(cedula);
        
        // Evitamos duplicados de la misma cédula
        for (auto& usr : tabla[indice]) {
            if (usr.cedula == cedula) {
                usr.nombre = nombre; // Si ya existe, actualizamos los datos
                usr.rol = rol;
                return;
            }
        }

        // Si no existe, lo agregamos al final de la lista de ese bucket (Chaining)
        tabla[indice].push_back({cedula, nombre, rol});
    }

    // Busca un usuario en O(1) promedio
    Usuario* buscar(const std::string& cedula) {
        int indice = funcionHash(cedula);
        
        // Buscamos linealmente dentro de la lista enlazada del bucket correspondiente
        for (auto& usr : tabla[indice]) {
            if (usr.cedula == cedula) {
                return &usr; // Retorna un puntero al usuario encontrado
            }
        }
        return nullptr; // No encontrado
    }

    // Elimina un usuario por su cédula (retorna true si lo encontró y eliminó)
    bool eliminar(const std::string& cedula) {
        int indice = funcionHash(cedula);
        auto& lista = tabla[indice];

        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (it->cedula == cedula) {
                lista.erase(it);
                return true; // Eliminado con éxito
            }
        }
        return false; // No existía
    }

    // Muestra la distribución interna de la tabla (Para fines de auditoría del Sprint)
    void mostrarTabla() const {
        std::cout << "Estructura de Almacenamiento de Tabla Hash (Encadenamiento):\n";
        for (int i = 0; i < TAMANIO_INICIAL; ++i) {
            std::cout << "  Bucket [" << i << "]: ";
            if (tabla[i].empty()) {
                std::cout << "[Vacio]";
            } else {
                for (const auto& usr : tabla[i]) {
                    std::cout << "-> [" << usr.cedula << ": " << usr.nombre << " (" << rolATexto(usr.rol) << ")] ";
                }
            }
            std::cout << "\n";
        }
    }

    /*
       ========================================================================
       RESOLUCIÓN DE COLISIONES Y LIMITACIONES:
       
       1. Resolución de Colisiones: Se maneja por ENCADENAMIENTO (Separate Chaining) 
          usando `std::list`. Si dos cédulas distintas producen el mismo índice hash,
          ambas se guardan en la misma posición dentro de una lista doblemente enlazada.
          
       2. Limitación - Tamaño Estático y Degradación O(N): Esta implementación no tiene 
          "Rehashing" dinámico (redimensionamiento cuando se llena). Si el número de 
          usuarios (N) supera por mucho el tamaño de la tabla (11 celdas), las listas 
          crecerán demasiado y la complejidad de búsqueda se degradará de O(1) a O(N).
       ========================================================================
    */
};

#endif // TABLAUSUARIOS_H
