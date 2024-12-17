#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/*
#include "servicios.h"
#include "servicios.cpp"
*/

#include "pacientes.cpp"
#include "medicos.cpp"
#include "cita_medica.cpp"


/*

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
class Medico
{
private:
    int id;
    string nombre;
    string especialidad;
    bool disponible;
    int aniosExperiencia;

public:
    Medico(int id, const string &nombre, const string &especialidad, bool disponible, int aniosExperiencia)
        : id(id), nombre(nombre), especialidad(especialidad), disponible(disponible), aniosExperiencia(aniosExperiencia) {}

    int getId() const { return id; }

    void mostrarDetalles() const
    {
        cout << "ID: " << id << "\n"
             << "Nombre: " << nombre << "\n"
             << "Especialidad: " << especialidad << "\n"
             << "Disponible: " << (disponible ? "Sí" : "No") << "\n"
             << "Años de experiencia: " << aniosExperiencia << "\n";
    }

    void guardarEnArchivo(const string &archivo) const
    {
        ofstream file(archivo, ios::app);
        if (!file)
        {
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


// Modificar medico
void modificarMedicoEnArchivo(const string &archivo, const string &nombreMedico)
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
            nombreActual = linea.substr(8); // Capturar el nombre del médico
            if (nombreActual == nombreMedico)
            {
                encontrado = true;
                cout << "Médico encontrado. Modifique los datos:\n";
                cout << "Ingrese nueva especialidad: ";
                string nuevaEspecialidad;
                getline(cin, nuevaEspecialidad);
                cout << "¿Está disponible? (1: Sí, 0: No): ";
                bool nuevaDisponibilidad;
                cin >> nuevaDisponibilidad;
                cin.ignore();

                fileOut << linea << '\n';
                fileOut << "Especialidad: " << nuevaEspecialidad << '\n';
                fileOut << "Disponible: " << (nuevaDisponibilidad ? "Sí" : "No") << '\n';
                getline(fileIn, linea); // Saltar línea de especialidad original
                getline(fileIn, linea); // Saltar línea de disponibilidad original
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
        cout << "Médico con nombre " << nombreMedico << " no encontrado.\n";
    }
}



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
*/


void mostrarMenu()
{
    cout << "=== Menú Principal ===\n"
         << "1. Modificar Datos\n"
         << "   1.1 Modificar Paciente\n"
         << "   1.2 Modificar Médico\n"
         << "   1.3 Modificar Cita Médica\n"
         << "2. Agregar Datos\n"
         << "   2.1 Agregar Paciente\n"
         << "   2.2 Agregar Médico\n"
         << "   2.3 Agregar Cita Médica\n"
         << "3. Ver Datos\n"
         << "   3.1 Ver Pacientes Registrados\n"
         << "   3.2 Ver Médicos Registrados\n"
         << "   3.3 Ver Citas Médicas\n"
         << "0. Salir\n"
             //Aquiiiiiiiiii
             /*
         << "4. Servicios\n"
         << "   4.2 Ver Servicios Disponibles\n"
         << "   4.1 Asignar un servicio a un paciente\n"
         << "   4.3Regresar al menu principal\n"
         */
         << "Seleccione una opción: ";

        /*
         GestionServicios gestionServicios;

    // Agregar servicios predefinidos
    gestionServicios.agregarServicio(Servicio(1, "Quimioterapia", 0.0));
    gestionServicios.agregarServicio(Servicio(2, "Asistencia presencial en casa", 20.0));
    gestionServicios.agregarServicio(Servicio(3, "Llevar medicamentos a casa", 30.0));
    */
}

void mostrarContenidoDesdeArchivo(const string &archivo)
{
    ifstream file(archivo);
    if (!file)
    {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return;
    }

    cout << "\n--- Contenido de " << archivo << " ---\n";
    string linea;
    while (getline(file, linea))
    {
        cout << linea << endl;
    }
    cout << "--------------------\n";
}

int main()
{
    int opcion;
    do
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1: // Modificar Datos
        {
            int subOpcion;
            cout << "Seleccione una opción para modificar:\n";
            cout << "1. Modificar Paciente\n"
                 << "2. Modificar Médico\n"
                 << "3. Modificar Cita Médica\n";
            cin >> subOpcion;
            cin.ignore();

            switch (subOpcion)
            {
            case 1: {
                cout << "Ingrese el nombre del paciente a modificar: ";
                string nombrePaciente;
                getline(cin, nombrePaciente);
                modificarPacienteEnArchivo("pacientes.txt", nombrePaciente);
                break;
                }
            case 2: {
                cout << "Ingrese el nombre del médico a modificar: ";
                string nombreMedico;
                getline(cin, nombreMedico);
                modificarMedicoEnArchivo("medicos.txt", nombreMedico);
                break;
                }
            case 3: {
                cout << "Ingrese el ID de la cita a modificar: ";
                int idCita;
                cin >> idCita;
                cin.ignore();
                modificarCitaEnArchivo("citas.txt", idCita);
                break;
                }
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
            }
            
            break;
        }
        case 2: // Agregar Datos
        {
            int subOpcion;
            cout << "Seleccione una opción para agregar:\n";
            cout << "1. Agregar Paciente\n"
                 << "2. Agregar Médico\n"
                 << "3. Agregar Cita Médica\n";
            cin >> subOpcion;
            cin.ignore();

            switch (subOpcion)
            {
            case 1:
            {
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
            {
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
                cout << " Está disponible (1: Sí, 0: No): ";
                cin >> disponible;
                cout << "Ingrese Años de experiencia: ";
                cin >> aniosExperiencia;

                Medico nuevoMedico(id, nombre, especialidad, disponible, aniosExperiencia);
                nuevoMedico.guardarEnArchivo("medicos.txt");
                cout << "Médico registrado exitosamente.\n";
                break;
            }
            case 3:
            {
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
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
            }
            break;
        }
        case 3: // Ver Datos
        {
            int subOpcion;
            cout << "Seleccione una opción para ver:\n";
            cout << "1. Ver Pacientes Registrados\n"
                 << "2. Ver Médicos Registrados\n"
                 << "3. Ver Citas Médicas\n";
            cin >> subOpcion;
            cin.ignore();

            switch (subOpcion)
            {
            case 1:
                mostrarContenidoDesdeArchivo("pacientes.txt");
                break;
            case 2:
                mostrarContenidoDesdeArchivo("medicos.txt");
                break;
            case 3:
                mostrarContenidoDesdeArchivo("citas.txt");
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
            }
            break;
        }
        /*
        case 4: // Servicios
        {
            int subOpcion;
            cout << "Seleccione una opción para ver:\n";
            cout << "1. Ver servicios Disponibles \n"
                 << "2. Asignar un servicio a un paciente\n"
                 << "3. Regresar al menu Principal\n";
            cin >> subOpcion;
            cin.ignore();

            switch (subOpcion)
            {
            case 1:
                            gestionServicios.mostrarServicios();
                            break;
                        case 2: {
                            int idServicio, idPaciente;
                            cout << "Ingrese ID del servicio: ";
                            cin >> idServicio;
                            cout << "Ingrese ID del paciente: ";
                            cin >> idPaciente;

                            try {
                                Servicio servicio = gestionServicios.buscarServicioPorId(idServicio);
                                cout << "Servicio asignado exitosamente al paciente con ID: " << idPaciente << "\n";
                                servicio.mostrarDetalles();
                                // Aquí puedes agregar lógica para guardar la asignación en un archivo
                            } catch (const exception &e) {
                                cerr << e.what() << "\n";
                            }
                            break;
                        }
                        case 3:
                            break;
                        default:
                            cout << "Opción no válida. Intente de nuevo.\n";
                            break;
                    }
                } while (opcionServicio != 0);
                break;
        case 0:
            cout << "Saliendo del programa...\n";
            break;
            */
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}