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
    QString estado;
};

bool registrarPrestamo(const Prestamo &p);

bool devolverPrestamo(int idPrestamo, const QString &fechaDevolucion);

QList<Prestamo> listarPrestamos();

QList<Prestamo> buscarPrestamos(int idBuscado);
#endif // PRESTAMO_H
