# Implementação

>[!NOTE] 
 O processo de implementação começou com a criação de uma tela principal que serve como menu, onde o usuário escolhe o tipo de gráfico: gráfico de linhas, barras ou setores (também conhecido como gráfico de pizza). Isto foi feito usando C++ e o QTcreator.
 A janela principal e os 3 tipos de gráficos utilizam cada um uma classe própia em um header file, além do arquivo .cpp de cada um onde contém o códico fonte. Existe também o arquivo principal (main.cpp) que abre o programa na janela principal. 
 Foi usado a biblioteca QtWidgets para elementos gráficos como botões(QPushButton), caixas de inserção de texto(QLineEdit) e rótulos(QLabel), eles servem para o usuário realizar a entrada de dados para o gráfico. Para desenhar os gráficos em si, foi usada uma área chamada cena com as bibliotecas QGraphicsScene e QGraphicsView.
 Para a janela principal foram usadas 3 imagens para ilustrar cada tipo de gráfico que o programa permite criar. Para mostrar essas imagens no programa, foi usado uma função no QT chamada QT Resources para embutir as imagens direto no arquivo executável do programa, garantindo que elas nunca quebrem. Não importa em qual computador o software seja rodado ou caso o caminho mude.
 O gráfico de linhas usou a biblioteca QGraphicsLineItem para desenhar as linhas que fazem o gráfico. O gráfico de barras usou QGraphicsRectItem para fazer os retângulos que são as barras do gráfico. E o gráfico de setores usou QGraphicsEllipseItem para desenhar os setores (ou fatias) do gráfico.
>

<div align="center">

[Retroceder](projeto.md) | [Avançar](testes.md)

</div>
