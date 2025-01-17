#include "Servicios.hpp"
#include <iostream>
#include <stdexcept>
#ifndef SERVICIOS_H
#define SERVICIOS_
#endif // SERVICIOS_H

#include <string>
#include <vector>
using namespace std;

Servicio::Servicio(int id, const string &descripcion, double precio)
    : id(id), descripcion(descripcion), precio(precio) {}

int Servicio::getId() const {
    return id;
}

string Servicio::getDescripcion() const {
    return descripcion;
}

double Servicio::getPrecio() const {
    return precio;
}

void Servicio::mostrarDetalles() const {
    cout << "ID: " << id << ", Descripción: " << descripcion << ", Precio: " << precio << " euros\n";
}

// Métodos de GestionServicios
void GestionServicios::agregarServicio(const Servicio &servicio) {
    servicios.push_back(servicio);
}

const vector<Servicio> &GestionServicios::getServicios() const {
    return servicios;
}

void GestionServicios::mostrarServicios() const {
    if (servicios.empty()) {
        cout << "No hay servicios disponibles.\n";
        return;
    }
    for (const auto &servicio : servicios) {
        servicio.mostrarDetalles();
    }
}

Servicio GestionServicios::buscarServicioPorId(int id) const {
    for (const auto &servicio : servicios) {
        if (servicio.getId() == id) {
            return servicio;
        }
    }
    throw invalid_argument("No se encontró el servicio con el ID proporcionado.");
}

// Función para inicializar los servicios
void inicializarServicios(GestionServicios &gestion) {
    gestion.agregarServicio(Servicio(1, "Quimioterapia", 0.0));
    gestion.agregarServicio(Servicio(2, "Asistencia presencial en casa", 20.0));
    gestion.agregarServicio(Servicio(3, "Llevar medicamentos a casa", 30.0));
}



class Servicio {
private:
    int id;
    string descripcion;
    double precio;

public:
    Servicio(int id, const string &descripcion, double precio);
    int getId() const;
    string getDescripcion() const;
    double getPrecio() const;
    void mostrarDetalles() const;
};

// Clase Gestion de servicios
class GestionServicios {
private:
    vector<Servicio> servicios;

public:
    void agregarServicio(const Servicio &servicio);
    const vector<Servicio> &getServicios() const;
    void mostrarServicios() const;
    Servicio buscarServicioPorId(int id) const;
};

// Función para inicializar los servicios
void inicializarServicios(GestionServicios &gestion);




