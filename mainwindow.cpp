#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>

#include "usuario.h"
#include "prestamo.h"
#include "libro.h"

//Interfaz gráfica y control de eventos de usuarios

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Navegación entre opciones
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

    connect(ui->btnPrestamoBuscar, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamosPages->setCurrentIndex(3);
    });

    ui->tablePrestamos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablePrestamosBuscados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// Sección Usuarios

void MainWindow::on_btnCrearUsuario_clicked(){
    if (ui->txtId->text().isEmpty() ||
        ui->txtNombre->text().isEmpty() ||
        ui->txtCedula->text().isEmpty() ||
        ui->txtCorreo->text().isEmpty() ||
        ui->txtTelefono->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }

    bool ok;
    int id = ui->txtId->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID debe ser numérico");
        return;
    }

    if (!ui->txtCorreo->text().contains("@")) {
        QMessageBox::warning(this, "Error", "Correo inválido");
        return;
    }

    Usuario u;
    u.id = id;
    u.nombre = ui->txtNombre->text();
    u.cedula = ui->txtCedula->text();
    u.correo = ui->txtCorreo->text();
    u.telefono = ui->txtTelefono->text();

    crearUsuario(u);

    QMessageBox::information(this, "Éxito", "Usuario guardado correctamente");
}

void MainWindow::on_btnListarUsuarios_clicked(){
    QString datos = listarUsuarios();

    if (datos.trimmed().isEmpty()) {
        QMessageBox::information(this, "Usuarios", "No hay usuarios registrados");
        return;
    }

    QMessageBox::information(this, "Usuarios", datos);
}

void MainWindow::on_btnModificarUsuario_clicked(){
    if (ui->txtId->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID a modificar");
        return;
    }

    bool ok;
    int id = ui->txtId->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID inválido");
        return;
    }

    Usuario u;
    u.id = id;
    u.nombre = ui->txtNombre->text();
    u.cedula = ui->txtCedula->text();
    u.correo = ui->txtCorreo->text();
    u.telefono = ui->txtTelefono->text();

    modificarUsuario(id, u);

    QMessageBox::information(this, "Éxito", "Usuario modificado");
}

void MainWindow::on_btnEliminarUsuario_clicked(){
    if (ui->txtId->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID a eliminar");
        return;
    }

    bool ok;
    int id = ui->txtId->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID inválido");
        return;
    }

    eliminarUsuario(id);

    QMessageBox::information(this, "Éxito", "Usuario eliminado");
}

void MainWindow::on_btnBuscarUsuario_clicked(){
    if (ui->txtId->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID a buscar");
        return;
    }

    bool ok;
    int id = ui->txtId->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID inválido");
        return;
    }

    QString resultado = buscarUsuario(id);

    if (resultado.isEmpty()) {
        QMessageBox::information(this, "Buscar", "Usuario no encontrado");
        return;
    }

    QMessageBox::information(this, "Usuario encontrado", resultado);
}

// Sección Préstamos

void MainWindow::on_btnConfirmarPrestamo_clicked(){
    if (ui->txtPrestamoId->text().isEmpty() ||
        ui->txtPrestamoLibro->text().isEmpty() ||
        ui->txtPrestamoUsuario->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }

    QDate fechaPrestamo = ui->txtPrestamoFecha->date();
    if (fechaPrestamo > QDate::currentDate()) {
        QMessageBox::warning(this, "Error", "La fecha no puede ser mayor a la actual");
        return;
    }

    Prestamo p;
    p.idPrestamo = ui->txtPrestamoId->text().toInt();
    p.idLibro = ui->txtPrestamoLibro->text().toInt();
    p.idUsuario = ui->txtPrestamoUsuario->text().toInt();
    p.fechaPrestamo = ui->txtPrestamoFecha->text();

    if (registrarPrestamo(p))
        QMessageBox::information(this, "Éxito", "Préstamo registrado");
    else
        QMessageBox::warning(this, "Error",
                             "No se pudo registrar.\nVerifique que el usuario y el libro existan.");

    ui->txtPrestamoId->clear();
    ui->txtPrestamoLibro->clear();
    ui->txtPrestamoUsuario->clear();
    ui->txtPrestamoFecha->clear();
}

void MainWindow::on_btnConfirmarDevolucion_clicked(){
    if (devolverPrestamo(ui->txtDevolverPrestamoId->text().toInt(),
                         ui->txtDevolverFecha->text()))
    {
        QMessageBox::information(this, "Éxito", "Préstamo devuelto");
    }
    else {
        QMessageBox::warning(this, "Error",
                             "No se pudo registrar.\nVerifique que el libro exista o que no esté devuelto.");
    }

    ui->txtDevolverPrestamoId->clear();
    ui->txtDevolverFecha->clear();
}

void MainWindow::on_btnRefrescarPrestamos_clicked(){
    ui->tablePrestamos->setRowCount(0);

    QList<Prestamo> lista = listarPrestamos();

    for (int i = 0; i < lista.size(); i++) {
        ui->tablePrestamos->insertRow(i);
        ui->tablePrestamos->setItem(i, 0, new QTableWidgetItem(QString::number(lista[i].idPrestamo)));
        ui->tablePrestamos->setItem(i, 1, new QTableWidgetItem(QString::number(lista[i].idUsuario)));
        ui->tablePrestamos->setItem(i, 2, new QTableWidgetItem(QString::number(lista[i].idLibro)));
        ui->tablePrestamos->setItem(i, 3, new QTableWidgetItem(lista[i].fechaPrestamo));
        ui->tablePrestamos->setItem(i, 4, new QTableWidgetItem(lista[i].estado));
    }
}

void MainWindow::on_btnBuscarPrestamos_clicked(){
    ui->tablePrestamosBuscados->setRowCount(0);

    int idBuscado = ui->txtBuscarPrestamoId->text().toInt();
    QList<Prestamo> lista = buscarPrestamos(idBuscado);

    for (int i = 0; i < lista.size(); i++) {
        ui->tablePrestamosBuscados->insertRow(i);
        ui->tablePrestamosBuscados->setItem(i, 0, new QTableWidgetItem(QString::number(lista[i].idPrestamo)));
        ui->tablePrestamosBuscados->setItem(i, 1, new QTableWidgetItem(QString::number(lista[i].idUsuario)));
        ui->tablePrestamosBuscados->setItem(i, 2, new QTableWidgetItem(QString::number(lista[i].idLibro)));
        ui->tablePrestamosBuscados->setItem(i, 3, new QTableWidgetItem(lista[i].fechaPrestamo));
        ui->tablePrestamosBuscados->setItem(i, 4, new QTableWidgetItem(lista[i].estado));
    }
}

// Sección Libros

void MainWindow::on_btnCrearLibro_clicked(){
    if (ui->txtIDLibro->text().isEmpty() ||
        ui->txtTitulo->text().isEmpty() ||
        ui->txtAutor->text().isEmpty() ||
        ui->txtAnioPublicacion->text().isEmpty())
    {
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }

    bool ok;
    int id = ui->txtIDLibro->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID debe ser numérico");
        return;
    }

    bool okAnio;
    int anio = ui->txtAnioPublicacion->text().toInt(&okAnio);
    if (!okAnio) {
        QMessageBox::warning(this, "Error", "El año debe ser numérico");
        return;
    }

    libros l;
    l.idLibro = id;
    l.titulo = ui->txtTitulo->text();
    l.autor = ui->txtAutor->text();
    l.anioPublicacion = anio;
    crearLibros(l);

    QMessageBox::information(this, "Éxito", "Libro registrado");

    ui->txtIDLibro->clear();
    ui->txtTitulo->clear();
    ui->txtAutor->clear();
    ui->txtAnioPublicacion->clear();
}

void MainWindow::on_btnListarLibro_clicked(){
    QString librosStr = listarLibros();

    if (librosStr.trimmed().isEmpty()) {
        QMessageBox::information(this, "Libros", "No hay libros registrados");
        return;
    }

    QMessageBox::information(this, "Libros", librosStr);
}

void MainWindow::on_btnBuscarLibro_clicked(){
    if (ui->txtIDLibro->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID del libro a buscar");
        return;
    }

    bool ok;
    int idBuscarLibros = ui->txtIDLibro->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "El ID del libro es inválido");
        return;
    }

    buscarLibros(idBuscarLibros);
}

void MainWindow::on_btnActualizarLibro_clicked(){
    if (ui->txtIDLibro->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID a modificar");
        return;
    }

    bool ok;
    int idBuscarLibros = ui->txtIDLibro->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID del libro inválido");
        return;
    }

    bool okAnio;
    int anio = ui->txtAnioPublicacion->text().toInt(&okAnio);
    if (!okAnio) {
        QMessageBox::warning(this, "Error", "El año debe ser numérico");
        return;
    }

    libros l;
    l.idLibro = idBuscarLibros;
    l.titulo = ui->txtTitulo->text();
    l.autor = ui->txtAutor->text();
    l.anioPublicacion = anio;

    actualizarLibros(idBuscarLibros, l);

    QMessageBox::information(this, "Éxito", "Libro actualizado");
}

void MainWindow::on_btnEliminarLibro_clicked(){
    if (ui->txtIDLibro->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID a eliminar");
        return;
    }

    bool ok;
    int idBuscarLibro = ui->txtIDLibro->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID inválido");
        return;
    }

    if (QMessageBox::question(this, "Confirmar","¿Seguro que desea eliminar el libro?",QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::No)
    {
        return;
    }

    eliminarLibros(idBuscarLibro);

    QMessageBox::information(this, "Éxito", "Libro eliminado");
}

MainWindow::~MainWindow()
{
    delete ui;
}
