#include "../include/Paciente.hpp"
#include "../include/Medico.hpp"
#include "../include/CitaMedica.hpp"
#include "../include/Servicio.hpp"
#include "../include/Funciones.hpp"

int main() {
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore();
        switch (opcion) {
            case 1: modificarDatos(); break;
            case 2: agregarDatos(); break;
            case 3: eliminarDatos(); break;
            case 4: verDatos(); break;
            default: std::cout << "Opción no válida. Intente de nuevo.\n"; break;
        }
    } while (opcion != 0);
    return 0;
}