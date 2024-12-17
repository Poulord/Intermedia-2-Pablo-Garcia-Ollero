#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
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
//Clase Servicios
class Servicio {
private:
    int id;
    string nombre;
    string descripcion;
    double costo;
public:
    Servicio(int id, const string& nombre, const string& descripcion, double costo)
        : id(id), nombre(nombre), descripcion(descripcion), costo(costo) {}
    int getId() const { return id; }
    void mostrarDetalles() const {
        cout << "ID del Servicio: " << id << "\n"
             << "Nombre: " << nombre << "\n"
             << "Descripción: " << descripcion << "\n"
             << "Costo: $" << costo << "\n";
    }
    void guardarEnArchivo(const string& archivo) const {
        ofstream file(archivo, ios::app);
        if (!file) {
            cerr << "Error al abrir el archivo: " << archivo << endl;
            return;
        }
        file << "Servicio " << id << "\n";
        file << "Nombre: " << nombre << "\n";
        file << "Descripción: " << descripcion << "\n";
        file << "Costo: " << costo << "\n\n";
    }
};
// Modificar servicios
void modificarServicioEnArchivo(const string& archivo, int idServicio) {
    ifstream fileIn(archivo);
    ofstream fileOut("temp.txt");
    if (!fileIn || !fileOut) {
        cerr << "Error al abrir los archivos para modificar.\n";
        return;
    }
    string linea;
    bool encontrado = false;
    while (getline(fileIn, linea)) {
        if (linea.find("Servicio ") != string::npos) {
            int idActual = stoi(linea.substr(9)); // Capturar el ID del servicio
            if (idActual == idServicio) {
                encontrado = true;
                cout << "Servicio encontrado. Modifique los datos:\n";
                cout << "Ingrese nuevo nombre: ";
                string nuevoNombre;
                getline(cin, nuevoNombre);
                cout << "Ingrese nueva descripción: ";
                string nuevaDescripcion;
                getline(cin, nuevaDescripcion);
                cout << "Ingrese nuevo costo: ";
                double nuevoCosto;
                cin >> nuevoCosto;
                cin.ignore();
                fileOut << linea << '\n';
                fileOut << "Nombre: " << nuevoNombre << '\n';
                fileOut << "Descripción: " << nuevaDescripcion << '\n';
                fileOut << "Costo: " << nuevoCosto << '\n';
                getline(fileIn, linea); // Saltar línea de nombre original
                getline(fileIn, linea); // Saltar línea de descripción original
                getline(fileIn, linea); // Saltar línea de costo original
            }
        }
        fileOut << linea << '\n';
    }
    fileIn.close();
    fileOut.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (!encontrado) {
        cout << "Servicio con ID " << idServicio << " no encontrado.\n";
    }
}
void mostrarMenu()
{
    cout << "=== Menú Principal ===\n"
         << "1. Modificar Datos\n"
         << "   1.1 Modificar Paciente\n"
         << "   1.2 Modificar Médico\n"
         << "   1.3 Modificar Cita Médica\n"
         << "   1.4 Modificar Servicio\n"
         << "2. Agregar Datos\n"
         << "   2.1 Agregar Paciente\n"
         << "   2.2 Agregar Médico\n"
         << "   2.3 Agregar Cita Médica\n"
         << "   2.4 Agregar Servicio\n"
         << "3. Ver Datos\n"
         << "   3.1 Ver Pacientes Registrados\n"
         << "   3.2 Ver Médicos Registrados\n"
         << "   3.3 Ver Citas Médicas\n"
         << "   3.4 Ver Servicios\n"
         << "0. Salir\n"
         << "Seleccione una opción: ";
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
                     << "3. Modificar Cita Médica\n"
                     << "4. Modificar Servicio\n";
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
            case 4: {
                    cout << "Ingrese el ID del servicio a modificar: ";
                    int idServicio;
                    cin >> idServicio;
                    cin.ignore();
                    modificarServicioEnArchivo("servicios.txt", idServicio);
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
                     << "3. Agregar Cita Médica\n"
                     << "4. Agregar Servicio\n";
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
            case 4: {
                    int id;
                    string nombre, descripcion;
                    double costo;
                    cout << "Ingrese ID del servicio: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Ingrese nombre del servicio: ";
                    getline(cin, nombre);
                    cout << "Ingrese descripción del servicio: ";
                    getline(cin, descripcion);
                    cout << "Ingrese costo del servicio: ";
                    cin >> costo;
                    Servicio nuevoServicio(id, nombre, descripcion, costo);
                    nuevoServicio.guardarEnArchivo("servicios.txt");
                    cout << "Servicio registrado exitosamente.\n";
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
                     << "3. Ver Citas Médicas\n"
                     << "4. Ver Servicios\n";
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
            case 4:
                    mostrarContenidoDesdeArchivo("servicios.txt");
                    break;
                default:
                    cout << "Opción no válida. Intente de nuevo.\n";
                    break;
                }
                break;
            }
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
            break;
        }
    } while (opcion != 0);
    return 0;
}