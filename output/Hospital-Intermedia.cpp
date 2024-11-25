#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Necesario para std::find y std::remove
#include <fstream>   // Necesario para manejo de archivos

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

    void guardarEnArchivo(ofstream& archivo) const {
        archivo << id << "," << nombre << "," << edad << "," << hospitalizado << ","
                << motivoIngreso << "," << telefono << "," << medicoCabecera << "\n";
    }

    static Paciente cargarDeArchivo(ifstream& archivo) {
        int id;
        string nombre;
        int edad;
        bool hospitalizado;
        string motivoIngreso;
        string telefono;
        string medicoCabecera;

        string linea;
        if (getline(archivo, linea)) {
            size_t pos = 0;
            pos = linea.find(","); id = stoi(linea.substr(0, pos)); linea.erase(0, pos + 1);
            pos = linea.find(","); nombre = linea.substr(0, pos); linea.erase(0, pos + 1);
            pos = linea.find(","); edad = stoi(linea.substr(0, pos)); linea.erase(0, pos + 1);
            pos = linea.find(","); hospitalizado = stoi(linea.substr(0, pos)); linea.erase(0, pos + 1);
            pos = linea.find(","); motivoIngreso = linea.substr(0, pos); linea.erase(0, pos + 1);
            pos = linea.find(","); telefono = linea.substr(0, pos); linea.erase(0, pos + 1);
            medicoCabecera = linea;
        }

        return Paciente(id, nombre, edad, telefono);
    }
};

void mostrarMenu() {
    cout << "\n--- Menu Principal ---\n";
    cout << "1. Agregar paciente\n";
    cout << "2. Ver pacientes desde archivo\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    vector<Paciente> pacientes;
    string archivoPacientes = "pacientes.txt";
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

            Paciente nuevoPaciente(id, nombre, edad, telefono);
            nuevoPaciente.ingresarPaciente(motivo);
            nuevoPaciente.asignarMedicoCabecera(medico);
            pacientes.push_back(nuevoPaciente);

            // Guardar en archivo
            ofstream archivoSalida(archivoPacientes, ios::app);
            if (archivoSalida.is_open()) {
                nuevoPaciente.guardarEnArchivo(archivoSalida);
                archivoSalida.close();
                cout << "Paciente guardado en el archivo.\n";
            } else {
                cout << "Error al abrir el archivo para guardar.\n";
            }
        } else if (opcion == 2) {
            // Ver pacientes desde archivo
            ifstream archivoEntrada(archivoPacientes);
            if (archivoEntrada.is_open()) {
                cout << "\n--- Lista de Pacientes ---\n";
                while (!archivoEntrada.eof()) {
                    Paciente p = Paciente::cargarDeArchivo(archivoEntrada);
                    if (archivoEntrada.eof()) break; // Evitar imprimir paciente vacío
                    p.mostrarDetalles();
                    cout << "--------------------\n";
                }
                archivoEntrada.close();
            } else {
                cout << "No se pudo abrir el archivo para lectura.\n";
            }
        } else if (opcion != 3) {
            cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 3);

    cout << "Programa terminado.\n";
    return 0;
}
