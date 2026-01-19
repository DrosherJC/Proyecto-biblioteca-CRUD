#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QMessageBox>
#include "usuario.h"

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

MainWindow::~MainWindow()
{
    delete ui;
}
