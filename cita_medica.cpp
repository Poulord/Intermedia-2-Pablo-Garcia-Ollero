
#define PACIENTE_CPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class CitaMedica
{
private:
    int id;
    string fechaHora;
    int prioridad;
    int idPaciente;
    int idMedico;

public:
    CitaMedica(int id, const string &fechaHora, int prioridad, int idPaciente, int idMedico)
        : id(id), fechaHora(fechaHora), prioridad(prioridad), idPaciente(idPaciente), idMedico(idMedico) {}

    void mostrarDetalles() const
    {
        cout << "ID de Cita: " << id << "\n"
             << "Fecha y Hora: " << fechaHora << "\n"
             << "Prioridad: " << (prioridad == 1 ? "Alta" : (prioridad == 2 ? "Media" : "Baja")) << "\n"
             << "ID Paciente: " << idPaciente << "\n"
             << "ID Médico: " << idMedico << "\n";
    }

    void guardarEnArchivo(const string &archivo) const
    {
        ofstream file(archivo, ios::app);
        if (!file)
        {
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

// Modificar citas
void modificarCitaEnArchivo(const string &archivo, int idCita)
{
    ifstream fileIn(archivo);
    ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut)
    {
        cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(fileIn, linea))
    {
        if (linea.find("Cita ") != string::npos)
        {
            int idActual = stoi(linea.substr(5)); // Capturar el ID de la cita
            if (idActual == idCita)
            {
                encontrado = true;
                cout << "Cita encontrada. Modifique los datos:\n";
                cout << "Ingrese nueva fecha y hora: ";
                string nuevaFechaHora;
                getline(cin, nuevaFechaHora);
                cout << "Ingrese nueva prioridad (1: Alta, 2: Media, 3: Baja): ";
                int nuevaPrioridad;
                cin >> nuevaPrioridad;
                cin.ignore();

                fileOut << linea << '\n';
                fileOut << "Fecha y Hora: " << nuevaFechaHora << '\n';
                fileOut << "Prioridad: " << (nuevaPrioridad == 1 ? "Alta" : (nuevaPrioridad == 2 ? "Media" : "Baja")) << '\n';
                getline(fileIn, linea); // Saltar línea de fecha y hora original
                getline(fileIn, linea); // Saltar línea de prioridad original
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
        cout << "Cita con ID " << idCita << " no encontrada.\n";
    }
}