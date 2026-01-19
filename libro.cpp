#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "usuario.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>

void guardarLibros(const libros &l) {
    //Abre el archivo
    QFile archivo("libros.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text)){
        //QMessageBox sirve para mensajes de error con el uso del warning
        //nullptr indica que el mensaje no esta asociado a alguna ventana
        QMessageBox :: warning(nullptr, "Error" , "No se pudo abrir el archivo");
        return;
    }
    //Crea un stream de salida, para poder escribir dentro del archivo usando el out
    QTextStream out(&archivo);
    //Escribe el texto 
    out << l.idLibro << "|"
        << l.titulo<< "|"
        << l.autor << "|"
        << l.anioPublicacion << "|"
        << (l.disponibilidad ? "si" : "no" ) << "\n";
   
    //Cierra el archivo
    archivo.close();
}

void guardarAutores(const autores &a){
    QFile archivo("autores.txt");
    if(!archivo.open(QIODevice::Append | QIODevice::Text)){
        return;
    }
    QTextStream out(&archivo);
    out << a.idAutor << "|"
        << a.nombre << "|"
        << a.nacionalidad << "|"
        << a.fechaNacimiento << "|" << "\n";
    archivo.close();
}

