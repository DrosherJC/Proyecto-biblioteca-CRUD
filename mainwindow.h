#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btnCrearUsuario_clicked();
    void on_btnListarUsuarios_clicked();
    void on_btnModificarUsuario_clicked();
    void on_btnEliminarUsuario_clicked();


    void on_btnConfirmarPrestamo_clicked();
    void on_btnConfirmarDevolucion_clicked();
    void on_btnRefrescarPrestamos_clicked();
    void on_btnBuscarPrestamos_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
