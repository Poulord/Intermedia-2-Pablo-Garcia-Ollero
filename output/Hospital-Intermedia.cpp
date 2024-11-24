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
};

int main() {
    // Paciente de ejemplo
    Paciente paciente1(1, "Pablo Garcia Ollero", 19);

    // Detalles del paciente
    paciente1.mostrarDetalles();

    return 0;
}
