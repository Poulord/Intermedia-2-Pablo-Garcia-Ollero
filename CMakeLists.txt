# CMakeLists.txt

# Establecer la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Establecer el nombre del proyecto
project(GestionHospitalaria)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agregar el ejecutable
add_executable(GestionHospitalaria pruebas2.0.cpp, main.cpp, medicos.cpp, pacientes.cpp, servicios.cpp, servicios.h, cita_media.cpp)

# add_executable(GestionHospitalaria main.cpp otros_archivos.cpp)