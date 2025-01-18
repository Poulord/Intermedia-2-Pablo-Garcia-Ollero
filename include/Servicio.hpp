#ifndef SERVICIO_HPP
#define SERVICIO_HPP

#include "../include/Funciones.hpp"

#include <iostream>
#include <string>
#include <fstream>

class Servicio {
private:
    int id;
    std::string nombre;
    std::string descripcion;
    double costo;

public:
    Servicio(int id, const std::string &nombre, const std::string &descripcion, double costo);
    int getId() const;
    void mostrarDetalles() const;
    void guardarEnArchivo(const std::string &archivo) const;
    void eliminarServicioEnArchivo(const std::string &archivo) const;
    void modificarServicioEnArchivo(const std::string &archivo) const; 
};

#endif // SERVICIO_HPP