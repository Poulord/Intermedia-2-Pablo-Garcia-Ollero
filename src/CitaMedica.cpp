
#include "../include/CitaMedica.hpp"

CitaMedica::CitaMedica(int id, const std::string &fechaHora, int prioridad, Paciente* paciente, Medico* medico)
    : id(id), fechaHora(fechaHora), prioridad(prioridad), paciente(paciente), medico(medico) {}

void CitaMedica::mostrarDetalles() const {
    std::cout << "ID de Cita: " << id << "\n"
              << "Fecha y Hora: " << fechaHora << "\n"
              << "Prioridad: " << (prioridad == 1 ? "Alta" : (prioridad == 2 ? "Media" : "Baja")) << "\n"
              << "Paciente: " << (paciente ? paciente->getId() : 0) << "\n"
              << "Médico: " << (medico ? medico->getId() : 0) << "\n";
}

void CitaMedica::guardarEnArchivo(const std::string &archivo) const {
    std::ofstream file(archivo, std::ios::app);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }
    file << "Cita " << id << "\n"
         << "Fecha y Hora: " << fechaHora << "\n"
         << "Prioridad: " << (prioridad == 1 ? "Alta" : (prioridad == 2 ? "Media" : "Baja")) << "\n"
         << "ID Paciente: " << (paciente ? paciente->getId() : 0) << "\n" 
         << "ID Médico: " << (medico ? medico->getId() : 0) << "\n\n"; 
}

void CitaMedica::eliminarCitaEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para eliminar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Cita " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            for (int i = 0; i < 4; ++i) 
                getline(fileIn, linea);
            continue; 
        }
        fileOut << linea << '\n';
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (encontrado) {
        std::cout << "Cita con ID " << id << " eliminada.\n";
    } else {
        std::cout << "Cita con ID " << id << " no encontrada.\n";
    }
}

void CitaMedica::modificarCitaEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Cita " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            std::cout << "Cita encontrada. Modifique los datos:\n";
            std::cout << "Ingrese nueva fecha y hora: ";
            std::string nuevaFechaHora;
            getline(std::cin, nuevaFechaHora);
            std::cout << "Ingrese nueva prioridad (1: Alta, 2: Media, 3: Baja): ";
            int nuevaPrioridad;
            std::cin >> nuevaPrioridad;
            std::cin.ignore();
            fileOut << linea << '\n';
            fileOut << "Fecha y Hora: " << nuevaFechaHora << '\n';
            fileOut << "Prioridad: " << (nuevaPrioridad == 1 ? "Alta" : (nuevaPrioridad == 2 ? "Media" : "Baja")) << '\n';
            getline(fileIn, linea); 
            getline(fileIn, linea); 
        } else {
            fileOut << linea << '\n';
        }
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (!encontrado) {
        std::cout << "Cita con ID " << id << " no encontrada.\n";
    }
}