#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"
#include "../include/CitaMedica.hpp"
#include "../include/Servicio.hpp"
#include "../include/Funciones.hpp"


Medico::Medico(int id, const std::string &nombre, const std::string &especialidad, bool disponible, int aniosExperiencia)
    : id(id), nombre(nombre), especialidad(especialidad), disponible(disponible), aniosExperiencia(aniosExperiencia) {}

int Medico::getId() const { return id; }

void Medico::mostrarDetalles() const {
    std::cout << "ID: " << id << "\n"
              << "Nombre: " << nombre << "\n"
              << "Especialidad: " << especialidad << "\n"
              << "Disponible: " << (disponible ? "Sí" : "No") << "\n"
              << "Años de experiencia: " << aniosExperiencia << "\n";
}

void Medico::guardarEnArchivo(const std::string &archivo) const {
    std::ofstream file(archivo, std::ios::app);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }
    file << "Médico " << id << "\n"
         << "Nombre: " << nombre << "\n"
         << "Especialidad: " << especialidad << "\n"
         << "Disponible: " << (disponible ? "Sí" : "No") << "\n"
         << "Años de experiencia: " << aniosExperiencia << "\n\n";
}

void Medico::eliminarMedicoEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para eliminar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Médico " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            for (int i = 0; i < 4; ++i) // Saltar las siguientes líneas del médico
                getline(fileIn, linea);
            continue; // No escribir este médico en el archivo temporal
        }
        fileOut << linea << '\n';
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (encontrado) {
        std::cout << "Médico con ID " << id << " eliminado.\n";
    } else {
        std::cout << "Médico con ID " << id << " no encontrado.\n";
    }
}

void Medico::modificarMedicoEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Médico " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            std::cout << "Médico encontrado. Modifique los datos:\n";
            std::cout << "Ingrese nueva especialidad: ";
            std::string nuevaEspecialidad;
            getline(std::cin, nuevaEspecialidad);
            std::cout << "¿Está disponible? (1: Sí, 0: No): ";
            bool nuevaDisponibilidad;
            std::cin >> nuevaDisponibilidad;
            std::cin.ignore();
            fileOut << linea << '\n';
            fileOut << "Especialidad: " << nuevaEspecialidad << '\n';
            fileOut << "Disponible: " << (nuevaDisponibilidad ? "Sí" : "No") << '\n';
            getline(fileIn, linea); // Saltar línea de especialidad original
            getline(fileIn, linea); // Saltar línea de disponibilidad original
        } else {
            fileOut << linea << '\n';
        }
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (!encontrado) {
        std::cout << "Médico con ID " << id << " no encontrado.\n";
    }
}