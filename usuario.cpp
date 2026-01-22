
#include "usuario.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

// Archivo: usuario.cpp
// Descripción: Manejo CRUD de usuarios usando archivo de texto

// Guarda un usuario en el archivo usuarios.txt
void crearUsuario(Usuario &u) {

    QFile archivo("usuarios.txt");
    // Abrir archivo en modo agregar
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&archivo);
    // Escribir datos separados por |
    out << u.id << "|" << u.nombre << "|" << u.cedula << "|" << u.correo << "|" << u.telefono << "\n";

    archivo.close();
}

// Lee todos los usuarios del archivo y los devuelve como texto
QString listarUsuarios(){
    QFile archivo("usuarios.txt");

    // Abrir archivo en modo lectura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return "No se pudo abrir el archivo";

    QTextStream in(&archivo);
    QString resultado;
    resultado += "ID\tNombre\tCédula\tCorreo\tTeléfono\n";
    resultado += "---------------------------------------------\n";
    // Leer línea por línea
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");
        if (datos.size() == 5) {
            resultado += datos[0] + "\t" + datos[1] + "\t" + datos[2] + "\t" + datos[3] + "\t" + datos[4] + "\n";
        }
    }

    archivo.close();
    return resultado;
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
            out << u.id << "|" << u.nombre << "|"<< u.cedula << "|" << u.correo << "|" << u.telefono << "\n";
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
void eliminarUsuario(int id)
{
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
QString buscarUsuario(int id)
{
    QFile archivo("usuarios.txt");
    QString resultado;

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&archivo);

    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() == id) {
            resultado = "ID: " + datos[0] + "\n" + "Nombre: " + datos[1] + "\n" + "Cédula: " + datos[2] + "\n" + "Correo: " + datos[3] + "\n"+ "Teléfono: " + datos[4];
            break;
        }
    }

    archivo.close();
    return resultado;
}
