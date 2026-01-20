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

// Registra un nuevo préstamo en el sistema
// Retorna true si el préstamo se guardó correctamente
bool registrarPrestamo(const Prestamo &p);
#endif // PRESTAMO_H
