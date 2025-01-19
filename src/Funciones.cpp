#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"
#include "../include/CitaMedica.hpp"
#include "../include/Servicio.hpp"
#include "../include/Funciones.hpp"
#include <iostream>
#include <fstream>

Paciente *buscarPacientePorId(int id, const std::string &archivo)
{
    std::ifstream file(archivo);
    if (!file)
    {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return nullptr;
    }

    std::string linea;
    while (getline(file, linea) && !linea.empty()) {
        if (linea.find("Paciente " + std::to_string(id)) != std::string::npos) {
            std::string nombre;
            int edad;
            std::string telefono;
            bool hospitalizado = false;
            std::string motivoIngreso;
            std::string medicoCabecera; 

            // Lee los detalles del paciente en cuestión
            getline(file, nombre);
            file >> edad;
            file.ignore(); 
            getline(file, telefono);
            getline(file, linea); 
            if (linea.find("Sí") != std::string::npos) {
                hospitalizado = true;
                getline(file, motivoIngreso);
            }
            getline(file, medicoCabecera); // Lee el Id del Medico de cabecera

            
            Paciente* paciente = new Paciente(id, nombre, edad, telefono);

           
            try {
                int idMedico = std::stoi(medicoCabecera); 
                Medico* medico = buscarMedicoPorId(idMedico, "medicos.txt");
                if (medico) {
                    paciente->asignarMedicoCabecera(medico); // Pasa el puntero a "Medico"
                }
            } catch (const std::invalid_argument&) {
                std::cerr << "ID de médico no válido: " << medicoCabecera << std::endl;
            } catch (const std::out_of_range&) {
                std::cerr << "ID de médico fuera de rango: " << medicoCabecera << std::endl;
            }

            if (hospitalizado) {
                paciente->ingresarPaciente(motivoIngreso);
            }
            return paciente;
        }
    }
    std::cerr << "Paciente con ID " << id << " no encontrado en el archivo." << std::endl;
    return nullptr; 
}

Medico *buscarMedicoPorId(int id, const std::string &archivo)
{
    std::ifstream file(archivo);
    if (!file)
    {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return nullptr;
    }

    std::string linea;
    while (getline(file, linea))
    {
        if (linea.find("Médico " + std::to_string(id)) != std::string::npos)
        {
            std::string nombre, especialidad;
            bool disponible;
            int aniosExperiencia;

            // Lee los detalles del médico en cuestión
            getline(file, nombre);
            getline(file, especialidad);
            getline(file, linea); 
            disponible = (linea.find("Sí") != std::string::npos);
            file >> aniosExperiencia;
            file.ignore(); 

            
            return new Medico(id, nombre, especialidad, disponible, aniosExperiencia);
        }
    }
    return nullptr; 
}


void asignarServicioAPaciente() {
    int idPaciente, idServicio;

    std::cout << "Ingrese ID del paciente: ";
    std::cin >> idPaciente;
    std::cin.ignore(); 

    // Busca a el paciente por Id
    Paciente* paciente = buscarPacientePorId(idPaciente, "pacientes.txt");
    if (!paciente) {
        std::cout << "Paciente no encontrado.\n";
        return;
    }

    std::cout << "Ingrese ID del servicio: ";
    std::cin >> idServicio;
    std::cin.ignore(); 

    // Buscar el servicio por Id
    Servicio* servicio = buscarServicioPorId(idServicio, "servicios.txt");
    if (!servicio) {
        std::cout << "Servicio no encontrado.\n";
        delete paciente; 
        return;
    }

    // Asignar selecionado por Id al paciente
    paciente->asignarServicio(*servicio);
    std::cout << "Servicio asignado exitosamente al paciente.\n";

    paciente->guardarEnArchivo("pacientes.txt");

    delete paciente; 
    delete servicio; 
}

void mostrarMenu()
{
    std::cout << "=== Menú Principal ===\n"
              << "1. Modificar Datos\n"
              << "2. Agregar Datos\n"
              << "3. Eliminar Datos\n"
              << "4. Ver Datos\n"
              << "0. Salir\n"
              << "Seleccione una opción: ";
}

void modificarDatos()
{
    int subOpcion;
    std::cout << "Seleccione una opción para modificar:\n"
              << "1. Modificar Paciente\n"
              << "2. Modificar Médico\n"
              << "3. Modificar Cita Médica\n"
              << "4. Modificar Servicio\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion)
    {
    case 1:
    {
        std::cout << "Ingrese el ID del paciente a modificar: ";
        int idPaciente;
        std::cin >> idPaciente;
        std::cin.ignore();
        Paciente paciente(idPaciente, "", 0, ""); 
        paciente.modificarPacienteEnArchivo("pacientes.txt");
        break;
    }
    case 2:
    {
        std::cout << "Ingrese el ID del médico a modificar: ";
        int idMedico;
        std::cin >> idMedico;
        std::cin.ignore();
        Medico medico(idMedico, "", "", true, 0); 
        medico.modificarMedicoEnArchivo("medicos.txt");
        break;
    }
    case 3:
    {
        std::cout << "Ingrese el ID de la cita a modificar: ";
        int idCita;
        std::cin >> idCita;
        std::cin.ignore();
        CitaMedica cita(idCita, "", 0, 0, 0); 
        cita.modificarCitaEnArchivo("citas.txt");
        break;
    }
    case 4:
    {
        std::cout << "Ingrese el ID del servicio a modificar: ";
        int idServicio;
        std::cin >> idServicio;
        std::cin.ignore();
        Servicio servicio(idServicio, "", "", 0.0); 
        servicio.modificarServicioEnArchivo("servicios.txt");
        break;
    }
    default:
        std::cout << "Opción no válida. Intente de nuevo.\n";
        break;
    }
}

void agregarDatos()
{
    int subOpcion;
    std::cout << "Seleccione una opción para agregar:\n";
    std::cout << "1. Agregar Paciente\n"
              << "2. Agregar Médico\n"
              << "3. Agregar Cita Médica\n"
              << "4. Agregar Servicio\n"
              << "5. Asignar Servicio a Paciente\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion)
    {
    case 1:
    {
        int id, edad;
        std::string nombre, telefono, motivo;
        std::cout << "Ingrese ID del paciente: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Ingrese nombre del paciente: ";
        getline(std::cin, nombre);
        std::cout << "Ingrese edad del paciente: ";
        std::cin >> edad;
        std::cin.ignore();
        std::cout << "Ingrese teléfono del paciente: ";
        getline(std::cin, telefono);
        std::cout << "Ingrese motivo de ingreso: ";
        getline(std::cin, motivo);

        // Obtiene el Id del médico
        int idMedico;
        std::cout << "Ingrese ID del médico cabecera: ";
        std::cin >> idMedico;

        // Busca a el médico por Id
        Medico *medicoCabecera = buscarMedicoPorId(idMedico, "medicos.txt");
        if (medicoCabecera)
        {
            // Crear el nuevo paciente
            Paciente nuevoPaciente(id, nombre, edad, telefono);
            nuevoPaciente.asignarMedicoCabecera(medicoCabecera); // Pasa el puntero hacia Medico
            nuevoPaciente.guardarEnArchivo("pacientes.txt");
            std::cout << "Paciente agregado exitosamente.\n";
            delete medicoCabecera; 
        }
        else
        {
            std::cout << "Médico no encontrado.\n";
        }
        break;
    }
    case 2:
    {
        int id, aniosExperiencia;
        std::string nombre, especialidad;
        bool disponible;
        std::cout << "Ingrese ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Ingrese Nombre: ";
        getline(std::cin, nombre);
        std::cout << "Ingrese Especialidad: ";
        getline(std::cin, especialidad);
        std::cout << "Está disponible (1: Sí, 0: No): ";
        std::cin >> disponible;
        std::cout << "Ingrese Años de experiencia: ";
        std::cin >> aniosExperiencia;
        Medico nuevoMedico(id, nombre, especialidad, disponible, aniosExperiencia);
        nuevoMedico.guardarEnArchivo("medicos .txt");
        std::cout << "Médico registrado exitosamente.\n";
        break;
    }
    case 3:
    {
        int id, prioridad;
        std::string fechaHora;
        std::cout << "Ingrese ID de la cita: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Ingrese fecha y hora de la cita: ";
        getline(std::cin, fechaHora);  // Leer la fecha y la hora como una cadena, no por parrafos separados
        std::cout << "Ingrese prioridad (1: Alta, 2: Media, 3: Baja): ";
        std::cin >> prioridad;

        int idPaciente, idMedico;
        std::cout << "Ingrese ID del paciente: ";
        std::cin >> idPaciente;
        std::cout << "Ingrese ID del médico: ";
        std::cin >> idMedico;

        // Valida que los IDs sean positivos para evitar errores
    if (idPaciente <= 0 || idMedico <= 0) {
        std::cout << "Los IDs deben ser números positivos.\n";
        break;
    }

        // Busca los objetos Paciente y Medico
        Paciente *paciente = buscarPacientePorId(idPaciente, "pacientes.txt");
        Medico *medico = buscarMedicoPorId(idMedico, "medicos.txt");

        if (paciente && medico)
        {
            // Crea la nueva cita médica
            CitaMedica nuevaCita(id, fechaHora, prioridad, paciente, medico);
            nuevaCita.guardarEnArchivo("citas.txt");
            std::cout << "Cita médica registrada exitosamente.\n";
        }
        else
        {
            std::cout << "No se pudo encontrar el paciente o el médico.\n";
            delete paciente; 
            delete medico;   
        }
        break;
    }
    case 4:
    {
        int id;
        std::string nombre, descripcion;
        double costo;
        std::cout << "Ingrese ID del servicio: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Ingrese nombre del servicio: ";
        getline(std::cin, nombre);
        std::cout << "Ingrese descripción del servicio: ";
        getline(std::cin, descripcion);
        std::cout << "Ingrese costo del servicio: ";
        std::cin >> costo;
        Servicio nuevoServicio(id, nombre, descripcion, costo);
        nuevoServicio.guardarEnArchivo("servicios.txt");
        std::cout << "Servicio registrado exitosamente.\n";
        break;
    }
    case 5:
            asignarServicioAPaciente(); 
            break;
    default:
        std::cout << "Opción no válida. Intente de nuevo.\n";
        break;
    }
}

void eliminarDatos()
{
    int subOpcion;
    std::cout << "Seleccione una opción para eliminar:\n"
              << "1. Eliminar Paciente\n"
              << "2. Eliminar Médico\n"
              << "3. Eliminar Cita Médica\n"
              << "4. Eliminar Servicio\n";
    std::cin >> subOpcion;
    std::cin.ignore();
    switch (subOpcion)
    {
    case 1:
    {
        std::cout << "Ingrese el ID del paciente a eliminar: ";
        int idPaciente;
        std::cin >> idPaciente;
        std::cin.ignore();
        Paciente paciente(idPaciente, "", 0, ""); 
        paciente.eliminarPacienteEnArchivo("pacientes.txt");
        break;
    }
    case 2:
    {
        std::cout << "Ingrese el ID del médico a eliminar: ";
        int idMedico;
        std::cin >> idMedico;
        std::cin.ignore();
        Medico medico(idMedico, "", "", true, 0); 
        medico.eliminarMedicoEnArchivo("medicos.txt");
        break;
    }
    case 3:
    {
        std::cout << "Ingrese el ID de la cita a eliminar: ";
        int idCita;
        std::cin >> idCita;
        std::cin.ignore();
        CitaMedica cita(idCita, "", 0, 0, 0); 
        cita.eliminarCitaEnArchivo("citas.txt");
        break;
    }
    case 4:
    {
        std::cout << "Ingrese el ID del servicio a eliminar: ";
        int idServicio;
        std::cin >> idServicio;
        std::cin.ignore();
        Servicio servicio(idServicio, "", "", 0.0); // Crea un objeto para llamar al método
        servicio.eliminarServicioEnArchivo("servicios.txt");
        break;
    }
    default:
        std::cout << "Opción no válida. Intente de nuevo.\n";
        break;
    }
}

void verDatos()
{
    int subOpcion;
    std::cout << "Seleccione una opción para ver:\n"
              << "1. Ver Pacientes Registrados\n"
              << "2. Ver Médicos Registrados\n"
              << "3. Ver Citas Médicas\n"
              << "4. Ver Servicios\n";
    std::cin >> subOpcion;
    std::cin.ignore();
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
        std::cout << "Opción no válida. Intente de nuevo.\n";
        break;
    }
}

void mostrarContenidoDesdeArchivo(const std::string &archivo)
{
    std::ifstream file(archivo); // Abrir el archivo
    if (!file)
    { // Verificar si el archivo se abrió correctamente
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return; // Salir de la función si no se puede abrir el archivo
    }

    std::cout << "\n--- Contenido de " << archivo << " ---\n";
    std::string linea;
    while (getline(file, linea))
    {                                    // Leer línea por línea
        std::cout << linea << std::endl; // Mostrar cada línea en la consola
    }
    std::cout << "--------------------\n";

    file.close(); // Cerrar el archivo
}

