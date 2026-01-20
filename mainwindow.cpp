#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QMessageBox>
#include "usuario.h"
#include "prestamo.h"
#include "libro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Navegación entre opciones
    connect(ui->btnLibros, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnUsuarios, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->btnPrestamos, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });
    // Navegación dentro de Préstamos
    connect(ui->btnPrestamoRegistrar, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamosPages->setCurrentIndex(0);
    });

    connect(ui->btnPrestamoDevolver, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamosPages->setCurrentIndex(1);
    });

    connect(ui->btnPrestamoListar, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamosPages->setCurrentIndex(2);
    });

    ui->tablePrestamos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
//Sección Usuarios
void MainWindow::on_btnCrearUsuario_clicked(){
    Usuario u;
    u.id = ui->txtId->text().toInt();
    u.nombre = ui->txtNombre->text();
    u.cedula = ui->txtCedula->text();
    u.correo = ui->txtCorreo->text();
    u.telefono = ui->txtTelefono->text();

    crearUsuario(u);

    QMessageBox::information(this, "Éxito", "Usuario guardado correctamente");
}
void MainWindow::on_btnListarUsuarios_clicked(){
    QString datos = listarUsuarios();
    QMessageBox::information(this, "Usuarios", datos);
}

void MainWindow::on_btnModificarUsuario_clicked(){
    Usuario u;
    u.id = ui->txtId->text().toInt();
    u.nombre = ui->txtNombre->text();
    u.cedula = ui->txtCedula->text();
    u.correo = ui->txtCorreo->text();
    u.telefono = ui->txtTelefono->text();

    modificarUsuario(u);

    QMessageBox::information(this, "Ok", "Usuario modificado");
}





//Sección Prestamos
void MainWindow::on_btnConfirmarPrestamo_clicked()
{
    // Crear objeto préstamo
    Prestamo p;

    // Obtener datos desde los campos de texto
    p.idPrestamo = ui->txtPrestamoId->text().toInt();
    p.idLibro = ui->txtPrestamoLibro->text().toInt();
    p.idUsuario = ui->txtPrestamoUsuario->text().toInt();
    p.fechaPrestamo = ui->txtPrestamoFecha->text();

    // Registrar préstamo
    if (registrarPrestamo(p))
        QMessageBox::information(this, "Éxito", "Préstamo registrado");
    else
        QMessageBox::warning(this, "Error", "No se pudo registrar");

    // Limpiar campos del formulario
    ui->txtPrestamoId->clear();
    ui->txtPrestamoLibro->clear();
    ui->txtPrestamoUsuario->clear();
    ui->txtPrestamoFecha->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
