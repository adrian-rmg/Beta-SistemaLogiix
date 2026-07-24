#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <limits>
#include "TablaUsuarios.h"
#include "ColaPedidos.h"
#include "HistorialPaquete.h"
#include "CatalogoProductos.h"
#include "InventarioProductos.h"
#include "RutaDistribucion.h"

using namespace std;

// Funciones auxiliares de la interfaz
void limpiarPantalla() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarEncabezado() {
    limpiarPantalla();
    cout << "==========================================================\n";
    cout << "          SISTEMA LOGISTICO Y DE DISTRIBUCION LOGIIX     \n";
    cout << "==========================================================\n\n";
}

// Submenú de Usuarios y Autenticación (Hashing)
void menuUsuarios(TablaUsuarios& tabla) {
    int opcion = 0;
    do {
        cout << "\n============================================\n";
        cout << "--- MÓDULO DE GESTIÓN DE USUARIOS (HASH TABLE) ---\n";
        cout << "============================================\n";
        cout << "1. Registrar / Actualizar Usuario\n";
        cout << "2. Buscar Usuario por Cédula / ID\n";
        cout << "3. Eliminar Usuario por Cédula / ID\n";
        cout << "4. Volver al Menú Principal\n";
        cout << "--------------------------------------------\n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[!] Entrada inválida. Ingrese un número.\n";
            pausar();
            continue;
        }

        switch (opcion) {
            case 1: {
                string cedula, nombre;

                cout << "\n--- Registrar Nuevo Usuario ---\n";
                cout << "Ingrese Cédula/ID: ";
                cin >> cedula;

                // Limpiamos el buffer del \n dejado por 'cin >> cedula' antes del primer getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Ingrese Nombre Completo: ";
                getline(cin, nombre);

                int opcionRol = 0;
                cout << "Seleccione Rol:\n";
                cout << "1. Administrador\n2. Repartidor\n3. Cliente\nOpción: ";
                cin >> opcionRol;

                RolUsuario rol = RolUsuario::Cliente; // Valor por defecto

                switch (opcionRol) {
                    case 1: rol = RolUsuario::Administrador; break;
                    case 2: rol = RolUsuario::Repartidor; break;
                    case 3: rol = RolUsuario::Cliente; break;
                    default: cout << "[!] Opción no válida, asignando 'Cliente' por defecto.\n";
                }

                // Validamos que no entren campos vacíos
                if (cedula.empty() || nombre.empty()) {
                    cout << "\n[!] Error: Todos los campos son obligatorios.\n";
                } else {
                    // INSERCIÓN REAL EN LA TABLA HASH
                    tabla.insertar(cedula, nombre, rol);
                    cout << "\n[OK] Usuario registrado/actualizado exitosamente en la Tabla Hash.\n";
                }

                pausar();
                break;
            }

            case 2: {
                string cedula;
                cout << "\n--- Buscar Usuario ---\n";
                cout << "Ingrese Cédula/ID a buscar: ";
                cin >> cedula;

                cout << "\n[INFO] Realizando búsqueda en Tabla Hash O(1)...\n";

                Usuario* usuario = tabla.buscar(cedula);

                if (usuario != nullptr) {
                    cout << "\n====================================\n";
                    cout << "       ¡USUARIO ENCONTRADO!         \n";
                    cout << "====================================\n";
                    cout << " Cédula / ID: " << usuario->cedula << "\n";
                    cout << " Nombre:      " << usuario->nombre << "\n";
                    cout << " Rol:         " << rolATexto(usuario->rol) << "\n";
                    cout << "====================================\n";
                } else {
                    cout << "\n[X] Error: No existe ningún usuario registrado con la cédula " << cedula << ".\n";
                }

                pausar();
                break;
            }

            case 3: {
                string cedula;
                cout << "\n--- Eliminar Usuario ---\n";
                cout << "Ingrese Cédula/ID a eliminar: ";
                cin >> cedula;

                cout << "\n[INFO] Intentando eliminar usuario...\n";

                if (tabla.eliminar(cedula)) {
                    cout << "\n[OK] Usuario con cédula " << cedula << " ELIMINADO CON ÉXITO.\n";
                } else {
                    cout << "\n[X] Error: No existe ningún usuario registrado con la cédula " << cedula << ".\n";
                }
                pausar();
                break;
            }

            case 4: {
                cout << "\nRegresando al menú principal...\n";
                break;
            }

            default: {
                cout << "\n[!] Opción inválida. Intente de nuevo.\n";
                pausar();
                break;
            }
        }

    } while (opcion != 4);
}

// Submenú de Procesamiento de Pedidos (Cola - FIFO) + Integración con Grafo y Pila de Trazabilidad
void menuPedidos(ColaPedidos& colaPedidos, TablaUsuarios& tablaUsuarios, InventarioProductos& inventario, RutaDistribucion& redRutas, std::unordered_map<int, HistorialPaquete>& mapaHistoriales) {
    int opcion = 0;
    do {
        mostrarEncabezado();
        cout << "--- MÓDULO DE PEDIDOS EN ESPERA (COLA - FIFO) ---\n";
        cout << "1. Registrar Nuevo Pedido (Validación Hash + 2-3 + Grafo)\n";
        cout << "2. Procesar y Despachar Siguiente Pedido (Dequeue -> Pila Trazabilidad)\n";
        cout << "3. Ver Pedido al Frente (Front)\n";
        cout << "4. Ver Toda la Cola de Pedidos\n";
        cout << "5. Volver al Menú Principal\n";
        cout << "--------------------------------------------------\n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[!] Entrada inválida. Ingrese un número.\n";
            pausar();
            continue;
        }

        switch (opcion) {
            case 1: {
                string cedula, destino;
                int idProducto = 0, cantidad = 0, idPedido = 0;

                cout << "\n--- Registrar Nuevo Pedido ---\n";
                cout << "Ingrese Cédula del Cliente: ";
                cin >> cedula;

                // 1. Integración con Tabla Hash (Clientes)
                Usuario* cliente = tablaUsuarios.buscar(cedula);
                if (cliente == nullptr) {
                    cout << "\n[X] Error: La cédula no está registrada en el sistema de usuarios.\n";
                    pausar();
                    break;
                }
                cout << "[OK] Cliente verificado: " << cliente->nombre << "\n\n";

                // 2. Integración con Árbol 2-3 (Stock)
                cout << "Ingrese ID del Producto a comprar: ";
                cin >> idProducto;
                ProductoInventario* prod = inventario.buscar(idProducto);

                if (prod == nullptr) {
                    cout << "\n[X] Error: El producto #" << idProducto << " no existe en el Inventario.\n";
                    pausar();
                    break;
                }

                cout << "  -> Producto: " << prod->nombre << " | Stock disponible: " << prod->stock << "\n";
                cout << "Ingrese Cantidad a solicitar: ";
                cin >> cantidad;

                if (cantidad <= 0 || prod->stock < cantidad) {
                    cout << "\n[X] Error: Cantidad inválida o stock insuficiente.\n";
                    pausar();
                    break;
                }

                // 3. INTEGRACIÓN CON EL GRAFO (Validación de Ciudad Destino)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese Ciudad / Destino de Entrega: ";
                getline(cin, destino);

                if (!redRutas.existeCiudad(destino)) {
                    cout << "\n[X] Error Logístico: La ciudad '" << destino
                         << "' NO existe en la Red de Distribución (Grafo).\n";
                    cout << "    Por favor, registre primero la ciudad o ruta en el Módulo de Rutas.\n";
                    pausar();
                    break;
                }

                cout << "Ingrese ID para el nuevo Pedido: ";
                cin >> idPedido;

                // Descontamos stock y encolamos
                prod->stock -= cantidad;
                colaPedidos.enqueue(idPedido, cedula, destino);

                // Inicializamos la Pila de Trazabilidad para este pedido con Estado: Registrado
                mapaHistoriales[idPedido].push(EstadoPaquete::Registrado);

                cout << "\n[OK] Pedido #" << idPedido << " encolado con éxito para " << cliente->nombre << ".\n";
                cout << "[OK] Destino verificado en Grafo: '" << destino << "'.\n";
                cout << "[OK] Trazabilidad inicializada en Estado: REGISTRADO.\n";

                pausar();
                break;
            }

            case 2: {
                cout << "\n--- Procesando y Despachando Siguiente Pedido ---\n";

                if (colaPedidos.estaVacia()) {
                    cout << "\n[!] No hay pedidos pendientes en la cola para procesar.\n";
                } else {
                    // Consultamos el pedido al frente de la cola
                    Pedido* alFrente = colaPedidos.obtenerFrente();
                    int idDespachado = alFrente->idPedido;
                    string destinoDespachado = alFrente->destino;

                    // 4. INTEGRACIÓN CON HISTORIAL PAQUETE (Pila)
                    // Actualizamos el estado en la Pila LIFO de trazabilidad a EnTransito
                    mapaHistoriales[idDespachado].push(EstadoPaquete::EnTransito);

                    cout << "\n[OK] ¡Pedido #" << idDespachado << " procesado y sacado de la Cola (Dequeue)!\n";
                    cout << " - Destino: " << destinoDespachado << "\n";
                    cout << " - Nuevo Estado en Trazabilidad (Pila): EN TRÁNSITO\n";

                    // Retiramos el pedido de la cola
                    colaPedidos.dequeue();
                }

                pausar();
                break;
            }

            case 3: {
                cout << "\n--- Consulta de Frente (Front) ---\n";
                Pedido* alFrente = colaPedidos.obtenerFrente();

                if (alFrente != nullptr) {
                    cout << "\nPróximo pedido a procesar:\n";
                    cout << " - ID Pedido: #" << alFrente->idPedido << "\n";
                    cout << " - Destino:   " << alFrente->destino << "\n";
                } else {
                    cout << "\n[INFO] La cola de espera está actualmente vacía.\n";
                }

                pausar();
                break;
            }

            case 4: {
                cout << "\n--- Estado Actual de la Cola ---\n";
                colaPedidos.mostrarCola();
                pausar();
                break;
            }

            case 5:
                cout << "\nRegresando al menú principal...\n";
                break;

            default:
                cout << "\n[!] Opción inválida. Intente de nuevo.\n";
                pausar();
                break;
        }

    } while (opcion != 5);
}

// Submenú de Rastreabilidad de Paquetes (Pila - LIFO)
void menuHistorial(std::unordered_map<int, HistorialPaquete>& mapaHistoriales) {
    if (mapaHistoriales.empty()) {
        cout << "\n[!] No hay historiales de pedidos registrados en el sistema.\n";
        pausar();
        return;
    }

    int idBuscado = 0;
    cout << "\n=== MÓDULO DE RASTREO E HISTORIAL (PILA - LIFO) ===\n";
    cout << "Ingrese el ID del Pedido a consultar/actualizar: ";

    if (!(cin >> idBuscado)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n[!] ID inválido.\n";
        pausar();
        return;
    }

    // Buscamos si existe la Pila/Historial para este idPedido en el unordered_map
    auto it = mapaHistoriales.find(idBuscado);

    if (it == mapaHistoriales.end()) {
        cout << "\n[X] Error: No se encontró historial para ningún pedido con ID #" << idBuscado << ".\n";
        pausar();
        return;
    }

    // Obtenemos una referencia directa a la Pila (HistorialPaquete) de este pedido
    HistorialPaquete& historial = it->second;

    int opcion = 0;
    do {
        mostrarEncabezado();
        cout << "--- RASTREO Y TRAZABILIDAD DEL PEDIDO #" << idBuscado << " ---\n";
        cout << "1. Registrar Nuevo Estado (Push)\n";
        cout << "2. Revertir Último Estado / Deshacer (Pop)\n";
        cout << "3. Consultar Estado Actual (Top)\n";
        cout << "4. Ver Trazabilidad Completa (Historial)\n";
        cout << "5. Cambiar de Pedido / Volver\n";
        cout << "---------------------------------------------------\n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                int opcionEstado = 0;
                cout << "\nSeleccione el Nuevo Estado:\n";
                cout << "1. En Almacén\n2. En Tránsito\n3. Entregado\n4. Cancelado\nOpción: ";
                if (cin >> opcionEstado) {
                    switch (opcionEstado) {
                        case 1:
                            historial.push(EstadoPaquete::EnAlmacen);
                            cout << "\n[OK] Estado 'En Almacén' añadido al historial.\n";
                            break;
                        case 2:
                            historial.push(EstadoPaquete::EnTransito);
                            cout << "\n[OK] Estado 'En Tránsito' añadido al historial.\n";
                            break;
                        case 3:
                            historial.push(EstadoPaquete::Entregado);
                            cout << "\n[OK] Estado 'Entregado' añadido al historial.\n";
                            break;
                        case 4:
                            historial.push(EstadoPaquete::Cancelado);
                            cout << "\n[OK] Estado 'Cancelado' añadido al historial.\n";
                            break;
                        default:
                            cout << "\n[!] Opción de estado no válida.\n";
                            break;
                    }
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] Entrada inválida.\n";
                }
                pausar();
                break;
            }

            case 2: {
                if (historial.estaVacia()) {
                    cout << "\n[!] No hay estados para revertir.\n";
                } else {
                    EstadoPaquete estadoEliminadoEnum = historial.obtenerEstadoActual();
                    string removido = estadoATexto(estadoEliminadoEnum);

                    historial.pop();

                    cout << "\n[OK] Estado '" << removido << "' revertido exitosamente.\n";
                    cout << "Nuevo Estado Actual: " << estadoATexto(historial.obtenerEstadoActual()) << "\n";
                }
                pausar();
                break;
            }

            case 3: {
                cout << "\n====================================\n";
                cout << " ESTADO ACTUAL: " << estadoATexto(historial.obtenerEstadoActual()) << "\n";
                cout << "====================================\n";
                pausar();
                break;
            }

            case 4: {
                cout << "\n--- TRAZABILIDAD COMPLETA DEL PEDIDO #" << idBuscado << " ---\n";
                historial.mostrarHistorial();
                pausar();
                break;
            }

            case 5:
                cout << "\nRegresando al menú de módulos...\n";
                break;

            default:
                cout << "\n[!] Opción inválida. Intente de nuevo.\n";
                pausar();
                break;
        }

    } while (opcion != 5);
}

// Submenú de Inventario y Catálogo (Integración Árbol AVL + Árbol 2-3)
void menuInventario(CatalogoProductos& catalogo, InventarioProductos& inventario) {
    int opcion = 0;
    do {
        mostrarEncabezado();
        cout << "--- MÓDULO DE GESTIÓN DE PRODUCTOS Y BODEGA ---\n";
        cout << "1. Registrar / Dar de Alta Producto (Catálogo AVL + Inventario 2-3)\n";
        cout << "2. Consultar Ficha Comercial en Catálogo (Búsqueda AVL - O(log n))\n";
        cout << "3. Reabastecer Stock en Bodega (Modificación en Árbol 2-3)\n";
        cout << "4. Ver Reporte General de Inventario Físico (Inorden - Árbol 2-3)\n";
        cout << "5. Dar de Baja Producto del Catálogo (Eliminación AVL)\n";
        cout << "6. Volver al Menú Principal\n";
        cout << "---------------------------------------------------------------\n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[!] Entrada inválida. Ingrese un número.\n";
            pausar();
            continue;
        }

        switch (opcion) {
            case 1: {
                int id = 0, stock = 0;
                double precio = 0.0;
                string nombre;

                cout << "\n--- Registrar Nuevo Producto en el Sistema ---\n";
                cout << "Ingrese ID del Producto: ";
                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] ID inválido.\n";
                    pausar();
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer antes del getline
                cout << "Ingrese Nombre del Producto: ";
                getline(cin, nombre);

                cout << "Ingrese Precio ($): ";
                if (!(cin >> precio) || precio < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] Precio inválido.\n";
                    pausar();
                    break;
                }

                cout << "Ingrese Stock Inicial para Bodega: ";
                if (!(cin >> stock) || stock < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] Stock inválido.\n";
                    pausar();
                    break;
                }

                if (nombre.empty()) {
                    cout << "\n[!] Error: El nombre del producto no puede estar vacío.\n";
                } else {
                    // 1. SINCRONIZACIÓN: Inserción en Catálogo Comercial (Árbol AVL)
                    catalogo.insertarProducto(id, nombre, precio);

                    // 2. SINCRONIZACIÓN: Inserción en Inventario Físico (Árbol 2-3)
                    ProductoInventario prod(id, nombre, stock, precio);
                    inventario.insertar(prod);

                    cout << "\n[OK] Producto '" << nombre << "' (ID: " << id
                         << ") registrado exitosamente en el Catálogo (AVL) e Inventario (2-3).\n";
                }

                pausar();
                break;
            }

            case 2: {
                int idBuscado = 0;
                cout << "\n--- Consulta Comercial en Catálogo (Búsqueda AVL) ---\n";
                cout << "Ingrese ID del Producto a consultar: ";
                if (!(cin >> idBuscado)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] ID inválido.\n";
                    pausar();
                    break;
                }

                cout << "\n[INFO] Búsqueda binaria balanceada O(log n) en ejecucion...\n";
                NodoProducto* prodCat = catalogo.buscar(idBuscado);

                if (prodCat != nullptr) {
                    cout << "\n=========================================\n";
                    cout << "       FICHA DE PRODUCTO (CATÁLOGO)      \n";
                    cout << "=========================================\n";
                    cout << " ID:     " << prodCat->idProducto << "\n";
                    cout << " Nombre: " << prodCat->nombre << "\n";
                    cout << " Precio: $" << prodCat->precio << "\n";
                    cout << "=========================================\n";
                } else {
                    cout << "\n[X] Error: El producto #" << idBuscado << " no está registrado en el Catálogo.\n";
                }

                pausar();
                break;
            }

            case 3: {
                int idBuscado = 0, cantidadAgregar = 0;
                cout << "\n--- Reabastecimiento de Bodega (Árbol 2-3) ---\n";
                cout << "Ingrese ID del Producto a reabastecer: ";
                if (!(cin >> idBuscado)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] ID inválido.\n";
                    pausar();
                    break;
                }

                // Buscamos directamente en el Árbol 2-3
                ProductoInventario* prodInv = inventario.buscar(idBuscado);

                if (prodInv == nullptr) {
                    cout << "\n[X] Error: El producto #" << idBuscado << " no se encuentra en el Inventario.\n";
                } else {
                    cout << "  -> Producto encontrado: " << prodInv->nombre << " | Stock Actual: " << prodInv->stock << "\n";
                    cout << "Ingrese cantidad a añadir al stock: ";
                    if (!(cin >> cantidadAgregar) || cantidadAgregar <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\n[!] Cantidad inválida.\n";
                        pausar();
                        break;
                    }

                    prodInv->stock += cantidadAgregar;
                    cout << "\n[OK] Stock actualizado. Nuevo Total de " << prodInv->nombre
                         << ": " << prodInv->stock << " unidades.\n";
                }

                pausar();
                break;
            }

            case 4: {
                cout << "\n======================================================\n";
                cout << "   REPORTES DE INVENTARIO Y CATÁLOGO DISPONIBLES     \n";
                cout << "======================================================\n";
                cout << "\n--- Catálogo Comercial (Árbol AVL In-Order) ---\n";
                catalogo.mostrarCatalogo();

                cout << "\n--- Inventario Físico de Bodega (Árbol 2-3 In-Order) ---\n";
                inventario.mostrar();
                cout << "======================================================\n";

                pausar();
                break;
            }

            case 5: {
                int idEliminar = 0;
                cout << "\n--- Dar de Baja Producto del Catálogo (AVL) ---\n";
                cout << "Ingrese ID del Producto a dar de baja: ";
                if (!(cin >> idEliminar)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] ID inválido.\n";
                    pausar();
                    break;
                }

                if (catalogo.darDeBaja(idEliminar)) {
                    cout << "\n[OK] Producto #" << idEliminar << " ELIMINADO del Catálogo AVL y árbol rebalanceado.\n";
                } else {
                    cout << "\n[X] Error: No existe ningún producto en el catálogo con ID #" << idEliminar << ".\n";
                }

                pausar();
                break;
            }

            case 6:
                cout << "\nRegresando al menú principal...\n";
                break;

            default:
                cout << "\n[!] Opción inválida. Intente de nuevo.\n";
                pausar();
                break;
        }

    } while (opcion != 6);
}

// Submenú de Red de Distribución (Grafo)
void menuRutas(RutaDistribucion& redRutas) {
    int opcion = 0;
    do {
        mostrarEncabezado();
        cout << "--- MÓDULO DE RUTAS Y DISTRIBUCIÓN (GRAFO) ---\n";
        cout << "1. Registrar / Conectar Ciudades (Crea Nodos y Arista en un paso)\n";
        cout << "2. Ver Red de Distribución Completa (Lista de Adyacencia)\n";
        cout << "3. Calcular Rutas Mínimas y Cobertura (Algoritmo de Dijkstra)\n";
        cout << "4. Volver al Menú Principal\n";
        cout << "----------------------------------------------- \n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[!] Entrada inválida. Ingrese un número.\n";
            pausar();
            continue;
        }

        switch (opcion) {
            case 1: {
                string origen, destino;
                int distancia = 0;
                int tipoConexion = 1;

                cout << "\n--- Conectar Ciudades en la Red Logística ---\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese Ciudad Origen: ";
                getline(cin, origen);
                cout << "Ingrese Ciudad Destino: ";
                getline(cin, destino);

                if (origen.empty() || destino.empty()) {
                    cout << "\n[!] Error: Los nombres de las ciudades no pueden estar vacíos.\n";
                    pausar();
                    break;
                }

                if (origen == destino) {
                    cout << "\n[!] Error: La ciudad origen y destino deben ser diferentes.\n";
                    pausar();
                    break;
                }

                cout << "Ingrese Distancia (en KM): ";
                if (!(cin >> distancia) || distancia <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] Distancia inválida. Debe ser un número positivo en KM.\n";
                    pausar();
                    break;
                }

                cout << "\nSeleccione Tipo de Ruta:\n";
                cout << "1. Unidireccional (" << origen << " -> " << destino << ")\n";
                cout << "2. Bidireccional / Ida y Vuelta (" << origen << " <-> " << destino << ")\n";
                cout << "Opción: ";
                cin >> tipoConexion;

                // El método agregarRuta ya se encarga internamente de llamar a agregarCiudad
                // para ambas ciudades si no existen en el unordered_map.
                redRutas.agregarRuta(origen, destino, distancia);

                if (tipoConexion == 2) {
                    redRutas.agregarRuta(destino, origen, distancia);
                    cout << "\n[OK] Ruta bidireccional registrada con éxito entre '"
                         << origen << "' y '" << destino << "' (" << distancia << " KM).\n";
                } else {
                    cout << "\n[OK] Ruta unidireccional registrada desde '"
                         << origen << "' hacia '" << destino << "' (" << distancia << " KM).\n";
                }

                pausar();
                break;
            }

            case 2: {
                cout << "\n======================================================\n";
                cout << "        RED LOGÍSTICA DE DISTRIBUCIÓN ACTUAL          \n";
                cout << "======================================================\n\n";

                redRutas.mostrarRed();

                cout << "\n======================================================\n";
                pausar();
                break;
            }

            case 3: {
                string origen;
                cout << "\n--- Cálculo de Rutas Óptimas y Cobertura (Dijkstra) ---\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese la Ciudad de Salida / Centro de Acopio: ";
                getline(cin, origen);

                if (origen.empty()) {
                    cout << "\n[!] Error: Debe ingresar el nombre de una ciudad.\n";
                } else {
                    cout << "\n[INFO] Ejecutando Dijkstra para optimizar distancias en KM...\n";
                    redRutas.calcularRutaDijkstra(origen);
                }

                pausar();
                break;
            }

            case 4:
                cout << "\nRegresando al menú principal...\n";
                break;

            default:
                cout << "\n[!] Opción inválida. Intente de nuevo.\n";
                pausar();
                break;
        }

    } while (opcion != 4);
}
#endif //LOGIIX_MENUS_H
