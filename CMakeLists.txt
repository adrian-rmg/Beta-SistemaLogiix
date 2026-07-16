cmake_minimum_required(VERSION 3.20)
project(Logiix CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Logiix
        src/main.cpp
        include/ColaPedidos.h
        include/HistorialPaquete.h
        include/ListaProductos.h
        include/CatalogoProductos.h
        include/InventarioProductos.h
        include/RutaDistribucion.h
        include/TablaUsuarios.h
)
