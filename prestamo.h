#ifndef PRESTAMO_H
#define PRESTAMO_H // Evita que este archivo de cabecera se incluya más de una vez
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

// Registra un nuevo préstamo en el sistema
// Retorna true si el préstamo se guardó correctamente
bool registrarPrestamo(const Prestamo &p);

// Marca un préstamo como devuelto usando su ID
// Actualiza la fecha de devolución
// Retorna true si se registró la devolución
bool devolverPrestamo(int idPrestamo, const QString &fechaDevolucion);

// Devuelve una lista con todos los préstamos registrados
QList<Prestamo> listarPrestamos();

#endif // PRESTAMO_H
