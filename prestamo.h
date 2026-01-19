#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <QString>

struct Prestamo
{
    int idPrestamo;
    int idLibro;
    int idUsuario;
    QString fechaPrestamo;
    QString fechaDevolucion;
    bool devuelto;
};

#endif // PRESTAMO_H
