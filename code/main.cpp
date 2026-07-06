#include "janelaprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(true);

    janelaprincipal * janela = new janelaprincipal();
    janela->setFixedSize(900, 500);
    janela->show();


    return a.exec();
}
