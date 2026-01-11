#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
struct Usuario {
    int id;
    QString nombre;
    QString cedula;
    QString correo;
    QString telefono;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLibros, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->btnUsuarios, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnPrestamos, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crearUsuario(const Usuario &u) {
	QFile archivo("usuarios.txt");
	
    if (!archivo.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream out(&archivo);
    out << u.id << "|" << u.nombre << "|" << u.cedula<< "|" << u.correo << "|" << u.telefono << "\n";

    archivo.close();
}
void MainWindow::listarUsuarios() {}
void MainWindow::modificarUsuario() {}
void MainWindow::eliminarUsuario() {}
