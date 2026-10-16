#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>

using namespace std;

class Red
{
private:
    map<char, Enrutador> enrutadores;

public:
    Red();

    void agregarEnrutador(char nombre);
    void eliminarEnrutador(char nombre);
    void agregarEnlace(char a, char b, int costo);
    void eliminarEnlace(char a, char b);
    void cambiarCosto(char a, char b, int costo);
    bool existeEnrutador(char nombre) const;

    void mostrarEnrutadores() const;
};

#endif
