
#ifndef GRAFICOSETORES_H
#define GRAFICOSETORES_H

#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

class janelaprincipal;

class GraficoSetores : public QWidget
{
    Q_OBJECT
public:
    explicit GraficoSetores(janelaprincipal *principal = nullptr, QWidget *parent = nullptr);

private:
    janelaprincipal *telaJanelaPrincipal; // guarda a referência da janela principal

    //referencias
    QPushButton * botaoNovoSetor;
    QPushButton * botaoDesenharGrafico;
    QPushButton * botaoVoltar;

    QLineEdit *entradaNomeSetor;
    QLineEdit *entradaValorSetor;
    QLineEdit *entradaCorSetor;
    int valorSetor = 0;
    QString nomeSetor;
    QString corSetor;

    QLabel * textoDadosSetor;
    QLabel * textoSetorAtual;
    QLabel * aviso;

    QVector<QString> nomesSetores; // guarda os nomes de cada setor
    QVector<int> valoresSetores;   // guarda os valores de cada setor
    QVector<QString> coresSetores; // guarda as cores em hexadecimal de cada setor

    QGraphicsScene * cena;
    QGraphicsView * view;

    QVector<QGraphicsEllipseItem*> setores; // guarda os setores desenhados
    QVector<QGraphicsRectItem*> legendaQuadrados; // guarda os quadrados da legenda
    QVector<QGraphicsTextItem*> legendaTextos; // guarda os textos da legenda

private slots:
    void voltar();
    void criarNovoSetor();
    void desenhoGraficoSetores();

signals:

};

#endif // GRAFICOSETORES_H