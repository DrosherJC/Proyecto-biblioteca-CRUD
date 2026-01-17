#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

struct Usuario {
    int id;
    QString nombre;
    QString cedula;
    QString correo;
    QString telefono;
};

void crearUsuario(Usuario &u);
void listarUsuarios();
void modificarUsuario();
void eliminarUsuario();

#endif // USUARIO_H
