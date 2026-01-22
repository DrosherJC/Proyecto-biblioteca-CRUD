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
QString listarUsuarios();
void modificarUsuario(int id, Usuario u);
void eliminarUsuario(int id);
QString buscarUsuario(int id);

#endif
