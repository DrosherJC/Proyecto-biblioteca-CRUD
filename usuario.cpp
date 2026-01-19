
#include "usuario.h"
#include <QFile>
#include <QTextStream>

void crearUsuario(Usuario &u) {
	QFile archivo("usuarios.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&archivo);
    out << u.id << "|" << u.nombre << "|" << u.cedula << "|" << u.correo << "|" << u.telefono << "\n";

    archivo.close();
}

QString listarUsuarios(){
    QFile archivo("usuarios.txt");
    QString datos;

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return "No se pudo abrir el archivo";

    QTextStream in(&archivo);
    while (!in.atEnd()) {
        datos += in.readLine() + "\n";
    }

    archivo.close();
    return datos;
}

void modificarUsuario() {
	QFile archivo("usuarios.txt");
    QFile temp("temp.txt");

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream in(&archivo);
    QTextStream out(&temp);

    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() == idBuscado) {
            out << u.id << "|" << u.nombre << "|"<< u.cedula << "|" << u.correo << "|" << u.telefono << "\n";
        } else {
            out << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    archivo.remove();
    temp.rename("usuarios.txt");
}

