#include "red.h"
#include <iostream>
#include <stdexcept>
#include <string>

Red::Red()
{
}

void Red::agregarEnrutador(char nombre)
{
    if (!enrutadores.emplace(nombre, Enrutador(nombre)).second)
        throw invalid_argument(string("El enrutador ") + nombre + " ya existe");
}

void Red::eliminarEnrutador(char nombre)
{
    map<char, Enrutador>::iterator it = enrutadores.find(nombre);
    if (it == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + nombre + " no existe");

    const map<char, int> &vecinos = it->second.getVecinos();
    for (map<char, int>::const_iterator v = vecinos.begin(); v != vecinos.end(); v++)
        enrutadores.at(v->first).eliminarVecino(nombre);

    enrutadores.erase(it);
}

void Red::agregarEnlace(char a, char b, int costo)
{
    if (a == b)
        throw invalid_argument("Un enrutador no puede enlazarse consigo mismo");
    if (costo <= 0)
        throw invalid_argument("El costo debe ser mayor que cero");

    map<char, Enrutador>::iterator ea = enrutadores.find(a);
    map<char, Enrutador>::iterator eb = enrutadores.find(b);
    if (ea == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + a + " no existe");
    if (eb == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + b + " no existe");
    if (ea->second.existeVecino(b))
        throw invalid_argument(string("El enlace ") + a + "-" + b + " ya existe");

    ea->second.agregarVecino(b, costo);
    eb->second.agregarVecino(a, costo);
}

void Red::eliminarEnlace(char a, char b)
{
    map<char, Enrutador>::iterator ea = enrutadores.find(a);
    map<char, Enrutador>::iterator eb = enrutadores.find(b);
    if (ea == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + a + " no existe");
    if (eb == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + b + " no existe");
    if (!ea->second.existeVecino(b))
        throw invalid_argument(string("El enlace ") + a + "-" + b + " no existe");

    ea->second.eliminarVecino(b);
    eb->second.eliminarVecino(a);
}

void Red::cambiarCosto(char a, char b, int costo)
{
    if (costo <= 0)
        throw invalid_argument("El costo debe ser mayor que cero");

    map<char, Enrutador>::iterator ea = enrutadores.find(a);
    map<char, Enrutador>::iterator eb = enrutadores.find(b);
    if (ea == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + a + " no existe");
    if (eb == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + b + " no existe");
    if (!ea->second.existeVecino(b))
        throw invalid_argument(string("El enlace ") + a + "-" + b + " no existe");

    ea->second.agregarVecino(b, costo);
    eb->second.agregarVecino(a, costo);
}

bool Red::existeEnrutador(char nombre) const
{
    return enrutadores.count(nombre) > 0;
}

void Red::mostrarEnrutadores() const
{
    cout << "La red tiene " << enrutadores.size() << " enrutador(es)" << endl;

    for (map<char, Enrutador>::const_iterator it = enrutadores.begin(); it != enrutadores.end(); it++)
    {
        cout << it->first << ":";
        const map<char, int> &vecinos = it->second.getVecinos();
        for (map<char, int>::const_iterator v = vecinos.begin(); v != vecinos.end(); v++)
            cout << "  " << v->first << "(" << v->second << ")";
        cout << endl;
    }
}
