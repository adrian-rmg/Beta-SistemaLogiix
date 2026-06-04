# Beta-SistemaLogiix
Análisis, diseño e implementación del **Sistema de Logística y Distribución "Logiix"**, una aplicación de consola robusta desarrollada en C++ para la gestión eficiente de envíos, rutas óptimas, usuarios e inventario.

---

## Integrantes del Proyecto
* Adrián Márquez - [@adrian-rmg](https://github.com/adrian-rmg)
* Greicel Salas - [@salasgreicel](https://github.com/salasgreicel)
* * Fernando Cedeño - [@cedenofernando](https://github.com/cedenofernando)



## Lenguaje y Herramientas
* Lenguaje Base: C++
* Entorno de Desarrollo (IDE's): CLion / VS Code
* Compilador: GCC
* Control de Versiones: Git & GitHub

---

## Arquitectura del Sistema y Estructura de Datos
El núcleo de Logiix está diseñado bajo el principio de eficiencia algorítmica. A continuación se detallan los módulos del sistema y las estructuras de datos avanzadas que resuelven cada problema:

### 1. Gestión de Usuarios y Autenticación
* **Tabla de Hash (Hashing):** Implementada para garantizar un inicio de sesión y autenticación de usuarios en tiempo constante $O(1)$.
* **Árbol AVL / Árbol B:** Utilizado para el almacenamiento indexado de usuarios por ID, permitiendo búsquedas rápidas y la generación de reportes administrativos ordenados alfabéticamente en tiempo $O(\log n)$.

### 2. Procesamiento de Pedidos y Envíos
* **Colas (Queues - FIFO):** Control de la "Cola de Espera" para pedidos entrantes, asegurando que el primer pedido en registrarse sea el primero en ser procesado.
* **Pilas (Stacks - LIFO):** Gestión del historial de estados de un paquete (ej: *En almacén* $\rightarrow$ *En camino* $\rightarrow$ *Entregado*), ideal para operaciones de rastreo y "deshacer" acciones.

### 3. Catálogo de Productos e Inventario
* **Árbol Binario de Búsqueda (ABB) / Árbol 2-3:** Estructura principal para el catálogo de productos disponibles, optimizando las operaciones de inserción, baja y modificación (CRUD).
* **Listas Enlazadas (Simples/Dobles):** Manejo del "carrito de compras" temporal del usuario y desglose de productos específicos contenidos dentro de un mismo paquete.

### 4. Rutas de Entrega y Ciudades
* **Grafos:** Representación matemática de la red de distribución. Las ciudades o almacenes actúan como **nodos**, mientras que las carreteras y rutas de envío son las **aristas** (cuyos pesos representan la distancia en km o el tiempo estimado de viaje).
