#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Necesario para std::find y std::remove

using namespace std;

class Paciente {
private:
    int id;
    string nombre;
    int edad;
    bool hospitalizado;
    string motivoIngreso;
    string telefono;
    string medicoCabecera;

public:
    Paciente(int id, const string& nombre, int edad, const string& telefono)
        : id(id), nombre(nombre), edad(edad), hospitalizado(false), telefono(telefono), medicoCabecera("") {}

    int getId() const { return id; }

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

    void ingresarPaciente(const string& motivo) {
        hospitalizado = true;
        motivoIngreso = motivo;
    }

    void asignarMedicoCabecera(const string& medico) {
        medicoCabecera = medico;
    }
};

class Medico {
private:
    int id;
    string nombre;
    string especialidad;
    bool disponible;
    int aniosExperiencia;

public:
    Medico(int id, const string& nombre, const string& especialidad, bool disponible, int aniosExperiencia)
        : id(id), nombre(nombre), especialidad(especialidad), disponible(disponible), aniosExperiencia(aniosExperiencia) {}

    int getId() const { return id; }

    void mostrarDetalles() const {
        cout << "ID: " << id << "\n"
             << "Nombre: " << nombre << "\n"
             << "Especialidad: " << especialidad << "\n"
             << "Disponible: " << (disponible ? "Sí" : "No") << "\n"
             << "Años de experiencia: " << aniosExperiencia << "\n";
    }
};

class CitaMedica {
private:
    int id;
    string fechaHora;
    int prioridad;
    int idPaciente;
    int idMedico;

public:
    CitaMedica(int id, const string& fechaHora, int prioridad, int idPaciente, int idMedico)
        : id(id), fechaHora(fechaHora), prioridad(prioridad), idPaciente(idPaciente), idMedico(idMedico) {}

    void mostrarDetalles() const {
        cout << "ID Cita: " << id << "\n"
             << "Fecha y Hora: " << fechaHora << "\n"
             << "Prioridad: " << prioridad << "\n"
             << "ID Paciente: " << idPaciente << "\n"
             << "ID Médico: " << idMedico << "\n";
    }

    int getIdPaciente() const { return idPaciente; }
    int getIdMedico() const { return idMedico; }
};

void mostrarMenu() {
    cout << "\n--- Menu Principal ---\n";
    cout << "1. Agregar paciente\n";
    cout << "2. Ver pacientes registrados\n";
    cout << "3. Agregar médico\n";
    cout << "4. Ver médicos registrados\n";
    cout << "5. Agregar cita médica\n";
    cout << "6. Ver citas médicas\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<CitaMedica> citas;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        if (opcion == 1) {
            // Agregar un paciente
            int id, edad;
            string nombre, telefono, motivo, medico;

            cout << "Ingrese ID del paciente: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nombre del paciente: ";
            getline(cin, nombre);
            cout << "Ingrese edad del paciente: ";
            cin >> edad;
            cin.ignore();
            cout << "Ingrese teléfono del paciente: ";
            getline(cin, telefono);
            cout << "Ingrese motivo de ingreso: ";
            getline(cin, motivo);
            cout << "Ingrese médico de cabecera: ";
            getline(cin, medico);

            Paciente nuevoPaciente (id, nombre, edad, telefono);
            nuevoPaciente.ingresarPaciente(motivo);
            nuevoPaciente.asignarMedicoCabecera(medico);
            pacientes.push_back(nuevoPaciente);

            cout << "Paciente registrado exitosamente.\n";
        } else if (opcion == 2) {
            // Ver pacientes registrados
            if (pacientes.empty()) {
                cout << "No hay pacientes registrados.\n";
            } else {
                cout << "\n--- Lista de Pacientes ---\n";
                for (const auto& paciente : pacientes) {
                    paciente.mostrarDetalles();
                    cout << "--------------------\n";
                }
            }
        } else if (opcion == 3) {
            // Agregar un médico
            int id, anios;
            string nombre, especialidad;
            bool disponible;

            cout << "Ingrese ID del médico: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nombre del médico: ";
            getline(cin, nombre);
            cout << "Ingrese especialidad del médico: ";
            getline(cin, especialidad);
            cout << "¿Está disponible? (1 para Sí, 0 para No): ";
            cin >> disponible;
            cout << "Ingrese años de experiencia: ";
            cin >> anios;
            cin.ignore();

            Medico nuevoMedico(id, nombre, especialidad, disponible, anios);
            medicos.push_back(nuevoMedico);

            cout << "Médico registrado exitosamente.\n";
        } else if (opcion == 4) {
            // Ver médicos registrados
            if (medicos.empty()) {
                cout << "No hay médicos registrados.\n";
            } else {
                cout << "\n--- Lista de Médicos ---\n";
                for (const auto& medico : medicos) {
                    medico.mostrarDetalles();
                    cout << "--------------------\n";
                }
            }
        } else if (opcion == 5) {
            // Agregar cita médica
            int id, prioridad, idPaciente, idMedico;
            string fechaHora;

            cout << "Ingrese ID de la cita: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese fecha y hora de la cita (DD-MM-AAAA HH:MM): ";
            getline(cin, fechaHora);
            cout << "Ingrese prioridad de la cita (1 = Alta, 3 = Baja): ";
            cin >> prioridad;
            cin.ignore();
            cout << "Ingrese ID del paciente: ";
            cin >> idPaciente;
            cin.ignore();
            cout << "Ingrese ID del médico: ";
            cin >> idMedico;
            cin.ignore();

            // Validar si existen el paciente y el médico
            bool pacienteExiste = any_of(pacientes.begin(), pacientes.end(), [&idPaciente](const Paciente& p) { return p.getId() == idPaciente; });
            bool medicoExiste = any_of(medicos.begin(), medicos.end(), [&idMedico](const Medico& m) { return m.getId() == idMedico; });

            if (pacienteExiste && medicoExiste) {
                CitaMedica nuevaCita(id, fechaHora, prioridad, idPaciente, idMedico);
                citas.push_back(nuevaCita);
                cout << "Cita médica registrada exitosamente.\n";
            } else {
                cout << "Error: Paciente o médico no encontrados.\n";
            }
        } else if (opcion == 6) {
            // Ver citas médicas
            if (citas.empty()) {
                cout << "No hay citas médicas registradas.\n";
            } else {
                cout << "\n--- Lista de Citas Médicas ---\n";
                for (const auto& cita : citas) {
                    cita.mostrarDetalles();
                    cout << "--------------------\n";
                }
            }
        } else if (opcion == 7) {
            cout << "Saliendo del sistema...\n";
        } else {
            cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}