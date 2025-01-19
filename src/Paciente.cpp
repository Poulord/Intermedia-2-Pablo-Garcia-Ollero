#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"
#include "../include/Servicio.hpp"

Paciente::Paciente(int id, const std::string &nombre, int edad, const std::string &telefono)
    : id(id), nombre(nombre), edad(edad), hospitalizado(false), telefono(telefono), medicoCabecera("") {}

int Paciente::getId() const { return id; }


void Paciente::asignarMedicoCabecera(Medico* medico) {
    if (medico) {
        medicoCabecera = std::to_string(medico->getId()); // Guarda solo el ID del médico
    }
}

void Paciente::mostrarDetalles() const {
    std::cout << "ID: " << id << "\n"
              << "Nombre: " << nombre << "\n"
              << "Edad: " << edad << "\n"
              << "Teléfono: " << telefono << "\n"
              << "Hospitalizado: " << (hospitalizado ? "Sí" : "No") << "\n";
    if (hospitalizado) {
        std::cout << "Motivo de ingreso: " << motivoIngreso << "\n";
    }
    std::cout << "Médico de cabecera: " << (medicoCabecera.empty() ? "Ninguno" : medicoCabecera) << "\n";
    std::cout << "Servicios asignados:\n";
    for (const auto &servicio : serviciosAsignados) {
        std::cout << "Servicio ID: " << servicio.getId() << ", Nombre: " << servicio.getNombre() << std::endl;
        servicio.mostrarDetalles();
    }
}

void Paciente::ingresarPaciente(const std::string &motivo) {
    hospitalizado = true;
    motivoIngreso = motivo;
}


void Paciente::asignarServicio(const Servicio &servicio) {
    serviciosAsignados.push_back(servicio); 
}

void Paciente::guardarEnArchivo(const std::string &archivo) const {
    std::ofstream file(archivo, std::ios::app);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }
    file << "Paciente " << id << "\n"
         << "Nombre: " << nombre << "\n"
         << "Edad: " << edad << "\n"
         << "Teléfono: " << telefono << "\n"
         << "Hospitalizado: " << (hospitalizado ? "Sí" : "No") << "\n";
    if (hospitalizado) {
        file << "Motivo de ingreso: " << motivoIngreso << "\n";
    }
    file << "Médico de cabecera: " << ( medicoCabecera.empty() ? "Ninguno" : medicoCabecera) << "\n";

    // Guarda los servicios asignados
    file << "Servicios: ";
    for (const auto &servicio : serviciosAsignados) {
        file << servicio.getId() << " "; // Guarda solamente los Ids de los servicios
    }
    file << "\n\n";
}

void Paciente::eliminarPacienteEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para eliminar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Paciente " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            for (int i = 0; i < 6; ++i) 
                getline(fileIn, linea);
            continue; // No escribe este paciente en el archivo txt
        }
        fileOut << linea << '\n';
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (encontrado) {
        std::cout << "Paciente con ID " << id << " eliminado.\n";
    } else {
        std::cout << "Paciente con ID " << id << " no encontrado.\n";
    }
}


void Paciente::modificarPacienteEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Paciente " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            std::cout << "Paciente encontrado. Modifique los datos:\n";
            std::cout << "Ingrese nuevo nombre: ";
            std::string nuevoNombre;
            getline(std::cin, nuevoNombre);
            std::cout << "Ingrese nueva edad: ";
            int nuevaEdad;
            std::cin >> nuevaEdad;
            std::cin.ignore();
            std::cout << "Ingrese nuevo teléfono: ";
            std::string nuevoTelefono;
            getline(std::cin, nuevoTelefono);
            fileOut << linea << '\n';
            fileOut << "Nombre: " << nuevoNombre << '\n';
            fileOut << "Edad: " << nuevaEdad << '\n';
            fileOut << "Teléfono: " << nuevoTelefono << '\n';
            getline(fileIn, linea); 
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
        std::cout << "Paciente con ID " << id << " no encontrado.\n";
    }
}