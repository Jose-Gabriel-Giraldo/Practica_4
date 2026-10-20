#include "red.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>

using namespace std;

string leerLinea(const string &mensaje)
{
    string linea;
    cout << mensaje;
    getline(cin, linea);
    if (!linea.empty() && linea[linea.size() - 1] == '\r')
        linea.erase(linea.size() - 1);
    return linea;
}

char leerEnrutador(const string &mensaje)
{
    string linea = leerLinea(mensaje);
    if (linea.size() != 1 || isspace((unsigned char)linea[0]))
        throw invalid_argument("El nombre del enrutador debe ser un solo caracter");
    return linea[0];
}

int leerEntero(const string &mensaje)
{
    string linea = leerLinea(mensaje);
    size_t usados = 0;
    int valor;

    try
    {
        valor = stoi(linea, &usados);
    }
    catch (const exception &)
    {
        throw invalid_argument("Debe ingresar un numero entero");
    }

    if (usados != linea.size())
        throw invalid_argument("Debe ingresar un numero entero");
    return valor;
}

void mostrarMenu()
{
    cout << endl;
    cout << "===== MENU PRINCIPAL =====" << endl;
    cout << "A. Agregar enrutador" << endl;
    cout << "B. Eliminar enrutador" << endl;
    cout << "C. Agregar enlace" << endl;
    cout << "D. Eliminar enlace" << endl;
    cout << "E. Cambiar costo de enlace" << endl;
    cout << "F. Ver enrutadores" << endl;
    cout << "G. Ver tablas de enrutamiento" << endl;
    cout << "H. Consultar ruta" << endl;
    cout << "I. Cargar archivo" << endl;
    cout << "S. Salir" << endl;
}

int main()
{
    Red red;
    char opcion = ' ';
    do
    {
        mostrarMenu();
        string linea = leerLinea("Opcion: ");
        if (!cin)
            break;

        try
        {
            if (linea.size() != 1)
                throw invalid_argument("Opcion invalida");

            opcion = toupper((unsigned char)linea[0]);

            switch (opcion)
            {
            case 'A':
                red.agregarEnrutador(leerEnrutador("Nombre del enrutador: "));
                cout << "Enrutador agregado" << endl;
                break;

            case 'B':
                red.eliminarEnrutador(leerEnrutador("Nombre del enrutador: "));
                cout << "Enrutador eliminado" << endl;
                break;

            case 'C':
            {
                char a = leerEnrutador("Primer enrutador: ");
                char b = leerEnrutador("Segundo enrutador: ");
                red.agregarEnlace(a, b, leerEntero("Costo: "));
                cout << "Enlace agregado" << endl;
                break;
            }

            case 'D':
            {
                char a = leerEnrutador("Primer enrutador: ");
                char b = leerEnrutador("Segundo enrutador: ");
                red.eliminarEnlace(a, b);
                cout << "Enlace eliminado" << endl;
                break;
            }

            case 'E':
            {
                char a = leerEnrutador("Primer enrutador: ");
                char b = leerEnrutador("Segundo enrutador: ");
                red.cambiarCosto(a, b, leerEntero("Nuevo costo: "));
                cout << "Costo actualizado" << endl;
                break;
            }

            case 'F':
                red.mostrarEnrutadores();
                break;

            case 'G':
                red.mostrarTablas();
                break;

            case 'H':
            {
                char origen = leerEnrutador("Origen: ");
                char destino = leerEnrutador("Destino: ");
                int costo = red.obtenerCosto(origen, destino);

                if (costo == -1)
                {
                    cout << "No hay ruta de " << origen << " a " << destino << endl;
                    break;
                }

                list<char> camino = red.obtenerCamino(origen, destino);
                cout << "Camino: ";
                for (list<char>::const_iterator it = camino.begin(); it != camino.end(); it++)
                {
                    if (it != camino.begin())
                        cout << " -> ";
                    cout << *it;
                }
                cout << endl << "Costo: " << costo << endl;
                break;
            }

            case 'I':
                red.cargarArchivo(leerLinea("Ruta del archivo: "));
                cout << "Archivo cargado" << endl;
                break;

            case 'S':
                cout << "Fin del programa" << endl;
                break;

            default:
                throw invalid_argument("Opcion invalida");
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    } while (opcion != 'S' && cin);

    return 0;
}
