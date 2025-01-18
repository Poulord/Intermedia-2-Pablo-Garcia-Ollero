#ifndef CITAMEDICA_HPP
#define CITAMEDICA_HPP

#include "../include/Funciones.hpp"

#include <iostream>
#include <string>
#include <fstream>

class CitaMedica {
private:
    int id;
    std::string fechaHora;
    int prioridad;
    int idPaciente;
    int idMedico;

public:
    CitaMedica(int id, const std::string &fechaHora, int prioridad, int idPaciente, int idMedico);
    void mostrarDetalles() const;
    void guardarEnArchivo(const std::string &archivo) const;
    void eliminarCitaEnArchivo(const std::string &archivo) const;
    void modificarCitaEnArchivo(const std::string &archivo) const;
};

#endif // CITAMEDICA_HPP