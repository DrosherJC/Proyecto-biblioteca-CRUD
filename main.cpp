#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

struct Usuario {
    int id;
    string nombre;
    string cedula;
    string correo;
    string telefono;
};

void crearUsuario();
void listarUsuarios();
void modificarUsuario();
void eliminarUsuario();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
