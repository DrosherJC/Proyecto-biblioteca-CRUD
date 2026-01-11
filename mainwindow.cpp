#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    ui->txtIdPrestamo->setPlaceholderText("ID Préstamo");
    ui->txtIdUsuario->setPlaceholderText("ID Usuario");
    ui->txtIdLibro->setPlaceholderText("ID Libro");
    ui->txtFechaPrestamo->setPlaceholderText("Fecha de préstamo");

    connect(ui->btnRegistrarPrestamo_3, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamos->setCurrentWidget(ui->pageRegistrarPrestamo);
    });

    connect(ui->btnDevolverPrestamo_3, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamos->setCurrentWidget(ui->pageDevolverPrestamo);
    });

    connect(ui->btnListarPrestamos_3, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamos->setCurrentWidget(ui->pageListarPrestamos);
    });


    ui->txtIdPrestamoDevolver->setPlaceholderText("ID del préstamo");
    ui->txtFechaDevolucion->setPlaceholderText("Fecha de devolución: YYYY-MM-DD");



}

MainWindow::~MainWindow()
{
    delete ui;
}
