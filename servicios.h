#ifndef SERVICIOS_H
#define SERVICIOS_H

#include <string>
#include <vector>
using namespace std;

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

//Clase Gestion de servicios
class GestionServicios {
private:
    vector<Servicio> servicios;

public:
    void agregarServicio(const Servicio &servicio);
    const vector<Servicio> &getServicios() const;
    void mostrarServicios() const;
    Servicio buscarServicioPorId(int id) const;
};

#endif // SERVICIOS_H
