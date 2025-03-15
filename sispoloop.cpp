#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h> // Para usar colores en la consola
using namespace std;

// Clase que representa una Zona
class Zona {
    public:
        string nombre;
        int cantidadDenuncias;
        float porcentajeDelincuencia;
    
        // Constructor de la clase Zona
        Zona(string nombre) : nombre(nombre), cantidadDenuncias(0), porcentajeDelincuencia(0) {}
};

// Clase que representa una Denuncia
class Denuncia {
    public:
        string zona;
        string descripcion;
        string fecha;
        string tipoDelito;
    
        // Constructor de la clase Denuncia
        Denuncia(string z, string d, string f, string t) : zona(z), descripcion(d), fecha(f), tipoDelito(t) {}
};

// Clase que gestiona el sistema de denuncias
class SistemaDenuncias {
private:
    vector<Zona> zonas; // Vector que almacena las zonas registradas
    vector<Denuncia> denuncias; // Vector que almacena las denuncias registradas

    void guardarZonas() { // Método para guardar las zonas en un archivo de texto
        ofstream archivo("datos_zonas.txt");
        if (archivo.is_open()) {
            archivo << zonas.size() << endl;
            for (const auto& zona : zonas) {
                archivo << zona.nombre << " " << zona.cantidadDenuncias << " " << zona.porcentajeDelincuencia << endl;
            }
            archivo.close();
        }
    }

    void guardarDenuncia(const Denuncia& denuncia) { // Método para guardar una denuncia en un archivo de texto
        ofstream archivo("denuncias.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Zona: " << denuncia.zona << endl;
            archivo << "Descripción: " << denuncia.descripcion << endl;
            archivo << "Fecha: " << denuncia.fecha << endl;
            archivo << "Tipo de Delito: " << denuncia.tipoDelito << endl;
            archivo << "---------------------------------\n";
            archivo.close();
        }
    }

    int calcularTotalDenuncias() { // Método para calcular el total de denuncias por zona
        int total = 0;
        for (const auto& zona : zonas) {
            total += zona.cantidadDenuncias;
        }
        return total;
    }

    void actualizarPorcentajes() { // Método para actualizar los porcentajes de criminalidad por zona
        int totalDenuncias = calcularTotalDenuncias();
        for (auto& zona : zonas) {
            zona.porcentajeDelincuencia = (totalDenuncias > 0) ? (float(zona.cantidadDenuncias) / totalDenuncias) * 100 : 0;
        }
    }

public:
    void registrarZona() { // Método para registrar una nueva zona
        string nombre;
        cout << "Ingrese el nombre de la zona: ";
        cin.ignore();
        getline(cin, nombre);
        zonas.push_back(Zona(nombre));
        guardarZonas();
        cout << "Zona registrada correctamente.\n";
    }

    void registrarDenuncia() { // Método para registrar una nueva denuncia
        string zona, descripcion, fecha, tipoDelito;
        cout << "Ingrese la zona: ";
        cin.ignore();
        getline(cin, zona);

        bool encontrada = false;
        for (auto& z : zonas) {
            if (z.nombre == zona) {
                z.cantidadDenuncias++;
                encontrada = true;
                break;
            }
        }

        if (!encontrada) {
            cout << "Error: La zona ingresada no existe.\n";
            return;
        }

        cout << "Ingrese la descripción de la denuncia: ";
        getline(cin, descripcion);
        cout << "Ingrese la fecha (DD/MM/AAAA): ";
        getline(cin, fecha);
        cout << "Ingrese el tipo de delito: ";
        getline(cin, tipoDelito);

        denuncias.push_back(Denuncia(zona, descripcion, fecha, tipoDelito));
        actualizarPorcentajes();
        guardarDenuncia(denuncias.back());
        guardarZonas();
        cout << "Denuncia registrada correctamente.\n";
    }

    void mostrarZonas() { // Método para mostrar todas las zonas registradas
        cout << "\n>> Zonas Registradas <<\n";
        for (const auto& zona : zonas) {
            cout << zona.nombre << " - Denuncias: " << zona.cantidadDenuncias << " - Nivel de delincuencia: " << zona.porcentajeDelincuencia << "%\n";
        }
    }

    void mostrarGrafico() { // Método para generar un gráfico de criminalidad en la consola
        cout << "\n>> Gráfico de Criminalidad por Zona <<\n";
        int maxBarLength = 50;
        for (const auto& zona : zonas) {
            int barLength = static_cast<int>(zona.porcentajeDelincuencia * maxBarLength / 100);
            cout << zona.nombre << ": ";
            for (int j = 0; j < barLength; j++) {
                cout << "#";
            }
            cout << " " << zona.porcentajeDelincuencia << "%\n";
        }
    }
};

// Función principal del programa
int main() {
    SistemaDenuncias sistema;
    int opcion;

    do {
        cout << "\n================== Sistema Sispol++ ==================" << endl;
        cout << "1. Registrar Zona\n";
        cout << "2. Registrar Denuncia\n";
        cout << "3. Mostrar Zonas\n";
        cout << "4. Mostrar Gráfico de Criminalidad\n";
        cout << "5. Salir\n";
        cout << "=====================================================\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                sistema.registrarZona();
                break;
            case 2:
                sistema.registrarDenuncia();
                break;
            case 3:
                sistema.mostrarZonas();
                break;
            case 4:
                sistema.mostrarGrafico();
                break;
            case 5:
                cout << "Saliendo del sistema. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
