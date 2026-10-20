#include "red.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <queue>
#include <vector>
#include <functional>

Red::Red()
{
}

void Red::agregarEnrutador(char nombre)
{
    if (!enrutadores.emplace(nombre, Enrutador(nombre)).second)
        throw invalid_argument(string("El enrutador ") + nombre + " ya existe");

    actualizarTablas();
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
    actualizarTablas();
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
    actualizarTablas();
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
    actualizarTablas();
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
    actualizarTablas();
}

bool Red::existeEnrutador(char nombre) const
{
    return enrutadores.count(nombre) > 0;
}

void Red::actualizarTablas()
{
    for (map<char, Enrutador>::iterator it = enrutadores.begin(); it != enrutadores.end(); it++)
        dijkstra(it->first);
}

void Red::dijkstra(char origen)
{
    map<char, int> distancia;
    map<char, char> anterior;
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pendientes;

    distancia[origen] = 0;
    pendientes.push(make_pair(0, origen));

    while (!pendientes.empty())
    {
        int d = pendientes.top().first;
        char actual = pendientes.top().second;
        pendientes.pop();

        if (d > distancia[actual])
            continue;

        const map<char, int> &vecinos = enrutadores.at(actual).getVecinos();
        for (map<char, int>::const_iterator v = vecinos.begin(); v != vecinos.end(); v++)
        {
            int nueva = d + v->second;
            map<char, int>::iterator dv = distancia.find(v->first);

            if (dv == distancia.end() || nueva < dv->second)
            {
                distancia[v->first] = nueva;
                anterior[v->first] = actual;
                pendientes.push(make_pair(nueva, v->first));
            }
        }
    }

    Enrutador &enrutador = enrutadores.at(origen);
    enrutador.limpiarTabla();

    for (map<char, Enrutador>::const_iterator it = enrutadores.begin(); it != enrutadores.end(); it++)
    {
        char destino = it->first;
        map<char, int>::const_iterator dd = distancia.find(destino);

        if (dd == distancia.end())
        {
            enrutador.setRuta(destino, -1, list<char>());
            continue;
        }

        list<char> camino;
        for (char paso = destino; paso != origen; paso = anterior[paso])
            camino.push_front(paso);
        camino.push_front(origen);

        enrutador.setRuta(destino, dd->second, camino);
    }
}

list<char> Red::obtenerCamino(char origen, char destino) const
{
    map<char, Enrutador>::const_iterator eo = enrutadores.find(origen);
    if (eo == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + origen + " no existe");
    if (enrutadores.count(destino) == 0)
        throw invalid_argument(string("El enrutador ") + destino + " no existe");

    return eo->second.getCamino(destino);
}

int Red::obtenerCosto(char origen, char destino) const
{
    map<char, Enrutador>::const_iterator eo = enrutadores.find(origen);
    if (eo == enrutadores.end())
        throw invalid_argument(string("El enrutador ") + origen + " no existe");
    if (enrutadores.count(destino) == 0)
        throw invalid_argument(string("El enrutador ") + destino + " no existe");

    return eo->second.getCosto(destino);
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

void Red::mostrarTablas() const
{
    for (map<char, Enrutador>::const_iterator it = enrutadores.begin(); it != enrutadores.end(); it++)
    {
        it->second.mostrarTabla();
        cout << endl;
    }
}
