#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <list>

using namespace std;

class Red
{
private:
    map<char, Enrutador> enrutadores;

    void actualizarTablas();
    void dijkstra(char origen);

public:
    Red();

    void agregarEnrutador(char nombre);
    void eliminarEnrutador(char nombre);
    void agregarEnlace(char a, char b, int costo);
    void eliminarEnlace(char a, char b);
    void cambiarCosto(char a, char b, int costo);
    bool existeEnrutador(char nombre) const;

    list<char> obtenerCamino(char origen, char destino) const;
    int obtenerCosto(char origen, char destino) const;

    void mostrarEnrutadores() const;
    void mostrarTablas() const;
};

#endif
