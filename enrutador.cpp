#include "enrutador.h"
#include <iostream>

Enrutador::Enrutador(char nombre) : nombre(nombre)
{
}

char Enrutador::getNombre() const
{
    return nombre;
}

void Enrutador::agregarVecino(char vecino, int costo)
{
    vecinos[vecino] = costo;
}

void Enrutador::eliminarVecino(char vecino)
{
    vecinos.erase(vecino);
}

bool Enrutador::existeVecino(char vecino) const
{
    return vecinos.count(vecino) > 0;
}

const map<char, int> &Enrutador::getVecinos() const
{
    return vecinos;
}

void Enrutador::setRuta(char destino, int costo, const list<char> &camino)
{
    costos[destino] = costo;
    caminos[destino] = camino;
}

int Enrutador::getCosto(char destino) const
{
    map<char, int>::const_iterator it = costos.find(destino);
    if (it == costos.end())
        return -1;
    return it->second;
}

list<char> Enrutador::getCamino(char destino) const
{
    map<char, list<char>>::const_iterator it = caminos.find(destino);
    if (it == caminos.end())
        return list<char>();
    return it->second;
}

void Enrutador::limpiarTabla()
{
    costos.clear();
    caminos.clear();
}

void Enrutador::mostrarTabla() const
{
    cout << "Tabla de " << nombre << endl;

    for (map<char, int>::const_iterator it = costos.begin(); it != costos.end(); it++)
    {
        cout << "  " << it->first << ": ";

        if (it->second == -1)
        {
            cout << "inalcanzable" << endl;
            continue;
        }

        cout << it->second << "  (";
        const list<char> &camino = caminos.at(it->first);
        for (list<char>::const_iterator c = camino.begin(); c != camino.end(); c++)
        {
            if (c != camino.begin())
                cout << " -> ";
            cout << *c;
        }
        cout << ")" << endl;
    }
}
