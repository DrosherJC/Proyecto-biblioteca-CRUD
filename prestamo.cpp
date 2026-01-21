#include "prestamo.h"
#include <QFile>
#include <QTextStream>

// Archivo
static const QString RUTA = "data/prestamos.txt";

/*
  Registra un nuevo préstamo
  Estado inicial: ACTIVO
 */
bool registrarPrestamo(const Prestamo &p){


    // Abre el archivo en modo agregar
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


/*
  Marca un préstamo como devuelto
  Actualiza fecha y estado
 */
bool devolverPrestamo(int idBuscado, const QString &fechaDev){
    QFile archivo(RUTA);
    QFile temp("data/temp_prestamos.txt");

    // Abre archivos de lectura y escritura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream in(&archivo);
    QTextStream out(&temp);

    // Procesa cada préstamo
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList d = linea.split("|");

        // Verifica si es el préstamo buscado
        if (d.size() == 6 && d[0].toInt() == idBuscado) {
            // Reescribe el préstamo actualizado
            out << d[0] << "|"
                << d[1] << "|"
                << d[2] << "|"
                << d[3] << "|"
                << fechaDev << "|"
                << "DEVUELTO\n";
        } else {
            // Copia el préstamo sin cambios
            out << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    // Reemplaza archivo original
    archivo.remove();
    temp.rename(RUTA);

    return true;
}


/*
  Lee los préstamos del archivo
  Retorna una lista de préstamos
 */
QList<Prestamo> listarPrestamos(){
    QList<Prestamo> lista;
    QFile archivo(RUTA);

    // Abrir archivo en modo lectura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return lista;

    QTextStream in(&archivo);

    // Leer cada línea del archivo
    while (!in.atEnd()) {
        QStringList d = in.readLine().split("|");
        if (d.size() != 6) continue;

        Prestamo p;
        p.idPrestamo = d[0].toInt();
        p.idLibro = d[1].toInt();
        p.idUsuario = d[2].toInt();
        p.fechaPrestamo = d[3];
        p.fechaDevolucion = d[4];
        p.estado = d[5];

        lista.append(p);
    }

    archivo.close();
    return lista;
}

QList<Prestamo> buscarPrestamos(int idBuscado){
    QList<Prestamo> lista;
    QFile archivo(RUTA);

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return lista;

    QTextStream in(&archivo);
    while (!in.atEnd()){
        QStringList d = in.readLine().split("|");
        if(d.size() != 6) continue;

        Prestamo p;
        p.idPrestamo = d[0].toInt();
        p.idLibro = d[1].toInt();
        p.idUsuario = d[2].toInt();
        p.fechaPrestamo = d[3];
        p.fechaDevolucion = d[4];
        p.estado = d[5];

        if(p.idUsuario == idBuscado){
            lista.append(p);
        }
    }
    archivo.close();
    return lista;
}

