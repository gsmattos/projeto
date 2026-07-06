
#include "graficosetores.h"
#include "janelaprincipal.h"

GraficoSetores::GraficoSetores(janelaprincipal *principal, QWidget *parent)
    : QWidget(parent), telaJanelaPrincipal(principal) {

    textoDadosSetor = new QLabel("Nome do Setor:        Valor:         Cor (Hex):", this);
    textoDadosSetor->move(400, 10);

    //botar para voltar à tela principal
    botaoVoltar = new QPushButton("Voltar", this);
    QObject::connect(botaoVoltar, SIGNAL(clicked(bool)), this, SLOT(voltar()));
    botaoVoltar->setFixedSize(70, 40);
    botaoVoltar->move(250, 30);

    //texto da contagem quantidade de setores do gráfico
    textoSetorAtual = new QLabel("Setor 1", this);
    textoSetorAtual->move(360, 40);

    entradaNomeSetor = new QLineEdit(this);
    entradaNomeSetor->setGeometry(400, 30, 90, 40);
    connect(entradaNomeSetor, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                nomeSetor = texto;
            });

    entradaValorSetor = new QLineEdit(this);
    entradaValorSetor->setGeometry(500, 30, 50, 40);
    connect(entradaValorSetor, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                valorSetor = texto.toInt();
            });

    //inserir texto para a cor do setor em hexadecimal (inicia com #FF0000, vermelho)
    entradaCorSetor = new QLineEdit("#FF0000", this);
    entradaCorSetor->setGeometry(560, 30, 75, 40);
    corSetor = "#FF0000"; // valor inicial padrão
    connect(entradaCorSetor, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                corSetor = texto;
            });

    //botão de desenhar o gráfico
    botaoDesenharGrafico = new QPushButton("Desenhar gráfico", this);
    QObject::connect(botaoDesenharGrafico, SIGNAL(clicked(bool)), this, SLOT(desenhoGraficoSetores()));
    botaoDesenharGrafico->setFixedSize(100, 40);
    botaoDesenharGrafico->move(750, 30);

    //botão para criar o próximo setor
    botaoNovoSetor = new QPushButton("Próximo Setor", this);
    QObject::connect(botaoNovoSetor, SIGNAL(clicked(bool)), this, SLOT(criarNovoSetor()));
    botaoNovoSetor->setFixedSize(100, 40);
    botaoNovoSetor->move(645, 30);

    aviso = new QLabel("", this); //texto de aviso caso o usuario insira valores invalidos
    aviso->setMinimumWidth(500); //aumentar o tamanho para não cortar o texto quando ele for alterado
    aviso->move(400, 80);

    cena = new QGraphicsScene;
    view = new QGraphicsView(cena, this);
    view->setGeometry(0, 0, 850, 350);
    view->move(50, 100);
}

void GraficoSetores::criarNovoSetor() {
    QColor testeCor(corSetor); //testa se a string hex colocada é válida

    if(nomeSetor != "" && valorSetor > 0 && testeCor.isValid()) {
        aviso->setText(""); //Valores enviados são validos, tira o aviso de erro, caso tenha

        //guarda nos vetores o nome, valor e cor que o usuário escreveu
        nomesSetores.push_back(nomeSetor);
        valoresSetores.push_back(valorSetor);
        coresSetores.push_back(corSetor);

        //atualizar texto que indica o número do próximo setor a ser inserido
        textoSetorAtual->setText("Setor " + QString::number(valoresSetores.size() + 1));

        //volta a cor padrão para #FF0000
        entradaCorSetor->setText("#FF0000");
        corSetor = "#FF0000";
    } else {
        aviso->setText("Invalido: insira um nome, valor maior que 0 e uma cor Hex válida (Ex: #FF0000)");
    }
}

void GraficoSetores::desenhoGraficoSetores() {
    if (valoresSetores.size() < 1) {
        aviso->setText("Invalido: Insira no mínimo 1 setor para desenhar o gráfico");
        return;
    }
    //limpa os elementos anteriores (setores e legendas) para depois redesenhar
    cena->clear();
    setores.clear();
    legendaQuadrados.clear();
    legendaTextos.clear();

    // calcular a soma total de todos os valores dos setores
    float total = 0;
    for (int i = 0; i < valoresSetores.size(); i++) {
        total += valoresSetores[i];
    }
    int anguloAtual = 0;

    for (int i = 0; i < valoresSetores.size(); i++) {
        //calcula a proporção do setor em relação a 360 graus, multiplica por 16 pois o QT trabalha com angulos em 1/16
        int proporcao = qRound((valoresSetores[i] / total) * 360.0f)*16.0f;

        //cria o setor
        QGraphicsEllipseItem *setor = cena->addEllipse(50, 20, 300, 300);
        setor->setStartAngle(anguloAtual);
        setor->setSpanAngle(proporcao);

        //aplica a cor definida pelo usuário
        setor->setBrush(QBrush(QColor(coresSetores[i])));
        setor->setPen(QPen(Qt::black));
        setores.push_back(setor);

        //atualiza o ângulo inicial do próximo setor
        anguloAtual += proporcao;

        //posisao Y da legenda que mostra o que cada cor do círculo significa
        float posLegendaY = 20 + (i * 25);

        QGraphicsRectItem *quadradoCor = cena->addRect(420, posLegendaY + 4, 15, 15);
        quadradoCor->setBrush(QBrush(QColor(coresSetores[i])));
        quadradoCor->setPen(QPen(Qt::black));
        legendaQuadrados.push_back(quadradoCor);

        //texto que mostra o nome e o valor da cor
        QString textoLegendaStr = nomesSetores[i] + " (" + QString::number(valoresSetores[i]) + ")";
        QGraphicsTextItem *textoLegenda = cena->addText(textoLegendaStr);
        textoLegenda->setPos(420 + 22,posLegendaY);
        legendaTextos.push_back(textoLegenda);
    }
}

void GraficoSetores::voltar() {
    if (telaJanelaPrincipal) {
        telaJanelaPrincipal->show(); // mostra a janela principal de volta
    }
    close(); // fecha a janela atual
}