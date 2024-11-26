#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

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

    void guardarEnArchivo(const string& archivo) const {
        ofstream file(archivo, ios::app);
        if (!file) {
            cerr << "Error al abrir el archivo: " << archivo << endl;
            return;
        }
        file << "Paciente " << id << "\n";
        file << "Nombre: " << nombre << "\n";
        file << "Edad: " << edad << "\n";
        file << "Teléfono: " << telefono << "\n";
        file << "Hospitalizado: " << (hospitalizado ? "Sí" : "No") << "\n";
        if (hospitalizado) {
            file << "Motivo de ingreso: " << motivoIngreso << "\n";
        }
        file << "Médico de cabecera: " << (medicoCabecera.empty() ? "Ninguno" : medicoCabecera) << "\n\n";
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

    void guardarEnArchivo(const string& archivo) const {
        ofstream file(archivo, ios::app);
        if (!file) {
            cerr << "Error al abrir el archivo: " << archivo << endl;
            return;
        }
        file << "Médico " << id << "\n";
        file << "Nombre: " << nombre << "\n";
        file << "Especialidad: " << especialidad << "\n";
        file << "Disponible: " << (disponible ? "Sí" : "No") << "\n";
        file << "Años de experiencia: " << aniosExperiencia << "\n\n";
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
        cout << "ID de Cita: " << id << "\n"
             << "Fecha y Hora: " << fechaHora << "\n"
             << "Prioridad: " << (prioridad == 1 ? "Alta" : (prioridad == 2 ? "Media"
             : "Baja")) << "\n"
             << "ID Paciente: " << idPaciente << "\n"
             << "ID Médico: " << idMedico << "\n";
    }

    void guardarEnArchivo(const string& archivo) const {
        ofstream file(archivo, ios::app);
        if (!file) {
            cerr << "Error al abrir el archivo: " << archivo << endl;
            return;
        }
        file << "Cita " << id << "\n";
        file << "Fecha y Hora: " << fechaHora << "\n";
        file << "Prioridad: " << (prioridad == 1 ? "Alta" : (prioridad == 2 ? "Media" : "Baja")) << "\n";
        file << "ID Paciente: " << idPaciente << "\n";
        file << "ID Médico: " << idMedico << "\n\n";
    }
};

void mostrarMenu() {
    cout << "1. Agregar Paciente\n"
         << "2. Ver Pacientes Registrados\n"
         << "3. Agregar Médico\n"
         << "4. Ver Médicos Registrados\n"
         << "5. Agregar Cita Médica\n"
         << "6. Ver Citas Médicas\n"
         << "7. Salir\n"
         << "Seleccione una opción: ";
}

void mostrarContenidoDesdeArchivo(const string& archivo) {
    ifstream file(archivo);
    if (!file) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return;
    }

    cout << "\n--- Contenido de " << archivo << " ---\n";
    string linea;
    while (getline(file, linea)) {
        cout << linea << endl;
    }
    cout << "--------------------\n";
}

int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
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

                Paciente nuevoPaciente(id, nombre, edad, telefono);
                nuevoPaciente.ingresarPaciente(motivo);
                nuevoPaciente.asignarMedicoCabecera(medico);
                nuevoPaciente.guardarEnArchivo("pacientes.txt");
                cout << "Paciente registrado exitosamente.\n";
                break;
            }
            case 2:
                mostrarContenidoDesdeArchivo("pacientes.txt");
                break;
            case 3: {
                int id, aniosExperiencia;
                string nombre, especialidad;
                bool disponible;
                cout << "Ingrese ID: ";
                cin >> id;
                cin.ignore();
                cout << "Ingrese Nombre: ";
                getline(cin, nombre);
                cout << "Ingrese Especialidad: ";
                getline(cin, especialidad);
                cout << "Está disponible (1: Sí, 0: No): ";
                cin >> disponible;
                cout << "Ingrese Años de experiencia: ";
                cin >> aniosExperiencia;

                Medico nuevoMedico(id, nombre, especialidad, disponible, aniosExperiencia);
                nuevoMedico.guardarEnArchivo("medicos.txt");
                cout << "Médico registrado exitosamente.\n";
                break;
            }
            case 4:
                mostrarContenidoDesdeArchivo("medicos.txt");
                break;
            case 5: {
                int id, prioridad, idPaciente, idMedico;
                string fechaHora;

                cout << "Ingrese ID de la cita: ";
                cin >> id;
                cin.ignore();
                cout << "Ingrese fecha y hora de la cita: ";
                getline(cin, fechaHora);
                cout << "Ingrese prioridad (1: Alta, 2: Media, 3: Baja): ";
                cin >> prioridad;
                cout << "Ingrese ID del paciente: ";
                cin >> idPaciente;
                cout << "Ingrese ID del médico: ";
                cin >> idMedico;

                CitaMedica nuevaCita(id, fechaHora, prioridad, idPaciente, idMedico);
                nuevaCita.guardarEnArchivo("citas.txt");
                cout << "Cita médica registrada exitosamente.\n";
                break;
            }
            case 6:
                mostrarContenidoDesdeArchivo("citas.txt");
                break;
            case 7:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 7);

    return 0;
}