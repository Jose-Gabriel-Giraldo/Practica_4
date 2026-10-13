#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <list>

using namespace std;

class Enrutador
{
private:
    char nombre;
    map<char, int> vecinos;
    map<char, int> costos;
    map<char, list<char>> caminos;

public:
    Enrutador(char nombre);

    char getNombre() const;

    void agregarVecino(char vecino, int costo);
    void eliminarVecino(char vecino);
    bool existeVecino(char vecino) const;
    const map<char, int> &getVecinos() const;

    void setRuta(char destino, int costo, const list<char> &camino);
    int getCosto(char destino) const;
    list<char> getCamino(char destino) const;
    void limpiarTabla();
    void mostrarTabla() const;
};

#endif
