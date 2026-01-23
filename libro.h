#ifndef LIBRO_H
#define LIBRO_H
#include <QString>

struct libros{
    int idLibro;
    QString titulo;
    QString autor;
    int anioPublicacion;
};
struct autores{
    int idAutor;
    QString nombre;
    QString nacionalidad;
    QString fechaNacimiento;
};

void crearLibros(const libros &l);
void buscarLibros(int idBuscarLibros);
QString listarLibros();
void actualizarLibros(int idBuscarLibros, const libros &l);
void eliminarLibros(int idBuscarLibros);

void crearAutores(const autores &a);
void buscarAutores(int idBuscarAutor);
QString listarAutores();
void actualizarAutores(int idBuscarAutor, const autores &a);
void eliminarAutores(int idBuscarAutor);

#endif // LIBRO_H
