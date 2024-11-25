#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Necesario para std::find y std::remove

using namespace std;

class Paciente {
private:
    int id;
    std::string nombre;
    int edad;
    bool hospitalizado;
    std::string motivoIngreso;
    std::string telefono;
    std::string medicoCabecera;

public:
    Paciente(int id, const std::string& nombre, int edad, const std::string& telefono)
        : id(id), nombre(nombre), edad(edad), hospitalizado(false), telefono(telefono), medicoCabecera("") {}

    void mostrarDetalles() const {
        cout << "ID: " << id << "\n"
             << "Nombre: " << nombre << "\n"
             << "Edad: " << edad << "\n"
             << "Teléfono: " << telefono << "\n"
             << "Hospitalizado: " << (hospitalizado ? "Sí" : "No") << "\n";
        if (hospitalizado) {
            cout << "Motivo de ingreso: " << motivoIngreso << "\n";
        }
        cout << "Médico de cabecera: " << (medicoCabecera.empty() ? "Ninguno" : medicoCabecera) << "\n";
    }

    void actualizarNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
    }

    void actualizarEdad(int nuevaEdad) {
        edad = nuevaEdad;
    }

    void asignarMedicoCabecera(const std::string& medico) {
        medicoCabecera = medico;
    }

    void ingresarPaciente(const std::string& motivo) {
        hospitalizado = true;
        motivoIngreso = motivo;
    }

    void darAlta() {
        hospitalizado = false;
        motivoIngreso = "";
    }

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
    int aniosExperiencia;
    std::string telefono;
    std::vector<int> pacientesActuales;

public:
    Medico(int id, const std::string& nombre, const std::string& especialidad, bool disponible, int aniosExperiencia, const std::string& telefono)
        : id(id), nombre(nombre), especialidad(especialidad), disponible(disponible), aniosExperiencia(aniosExperiencia), telefono(telefono) {}

    void mostrarDetalles() const {
        cout << "ID: " << id << "\n"
             << "Nombre: " << nombre << "\n"
             << "Especialidad: " << especialidad << "\n"
             << "Disponible: " << (disponible ? "Sí" : "No") << "\n"
             << "Años de experiencia: " << aniosExperiencia << "\n"
             << "Teléfono: " << telefono << "\n"
             << "Pacientes actuales: " << pacientesActuales.size() << "\n";
    }

    void actualizarEspecialidad(const std::string& nuevaEspecialidad) {
        especialidad = nuevaEspecialidad;
    }

    void cambiarDisponibilidad(bool nuevaDisponibilidad) {
        disponible = nuevaDisponibilidad;
    }

    void asignarPaciente(int pacienteID) {
        pacientesActuales.push_back(pacienteID);
    }

    void eliminarPaciente(int pacienteID) {
        auto it = std::find(pacientesActuales.begin(), pacientesActuales.end(), pacienteID);
        if (it != pacientesActuales.end()) {
            pacientesActuales.erase(it);
        } else {
            cout << "El paciente con ID " << pacienteID << " no está asignado a este médico.\n";
        }
    }
};

int main() {
    Paciente paciente1(1, "Juan Perez", 30, "123-456-789");
    paciente1.mostrarDetalles();

    paciente1.actualizarNombre("Juan Gómez");
    paciente1.actualizarEdad(35);
    paciente1.ingresarPaciente("Neumonía");
    paciente1.asignarMedicoCabecera("Dra. María López");

    cout << "\nDetalles actualizados:\n";
    paciente1.mostrarDetalles();

    Medico medico1(101, "Dra. María López", "Cardiología", true, 15, "987-654-321");
    medico1.mostrarDetalles();

    medico1.actualizarEspecialidad("Neurología");
    medico1.cambiarDisponibilidad(false);
    medico1.asignarPaciente(1);

    cout << "\nDetalles actualizados del médico:\n";
    medico1.mostrarDetalles();

    medico1.eliminarPaciente(1);
    cout << "\nDetalles del médico después de eliminar paciente:\n";
    medico1.mostrarDetalles();

    return 0;
}
