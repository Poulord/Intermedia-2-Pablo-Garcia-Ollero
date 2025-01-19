#ifndef CITAMEDICA_HPP
#define CITAMEDICA_HPP

#include "../include/Funciones.hpp"
#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"

#include <iostream>
#include <string>
#include <fstream>

class CitaMedica {
private:
    int id;
    std::string fechaHora;
    int prioridad;
    Paciente* paciente; // CHe implementado punteros para la busqueda de datos del id de paientes y medicos 
    Medico* medico;     

public:
    CitaMedica(int id, const std::string &fechaHora, int prioridad, Paciente* paciente, Medico* medico);
    void mostrarDetalles() const;
    void guardarEnArchivo(const std::string &archivo) const;
    void eliminarCitaEnArchivo(const std::string &archivo) const;
    void modificarCitaEnArchivo(const std::string &archivo) const;
};

#endif 