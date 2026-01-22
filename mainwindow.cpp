#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include "usuario.h"
#include "prestamo.h"
#include "libro.h"

// Archivo: mainwindow.cpp
// Descripción: Interfaz gráfica y control de eventos de usuarios

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

    connect(ui->btnPrestamoBuscar, &QPushButton::clicked, this, [=]() {
        ui->stackedPrestamosPages->setCurrentIndex(3);
    });

    ui->tablePrestamos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablePrestamosBuscados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


//Sección Usuarios

// Evento del botón Crear Usuario
void MainWindow::on_btnCrearUsuario_clicked()
{
    // Validar campos vacíos
    if (ui->txtId->text().isEmpty() ||ui->txtNombre->text().isEmpty() ||ui->txtCedula->text().isEmpty() ||ui->txtCorreo->text().isEmpty() || ui->txtTelefono->text().isEmpty())
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

// Evento del botón Listar Usuarios
void MainWindow::on_btnListarUsuarios_clicked()
{
    QString datos = listarUsuarios();

    if (datos.trimmed().isEmpty()) {
        QMessageBox::information(this, "Usuarios", "No hay usuarios registrados");
        return;
    }

    QMessageBox::information(this, "Usuarios", datos);
}

// Evento del botón Modificar Usuario
void MainWindow::on_btnModificarUsuario_clicked()
{
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

    modificarUsuario(id,u);


    QMessageBox::information(this, "Éxito", "Usuario modificado");
}

// Evento del botón Eliminar Usuario
void MainWindow::on_btnEliminarUsuario_clicked()
{
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

// Evento del botón Buscar Usuario
void MainWindow::on_btnBuscarUsuario_clicked()
{
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






//Sección Prestamos
void MainWindow::on_btnConfirmarPrestamo_clicked(){
    if(ui->txtPrestamoId->text().isEmpty()
    || ui->txtPrestamoLibro->text().isEmpty()
    || ui->txtPrestamoUsuario->text().isEmpty()
        ){
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }

    QDate fechaPrestamo = ui->txtPrestamoFecha->date();

    if(fechaPrestamo > QDate::currentDate()){
        QMessageBox::warning(this, "Error", "La fecha no puede ser mayor a la actual");
        return;
    }

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

void MainWindow::on_btnConfirmarDevolucion_clicked()
{
    if (devolverPrestamo( // Llama a función externa para devolver préstamo
            ui->txtDevolverPrestamoId->text().toInt(),
            ui->txtDevolverFecha->text()))
        QMessageBox::information(this, "Éxito", "Préstamo devuelto");
    else
        QMessageBox::warning(this, "Error", "No se pudo devolver");

    ui->txtDevolverPrestamoId->clear();
    ui->txtDevolverFecha->clear();
}

void MainWindow::on_btnRefrescarPrestamos_clicked()
{
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
        ui->tablePrestamosBuscados->setItem(i,0,new QTableWidgetItem(QString::number(lista[i].idPrestamo)));
        ui->tablePrestamosBuscados->setItem(i,1,new QTableWidgetItem(QString::number(lista[i].idUsuario)));
        ui->tablePrestamosBuscados->setItem(i,2,new QTableWidgetItem(QString::number(lista[i].idLibro)));
        ui->tablePrestamosBuscados->setItem(i,3,new QTableWidgetItem((lista[i].fechaPrestamo)));
        ui->tablePrestamosBuscados->setItem(i,4,new QTableWidgetItem((lista[i].estado)));
    }
}






//Seccion Libros
void MainWindow::on_btnCrearLibro_clicked(){
    //comprobar que ingrese datos
    if(ui->txtIDLibro->text().isEmpty() || ui->txtTitulo->text().isEmpty() || ui->txtAutor->text().isEmpty() || ui->txtAnioPublicacion->text().isEmpty() || ui->txtDisponible->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }
    bool ok;
    int id = ui->txtIDLibro->text().toInt(&ok);
    if(!ok){
        QMessageBox::warning(this, "Error", "ID debe ser numerico");
        return;
    }
    libros l;
    l.idLibro = id;
    l.titulo = ui->txtTitulo->text();
    l.autor = ui->txtAutor ->text();
    bool okAnio;
    l.anioPublicacion = ui->txtAnioPublicacion->text().toInt(&okAnio);
    if (!okAnio){
        QMessageBox::warning(this, "Error", "El año debe ser numérico");
        return;
    }
    QString disp = ui->txtDisponible->text().toLower();
    if(disp == "1" || disp == "disponible" || disp == "si" || disp == "sí" || disp == "true"){
        l.disponibilidad = true;
    } else {
        l.disponibilidad = false;
    }
    crearLibros(l);
    QMessageBox::information(this, "Exito", "Libro guardado exitosamente");
    ui->txtIDLibro->clear();
    ui->txtTitulo->clear();
    ui->txtAutor->clear();
    ui->txtAnioPublicacion->clear();
    ui->txtDisponible->clear();
}

void MainWindow::on_btnListarLibro_clicked(){
    QString librosStr = listarLibros();
    if(librosStr.trimmed().isEmpty()){
        QMessageBox::information(this, "Libros", "No hay libros registrados");
        return;
    }
    QMessageBox::information(this, "Libros", librosStr);
}

void MainWindow::on_btnBuscarLibro_clicked(){

    if(ui->txtIDLibro->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Ingrese el ID del libro a buscar");
        return;
    }

    bool ok;
    int idBuscarLibros = ui->txtIDLibro->text().toInt(&ok);
    if(!ok){
        QMessageBox::warning(this, "Error", "El ID del libro es inválido");
        return;
    }

    buscarLibros(idBuscarLibros);
}

void MainWindow::on_btnActualizarLibro_clicked(){
    if(ui->txtIDLibro->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Ingrese el ID a modificar");
        return;
    }
    bool ok;
    int idBuscarLibros = ui->txtIDLibro->text().toInt(&ok);

    if(!ok){
        QMessageBox::warning(this, "Error", "ID del libro inválido");
        return;
    }
    libros l;
    l.idLibro = idBuscarLibros;
    l.titulo = ui->txtTitulo ->text();
    l.autor = ui->txtAutor->text();
    bool okAnio;
    l.anioPublicacion = ui->txtAnioPublicacion->text().toInt(&okAnio);
    if (!okAnio){
        QMessageBox::warning(this, "Error", "El año debe ser numérico");
        return;
    }
    QString disp = ui->txtDisponible->text().toLower();
    if(disp == "1" || disp == "disponible" || disp == "si" || disp == "sí" || disp == "true"){
        l.disponibilidad = true;
    } else {
        l.disponibilidad = false;
    }
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
    if(QMessageBox::question(this, "Confirmar", "¿Seguro que desea eliminar el libro?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        return;
    }

    eliminarLibros(idBuscarLibro);

    QMessageBox::information(this, "Éxito", "Libro eliminado");
}




//Seccion de autores
void MainWindow::on_btnCrearAutor_clicked(){
    //comprobar que ingrese datos
    if(ui->txtIDAutor->text().isEmpty() || ui->txtNombreAutor->text().isEmpty() || ui->txtNacionalidad->text().isEmpty() || ui->txtAnioNacimiento->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }
    bool ok;
    int id = ui->txtIDAutor->text().toInt(&ok);
    if(!ok){
        QMessageBox::warning(this, "Error", "ID debe ser numerico");
        return;
    }

    autores a;
    a.idAutor = id;
    a.nombre = ui->txtNombreAutor->text();
    a.nacionalidad = ui->txtNacionalidad->text();
    a.fechaNacimiento = ui->txtAnioNacimiento->text();

    crearAutores(a);
    QMessageBox::information(this, "Exito", "Autor guardado exitosamente");
    ui->txtIDAutor->clear();
    ui->txtNombreAutor->clear();
    ui->txtNacionalidad->clear();
    ui->txtAnioNacimiento->clear();
}

void MainWindow::on_btnListarAutor_clicked(){
    QString autoresStr = listarAutores();
    if(autoresStr.trimmed().isEmpty()){
        QMessageBox::information(this, "Autores", "No hay autores registrados");
        return;
    }
    QMessageBox::information(this, "Autores", autoresStr);
}

void MainWindow::on_btnBuscarAutor_clicked(){

    if(ui->txtIDAutor->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Ingrese el ID del autor a buscar");
        return;
    }

    bool ok;
    int idBuscarAutores = ui->txtIDAutor->text().toInt(&ok);
    if(!ok){
        QMessageBox::warning(this, "Error", "El ID del autor es inválido");
        return;
    }
    buscarAutores(idBuscarAutores);
}

void MainWindow::on_btnActualizarAutor_clicked(){
    if(ui->txtIDAutor->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Ingrese el ID a modificar");
        return;
    }
    bool ok;
    int idBuscarAutores = ui->txtIDAutor->text().toInt(&ok);

    if(!ok){
        QMessageBox::warning(this, "Error", "ID del autor invalido");
        return;
    }

    autores a;
    a.idAutor = idBuscarAutores;
    a.nombre = ui->txtNombreAutor->text();
    a.nacionalidad = ui->txtNacionalidad->text();
    a.fechaNacimiento = ui->txtAnioNacimiento->text();
    actualizarAutores(idBuscarAutores, a);
    QMessageBox::information(this, "Éxito", "Autor actualizado");
}

void MainWindow::on_btnEliminarAutor_clicked(){
    if (ui->txtIDAutor->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese el ID a eliminar");
        return;
    }

    bool ok;
    int idBuscarAutor = ui->txtIDAutor->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "ID inválido");
        return;
    }
    if(QMessageBox::question(this, "Comfirmar", "¿Seguro que desea eliminar el autor?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        return;
    }
    eliminarAutores(idBuscarAutor);

    QMessageBox::information(this, "Éxito", "Autor eliminado");
}



MainWindow::~MainWindow()
{
    delete ui;  // Libera la memoria de la interfaz de usuario
}
