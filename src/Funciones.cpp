#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"
#include "../include/CitaMedica.hpp"
#include "../include/Servicio.hpp"
#include "../include/Funciones.hpp"
#include <iostream>
#include <fstream>

void mostrarMenu() {
    std::cout << "=== Menú Principal ===\n"
              << "1. Modificar Datos\n"
              << "2. Agregar Datos\n"
              << "3. Eliminar Datos\n"
              << "4. Ver Datos\n"
              << "0. Salir\n"
              << "Seleccione una opción: ";
}

void modificarDatos() {
    int subOpcion;
    std::cout << "Seleccione una opción para modificar:\n"
              << "1. Modificar Paciente\n"
              << "2. Modificar Médico\n"
              << "3. Modificar Cita Médica\n"
              << "4. Modificar Servicio\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion) {
        case 1: {
            std::cout << "Ingrese el ID del paciente a modificar: ";
            int idPaciente;
            std::cin >> idPaciente;
            std::cin.ignore();
            Paciente paciente(idPaciente, "", 0, ""); // Crear objeto para llamar al método
            paciente.modificarPacienteEnArchivo("pacientes.txt");
            break;
        }
        case 2: {
            std::cout << "Ingrese el ID del médico a modificar: ";
            int idMedico;
            std::cin >> idMedico;
            std::cin.ignore();
            Medico medico(idMedico, "", "", true, 0); // Crear objeto para llamar al método
            medico.modificarMedicoEnArchivo("medicos.txt");
            break;
        }
        case 3: {
            std::cout << "Ingrese el ID de la cita a modificar: ";
            int idCita;
            std::cin >> idCita;
            std::cin.ignore();
            CitaMedica cita(idCita, "", 0, 0, 0); // Crear objeto para llamar al método
            cita.modificarCitaEnArchivo("citas.txt");
            break;
        }
        case 4: {
            std::cout << "Ingrese el ID del servicio a modificar: ";
            int idServicio;
            std::cin >> idServicio;
            std::cin.ignore();
            Servicio servicio(idServicio, "", "", 0.0); // Crear objeto para llamar al método
            servicio.modificarServicioEnArchivo("servicios.txt");
            break;
        }
        default:
            std::cout << "Opción no válida. Intente de nuevo.\n";
            break;
    }
}

void agregarDatos() {
    int subOpcion;
    std::cout << "Seleccione una opción para agregar:\n";
    std::cout << "1. Agregar Paciente\n"
              << "2. Agregar Médico\n"
              << "3. Agregar Cita Médica\n"
              << "4. Agregar Servicio\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion) {
        case 1: {
            int id, edad;
            std::string nombre, telefono, motivo, medico;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Ingrese nombre del paciente: ";
            getline(std::cin, nombre);
            std::cout << "Ingrese edad del paciente: ";
            std::cin >> edad;
            std::cin.ignore();
            std::cout << "Ingrese teléfono del paciente: ";
            getline(std::cin, telefono);
            std::cout << "Ingrese motivo de ingreso: ";
            getline(std::cin, motivo);
            std::cout << "Ingrese médico de cabecera: ";
            getline(std::cin, medico);
            Paciente nuevoPaciente(id, nombre, edad, telefono);
            nuevoPaciente.ingresarPaciente(motivo);
            nuevoPaciente.asignarMedicoCabecera(medico);
            nuevoPaciente.guardarEnArchivo("pacientes.txt");
            std::cout << "Paciente registrado exitosamente.\n";
            break;
        }
        case 2: {
            int id, aniosExperiencia;
            std::string nombre, especialidad;
            bool disponible;
            std::cout << "Ingrese ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Ingrese Nombre: ";
            getline(std::cin, nombre);
            std::cout << "Ingrese Especialidad: ";
            getline(std::cin, especialidad);
            std::cout << "Está disponible (1: Sí, 0: No): ";
            std::cin >> disponible;
            std::cout << "Ingrese Años de experiencia: ";
            std::cin >> aniosExperiencia;
            Medico nuevoMedico(id, nombre, especialidad, disponible, aniosExperiencia);
            nuevoMedico.guardarEnArchivo("medicos.txt");
            std::cout << "Médico registrado exitosamente.\n";
            break;
        }
        case 3: {
            int id, prioridad, idPaciente, idMedico;
            std::string fechaHora;
            std::cout << "Ingrese ID de la cita: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Ingrese fecha y hora de la cita: ";
            getline(std::cin, fechaHora);
            std::cout << "Ingrese prioridad (1: Alta, 2: Media, 3: Baja): ";
            std::cin >> prioridad;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> idPaciente;
            std::cout << "Ingrese ID del médico: ";
            std::cin >> idMedico;
            CitaMedica nuevaCita(id, fechaHora, prioridad, idPaciente, idMedico);
            nuevaCita.guardarEnArchivo("citas.txt");
            std::cout << "Cita médica registrada exitosamente.\n";
            break;
        }
        case 4: {
            int id;
            std::string nombre, descripcion;
            double costo;
            std::cout << "Ingrese ID del servicio: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Ingrese nombre del servicio: ";
            getline(std::cin, nombre);
            std::cout << "Ingrese descripción del servicio: ";
            getline(std::cin, descripcion);
            std::cout << "Ingrese costo del servicio: ";
            std::cin >> costo;
            Servicio nuevoServicio(id, nombre, descripcion, costo);
            nuevoServicio.guardarEnArchivo("servicios.txt");
            std::cout << "Servicio registrado exitosamente.\n";
            break;
        }
        default:
            std::cout << "Opción no válida. Intente de nuevo.\n";
            break;
    }
}

void eliminarDatos() {
    int subOpcion;
    std::cout << "Seleccione una opción para eliminar:\n"
              << "1. Eliminar Paciente\n"
              << "2. Eliminar Médico\n"
              << "3. Eliminar Cita Médica\n"
              << "4. Eliminar Servicio\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion) {
        case 1: {
            std::cout << "Ingrese el ID del paciente a eliminar: ";
            int idPaciente;
            std::cin >> idPaciente;
            std::cin.ignore();
            Paciente paciente(idPaciente, "", 0, ""); // Crear objeto para llamar al método
            paciente.eliminarPacienteEnArchivo("pacientes.txt");
            break;
        }
        case 2: {
            std::cout << "Ingrese el ID del médico a eliminar: ";
            int idMedico;
            std::cin >> idMedico;
            std::cin.ignore();
            Medico medico(idMedico, "", "", true, 0); // Crear objeto para llamar al método
            medico.eliminarMedicoEnArchivo("medicos.txt");
            break;
        }
        case 3: {
            std::cout << "Ingrese el ID de la cita a eliminar: ";
            int idCita;
            std::cin >> idCita;
            std::cin.ignore();
            CitaMedica cita(idCita, "", 0, 0, 0); // Crear objeto para llamar al método
            cita.eliminarCitaEnArchivo("citas.txt");
            break;
        }
        case 4: {
            std::cout << "Ingrese el ID del servicio a eliminar: ";
            int idServicio;
            std::cin >> idServicio;
            std::cin.ignore();
            Servicio servicio(idServicio, "", "", 0.0); // Crear objeto para llamar al método
            servicio.eliminarServicioEnArchivo("servicios.txt");
            break;
        }
        default:
            std::cout << "Opción no válida. Intente de nuevo.\n";
            break;
    }
}

void verDatos() {
    int subOpcion;
    std::cout << "Seleccione una opción para ver:\n"
              << "1. Ver Pacientes Registrados\n"
              << "2. Ver Médicos Registrados\n"
              << "3. Ver Citas Médicas\n"
              << "4. Ver Servicios\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion) {
        case 1:
            mostrarContenidoDesdeArchivo("pacientes.txt");
            break;
        case 2:
            mostrarContenidoDesdeArchivo("medicos.txt");
            break;
        case 3:
            mostrarContenidoDesdeArchivo("citas.txt");
            break;
        case 4:
            mostrarContenidoDesdeArchivo("servicios.txt");
            break;
        default:
            std::cout << "Opción no válida. Intente de nuevo.\n";
            break;
    }
}

void mostrarContenidoDesdeArchivo(const std::string &archivo) {
    std::ifstream file(archivo); // Abrir el archivo
    if (!file) { // Verificar si el archivo se abrió correctamente
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return; // Salir de la función si no se puede abrir el archivo
    }

    std::cout << "\n--- Contenido de " << archivo << " ---\n";
    std::string linea;
    while (getline(file, linea)) { // Leer línea por línea
        std::cout << linea << std::endl; // Mostrar cada línea en la consola
    }
    std::cout << "--------------------\n";

    file.close(); // Cerrar el archivo
}
