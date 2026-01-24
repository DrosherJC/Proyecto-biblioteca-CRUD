
#include "usuario.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

// Guarda un usuario en el archivo usuarios.txt
void crearUsuario(Usuario &u) {

    QFile archivo("usuarios.txt");
    // Abrir archivo en modo agregar
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&archivo);
    // Escribir datos separados por |
    out << u.id << "|"
        << u.nombre << "|"
        << u.cedula << "|"
        << u.correo << "|"
        << u.telefono << "\n";

    archivo.close();
}

// Lee todos los usuarios del archivo y los devuelve como texto
QString listarUsuarios(){
    QFile archivo("usuarios.txt");
    QString datos;

    // Abre el archivo en modo lectura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    QTextStream in(&archivo);

    // Lee cada línea del archivo
    while (!in.atEnd()) {
        QStringList campos = in.readLine().split("|");

        // Verifica que la línea sea válida
        if (campos.size() != 5) continue;

        // Agrega la información al texto final
        datos += "ID: " + campos[0] +
                 " | Nombre: " + campos[1] +
                 " | Cédula: " + campos[2] +
                 " | Correo: " + campos[3] +
                 " | Teléfono: " + campos[4] + "\n";
    }

    // Cierra el archivo
    archivo.close();
    return datos;
}


// Modifica un usuario según el ID
void modificarUsuario(int id, Usuario u) {
    QFile archivo("usuarios.txt");
    QFile temp("temp.txt");

    // Abrir archivos
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream in(&archivo);
    QTextStream out(&temp);

    // Copiar todos menos el que se va a modificar
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() == id){

            // Reemplazar datos
            out << u.id << "|"
                << u.nombre << "|"
                << u.cedula << "|"
                << u.correo << "|"
                << u.telefono << "\n";
        } else {
            out << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    // Reemplazar archivo original
    archivo.remove();
    temp.rename("usuarios.txt");
}

// Elimina un usuario según el ID
void eliminarUsuario(int id){
    QFile archivo("usuarios.txt");
    QFile temp("temp.txt");

    // Abrir archivos
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream in(&archivo);
    QTextStream out(&temp);

    // Copiar todo menos el usuario eliminado
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() != id) {
            out << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    // Reemplazar archivo original
    archivo.remove();
    temp.rename("usuarios.txt");
}

// Busca un usuario por ID
QString buscarUsuario(int id){
    QFile archivo("usuarios.txt");
    QString resultado;

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&archivo);

    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() == id) {
            resultado = "ID: " + datos[0]
                        + "\n" + "Nombre: " + datos[1]
                        + "\n" + "Cédula: " + datos[2]
                        + "\n" + "Correo: " + datos[3]
                        + "\n"+ "Teléfono: " + datos[4];
            break;
        }
    }

    archivo.close();
    return resultado;
}
