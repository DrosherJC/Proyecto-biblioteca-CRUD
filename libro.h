#ifndef LIBRO_H
#define LIBRO_H
#include <QString>

struct libros{
    int idLibro;
    QString titulo;
    QString autor;
    int anioPublicacion;
};

void crearLibros(const libros &l);
void buscarLibros(int idBuscarLibros);
QString listarLibros();
void actualizarLibros(int idBuscarLibros, const libros &l);
void eliminarLibros(int idBuscarLibros);
#endif // LIBRO_H
