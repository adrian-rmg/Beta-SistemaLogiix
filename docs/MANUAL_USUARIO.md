# 📖 Manual de Usuario - Sistema Logístico LOGIIX

¡Bienvenido al sistema **LOGIIX**! Este manual contiene la información necesaria para preparar el entorno de ejecución, compilar el código fuente y operar la interfaz de consola del sistema.

---

## 1. Requisitos del Sistema

Para compilar y ejecutar **LOGIIX** correctamente, tu equipo debe contar con las siguientes herramientas:

* **Lenguaje:** C++ (Estándar C++17 o superior; el proyecto está configurado para C++17 en el `CMakeLists.txt`).
* **Compilador Recomendado:** GCC (g++) v7.0+, Clang o MSVC.
* **Entornos de Desarrollo Probados:** CLion, VS Code y terminal nativa (Linux/macOS/Windows PowerShell).
* **Dependencias Externas:** Ninguna. El proyecto utiliza exclusivamente la **Biblioteca Estándar de C++ (STL)**.

---

## 2. Instrucciones de Compilación y Ejecución

### Opción A: Desde Terminal con GCC / g++

1. **Clonar o descargar el repositorio:**
   ```bash
   git clone https://github.com/adrian-rmg/Beta-SistemaLogiix.git
   cd Beta-SistemaLogiix
   ```

2. **Compilar todos los archivos fuentes:**
   ```bash
   g++ -std=c++17 -Wall src/main.cpp -I include/ -o logiix
   ```

3. **Ejecutar la aplicación:**
   - En Linux / macOS:
     ```bash
     ./logiix
     ```
   - En Windows (PowerShell / CMD):
     ```dos
     logiix.exe
     ```

### Opción B: Usando CMake (recomendado para IDEs)

El proyecto incluye un archivo `CMakeLists.txt` que facilita la compilación. Puedes generar los binarios con:

```bash
mkdir build && cd build
cmake ..
make
```

El ejecutable `Logiix` (o `Logiix.exe` en Windows) se generará en la carpeta `build`.

### Opción C: Desde IDEs (CLion / VS Code)

- **CLion:** Abre la carpeta raíz del proyecto. CLion detectará automáticamente el `CMakeLists.txt`. Haz clic en **Run** (Ctrl + R / Shift + F10).
- **VS Code:** Instala la extensión **C/C++** o **Code Runner**, abre `src/main.cpp` y presiona `F5` para iniciar el depurador/ejecutor.

---

## 3. Guía de Operación y Menú Principal

Al iniciar la aplicación, serás recibido por la CLI del sistema con **6 módulos principales**:

```
==========================================================
          SISTEMA LOGISTICO Y DE DISTRIBUCION LOGIIX     
==========================================================
SELECCIONE EL MÓDULO A GESTIONAR:

1. Módulo de Usuarios y Autenticación (Tabla Hash)
2. Módulo de Pedidos en Espera (Cola - FIFO)
3. Módulo de Rastreo de Envíos (Pila - LIFO)
4. Módulo de Catálogo e Inventario (Árboles AVL / 2-3)
5. Módulo de Red de Distribución (Grafo)
6. Salir del Sistema

Ingrese su opción (1-6): 
```

### Descripción de Módulos

| Módulo | Descripción |
|--------|-------------|
| **1 - Usuarios y Autenticación** (TablaUsuarios) | Permite registrar usuarios asignándoles un ID único, nombre y rol (Administrador, Cliente, Repartidor). Valida credenciales en tiempo constante O(1). |
| **2 - Pedidos en Espera** (ColaPedidos) | Registra los envíos solicitados por los clientes en una Cola FIFO. Procesa las entregas respetando de forma estricta el orden de llegada. |
| **3 - Rastreo de Envíos** (HistorialPaquete) | Permite consultar la Pila LIFO de cambios de estado de un pedido (ej. *En Almacén → En Tránsito → Entregado*). Permite revertir (Pop) el último estado registrado en caso de correcciones. |
| **4 - Catálogo e Inventario** (CatalogoProductos / InventarioProductos) | Consulta comercial e inventario físico estructurado en árboles AVL y Árbol 2-3. Muestra reportes e inorden del stock disponible. |
| **5 - Red de Distribución** (RutaDistribucion) | Muestra las ciudades y carreteras integradas en el Grafo. Ejecuta el Algoritmo de Dijkstra para simular la cobertura desde un origen dado, hallando la ruta más corta hacia todos los nodos restantes. |
| **6 - Salir** | Finaliza la sesión del programa de forma limpia. |

---

## 4. Ejemplos de Uso

### Ejemplo 1: Registro y Conexión de dos Ciudades

```
>>> Módulo seleccionado: 5
--- MÓDULO DE RUTAS Y DISTRIBUCIÓN (GRAFO) ---
1. Registrar / Conectar Ciudades (Crea Nodos y Arista en un paso)
2. Ver Red de Distribución Completa (Lista de Adyacencia)
3. Calcular Rutas Mínimas y Cobertura (Algoritmo de Dijkstra)
4. Volver al Menú Principal
----------------------------------------------- 
Seleccione una opción: 
>>> Opción seleccionada: 1

--- Conectar Ciudades en la Red Logística ---
Ingrese Ciudad Origen: 
>>> Maturín

Ingrese Ciudad Destino: 
>>> Caracas

Ingrese Distancia (en KM): 
>>> 500

Seleccione Tipo de Ruta:
1. Unidireccional (Maturín -> Caracas)
2. Bidireccional / Ida y Vuelta (Maturín <-> Caracas)
Opción:
>>> Opción seleccionada: 2

[OK] Ruta bidireccional registrada con éxito entre 'Maturín' y 'Caracas' (500 KM).
```

### Ejemplo 2: Dar de Alta un Producto
```
>>> Módulo seleccionado: 4
--- MÓDULO DE GESTIÓN DE PRODUCTOS Y BODEGA ---
1. Registrar / Dar de Alta Producto (Catálogo AVL + Inventario 2-3)
2. Consultar Ficha Comercial en Catálogo (Búsqueda AVL - O(log n))
3. Reabastecer Stock en Bodega (Modificación en Árbol 2-3)
4. Ver Reporte General de Inventario Físico (Inorden - Árbol 2-3)
5. Dar de Baja Producto del Catálogo (Eliminación AVL)
6. Volver al Menú Principal
-----------------------------------------------
Seleccione una opción:
>>> Opción seleccionada: 1

--- Registrar Nuevo Producto en el Sistema ---
Ingrese ID del Producto: 
>>> 101

Ingrese Nombre del Producto: 
>>> Caja de Cartón Reforzada (Grande)

Ingrese Precio ($): 
>>> 2.50

Ingrese Stock Inicial para Bodega: 
>>> 150

[OK] Producto 'Caja de Cartón Reforzada (Grande)' (ID: 101) registrado exitosamente en el Catálogo (AVL) e Inventario (2-3).
```
---

## 5. Documentación Técnica de Estructuras de Datos

A continuación se detalla la correspondencia entre las estructuras de datos implementadas en el sistema y sus respectivos archivos fuente de soporte:

| Estructura de Datos | Archivo del Proyecto | Caso de Uso en LOGIIX | Complejidad Temporal |
| :--- | :--- | :--- | :--- |
| **Tabla Hash** | `include/TablaUsuarios.h` | Búsqueda y autenticación directa de usuarios por ID. | O(1) promedio |
| **Cola (FIFO)** | `include/ColaPedidos.h` | Control del flujo de pedidos pendientes por despachar. | O(1) inserción/remoción |
| **Pila (LIFO)** | `include/HistorialPaquete.h` | Trazabilidad de estados de envío por paquete. | O(1) push/pop |
| **Árbol AVL** | `include/CatalogoProductos.h` | Búsqueda y balanceo automático del catálogo comercial. | O(log n) |
| **Árbol 2-3** | `include/InventarioProductos.h` | Gestión multi-camino de existencias masivas de almacén. | O(log n) |
| **Grafo + Dijkstra** | `include/RutaDistribucion.h` | Red de ciudades/rutas y algoritmo de camino mínimo. | O((V + E)log V) |

---

## 6. Enlaces y Referencias

- **Repositorio oficial:** [Beta-SistemaLogiix](https://github.com/adrian-rmg/Beta-SistemaLogiix/)
- **Archivo de configuración CMake:** [`CMakeLists.txt`](https://github.com/adrian-rmg/Beta-SistemaLogiix/blob/main/CMakeLists.txt) (C++17, inclusión automática de cabeceras)

---

*¡Gracias por usar LOGIIX! Para cualquier duda o sugerencia, no dudes en contactar al equipo de desarrollo.*
