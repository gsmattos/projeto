#include "janelaprincipal.h"

janelaprincipal::janelaprincipal(QWidget *parent)
    : QWidget(parent)
{
    texto = new QLabel("<h1><font color=red>Programa de Desenhar Gráficos</font></h1",this);
    texto->adjustSize();
    texto->move(450-texto->width() / 2, 20);

    botao1 = new QPushButton("Gráfico de Linhas", this);
    QObject::connect(botao1, SIGNAL(clicked(bool)), this, SLOT(abrirGraficoLinha()));
    botao1->setFixedSize(150, 80);
    botao1->move(200, 100);

    botao2 = new QPushButton("Grafico de Barras", this);
    QObject::connect(botao2, SIGNAL(clicked(bool)), this, SLOT(abrirGraficoBarras()));
    botao2->setFixedSize(150, 80);
    botao2->move(200, 200);

    botao3 = new QPushButton("Gráfico de Setores", this);
    QObject::connect(botao3, SIGNAL(clicked(bool)), this, SLOT(abrirGraficoSetores()));
    botao3->setFixedSize(150, 80);
    botao3->move(200, 300);

    QLabel *imagem1 = new QLabel(this);
    QPixmap pixmapImagem1(":/graficodelinhas.png");
    imagem1->setPixmap(pixmapImagem1);
    imagem1->setScaledContents(true);
    imagem1->setGeometry(400, 55, 330, 120);

    QLabel *imagem2 = new QLabel(this);
    QPixmap pixmapImagem2(":/graficodebarras.png");
    imagem2->setPixmap(pixmapImagem2);
    imagem2->setScaledContents(true);
    imagem2->setGeometry(400, 180, 330, 120);

    QLabel *imagem3 = new QLabel(this);
    QPixmap pixmapImagem3(":/graficodesetores.png");
    imagem3->setPixmap(pixmapImagem3);
    imagem3->setScaledContents(true);
    imagem3->setGeometry(420, 300, 260, 120);

}

void janelaprincipal::abrirGraficoLinha()
{
    telaGraficoLinha = new GraficoLinha(this);
    telaGraficoLinha->setFixedSize(900, 500);
    telaGraficoLinha->show();
    hide();
}

void janelaprincipal::abrirGraficoBarras()
{
    telaGraficoBarras = new GraficoBarras(this);
    telaGraficoBarras->setFixedSize(900, 500);
    telaGraficoBarras->show();
    hide();
}

void janelaprincipal::abrirGraficoSetores()
{
    telaGraficoSetores = new GraficoSetores(this);
    telaGraficoSetores->setFixedSize(900, 500);
    telaGraficoSetores->show();
    hide();
}

janelaprincipal::~janelaprincipal()
{
}

