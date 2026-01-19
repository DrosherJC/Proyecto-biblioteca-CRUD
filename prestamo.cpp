#include "prestamo.h"
#include <QFile>
#include <QTextStream>

// Registrar un nuevo préstamo en el archivo
bool PrestamoDAO::registrar(const Prestamo &p)
{
    // Abre el archivo
    QFile archivo("prestamos.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return false;

    // Escribe los datos del préstamo
    QTextStream out(&archivo);
    out << p.idPrestamo << "|"
        << p.idLibro << "|"
        << p.idUsuario << "|"
        << p.fechaPrestamo << "|"
        << "null" << "|"          // Fecha de devolución vacía
        << 0 << "\n";             // 0 = préstamo activo

    archivo.close();
    return true;
}
