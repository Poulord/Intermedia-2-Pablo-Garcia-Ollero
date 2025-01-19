#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <string>
#include <vector>
#include <iostream>
#include <string>


#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"

class Paciente; 

void mostrarMenu();
void modificarDatos();
void agregarDatos();
void eliminarDatos();
void verDatos();
void mostrarContenidoDesdeArchivo(const std::string &archivo);

Paciente* buscarPacientePorId(int id, const std::string &archivo);
Medico* buscarMedicoPorId(int id, const std::string &archivo);
Servicio* buscarServicioPorId(int id, const std::string &archivo);

#endif 