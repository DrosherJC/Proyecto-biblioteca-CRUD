#ifndef LIBRO_H
#define LIBRO_H
#include <QString>
using namespace std;
struct libros{
    int idLibro;
    QString titulo;
    QString autor;
    int anioPublicacion;
    bool disponibilidad;
};
struct autores{
    int idAutor;
    QString nombre;
    QString nacionalidad;
    QString fechaNacimiento;
};

void guardarLibros(const libros &l);
void guardarAutores(const autores &a);
#endif // LIBRO_H
