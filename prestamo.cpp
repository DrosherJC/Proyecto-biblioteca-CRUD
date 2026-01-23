#include "prestamo.h"
#include <QFile>
#include <QTextStream>

// Ruta del archivo de préstamos
static const QString RUTA = "prestamos.txt";

// Función para validar si existe un usuario
bool existeUsuario(int idUsuario){
    // Abre el archivo de usuarios
    QFile archivo("usuarios.txt");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&archivo);

    // Recorre el archivo buscando el ID
    while (!in.atEnd()) {
        QStringList d = in.readLine().split("|");
        if (d.size() > 0 && d[0].toInt() == idUsuario) {
            archivo.close();
            return true;
        }
    }

    // Cierra el archivo si no se encuentra
    archivo.close();
    return false;
}

// Función para validar si existe un libro
bool existeLibro(int idLibro){
    // Abre el archivo de libros
    QFile archivo("libros.txt");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&archivo);

    // Recorre el archivo buscando el ID
    while (!in.atEnd()) {
        QStringList d = in.readLine().split("|");
        if (d.size() > 0 && d[0].toInt() == idLibro) {
            archivo.close();
            return true;
        }
    }

    // Cierra el archivo si no se encuentra
    archivo.close();
    return false;
}

/*
  Registra un nuevo préstamo
  Estado inicial ACTIVO
 */
bool registrarPrestamo(const Prestamo &p){
    // Verifica que el usuario exista
    if (!existeUsuario(p.idUsuario))
        return false;

    // Verifica que el libro exista
    if (!existeLibro(p.idLibro))
        return false;

    // Abre el archivo en modo agregar
    QFile archivo(RUTA);
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return false;

    QTextStream out(&archivo);

    // Guarda los datos del préstamo
    out << p.idPrestamo << "|"
        << p.idLibro << "|"
        << p.idUsuario << "|"
        << p.fechaPrestamo << "|"
        << "-" << "|"
        << "ACTIVO\n";

    // Cierra el archivo
    archivo.close();
    return true;
}

/*
  Marca un préstamo como DEVUELTO
*/
bool devolverPrestamo(int idBuscado, const QString &fechaDev){
    QFile archivo(RUTA);
    QFile temp("temp.txt");

    // Abre el archivo original y el temporal
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream in(&archivo);
    QTextStream out(&temp);

    bool encontrado = false;
    bool yaDevuelto = false;

    // Recorre todos los préstamos
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList d = linea.split("|");

        // Si la línea no es válida, se copia
        if (d.size() != 6) {
            out << linea << "\n";
            continue;
        }

        int idPrestamo = d[0].toInt();
        QString estado = d[5].trimmed();

        if (idPrestamo == idBuscado) {
            encontrado = true;

            // Verifica si ya fue devuelto
            if (estado == "DEVUELTO") {
                yaDevuelto = true;
                out << linea << "\n";
            } else {
                // Actualiza el estado a DEVUELTO
                out << d[0] << "|"
                    << d[1] << "|"
                    << d[2] << "|"
                    << d[3] << "|"
                    << fechaDev << "|"
                    << "DEVUELTO\n";
            }
        } else {
            // Copia los demás registros
            out << linea << "\n";
        }
    }

    // Cierra los archivos
    archivo.close();
    temp.close();

    // Si no existe o está devuelto, no se guarda
    if (!encontrado || yaDevuelto) {
        temp.remove();
        return false;
    }

    // Reemplaza el archivo original
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

    // Abre el archivo en modo lectura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return lista;

    QTextStream in(&archivo);

    // Lee cada préstamo
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

    // Cierra el archivo
    archivo.close();
    return lista;
}

// Función para buscar préstamos por ID de usuario
QList<Prestamo> buscarPrestamos(int idBuscado){
    QList<Prestamo> lista;
    QFile archivo(RUTA);

    // Abre el archivo en modo lectura
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return lista;

    QTextStream in(&archivo);

    // Recorre todos los préstamos
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

        // Agrega solo los préstamos del usuario buscado
        if(p.idUsuario == idBuscado){
            lista.append(p);
        }
    }

    // Cierra el archivo
    archivo.close();
    return lista;
}
