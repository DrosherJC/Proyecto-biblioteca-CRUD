#include "prestamo.h"
#include <QFile>
#include <QTextStream>

// Archivo
static const QString RUTA = "data/prestamos.txt";

/*
  Registra un nuevo préstamo
  Estado inicial: ACTIVO
 */
bool registrarPrestamo(const Prestamo &p)
{
    // Abrir archivo en modo agregar
    QFile archivo(RUTA);
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return false;

    QTextStream out(&archivo);

    // Escribir datos del préstamo
    out << p.idPrestamo << "|"
        << p.idLibro << "|"
        << p.idUsuario << "|"
        << p.fechaPrestamo << "|"
        << "-" << "|"
        << "ACTIVO\n";

    archivo.close();
    return true;
}
