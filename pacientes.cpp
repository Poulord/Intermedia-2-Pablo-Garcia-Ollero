
#define PACIENTE_CPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class Paciente
{
private:
    int id;
    string nombre;
    int edad;
    bool hospitalizado;
    string motivoIngreso;
    string telefono;
    string medicoCabecera;

public:
    Paciente(int id, const string &nombre, int edad, const string &telefono)
        : id(id), nombre(nombre), edad(edad), hospitalizado(false), telefono(telefono), medicoCabecera("") {}

    int getId() const { return id; }

    void mostrarDetalles() const
    {
        cout << "ID: " << id << "\n"
             << "Nombre: " << nombre << "\n"
             << "Edad: " << edad << "\n"
             << "Teléfono: " << telefono << "\n"
             << "Hospitalizado: " << (hospitalizado ? "Sí" : "No") << "\n";
        if (hospitalizado)
        {
            cout << "Motivo de ingreso: " << motivoIngreso << "\n";
        }
        cout << "Médico de cabecera: " << (medicoCabecera.empty() ? "Ninguno" : medicoCabecera) << "\n";
    }

    void ingresarPaciente(const string &motivo)
    {
        hospitalizado = true;
        motivoIngreso = motivo;
    }

    void asignarMedicoCabecera(const string &medico)
    {
        medicoCabecera = medico;
    }

    void guardarEnArchivo(const string &archivo) const
    {
        ofstream file(archivo, ios::app);
        if (!file)
        {
            cerr << "Error al abrir el archivo: " << archivo << endl;
            return;
        }
        file << "Paciente " << id << "\n";
        file << "Nombre: " << nombre << "\n";
        file << "Edad: " << edad << "\n";
        file << "Teléfono: " << telefono << "\n";
        file << "Hospitalizado: " << (hospitalizado ? "Sí" : "No") << "\n";
        if (hospitalizado)
        {
            file << "Motivo de ingreso: " << motivoIngreso << "\n";
        }
        file << "Médico de cabecera: " << (medicoCabecera.empty() ? "Ninguno" : medicoCabecera) << "\n\n";
    }
};

// Modificar pacientes
void modificarPacienteEnArchivo(const string &archivo, const string &nombrePaciente)
{
    ifstream fileIn(archivo);
    ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut)
    {
        cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }

    string linea, nombreActual;
    bool encontrado = false;

    while (getline(fileIn, linea))
    {
        if (linea.find("Nombre: ") != string::npos)
        {
            nombreActual = linea.substr(8); // Capturar el nombre del paciente
            if (nombreActual == nombrePaciente)
            {
                encontrado = true;
                cout << "Paciente encontrado. Modifique los datos:\n";
                cout << "Ingrese nueva edad: ";
                int nuevaEdad;
                cin >> nuevaEdad;
                cin.ignore();
                cout << "Ingrese nuevo teléfono: ";
                string nuevoTelefono;
                getline(cin, nuevoTelefono);

                fileOut << linea << '\n';
                fileOut << "Edad: " << nuevaEdad << '\n';
                fileOut << "Teléfono: " << nuevoTelefono << '\n';
                getline(fileIn, linea); // Saltar línea de edad original
                getline(fileIn, linea); // Saltar línea de teléfono original
            }
        }
        fileOut << linea << '\n';
    }

    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());

    if (!encontrado)
    {
        cout << "Paciente con nombre " << nombrePaciente << " no encontrado.\n";
    }
}