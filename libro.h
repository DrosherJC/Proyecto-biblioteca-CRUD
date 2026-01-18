#ifndef LIBRO_H
#define LIBRO_H
#include <string>
using namespace std;

struct libros{
    int idLibro;
    string titulo;
    string autor;
    int anioPublicacion;
    bool disponibilidad;
};

void guardarLibros(const libros &l);

#endif // LIBRO_H
