#include "graficobarras.h"
#include "janelaprincipal.h"

GraficoBarras::GraficoBarras(janelaprincipal *principal, QWidget *parent)
    : QWidget(parent), telaJanelaPrincipal(principal) {

    //dar nome ao eixo vertical
    textoEixoY = new QLabel("Nome do eixo Y:",this);
    textoEixoY->move(180, 10);
    entradaNomeEixoY = new QLineEdit(this);
    entradaNomeEixoY->setGeometry(180, 30, 150, 30);
    connect(entradaNomeEixoY, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                nomeEixoY = entradaNomeEixoY->text(); //da o nome digitado para a variavel nomeEixoY
            });

    textoDadosBarra = new QLabel("Nome da Barra:               Valor:",this);
    textoDadosBarra->move(500, 10);

    //botar para voltar à tela principal
    botaoVoltar = new QPushButton("Voltar", this);
    QObject::connect(botaoVoltar, SIGNAL(clicked(bool)), this, SLOT(voltar()));
    botaoVoltar->setFixedSize(70, 40);
    botaoVoltar->move(350, 30);

    //contagem quantidade de barras do gráfico
    textoBarraAtual = new QLabel("Barra 1",this);
    textoBarraAtual->move(450, 40);

    entradaNomeBarra = new QLineEdit(this);
    entradaNomeBarra->setGeometry(500, 30, 90, 40); // Um pouco mais largo para caber texto
    connect(entradaNomeBarra, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                nomeBarra = texto;
            });

    entradaValorBarra = new QLineEdit(this);
    entradaValorBarra->setGeometry(610, 30, 60, 40);
    connect(entradaValorBarra, &QLineEdit::textChanged, this,
            [this](const QString &texto)
            {
                valorBarra = texto.toInt();
            });

    //botão de desenhar o gráfico
    botaoDesenharGrafico = new QPushButton("Desenhar gráfico", this);
    QObject::connect(botaoDesenharGrafico, SIGNAL(clicked(bool)), this, SLOT(calcularTamanhoBarras()));
    botaoDesenharGrafico->setFixedSize(100, 40);
    botaoDesenharGrafico->move(780, 30);

    //botão para criar a próxima barra
    botaoNovaBarra = new QPushButton("Próxima Barra", this);
    QObject::connect(botaoNovaBarra, SIGNAL(clicked(bool)), this, SLOT(criarNovaBarra()));
    botaoNovaBarra->setFixedSize(100, 40);
    botaoNovaBarra->move(680, 30);

    aviso = new QLabel("",this); //texto de aviso caso o usuario insira valores invalidos
    aviso->setMinimumWidth(400); //aumentar o tamanho para não cortar o texto quando ele for alterado
    aviso->move(400, 80);
    //QGraphicsScene para ser possível desenhar as barras do gráfico
    cena = new QGraphicsScene;
    view = new QGraphicsView(cena, this);
    view->setGeometry(0, 0, 850, 350);
    view->move(50,100);

    //texto que mostra o título dos eixo vertical (pode ser mudado depois)
    textoNomeEixoY = new QLabel("Eixo Y",this);
    textoNomeEixoY->setMinimumWidth(400);
    textoNomeEixoY->move(10, 80);
}

void GraficoBarras::criarNovaBarra() {
    if(nomeBarra != "" && valorBarra > 0) {
        aviso->setText(""); //Valores enviados são validos, tira o aviso de erro, caso tenha

        //guarda o nome e valor que o usuário escreveu para os vetores
        nomesBarras.push_back(nomeBarra);
        valoresBarras.push_back(valorBarra);

        //atualizar texto que indica o número da próxima barra a ser inserida
        textoBarraAtual->setText("Barra " + QString::number(valoresBarras.size() + 1));
    } else {
        aviso->setText("Invalido: insira um nome e um valor maior que 0");
    }
}

void GraficoBarras::calcularTamanhoBarras() {
    if(valoresBarras.size() >= 1) { //verifica se o usuario pelo menos inseriu 1 valor ou mais
        larguraDisponivel = 840.0f / valoresBarras.size();//calcular o fator de escala baseado no tamanho da tela (840 de largura)
        larguraBarra = larguraDisponivel * 0.7f;//70% do espaço é a barra, 30% é o espaçamento entre elas
        espacamento = larguraDisponivel * 0.3f;

        GraficoBarras::desenhoGraficoBarras();
    } else {
        aviso->setText("Invalido: Insira no mínimo 1 barra para desenhar o gráfico");
    }
}

void GraficoBarras::desenhoGraficoBarras() {
    if (nomeEixoY != "") { //adicionar o titulo que o usuario escolheu para os eixos, caso não seja vazio
        textoNomeEixoY->setText(nomeEixoY);
    }

    //limpa os elementos anteriores (barras, nomes e valores) para depois redesenhar
    for (int i = 0; i < barras.size(); i++) {
        cena->removeItem(barras[i]);
        delete barras[i];
        delete textoNomesBarras[i];
        delete textoValoresBarras[i];
    }
    barras.clear();
    textoNomesBarras.clear();
    textoValoresBarras.clear();

    // descobrir o valor máximo para fazer a proporção (a maior barra terá a altura total de 320)
    float maxVal = *std::max_element(valoresBarras.begin(), valoresBarras.end());

    for (int i = 0; i < valoresBarras.size(); i++) {
        //calcula a altura proporcional baseada no valor máximo
        float alturaBarra = (valoresBarras[i] / maxVal) * 320.0f;

        //posição horizontal da barra
        float posX = (i * larguraDisponivel) + (espacamento / 2.0f);

        //no Qt o Y cresce para baixo, então para a barra começar da base da cena (320):
        float posY = 320.0f - alturaBarra;

        //desenha o retângulo da barra atribuindo as respectivas posisoes e tamanho de cada barra
        barras.push_back(cena->addRect(posX, posY, larguraBarra, alturaBarra, QPen(Qt::black), QBrush(Qt::blue)));

        //cria o texto para exibir o valor da barra
        QLabel *labelValor = new QLabel(QString::number(valoresBarras[i]), this);
        labelValor->setMinimumWidth(larguraDisponivel);
        labelValor->setAlignment(Qt::AlignCenter);
        //centraliza a posisao horizontal do texto na barra e o coloca em cima dela
        labelValor->move(50 + posX - (espacamento / 2.0f), 100 + posY);
        labelValor->show();
        textoValoresBarras.push_back(labelValor);

        //cria o texto com o nome da barra logo abaixo do eixo X (lado de fora)
        QLabel *labelNome = new QLabel(nomesBarras[i], this);
        labelNome->setMinimumWidth(larguraDisponivel);
        labelNome->setAlignment(Qt::AlignCenter);
        //centraliza a posisao horizontal do texto na barra e o coloca em baixo dela
        labelNome->move(50 + posX - (espacamento / 2.0f), 455);
        labelNome->show();
        textoNomesBarras.push_back(labelNome);
    }
}

void GraficoBarras::voltar() {
    if (telaJanelaPrincipal) {
        telaJanelaPrincipal->show(); // mostra a janela principal de volta
    }
    close(); // fecha a janela atual
}
