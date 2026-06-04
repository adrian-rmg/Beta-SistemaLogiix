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
| Hashing | Módulo de usuarios | hash_function(), insert(), search_key() para validación de credenciales en O(1) | Desde cero |0
---
## 2. CRONOGRAMA TENTATIVO Y DIVISIÓN DE TAREAS
Dada la naturaleza compleja y la exigencia técnica del Sistema Logiix, el equipo ha definido una estructura de roles especializada para garantizar la eficiencia en el desarrollo, la calidad del código y el cumplimiento de los sprints.
* Adrián Márquez actúa como Desarrollador Principal (Lead Developer). Es el responsable de la arquitectura del sistema, la implementación de las estructuras de datos más críticas (Árboles AVL, 2-3, B, Grafos y Hashing), la integración de todos los módulos y la resolución de conflictos técnicos. Su experiencia y dedicación al proyecto permiten mantener un ritmo de desarrollo constante y una alta calidad en el código base.
* El resto de los integrantes (Andrés Mata, Fernando Cedeño, Greicel Salas, Jesús Romero) cumplen un rol dual de Analistas / QA y Desarrolladores de Soporte.
* * Analistas / QA: Participan activamente en la especificación de requisitos, la validación de casos de uso, la revisión de código y las pruebas unitarias y de integración de las estructuras asignadas a Adrián.
* * Desarrolladores de Soporte: Implementan estructuras de datos de menor complejidad (Pilas, Colas, Listas Enlazadas, Árbol Binario básico) bajo la supervisión del desarrollador principal. Estas tareas les permiten afianzar sus competencias en estructuras de datos sin comprometer la criticidad del sistema.
Este modelo de trabajo colaborativo (similar al de muchos equipos ágiles de software) asegura que cada miembro aporte valor según sus fortalezas, mientras que la responsabilidad final de la integración y el rendimiento recae en el perfil más técnico. Se ajusta además al cronograma de sprints, permitiendo entregas progresivas y una carga de trabajo balanceada en términos de esfuerzo académico.
### Sprint #1: Configuración Inicial 0
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
