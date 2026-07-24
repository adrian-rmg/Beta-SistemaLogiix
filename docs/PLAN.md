# PLAN DE ANÁLISIS, DISEÑO E IMPLEMENTACIÓN: SISTEMA LOGIIX 
Este documento detalla la planificación estratégica, la asignación de componentes técnicos y el cronograma general para el desarrollo del Sistema de Logística y Distribución **"Logiix"**. La arquitectura está guiada por la eficiencia algorítmica y el cumplimiento riguroso de las entregas académicas estructuradas en Sprints.
---
## 1. MATRIZ DE ESTRUCTURAS DE DATOS, CASOS DE USOS Y OPERACIONES (REFERENCIAL)
| Estructura de datos | ¿En qué parte del proyecto se usará? | ¿Qué operaciones específicas se necesitarán? | ¿Se implementará desde cero o se usará alguna biblioteca? |
| :--- | :--- | :--- | :--- |
| Pila | Módulo de envios | push(), pop(), top() | Desde cero |
| Cola | Módulo de pedidos | enqueue(), dequeue(), front() | Desde cero |
| Lista Enlazada | Módulo de inventario | insert_back(), remove(), clear(), recorrido secuencial de productos | Desde cero |
| Árbol Binario | Módulo de inventario | insert(), search() por código, remove(), recorridos | Desde cero |
| Árbol AVL | Módulo de usuarios | insert(), search(), rotaciones para auto-balanceo | Desde cero |
| Árbol 2-3 | Módulo de inventario | insert(), split() de nodos, search() balanceado en tiempo O(log n) | Desde cero |
| Árbol B | Módulo de usuarios | insert(), search(), manejo de páginas/nodos hijos de orden M | Desde cero |
| Grafo | Módulo de rutas | add_vertex(), add_edge(), algoritmo de Dijkstra o Floyd-Warshall para ruta óptima | Desde cero |
| Hashing | Módulo de usuarios | hash_function(), insert(), search_key() para validación de credenciales en O(1) | Desde cero |
---
## 2. CRONOGRAMA TENTATIVO Y DIVISIÓN DE TAREAS
Dada la naturaleza compleja y la exigencia técnica del Sistema Logiix, el equipo ha definido una estructura de roles especializada para garantizar la eficiencia en el desarrollo, la calidad del código y el cumplimiento de los sprints.
* Adrián Márquez actúa como Desarrollador Principal (Lead Developer). Es el responsable de la arquitectura del sistema, la implementación de las estructuras de datos más críticas (Árboles AVL, 2-3, B, Grafos y Hashing), la integración de todos los módulos y la resolución de conflictos técnicos. Su experiencia y dedicación al proyecto permiten mantener un ritmo de desarrollo constante y una alta calidad en el código base.
* El resto de los integrantes (Andrés Mata, Fernando Cedeño, Greicel Salas, Jesús Romero) cumplen un rol dual de Analistas / QA y Desarrolladores de Soporte.
  * Analistas / QA: Participan activamente en la especificación de requisitos, la validación de casos de uso, la revisión de código y las pruebas unitarias y de integración de las estructuras asignadas a Adrián.
  * Desarrolladores de Soporte: Implementan estructuras de datos de menor complejidad (Pilas, Colas, Listas Enlazadas, Árbol Binario básico) bajo la supervisión del desarrollador principal. Estas tareas les permiten afianzar sus competencias en estructuras de datos sin comprometer la criticidad del sistema.
Este modelo de trabajo colaborativo (similar al de muchos equipos ágiles de software) asegura que cada miembro aporte valor según sus fortalezas, mientras que la responsabilidad final de la integración y el rendimiento recae en el perfil más técnico. Se ajusta además al cronograma de sprints, permitiendo entregas progresivas y una carga de trabajo balanceada en términos de esfuerzo académico.
---
### Sprint #1: Configuración Inicial
* Fecha Tentativa de Entrega: 10/06
* Asignación: Adrián Márquez.
### Sprint #2: Pilas y Colals
* Fecha Tentativa de Entrega: 17/06
* Asignación: Andrés Mata, Adrián Márquez
### Sprint #3: Listas Enlazadas
* Fecha Tentativa de Entrega: 24/06
* Asignación: Fernando Cedeño, Adrián Márquez
### Sprint #4: Árboles Binarios y AVL
* Fecha Tentativa de Entrega: 01/07
* Asignación: Greicel Salas, Adrián Márquez
### Sprint #5: Árboles 2-3 y B
* Fecha Tentativa de Entrega: 08/07
* Asignación: Jesús Romero, Adrián Márquez
### Sprint #6: Grafos y Hashing
* Fecha Tentativa de Entrega: 15/07
* Asignación: Adrián Márquez
### Sprint #7: Integración y Entrega Final
* Fecha Tentativa de Entrega: 22/07
* Asignación: Todos

---

## 3. CHECKLIST DE CUMPLIMIENTO Y RESULTADOS FINALES

| Componente / Estructura | Planificado Inicialmente | Estado Final en Código | Observaciones y Desviaciones |
| :--- | :--- | :--- | :--- |
| **Pila (Stack)** | Módulo de envíos (Desde cero) | **Completado** | Integrada en `HistorialPaquete` mediante `std::stack` dentro de un mapa Hash. |
| **Cola (Queue)** | Módulo de pedidos (Desde cero) | **Completado** | Implementada en `ColaPedidos` (`std::queue`) para el flujo FIFO. |
| **Lista Enlazada** | Módulo de inventario | **Sustituido** | Se optó por estructuras arborescentes de mayor rendimiento ($O(\log n)$). |
| **Árbol Binario (ABB)** | Módulo de inventario | **Sustituido** | Reemplazado por **Árbol AVL** para garantizar auto-balanceo en el catálogo comercial. |
| **Árbol AVL** | Módulo de usuarios | **Reasignado** | Se migró al **Catálogo de Productos** (`CatalogoProductos`) para optimizar búsquedas por ID. |
| **Árbol 2-3** | Módulo de inventario | **Completado** | Implementado desde cero en `InventarioProductos.h` para balanceo multi-camino. |
| **Árbol B** | Módulo de usuarios | **Simplificado** | La gestión de usuarios se consolidó en la Tabla Hash para acceso directo $O(1)$. |
| **Grafo** | Módulo de rutas (Dijkstra) | **Completado** | Implementado en `RutaDistribucion.h` con lista de adyacencia y **Dijkstra** (Min-Heap). |
| **Hashing** | Módulo de usuarios | **Completado** | Implementado en `TablaUsuarios.h` (`std::unordered_map`) para autenticación $O(1)$. |

---

## 4. ANEXO DE DECISIONES Y AJUSTES DE ARQUITECTURA

Durante la fase de integración (Sprint #7), se tomaron decisiones de diseño de software para mejorar la mantenibilidad y estabilidad de la aplicación:

1. **Desacoplamiento UI / Lógica (Refactorización `Menus.h`):**
   * **Plan Original:** Lógica de presentación dispersa en `main.cpp` o en cada módulo.
   * **Ajuste Realizado:** Se centralizó la interfaz CLI en `Menus.h` y se mantuvo `main.cpp` como un orquestador limpio.

2. **Alineación de Hashing sobre Árbol B/AVL en Usuarios:**
   * **Plan Original:** Usar Árbol B y AVL para autenticar usuarios.
   * **Ajuste Realizado:** Se priorizó el uso de **Tabla Hash** (`unordered_map`) dado que el caso de uso principal (login) requiere una complejidad de $O(1)$ en lugar de $O(\log n)$.

3. **Evolución del Catálogo Físico (AVL + Árbol 2-3):**
   * **Plan Original:** Usar ABB básico y Listas Enlazadas para inventario.
   * **Ajuste Realizado:** Se implementaron **Árbol AVL** y **Árbol 2-3 desde cero**, garantizando balanceo estricto y eliminando la degradación de rendimiento de los ABB simples.

4. **Trazabilidad LIFO Desacoplada:**
   * **Plan Original:** Pila dependiente de la Cola de Pedidos.
   * **Ajuste Realizado:** Se independizó el historial en un mapa de Pilas (`std::unordered_map<int, HistorialPaquete>`), permitiendo consultar el rastreo de envíos procesados (`dequeue`) sin perder su historial.
