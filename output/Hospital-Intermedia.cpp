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

class Medico {
private:
    int id;
    std::string nombre;
    std::string especialidad;
    bool disponible;

public:
    // Constructor
    Medico(int id, const std::string& nombre, const std::string& especialidad, bool disponible)
        : id(id), nombre(nombre), especialidad(especialidad), disponible(disponible) {}

    // Método para mostrar detalles del médico
    void mostrarDetalles() const {
        std::cout << "ID: " << id << "\n"
                  << "Nombre: " << nombre << "\n"
                  << "Especialidad: " << especialidad << "\n"
                  << "Disponible: " << (disponible ? "Sí" : "No") << "\n";
    }

    // Método para actualizar la especialidad del médico
    void actualizarEspecialidad(const std::string& nuevaEspecialidad) {
        especialidad = nuevaEspecialidad;
    }

    // Método para cambiar la disponibilidad del médico
    void cambiarDisponibilidad(bool nuevaDisponibilidad) {
        disponible = nuevaDisponibilidad;
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

    // Crear un médico de ejemplo
    Medico medico1(101, "Dra. María López", "Cardiología", true);

    // Mostrar detalles del médico
    std::cout << "\nDetalles del médico:\n";
    medico1.mostrarDetalles();

    // Actualizar la especialidad del médico
    medico1.actualizarEspecialidad("Neurología");

    // Cambiar la disponibilidad del médico
    medico1.cambiarDisponibilidad(false);

    // Mostrar detalles actualizados del médico
    std::cout << "\nDetalles actualizados del médico:\n";
    medico1.mostrarDetalles();

    return 0;
}
