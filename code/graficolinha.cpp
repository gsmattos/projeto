#include "graficolinha.h"
#include "janelaprincipal.h"


GraficoLinha::GraficoLinha(janelaprincipal *principal, QWidget *parent)
    : QWidget(parent), telaJanelaPrincipal(principal) {

    //dar nome ao eixo horizontal
    textoEixoX = new QLabel("Nome do eixo X:",this);
    textoEixoX->move(10, 10);
    entradaNomeEixoX = new QLineEdit(this);
    entradaNomeEixoX->setGeometry(10, 30, 150, 30);
    nomeEixoX = entradaNomeEixoX->text();
    connect(entradaNomeEixoX, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                nomeEixoX = entradaNomeEixoX->text(); //da o nome digitado para a variavel nomeEixoX
            });

    //dar nome ao eixo vertical
    textoEixoY = new QLabel("Nome do eixo Y:",this);
    textoEixoY->move(180, 10);
    entradaNomeEixoY = new QLineEdit(this);
    entradaNomeEixoY->setGeometry(180, 30, 150, 30);
    connect(entradaNomeEixoY, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                nomeEixoY = entradaNomeEixoY->text();  //da o nome digitado para a variavel nomeEixoY
            });

    textoXY = new QLabel("Valor X:                   Valor Y:",this);
    textoXY->move(500, 10);

    //botar para voltar à tela principal
    botaoVoltar = new QPushButton("Voltar", this);
    QObject::connect( botaoVoltar, SIGNAL(clicked(bool)), this, SLOT(voltar()));
    botaoVoltar->setFixedSize(70, 40);
    botaoVoltar->move(350, 30);

    //contagem da quantidade de pontos do gráfico
    textoPonto = new QLabel("Ponto 1",this);
    textoPonto->move(450, 40);

    entradaValorX = new QLineEdit(this);
    entradaValorX->setGeometry(500, 30, 60, 40);
    connect(entradaValorX, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                valorX = texto.toInt();
            });

    entradaValorY = new QLineEdit(this);
    entradaValorY->setGeometry(600, 30, 60, 40);
    connect(entradaValorY, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                valorY = texto.toInt();
            });

    //botão de desenhar o gráfico
    botaoDesenharGrafico = new QPushButton("Desenhar gráfico", this);
    QObject::connect( botaoDesenharGrafico, SIGNAL(clicked(bool)), this, SLOT(calcularPosisaoPontos()));
    botaoDesenharGrafico->setFixedSize(100, 40);
    botaoDesenharGrafico->move(780, 30);

    //botão para fazer o próximo ponto
    botaoNovoPonto = new QPushButton("Próximo Ponto", this);
    QObject::connect(botaoNovoPonto, SIGNAL(clicked(bool)), this, SLOT(criarNovoPonto()));
    botaoNovoPonto->setFixedSize(100, 40);
    botaoNovoPonto->move(680, 30);

    aviso = new QLabel("",this); //texto de aviso caso o usuario insira valores invalidos
    aviso->setMinimumWidth(400); //aumentar o tamanho para não cortar o texto quando ele for alterado
    aviso->move(400, 80);
    //QGraphicsScene para ser possível desenhar as linhas do gráfico
    cena = new QGraphicsScene;
    view = new QGraphicsView(cena, this);
    view->setGeometry(0, 0, 850, 350);
    view->move(50,100);

    //texto que mostra o título dos eixos horizontal e vertical (podem ser mudados depois)
    textoNomeEixoX = new QLabel("Eixo X",this);
    textoNomeEixoX->setMinimumWidth(400);
    textoNomeEixoX->move(455, 480);

    textoNomeEixoY = new QLabel("Eixo Y",this);
    textoNomeEixoY->setMinimumWidth(400);
    textoNomeEixoY->move(10, 80);

    //criação dos texto que mostram a escala do gráfico, 3 para o eixo horizontal e 3 para o eixo vertical
    textoEscalaX1 = new QLabel("",this);
    textoEscalaX1->setMinimumWidth(400);
    textoEscalaX1->move(70, 465);
    textoEscalaX2 = new QLabel("",this);
    textoEscalaX2->setMinimumWidth(400);
    textoEscalaX2->move(455, 465);
    textoEscalaX3 = new QLabel("",this);
    textoEscalaX3->setMinimumWidth(400);
    textoEscalaX3->move(840, 465);

    textoEscalaY1 = new QLabel("",this);
    textoEscalaY1->setMinimumWidth(400);
    textoEscalaY1->move(10, 425);
    textoEscalaY2 = new QLabel("",this);
    textoEscalaY2->setMinimumWidth(400);
    textoEscalaY2->move(10, 262);
    textoEscalaY3 = new QLabel("",this);
    textoEscalaY3->setMinimumWidth(400);
    textoEscalaY3->move(10, 100);
}

void GraficoLinha::criarNovoPonto() {
    for (int i = 0; i < pontosX.size(); i++)
    {
        if (valorX <= pontosX[i])
        {
            aviso->setText("Invalido: valor de X deve ser maior que o do ponto anterior");
            return;
        }
    }

    if(valorX >= 0 && valorY >= 0) {
        aviso->setText(""); //Valores enviados são validos, tira o aviso de erro, caso tenha

        //guarda o nome e valor que o usuário escreveu para os vetores
        pontosX.push_back(valorX);
        posPontosX.push_back(0);
        pontosY.push_back(valorY);
        posPontosY.push_back(0);

        //atualizar texto que indica o  número do próximo ponto a ser inserido
        textoPonto->setText("Ponto " + QString::number(pontosX.size()+1));
    } else {
        aviso->setText("Invalido: os valores devem ser maiores que 0");
    }

}

void GraficoLinha::calcularPosisaoPontos() {
    if(pontosX.size() > 1) {
        //descobrir os valores mínimos e máximos de X e Y
        float minX = *std::min_element(pontosX.begin(), pontosX.end());
        float maxX = *std::max_element(pontosX.begin(), pontosX.end());
        float minY = *std::min_element(pontosY.begin(), pontosY.end());
        float maxY = *std::max_element(pontosY.begin(), pontosY.end());

        //calcular o fator de escala baseado no tamanho da tela (840x340)
        calculoGraficoLinhaX = 840.0f / (maxX-minX);
        calculoGraficoLinhaY = 340.0f / (maxY-minY);

        //calcular a posição de todos os pontos
        for (int i = 0; i < posPontosX.size(); i++) {
            posPontosX[i] = (pontosX[i] - minX) * calculoGraficoLinhaX;
            //como no QT quanto maior o Y mais baixo é nas coordenasas, então é preciso inverter ele
            posPontosY[i] = 340 - ((pontosY[i] - minY) * calculoGraficoLinhaY);
        }

        GraficoLinha::desenharGraficoLinha();
    } else {
        aviso->setText("Invalido: Insira no mínimo 2 pontos para desenhar o gráfico");
    }
}

void GraficoLinha::desenharGraficoLinha() {
    if (nomeEixoX != "") { //adicionar o titulo que o usuario escolheu para os eixos, caso não seja vazio
        textoNomeEixoX->setText(nomeEixoX);
    }
    if (nomeEixoY != "") {
        textoNomeEixoY->setText(nomeEixoY);
    }
    for (int i = 0; i < linhas.size(); i++) //limpar todas as linhas do gráfico para depois redesenhar
    {
        cena->removeItem(linhas[i]);
        delete linhas[i];
    }
    linhas.clear();

    for (int i = 1; i < posPontosX.size(); i++) {
        linhas.push_back(cena->addLine( //desenha as linhas do gráfico atribuindo as respectivas cordenadas X e Y de cada ponto
            posPontosX[i - 1], //o primeiro ponto de uma linha é o último ponto da linha anterior, para elas se conectarem
            posPontosY[i - 1],
            posPontosX[i],
            posPontosY[i]
        ));
    }

    //textos que indicam a escala do gráfico para ajudar em sua visualização
    textoEscalaX1->setText(QString::number(*std::min_element(pontosX.begin(), pontosX.end()))); //X máximo
    textoEscalaX3->setText(QString::number(*std::max_element(pontosX.begin(), pontosX.end()))); //X mínimo
    textoEscalaX2->setText(QString::number( //média entre os dois
        ((*std::max_element(pontosX.begin(), pontosX.end())) +
         (*std::min_element(pontosX.begin(), pontosX.end()))) / 2
    ));

    textoEscalaY1->setText(QString::number(*std::min_element(pontosY.begin(), pontosY.end())));//Y máximo
    textoEscalaY3->setText(QString::number(*std::max_element(pontosY.begin(), pontosY.end())));//Y mínimo
    textoEscalaY2->setText(QString::number( //média entre os dois
        ((*std::max_element(pontosY.begin(), pontosY.end())) +
        (*std::min_element(pontosY.begin(), pontosY.end()))) / 2
    ));
}

void GraficoLinha::voltar() {
    telaJanelaPrincipal->show();
    close();
}
