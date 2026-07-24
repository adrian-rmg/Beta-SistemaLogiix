#ifndef ENUMS_H
#define ENUMS_H

#include <string>

// Roles de Usuario
enum class RolUsuario {
    Administrador,
    Repartidor,
    Cliente,
    Desconocido
};

// Estados del Paquete (Historial)
enum class EstadoPaquete {
    Registrado,
    EnAlmacen,
    EnTransito,
    Entregado,
    Cancelado
};

// --- Funciones auxiliares de conversión a Texto ---

inline std::string rolATexto(RolUsuario rol) {
    switch (rol) {
        case RolUsuario::Administrador: return "Administrador";
        case RolUsuario::Repartidor:    return "Repartidor";
        case RolUsuario::Cliente:       return "Cliente";
        default:                        return "Desconocido";
    }
}

inline std::string estadoATexto(EstadoPaquete estado) {
    switch (estado) {
        case EstadoPaquete::Registrado: return "Registrado en Sistema";
        case EstadoPaquete::EnAlmacen:  return "En Almacén";
        case EstadoPaquete::EnTransito: return "En Tránsito";
        case EstadoPaquete::Entregado:  return "Entregado";
        case EstadoPaquete::Cancelado:  return "Cancelado";
        default:                        return "Desconocido";
    }
}

#endif // ENUMS_H
