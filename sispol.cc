#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // Para usar system("cls") y limpiar la pantalla
#include <windows.h> // Para usar colores en la consola
using namespace std;

// Estructura que representa una Zona con nombre, cantidad de denuncias y porcentaje de delincuencia
struct Zona {
    string nombre;
    int cantidadDenuncias;
    float porcentajeDelincuencia;
};

// Estructura que representa una Denuncia con datos como la zona, descripción, fecha y tipo de delito
struct Denuncia {
    string zona;
    string descripcion;
    string fecha;
    string tipoDelito;
};

// Función para cambiar el color del texto en la consola
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Función que calcula el total de denuncias en todas las zonas registradas
int calcularTotalDenuncias(const Zona zonas[], int cantidad) {
    int total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += zonas[i].cantidadDenuncias;
    }
    return total;
}

// Función que guarda los datos de las zonas en un archivo de texto
void guardarDatos(const Zona zonas[], int cantidad) {
    ofstream archivo("datos_zonas.txt"); // Abre el archivo en modo escritura
    if (archivo.is_open()) {
        archivo << cantidad << endl; // Guarda la cantidad de zonas
        for (int i = 0; i < cantidad; i++) {
            archivo << zonas[i].nombre << " " << zonas[i].cantidadDenuncias << " " << zonas[i].porcentajeDelincuencia << endl;
        }
        archivo.close();
        setColor(10);
        cout << "Datos guardados correctamente en 'datos_zonas.txt'.\n";
        setColor(15);
    } else {
        setColor(12);
        cout << "Error al guardar los datos.\n";
        setColor(15);
    }
}

// Función que guarda una denuncia en un archivo de texto
void guardarDenuncia(const Denuncia& denuncia) {
    ofstream archivo("denuncias.txt", ios::app); // Abre el archivo en modo append para no sobrescribir datos
    if (archivo.is_open()) {
        archivo << "Zona: " << denuncia.zona << endl;
        archivo << "Descripción: " << denuncia.descripcion << endl;
        archivo << "Fecha: " << denuncia.fecha << endl;
        archivo << "Tipo de Delito: " << denuncia.tipoDelito << endl;
        archivo << "---------------------------------\n";
        archivo.close();
    }
}

// Función para registrar nuevas zonas en el sistema
void registrarZonas(Zona zonas[], int& cantidad) {
    setColor(10);
    cout << "\n>> Registrando Zonas <<\n";
    setColor(15);

    cout << "Ingrese la cantidad de zonas en Tingo María: ";
    cin >> cantidad;
    cin.ignore();

    for (int i = 0; i < cantidad; i++) {
        cout << "\nIngrese el nombre de la zona " << (i + 1) << ": ";
        getline(cin, zonas[i].nombre);
        zonas[i].cantidadDenuncias = 0;
        zonas[i].porcentajeDelincuencia = 0;
    }

    guardarDatos(zonas, cantidad); // Guarda los datos en el archivo
    setColor(10);
    cout << "\nZonas registradas correctamente.\n";
    setColor(15);
}

// Función para registrar una denuncia en una zona específica
void registrarDenuncia(Zona zonas[], int cantidad) {
    setColor(11);
    cout << "\n>> Registrar Denuncia <<\n";
    setColor(15);

    Denuncia nuevaDenuncia;
    cout << "Ingrese el nombre de la zona donde ocurrió la denuncia: ";
    cin.ignore();
    getline(cin, nuevaDenuncia.zona);

    bool zonaEncontrada = false;
    for (int i = 0; i < cantidad; i++) {
        if (zonas[i].nombre == nuevaDenuncia.zona) {
            zonas[i].cantidadDenuncias++;
            zonaEncontrada = true;
            int totalDenuncias = calcularTotalDenuncias(zonas, cantidad);
            
            // Actualiza los porcentajes de delincuencia de todas las zonas
            for (int j = 0; j < cantidad; j++) {
                if (totalDenuncias > 0)
                    zonas[j].porcentajeDelincuencia = (float(zonas[j].cantidadDenuncias) / totalDenuncias) * 100;
                else
                    zonas[j].porcentajeDelincuencia = 0;
            }

            cout << "Ingrese la descripción de la denuncia: ";
            getline(cin, nuevaDenuncia.descripcion);
            cout << "Ingrese la fecha (DD/MM/AAAA): ";
            getline(cin, nuevaDenuncia.fecha);
            cout << "Ingrese el tipo de delito: ";
            getline(cin, nuevaDenuncia.tipoDelito);

            guardarDenuncia(nuevaDenuncia); // Guarda la denuncia en el archivo
            guardarDatos(zonas, cantidad); // Guarda los datos actualizados en el archivo
            cout << "Denuncia registrada correctamente en " << zonas[i].nombre << "\n";
            break;
        }
    }

    if (!zonaEncontrada) {
        setColor(12);
        cout << "Error: La zona ingresada no existe en el sistema." << endl;
        setColor(15);
    }
}

// Función para mostrar todas las zonas registradas con su información
void mostrarZonas(const Zona zonas[], int cantidad) {
    setColor(14);
    cout << "\n>> Zonas Registradas <<\n";
    setColor(15);

    for (int i = 0; i < cantidad; i++) {
        cout << "\n" << (i + 1) << ". " << zonas[i].nombre 
             << " - Denuncias: " << zonas[i].cantidadDenuncias 
             << " - Nivel de delincuencia: " << zonas[i].porcentajeDelincuencia << "%" << endl;
    }
}

// Función que muestra un gráfico de criminalidad usando barras de texto
void mostrarGrafico(const Zona zonas[], int cantidad) {
    setColor(13);
    cout << "\n>> Gráfico de Criminalidad por Zona <<\n";
    setColor(15);

    int maxBarLength = 50; // La longitud máxima de las barras (en caracteres)
    
    for (int i = 0; i < cantidad; i++) {
        int barLength = (int)(zonas[i].porcentajeDelincuencia * maxBarLength / 100); // Calcular el largo de la barra
        cout << zonas[i].nombre << ": ";
        
        // Color según el porcentaje de delincuencia
        if (zonas[i].porcentajeDelincuencia > 70) {
            setColor(12);  // Rojo para alta delincuencia
        } else if (zonas[i].porcentajeDelincuencia > 30) {
            setColor(14);  // Amarillo para delincuencia media
        } else {
            setColor(10);  // Verde para baja delincuencia
        }

        // Imprimir la barra
        for (int j = 0; j < barLength; j++) {
            cout << "#";
        }

        // Restablecer color
        setColor(15);

        // Imprimir el porcentaje al final de la barra
        cout << " " << zonas[i].porcentajeDelincuencia << "%" << endl;
    }
}

// Función para limpiar la pantalla
void limpiarPantalla() {
    system("cls");
}

// Función para mostrar el menú principal
void mostrarMenu() {
    setColor(9);
    cout << "\n================== Sistema Sispol++ ==================\n";
    setColor(15);
    cout << "1. Registrar Zonas\n";
    cout << "2. Registrar Denuncia\n";
    cout << "3. Mostrar Zonas\n";
    cout << "4. Mostrar Gráfico de Criminalidad\n";
    cout << "5. Salir\n";
    cout << "=====================================================\n";
}

// Función principal del programa
int main() {
    const int Maxzonas = 100;
    Zona zonas[Maxzonas];
    int cantidad = 0;
    int opcion;

    do {
        limpiarPantalla();
        mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarZonas(zonas, cantidad);
                break;
            case 2:
                registrarDenuncia(zonas, cantidad);
                break;
            case 3:
                mostrarZonas(zonas, cantidad);
                break;
            case 4:
                mostrarGrafico(zonas, cantidad);
                break;
            case 5:
                setColor(10);
                cout << "Saliendo del sistema. ¡Hasta luego!" << endl;
                setColor(15);
                break;
        }

        if (opcion != 5) system("pause");

    } while (opcion != 5);

    return 0;
}
