#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "../include/Funciones.hpp"
#include "../include/Servicio.hpp"

#include <iostream>
#include <string>
#include <vector>


class Paciente {
private:
    int id;
    std::string nombre;
    int edad;
    bool hospitalizado;
    std::string motivoIngreso;
    std::string telefono;
    std::string medicoCabecera;
    std::vector<Servicio> serviciosAsignados;

public:
    Paciente(int id, const std::string &nombre, int edad, const std::string &telefono);
    int getId() const;
    void mostrarDetalles() const;
    void ingresarPaciente(const std::string &motivo);
    void asignarMedicoCabecera(const std::string &medico);
    void asignarServicio(const Servicio &servicio);
    void guardarEnArchivo(const std::string &archivo) const;
    void eliminarPacienteEnArchivo(const std::string &archivo) const;
    void modificarPacienteEnArchivo(const std::string &archivo) const;
};

#endif // PACIENTE_HPP