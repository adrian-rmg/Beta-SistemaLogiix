# 📝 Justificación Técnica de Selección y Omisión de Estructuras

Durante el desarrollo del sistema **LOGIIX**, se evaluaron las distintas estructuras de datos contempladas en el plan académico. En el proceso de integración final (Sprint 7), se tomaron decisiones de diseño algorítmico fundamentadas en la eficiencia, el mantenimiento y la adecuación al caso de uso real.

A continuación se justifican las omisiones y sustituciones de estructuras específicas:

---

### 1. Sustitución de Árbol B por Tabla Hash (`std::unordered_map`) en Usuarios
* **Estructura en Plan Inicial:** Árbol B.
* **Estructura Final Implementada:** Tabla Hash (`TablaUsuarios.h`).
* **Justificación:** Los Árboles B están diseñados principalmente para optimizar lecturas/escrituras masivas en memoria secundaria (discos duros/bases de datos). Dado que la gestión de usuarios en LOGIIX opera totalmente en memoria RAM y requiere validaciones instantáneas de credenciales al iniciar sesión, la Tabla Hash ofrece una complejidad de tiempo constante de **O(1)**, superando la complejidad de **O(log_M n)** que exigiría un Árbol B.

---

### 2. Sustitución de Árbol Binario de Búsqueda (ABB) por Árbol AVL
* **Estructura en Plan Inicial:** ABB Estándar.
* **Estructura Final Implementada:** Árbol AVL (`CatalogoProductos.h`).
* **Justificación:** Un ABB convencional presenta el riesgo de degenerar en una lista enlazada $O(n)$ si los datos se insertan de forma ordenada (por ejemplo, IDs correlativos de productos). Para garantizar búsquedas, inserciones y eliminaciones en tiempo logarítmico **O(log n)** en el peor caso, se implementó un **Árbol AVL** con auto-balanceo mediante rotaciones simples y dobles.

---

### 3. Sustitución de Listas Enlazadas por Estructuras Arborescentes en Inventario
* **Estructura en Plan Inicial:** Lista Enlazada Simple/Doble para Inventario.
* **Estructura Final Implementada:** Árbol 2-3 (`InventarioProductos.h`).
* **Justificación:** Las Listas Enlazadas requieren recorridos secuenciales de complejidad **O(n)** para la localización de un ítem, lo cual resulta ineficiente para inventarios con volúmenes altos de artículos. Al migrar el control físico a un **Árbol 2-3**, las operaciones de búsqueda y actualización de stock se reducen a **O(log n)**, manteniendo el árbol perfectamente balanceado de forma ascendente mediante división de nodos (*split*).

---

### 4. Integración de la Pila LIFO en Mapeo Hash
* **Estructura en Plan Inicial:** Pila aislada o acoplada secuencialmente a la Cola.
* **Estructura Final Implementada:** Mapeo de Pilas por ID de Paquete (`std::unordered_map<int, HistorialPaquete>`).
* **Justificación:** Una Pila única para todos los paquetes mezclaría los estados de envíos distintos. Al estructurar un mapa de Pilas indexado por la clave del paquete, el sistema permite que cada paquete mantenga su propio historial LIFO independiente, optimizando la consulta individual en O(1).
