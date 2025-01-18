#ifndef MEDICO_HPP
#define MEDICO_HPP

#include "../include/Funciones.hpp"

#include <iostream>
#include <string>
#include <fstream>

class Medico {
private:
    int id;
    std::string nombre;
    std::string especialidad;
    bool disponible;
    int aniosExperiencia;

public:
    Medico(int id, const std::string &nombre, const std::string &especialidad, bool disponible, int aniosExperiencia);
    int getId() const;
    void mostrarDetalles() const;
    void guardarEnArchivo(const std::string &archivo) const;
    void eliminarMedicoEnArchivo(const std::string &archivo) const;
    void modificarMedicoEnArchivo(const std::string &archivo) const;
};

#endif // MEDICO_HPP