#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QWidget>
#include <QtWidgets>
#include "graficolinha.h"
#include "graficobarras.h"
#include "graficosetores.h"

class janelaprincipal : public QWidget
{
    Q_OBJECT

public:
    janelaprincipal(QWidget *parent = nullptr);
    ~janelaprincipal();

private slots:
    void abrirGraficoLinha();
    void abrirGraficoBarras();
    void abrirGraficoSetores();

private:
    QLabel * texto;
    QPushButton * botao1;
    QPushButton * botao2;
    QPushButton * botao3;

    GraficoLinha *telaGraficoLinha;
    GraficoBarras *telaGraficoBarras;
    GraficoSetores *telaGraficoSetores;
};
#endif // JANELAPRINCIPAL_H
