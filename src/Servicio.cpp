
#include "../include/Servicio.hpp"

Servicio::Servicio(int id, const std::string &nombre, const std::string &descripcion, double costo)
    : id(id), nombre(nombre), descripcion(descripcion), costo(costo) {}

int Servicio::getId() const { return id; }

void Servicio::mostrarDetalles() const {
    std::cout << "ID del Servicio: " << id << "\n"
              << "Nombre: " << nombre << "\n"
              << "Descripción: " << descripcion << "\n"
              << "Costo: $" << costo << "\n";
}

void Servicio::guardarEnArchivo(const std::string &archivo) const {
    std::ofstream file(archivo, std::ios::app);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }
    file << "Servicio " << id << "\n"
         << "Nombre: " << nombre << "\n"
         << "Descripción: " << descripcion << "\n"
         << "Costo: " << costo << "\n\n";
}

void Servicio::eliminarServicioEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para eliminar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Servicio " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            for (int i = 0; i < 4; ++i) // Saltar las siguientes líneas del servicio
                getline(fileIn, linea);
            continue; // No escribir este servicio en el archivo temporal
        }
        fileOut << linea << '\n';
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (encontrado) {
        std::cout << "Servicio con ID " << id << " eliminado.\n";
    } else {
        std::cout << "Servicio con ID " << id << " no encontrado.\n";
    }
}

void Servicio::modificarServicioEnArchivo(const std::string &archivo) const {
    std::ifstream fileIn(archivo);
    std::ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        std::cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }
    std::string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Servicio " + std::to_string(id)) != std::string::npos) {
            encontrado = true;
            std::cout << "Servicio encontrado. Modifique los datos:\n";
            std::cout << "Ingrese nuevo nombre: ";
            std::string nuevoNombre;
            getline(std::cin, nuevoNombre);
            std::cout << "Ingrese nueva descripción: ";
            std::string nuevaDescripcion;
            getline(std::cin, nuevaDescripcion);
            std::cout << "Ingrese nuevo costo: ";
            double nuevoCosto;
            std::cin >> nuevoCosto;
            std::cin.ignore();
            fileOut << linea << '\n';
            fileOut << "Nombre: " << nuevoNombre << '\n';
            fileOut << "Descripción: " << nuevaDescripcion << '\n';
            fileOut << "Costo: " << nuevoCosto << '\n';
            getline(fileIn, linea); // Saltar línea de nombre original
            getline(fileIn, linea); // Saltar línea de descripción original
            getline(fileIn, linea); // Saltar línea de costo original
        } else {
            fileOut << linea << '\n';
        }
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (!encontrado) {
        std::cout << "Servicio con ID " << id << " no encontrado.\n";
    }
}