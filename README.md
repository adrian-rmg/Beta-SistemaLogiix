# Beta-SistemaLogiix
Análisis, diseño e implementación del **Sistema de Logística y Distribución "Logiix"**, una aplicación de consola robusta desarrollada en C++ para la gestión eficiente de envíos, rutas óptimas, usuarios e inventario.

---

## Integrantes del Proyecto
* Adrián Márquez - [@adrian-rmg](https://github.com/adrian-rmg)
* Greicel Salas - [@salasgreicel](https://github.com/salasgreicel)
* Fernando Cedeño - [@cedenofernando](https://github.com/cedenofernando)
* Jesus Romero - [@luluucreativo](https://github.com/luluucreativo)
* Andrés Mata - [andresmataromero-blip](https://github.com/andresmataromero-blip).
## Lenguaje y Herramientas
* Lenguaje Base: C++
* Entorno de Desarrollo (IDE's): CLion / VS Code
* Compilador: GCC
* Control de Versiones: Git & GitHub

---

### Arquitectura del Sistema y Estructura de Datos

El núcleo de Logiix está diseñado bajo el principio de eficiencia algorítmica y desacoplamiento modular:

1. **Gestión de Usuarios y Autenticación**
   * **Tabla Hash (`std::unordered_map`):** Garantiza la búsqueda, validación y registro de usuarios (Administrador, Repartidor, Cliente) en tiempo constante $O(1)$.

2. **Procesamiento de Pedidos y Trazabilidad**
   * **Colas (FIFO):** Control del flujo de pedidos en espera, garantizando atención por orden de llegada.
   * **Pilas (LIFO) + Mapeo Hash:** Gestión del historial de estados de envío por paquete (ej. *Registrado -> En Tránsito -> Entregado*), permitiendo operaciones de rastreo y reversión (*Pop*) asociadas a un ID de pedido.

3. **Catálogo de Productos e Inventario (Doble Estructura)**
   * **Árbol AVL:** Almacenamiento balanceado para el Catálogo Comercial, garantizando búsquedas rápidas $O(\log n)$ por ID de producto.
   * **Árbol 2-3:** Estructura multi-camino autosustentada para el reporte de Inventario Físico en Bodega y control masivo de stock mediante recorridos Inorden.

4. **Red de Distribución y Rutas de Entrega**
   * **Grafos (Lista de Adyacencia + Dijkstra):** Representación dinámica de la red logística donde las ciudades representan nodos y las carreteras aristas ponderadas (distancia en KM). Implementa el algoritmo de Dijkstra con cola de prioridad (*min-heap*) para el cálculo de rutas óptimas.
