#include <iostream>
#include <string>

class Paciente {
private:
    int id;
    std::string nombre;
    int edad;

public:
    // Constructor
    Paciente(int id, const std::string& nombre, int edad) : id(id), nombre(nombre), edad(edad) {}

    // Método para mostrar detalles del paciente
    void mostrarDetalles() const {
        std::cout << "ID: " << id << "\n"
                  << "Nombre: " << nombre << "\n"
                  << "Edad: " << edad << "\n";
    }

    // Método para actualizar el nombre del paciente
    void actualizarNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
    }

    // Método para actualizar la edad del paciente
    void actualizarEdad(int nuevaEdad) {
        edad = nuevaEdad;
    }

    // Método para buscar paciente por ID
    bool buscarPorID(int criterioID) const {
        return id == criterioID;
    }
};

int main() {
    // Crear un paciente de ejemplo
    Paciente paciente1(1, "Juan Perez", 30);

    // Mostrar detalles del paciente
    paciente1.mostrarDetalles();

    // Actualizar el nombre y la edad del paciente
    paciente1.actualizarNombre("Juan Gómez");
    paciente1.actualizarEdad(35);

    // Mostrar detalles actualizados del paciente
    std::cout << "\nDetalles actualizados:\n";
    paciente1.mostrarDetalles();

    // Buscar al paciente por ID
    int criterioID = 1;
    if (paciente1.buscarPorID(criterioID)) {
        std::cout << "\nPaciente encontrado con ID: " << criterioID << "\n";
    } else {
        std::cout << "\nNo se encontró ningún paciente con ID: " << criterioID << "\n";
    }

    return 0;
}

