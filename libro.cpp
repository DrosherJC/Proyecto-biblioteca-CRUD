#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libro.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>

void crearLibros(const libros &l) {
    //Abre el archivo
    QFile archivo("libros.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text)){
        //QMessageBox sirve para mensajes de error con el uso del warning
        //nullptr indica que el mensaje no esta asociado a alguna ventana
        QMessageBox :: warning(nullptr, "Error" , "No se pudo abrir el archivo de libros");
        return;
    }
    //Crea un stream de salida, para poder escribir dentro del archivo usando el out
    QTextStream out(&archivo);
    //Escribe el texto 
    out << l.idLibro 
        << "|"<< l.titulo
        << "|"<< l.autor 
        << "|"<< l.anioPublicacion 
        << "|"<< (l.disponibilidad ? "si" : "no" ) << "\n";
   
    //Cierra el archivo
    archivo.close();
}

void buscarLibros(int idBuscarLibros){
    QFile archivo("libros.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return;
    }
    QTextStream in(&archivo);
    bool encontrado = false;

    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split("|");
        if(datos.size() < 5){
            continue;
        }

        if (datos[0].toInt() == idBuscarLibros) {
            QString disponible = (datos[4] == "si")? "Disponible" : "No disponible";
            QString info = "\n" + "ID: " + datos[0] + "\n" + 
                           "Titulo: " + datos[1] + "\n" + 
                           "Autor: " + datos[2] + "\n" + 
                           "Anio de publicacion: " + datos[3] + "\n" + 
                           "Estado: " + disponible + "\n";
            QMessageBox::information(nullptr, " Libro encontrado", info);
            encontrado = true;
            break;
        }
    }
    archivo.close();
    if(!encontrado){
        QMessageBox::warning(nullptr, "No encontrado", "No existe un libro con ese ID ");
    }
}

QString listarLibros(){
    QFile archivo("libros.txt");
    QString datos;

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return "No se pudo abrir el archivo";
    }

    QTextStream in(&archivo);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList campos = linea.split("|");
        if(campos.size() < 5){
            continue;
        }
        QString disponible = (campos[4] == "si")? "Disponible" : "No disponible";
        datos += "ID: " + campos[0] +
                  " | Titulo: " + campos[1] +
                  " | Autor: " + campos[2] +
                  " | Anio de Publicacion: " + campos[3] +
                  " | Estado: " + disponible + "\n";
    }

    archivo.close();
    return datos;
}

void actualizarLibros(int idBuscarLibros, const libros &l){
	QFile archivo("libros.txt");
    QFile archTemp("temp.txt");

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||!archTemp.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return;
    }

    QTextStream in(&archivo);
    QTextStream out(&archTemp);

    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() == idBuscarLibros) {
            out << l.idLibro << "|"
                << l.titulo << "|"
                << l.autor << "|"
                << l.anioPublicacion << "|"
                << (l.disponibilidad ? "si" : "no") << "\n";
        } else {
            out << linea << "\n";
        }
    }
    archivo.close();
    archTemp.close();
    archivo.remove();
    archTemp.rename("libros.txt");
}

void eliminarLibros(int idBuscarLibros){
    QFile archivo("libros.txt");
    QFile archTemp("temp.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)||!archTemp.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
       return;
    }

    QTextStream in(&archivo);
    QTextStream out(&archTemp);
    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split("|");
        if(datos[0].toInt() != idBuscarLibros){
            out << linea << "\n";
        }
    }
    archivo.close();
    archTemp.close();
    archivo.remove();
    archTemp.rename("libros.txt");
}


void crearAutores(const autores &a){
    QFile archivo("autores.txt");
    if(!archivo.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de autores");
        return;
    }
    QTextStream out(&archivo);
    out << a.idAutor << "|"
        << a.nombre << "|"
        << a.nacionalidad << "|"
        << a.fechaNacimiento << "\n";
    archivo.close();
}

void buscarAutores(int idBuscarAutor){
    QFile archivo("autores.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de autores");
        return;
    }
    QTextStream in(&archivo);
    bool encontrado = false;

    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split("|");
        if(datos.size() < 4){
            continue;
        }

        if (datos[0].toInt() == idBuscarAutor) {
            QString info = "\n" + "ID: " + datos[0] + "\n" + 
                           "Nombre: " + datos[1] + "\n" + 
                           "Nacionalidad: " + datos[2] + "\n" + 
                           "Fecha de nacimiento: " + datos[3] + "\n";
            QMessageBox::information(nullptr, "Autor encontrado", info);
            encontrado = true;
            break;
        }
    }
    archivo.close();
    if(!encontrado){
        QMessageBox::warning(nullptr, "No encontrado", "No existe un autor con ese ID ");
    }
}

QString listarAutores(){
    QFile archivo("autores.txt");
    QString datos;

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de autores");
        return "No se pudo abrir el archivo";
    }

    QTextStream in(&archivo);

    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList campos = linea.split("|");
        if(campos.size() < 4){
            continue;
        }

        datos += "ID: " + campos[0] +
                 " | Nombre: " + campos[1] +
                 " | Nacionalidad: " + campos[2] +
                 " | Fecha de Nacimiento: " + campos[3] + "\n";
    }

    archivo.close();
    return datos;
}

void actualizarAutores(int idBuscarAutor, const autores &a){
	QFile archivo("autores.txt");
    QFile archTemp("temp.txt");

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||!archTemp.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de autores");
        return;
    }

    QTextStream in(&archivo);
    QTextStream out(&archTemp);

    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if (datos[0].toInt() == idBuscarAutor) {
            out << a.idAutor 
                << "|"<< a.nombre 
                << "|"<< a.nacionalidad 
                << "|"<< a.fechaNacimiento 
                << "\n";
        } else {
            out << linea << "\n";
        }
    }
    archivo.close();
    archTemp.close();
    archivo.remove();
    archTemp.rename("autores.txt");
}

void eliminarAutores(int idBuscarAutor){
    QFile archivo("autores.txt");
    QFile archTemp("temp.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)||!archTemp.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de autores");
       return;
    }

    QTextStream in(&archivo);
    QTextStream out(&archTemp);

    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split("|");
        if(datos[0].toInt() != idBuscarAutor){
            out << linea << "\n";
        }
    }
    archivo.close();
    archTemp.close();
    archivo.remove();
    archTemp.rename("autores.txt");
}
