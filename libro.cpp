#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libro.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>

// Función para crear un nuevo libro
void crearLibros(const libros &l) {
    // Abre el archivo de libros en modo escritura (agregar)
    QFile archivo("libros.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text)){
        // Muestra un mensaje si no se puede abrir el archivo
        QMessageBox::warning(nullptr, "Error" , "No se pudo abrir el archivo de libros");
        return;
    }

    // Stream para escribir en el archivo
    QTextStream out(&archivo);

    // Guarda los datos del libro separados por |
    out << l.idLibro
        << "|" << l.titulo
        << "|" << l.autor
        << "|" << l.anioPublicacion
        << "\n";

    // Cierra el archivo
    archivo.close();
}

// Función para buscar un libro por ID
void buscarLibros(int idBuscarLibros){
    // Abre el archivo en modo lectura
    QFile archivo("libros.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return;
    }

    QTextStream in(&archivo);
    bool encontrado = false;

    // Recorre el archivo línea por línea
    while(!in.atEnd()){
        QStringList datos = in.readLine().split("|");

        // Verifica que la línea tenga el formato correcto
        if(datos.size() != 4) continue;

        // Comprueba si el ID coincide
        if (datos[0].toInt() == idBuscarLibros) {

            // Arma el mensaje con la información del libro
            QString info =
                "ID: " + datos[0] + "\n" +
                "Título: " + datos[1] + "\n" +
                "Autor: " + datos[2] + "\n" +
                "Año de publicación: " + datos[3];

            // Muestra la información
            QMessageBox::information(nullptr, "Libro encontrado", info);
            encontrado = true;
            break;
        }
    }
    // Cierra el archivo
    archivo.close();

    // Mensaje si no se encontró el libro
    if(!encontrado){
        QMessageBox::warning(nullptr, "No encontrado", "No existe un libro con ese ID");
    }
}

// Función para listar todos los libros
QString listarLibros(){
    QFile archivo("libros.txt");
    QString datos;

    // Abre el archivo en modo lectura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return "";
    }

    QTextStream in(&archivo);

    // Lee cada línea del archivo
    while (!in.atEnd()) {
        QStringList campos = in.readLine().split("|");

        // Verifica que la línea sea válida
        if(campos.size() != 4) continue;

        // Agrega la información al texto final
        datos += "ID: " + campos[0] +
                 " | Título: " + campos[1] +
                 " | Autor: " + campos[2] +
                 " | Año: " + campos[3] + "\n";
    }
    // Cierra el archivo
    archivo.close();
    return datos;
}

// Función para actualizar un libro existente
void actualizarLibros(int idBuscarLibros, const libros &l){
    QFile archivo("libros.txt");
    QFile archTemp("temp.txt");

    // Abre el archivo original y el temporal
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !archTemp.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return;
    }

    QTextStream in(&archivo);
    QTextStream out(&archTemp);

    // Recorre todos los libros
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        // Si es el libro buscado, se actualiza
        if (datos.size() == 4 && datos[0].toInt() == idBuscarLibros) {
            out << l.idLibro << "|"
                << l.titulo << "|"
                << l.autor << "|"
                << l.anioPublicacion << "\n";
        } else {
            // Si no, se copia sin cambios
            out << linea << "\n";
        }
    }
    // Cierra archivos
    archivo.close();
    archTemp.close();

    // Reemplaza el archivo original
    archivo.remove();
    archTemp.rename("libros.txt");
}

// Función para eliminar un libro por ID
void eliminarLibros(int idBuscarLibros){
    QFile archivo("libros.txt");
    QFile archTemp("temp.txt");

    // Abre el archivo original y el temporal
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !archTemp.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo de libros");
        return;
    }

    QTextStream in(&archivo);
    QTextStream out(&archTemp);

    // Copia todos los libros excepto el que se va a eliminar
    while(!in.atEnd()){
        QString linea = in.readLine();
        QStringList datos = linea.split("|");

        if(datos[0].toInt() != idBuscarLibros){
            out << linea << "\n";
        }
    }
    // Cierra archivos
    archivo.close();
    archTemp.close();

    // Reemplaza el archivo original
    archivo.remove();
    archTemp.rename("libros.txt");
}
