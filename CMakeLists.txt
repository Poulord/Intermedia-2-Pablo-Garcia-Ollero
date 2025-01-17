cmake_minimum_required(VERSION 3.6)

project(Pruebas CMAKE LIST)

# Especificación de C++ estándar
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Para evitar extensiones específicas del compilador
set(CMAKE_CXX_COMPILER "g++") # clang++/g++/icx/cl
#set(CMAKE_CXX_COMPILER_ID "")
#set(CMAKE_AR "llvm-ar")
#set(CMAKE_RANLIB "llvm-ranlib")

# Configuración de compilación (Debug/Release)
#set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build: Debug or Release")
set(CMAKE_BUILD_TYPE Debug)

# Configuración específica del compilador
if (CMAKE_CXX_COMPILER STREQUAL "g++")
    add_compile_options(
        "$<$<CONFIG:Debug>:-Wpedantic;-Wall;-Wextra;-Wconversion;-Wshadow;-Wcast-qual;-Wwrite-strings;-DDEBUG>"
        "$<$<CONFIG:Release>:-pedantic;-Wall;-O3>"
    )

# Verificar compilador activo

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

# Configuración del ejecutable
add_executable(MiEjecutable DE PRUEBA ${SOURCES})

# Directorios de encabezados
target_include_directories(AB FINAL PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Directorio de salida
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Instalación
install(TARGETS AB FINAL RUNTIME DESTINATION bin)


