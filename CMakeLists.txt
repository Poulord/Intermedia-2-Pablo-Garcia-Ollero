cmake_minimum_required(VERSION 3.10)
project(HospitalManagement)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agregar la carpeta de encabezados
include_directories(include)

# Agregar el ejecutable y los archivos fuente
add_executable(HospitalManagement 
    src/main.cpp 
    src/Funciones.cpp 
    src/Servicio.cpp 
    src/Paciente.cpp 
    src/Medico.cpp 
    src/CitaMedica.cpp
)

# Opcional: Configuración de opciones de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")