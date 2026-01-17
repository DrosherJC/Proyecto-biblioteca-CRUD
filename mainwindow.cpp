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
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->btnUsuarios, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnPrestamos, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::crearUsuario(const Usuario &u) {
    crearUsuario(u);

    QMessageBox::information(this, "Éxito", "Usuario guardado correctamente");
}


MainWindow::~MainWindow()
{
    delete ui;
}

