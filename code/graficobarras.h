
#ifndef GRAFICOBARRAS_H
#define GRAFICOBARRAS_H

#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem> // Alterado para desenhar retângulos (barras)

    class janelaprincipal;

class GraficoBarras : public QWidget //classe da janela
{
    Q_OBJECT
public:
    explicit GraficoBarras(janelaprincipal *principal = nullptr, QWidget *parent = nullptr);

private:
    janelaprincipal *telaJanelaPrincipal; // guarda a referência da janela principal

    //referencias
    QPushButton * botaoNovaBarra;
    QPushButton * botaoDesenharGrafico;
    QPushButton * botaoVoltar;

    QLineEdit *entradaNomeEixoY;
    QLineEdit *entradaNomeBarra;
    QLineEdit *entradaValorBarra;
    int valorBarra = 0;
    QString nomeBarra;

    QLabel * textoEixoY;
    QString nomeEixoY;
    QLabel * textoDadosBarra;
    QLabel * textoBarraAtual;
    QLabel * aviso;

    float larguraDisponivel;
    float larguraBarra;
    float espacamento;

    QVector<QString> nomesBarras; // guarda os nomes de cada barra
    QVector<int> valoresBarras;   // guarda os valores de cada barra

    QGraphicsScene * cena;
    QGraphicsView * view;
    QLabel * textoNomeEixoY;

    QVector<QGraphicsRectItem*> barras; // guarda as barras desenhadas
    QVector<QLabel*> textoNomesBarras; //vetor que guarda os textos dos nomes em baixo das barras
    QVector<QLabel*> textoValoresBarras; //vetor que guarda os textos dos valores no topo de cada barra

private slots:
    void voltar();
    void criarNovaBarra();
    void calcularTamanhoBarras();
    void desenhoGraficoBarras();

signals:

};

#endif // GRAFICOBARRAS_H