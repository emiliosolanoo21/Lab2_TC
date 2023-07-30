# Establecer la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.7)

# Definir el nombre del proyecto y el lenguaje utilizado
project(MiProyecto CXX)

# Agregar los archivos fuente de tu proyecto
# Aquí, simplemente se enumeran los archivos fuente manualmente.
# En proyectos más grandes, es común usar variables o funciones para facilitar la gestión.
set(SOURCES
    main.cpp
)

# Agregar un ejecutable usando los archivos fuente enumerados
add_executable(${PROJECT_NAME} ${SOURCES})
