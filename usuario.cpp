#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "usuario.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

void crearUsuario(const Usuario &u) {
    QFile archivo("usuarios.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&archivo);
    out << u.id << "|"
        << u.nombre << "|"
        << u.cedula << "|"
        << u.correo << "|"
        << u.telefono << "\n";

    archivo.close();
}

void MainWindow::listarUsuarios() {}

void MainWindow::modificarUsuario() {}

void MainWindow::eliminarUsuario() {}
