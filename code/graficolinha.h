#ifndef GRAFICOLINHA_H
#define GRAFICOLINHA_H

#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>

class janelaprincipal;

class GraficoLinha : public QWidget //classe da janela
{
    Q_OBJECT
public:
    explicit GraficoLinha(janelaprincipal *principal = nullptr, QWidget *parent = nullptr);

private:

    janelaprincipal *telaJanelaPrincipal; // guarda a referência da janela principal

    //referencias
    QPushButton * botaoNovoPonto;
    QPushButton * botaoDesenharGrafico;
    QPushButton * botaoVoltar;

    QLineEdit *entradaNomeEixoX;
    QLineEdit *entradaNomeEixoY;
    QLineEdit *entradaValorX;
    QLineEdit *entradaValorY;
    int valorX = 0;
    int valorY = 0;
    float calculoGraficoLinhaX = 0;
    float calculoGraficoLinhaY = 0;

    QLabel * textoEixoX;
    QLabel * textoEixoY;
    QString nomeEixoX;
    QString nomeEixoY;
    QLabel * textoXY;
    QLabel * textoPonto;
    QLabel * aviso;

    QVector<int> pontosX; //guarda os valores dos pontos X e Y
    QVector<int> pontosY;

    QGraphicsScene * cena;
    QGraphicsView * view;
    QLabel * textoNomeEixoX; //textos que mostram os nomes do eixo vertical e horizontal
    QLabel * textoNomeEixoY;

    QLabel * textoEscalaX1;//textos que mostram a escala do grafico
    QLabel * textoEscalaX2;
    QLabel * textoEscalaX3;

    QLabel * textoEscalaY1;
    QLabel * textoEscalaY2;
    QLabel * textoEscalaY3;

    QVector<float> posPontosX; //vetor que guarda as posições na tela que os pontos devem ficar na hora de fazer o gráfico
    QVector<float> posPontosY;
    QVector<QGraphicsLineItem*> linhas;//guarda as linhas do gráfico

private slots:
    void voltar();
    void criarNovoPonto();
    void calcularPosisaoPontos();
    void desenharGraficoLinha();

signals:

};

#endif // GRAFICOLINHA_H
