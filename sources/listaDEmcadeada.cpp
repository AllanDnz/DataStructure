#include "listaDEmcadeada.h"
#include "ui_listaDEmcadeada.h"

QString widgetStyles3 = "background: #fff; "
                       "color: #000721;"
                       "height: 500px; "
                       "border-radius: 10px;"
                       "height: 500px;"
                       "font-size: 15px;"
                       "font-weight: 400; ";

QString butonsL3 = "QPushButton {"
                 "   background: #000721; /* Estilo padrão */"
                 "   color: #fff; /* Estilo padrão */"
                 "   padding: 10px; /* Estilo padrão */"
                 "   font-size: 15px; /* Estilo padrão */"
                 "   height: 20px;"
                 "   max-width: 200px;"
                 "   border-radius: 10px; /* Estilo padrão */"
                 "   font-weight: 400; /* Estilo padrão */"
                 "}"
                 "QPushButton:focus,"
                 "QPushButton:hover"
                 " {"
                 "   border: none;"
                 "   list-style: none;"
                 "outline: none;"
                 "   background: #01696f; /* Estilo quando o botão está em foco */"
                 "   color: #fff; /* Estilo quando o botão está em foco */"
                 "}";

QString elementoLista3 = "QPushButton {"
                        "   background: #fff; /* Estilo padrão */"
                        "   color: #000721; /* Estilo padrão */"
                        "   padding: 10px; /* Estilo padrão */"
                        "   font-size: 15px; /* Estilo padrão */"
                        "   height: 20px;"
                        "   max-width: 100px;"
                        "   border-radius: 10px; /* Estilo padrão */"
                        "   font-weight: 400; /* Estilo padrão */"
                        "}";
QString elementoListaEfeito3 = "QPushButton {"
                        "   background: #000; /* Estilo padrão */"
                        "   color: #fff; /* Estilo padrão */"
                        "   padding: 10px; /* Estilo padrão */"
                        "   font-size: 15px; /* Estilo padrão */"
                        "   height: 25px;"
                        "   max-width: 45px;"
                        "   border-radius: 10px; /* Estilo padrão */"
                        "   font-weight: 400; /* Estilo padrão */"
                        "}";

listaDEmcadeada::listaDEmcadeada(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::listaDEmcadeada),
    mainWindow(mainWindow) // Inicialize o ponteiro para a MainWindow
{
    //connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaMenu()));


    colorChangeTimer = new QTimer(this);
    connect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(changeButtonColor()));
    colorChangeTimer->setSingleShot(true); // só queremos que ele seja disparado uma vez
    restoreColorTimer = new QTimer(this);
    connect(restoreColorTimer, SIGNAL(timeout()), this, SLOT(restoreButtonColor()));
    restoreColorTimer->setSingleShot(true); // só queremos que ele seja disparado uma vez


    ui->setupUi(this);
    setStyleSheet("background: #000721; max-width: 700px; width: 700px; max-height: 600px; color: #fff;"); //bacground da aplicação
    setGeometry(0, 0, 700, 400);
    setMinimumSize(1000, 500);

    //ui->pushButton->setStyleSheet("height: 30px; width: 150px; border-radius: 10px; background: #fff; color: #000721;");
    ui->pushButton1->setStyleSheet(butonsL3);
    ui->label->setStyleSheet("height: 30px;");
    ui->label->setStyleSheet("color: #fff; font-size: 25px; font-weight: 900;");
    ui->widget_2->setStyleSheet(widgetStyles3);
    ui->widget_2->setMinimumSize(170, 280);
    ui->verticalLayoutWidget_2->setMinimumSize(160, 275);
    ui->lineEdit_1->setStyleSheet("background-color: #CDCFCD; height: 35px;");
    ui->lineEdit_2->setStyleSheet("background-color: #CDCFCD; height: 35px;");
    ui->pushButton_2->setStyleSheet(butonsL3);
    ui->pushButton_4->setStyleSheet(butonsL3);
    ui->pushButton_10->setStyleSheet(butonsL3);
    //layout da lista
    ui->horizontalLayout_5->setAlignment(Qt::AlignCenter);

    // Suponha que 'lista' seja uma QList ou QVector contendo dados.
    LDE lista2;
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(clickBotaoAdd()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(removerElemento()));
    connect(ui->pushButton1, SIGNAL(clicked(bool)), this, SLOT(abrirJanelaMenu()));
    connect(ui->pushButton_10, SIGNAL(clicked(bool)), this, SLOT(buscaElemento()));
     /*QList<int> lista = {10, 20, 30, 40, 50}; // Exemplo de dados na lista.

    // Suponha que você tenha um QHBoxLayout chamado 'horizontalLayout_5'.
    QHBoxLayout *layout = ui->horizontalLayout_5; // Substitua 'ui' pelo nome da sua classe UI.

    int larguraDaArea = 280; // Largura da área onde deseja exibir os quadrados.

    foreach (int elemento, lista) {
        QPushButton *botao = new QPushButton(QString::number(elemento));
        botao->setFixedSize(elemento * larguraDaArea / 100, 30); // Ajuste o tamanho conforme necessário.

        layout->addWidget(botao);
    }*/

}

listaDEmcadeada::~listaDEmcadeada()
{
    delete ui;
}

void listaDEmcadeada::addElemento(){
    QString elementoStr = ui->lineEdit_1->text();
    QString posStr = ui->lineEdit_2->text();

    bool ok;
    int elemento = elementoStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (elemento não é um número válido).
        return;
    }

    int pos = posStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (posição não é um número válido).
        return;
    }

    // Suponha que a instância de ListaSeq já foi criada no construtor.
    if (lista2.insere(pos, elemento)) {
        printf("Elemento inserido com sucesso.\n");
        QPushButton* botao = new QPushButton(QString::number(elemento));
        botao->setStyleSheet(elementoLista3);
        //botao->setFixedSize(elemento * 280 / 100, 30); // Ajuste o tamanho conforme necessário.
        QHBoxLayout* layout = ui->horizontalLayout_5; // Substitua 'ui' pelo nome da sua classe UI.
        QPushButton* botaoAnt = nullptr;
        printf("%d\n",  layout->count());
        if(layout->count() == 0){
            layout->addWidget(botao);
        }
        // Verifique se já existe um botão na posição especificada.
        else if ((pos - 1) < layout->count()) {
            botao->setText(QString("%1 --->").arg(elemento));
            layout->insertWidget(pos - 1, botao);
        } else if((pos) > layout->count()){
                // Verifique se já existe um botão na posição especificada.
                    QLayoutItem* item = layout->itemAt(pos - 2);
                    if (item) {
                        // Obtenha o botão existente.
                        botaoAnt = qobject_cast<QPushButton*>(item->widget());
                        // Se o botão existir, obtenha seu texto atual.
                        QString textoAtual = botaoAnt->text();

                // Atualize o texto do botão com o valor atual e adicione a seta (->).
                botaoAnt->setText(QString("%1 --->").arg(textoAtual));
                botao->setText(QString("<--- %1").arg(elemento));
                layout->addWidget(botao);
                    }
        } else {
            // A posição não existe, então adicione um novo botão.
            layout->addWidget(botao);
        }

    } else {
        printf("Falha ao inserir elemento.\n");
    }
}

// Função para mudar a cor dos botões
void listaDEmcadeada::changeButtonColor() {
    QString posStr = ui->lineEdit_2->text(); // Suponha que você tenha uma caixa de texto para inserir a posição a ser removida.

    bool ok;
    int pos = posStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (posição não é um número válido).
        return;
    }

    // Suponha que 'lista2' seja a instância da sua classe ListaSeq.
    int numButtons = ui->horizontalLayout_5->count();
    printf("%d %d\n",numButtons, currentButtonIndex);
    if(numButtons == 0){
            addElemento();
        return;
    }
    printf("%d %d", pos, currentButtonIndex);
    // Se chegarmos ao final da lista, pare o timer
    if (currentButtonIndex == numButtons || pos <= currentButtonIndex) {
            printf("remove %b", removeelemento);
            if(removeelemento){
            removerElemento();
            //removeelemento = false;
            }else{
            addElemento();
            }
            colorChangeTimer->stop();
            return;
    }
    if (currentButtonIndex < numButtons && pos >= currentButtonIndex) {
        // Obtenha o botão atual
        QLayoutItem* item = ui->horizontalLayout_5->itemAt(currentButtonIndex);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                // Mude a cor do botão (exemplo: para vermelho)
                button->setStyleSheet(elementoListaEfeito3);
                currentChangedButton = button;
                restoreColorTimer->start(500); // espera 1 segundo para restaurar a cor
            }
        }

        // Avance para o próximo botão
        currentButtonIndex++;

    }

}

void listaDEmcadeada::restoreButtonColor() {
     int numButtons = ui->horizontalLayout_5->count();
    QString posStr = ui->lineEdit_2->text(); // Suponha que você tenha uma caixa de texto para inserir a posição a ser removida.

    bool ok;
    int pos = posStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (posição não é um número válido).
        return;
    }
    if(pos == numButtons && removeelemento == true){
        removeelemento = false;
        return;
    }
    if (currentChangedButton) {
        currentChangedButton->setStyleSheet(elementoLista3); // supondo que "elementoLista" seja a folha de estilo original
        currentChangedButton = nullptr; // reset para null
        colorChangeTimer->start(100); // reinicie o colorChangeTimer para alterar o próximo botão
    }
}

void listaDEmcadeada::removerElemento() {
    QString posStr = ui->lineEdit_2->text(); // Suponha que você tenha uma caixa de texto para inserir a posição a ser removida.
    QHBoxLayout* layout = ui->horizontalLayout_5;

    bool ok;
    int pos = posStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (posição não é um número válido).
        return;
    }

    // Suponha que a instância de ListaSeq já foi criada no construtor.
    int elemento = lista2.remove(pos);
    printf("%d", elemento);

    if (elemento >= 0) {
        printf("Elemento removido com sucesso.\n");

        // Atualize a interface gráfica para refletir a remoção.
        // Por exemplo, você pode remover o botão correspondente à posição 'pos' da interface.
        QLayoutItem* item = ui->horizontalLayout_5->itemAt(pos - 1);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                ui->horizontalLayout_5->removeWidget(button);
                printf("%d %d\n", pos, layout->count());
                if(pos - 1 == layout->count()){
                    QLayoutItem* item = layout->itemAt(pos - 2);
                    if (item) {
                        printf("entoruuu");
                        // Obtenha o botão existente.
                        QPushButton* botaoAnt = qobject_cast<QPushButton*>(item->widget());
                        // Se o botão existir, obtenha seu texto atual.
                        QString textoAtual = botaoAnt->text();
                        int indexSeta = textoAtual.indexOf("--->");
                        if (indexSeta != -1) {
                            textoAtual = textoAtual.left(indexSeta);
                        }

                        // Atualize o texto do botão com o valor atual e adicione a seta (->).
                        botaoAnt->setText(QString("%1").arg(textoAtual));
                    }
                }
                delete button; // Certifique-se de liberar a memória do botão removido.
                // Depois de remover e excluir o botão, ajuste o layout para que os outros botões se reposicionem corretamente.
                ui->horizontalLayout_5->update();
            }
        }


    } else {
        printf("Falha ao remover elemento.\n");
    }
}

void listaDEmcadeada::clickBotaoAdd(){
    currentButtonIndex = 0;
    changeButtonColor();
}

void listaDEmcadeada::clickBotaoRemove(){
    currentButtonIndex = 0;
    removeelemento = true;
    changeButtonColor();
}

void listaDEmcadeada::abrirJanelaMenu() {
    if (mainWindow) {
        this->hide(); // Feche a janela atual
        mainWindow->show(); // Mostre a MainWindow existente
    }
}

void listaDEmcadeada::buscaElemento() {
    QString elementoStr = ui->lineEdit_1->text();
    QString posStr = ui->lineEdit_2->text();
    bool ok;
    int position = 0;
    position = posStr.toInt(&ok);

    if(position > 0){
        printf("entourshoww %d\n", position);
    }else if(elementoStr.toInt(&ok) >= 0){
        position = lista2.posicao(elementoStr.toInt(&ok));
    }else{
        return;
    }

    if(position == -1){
        return;
    }

    // Obtenha o botão correspondente à posição.
    QLayoutItem* item = ui->horizontalLayout_5->itemAt(position -1);
    printf("entouremm522\n");
    if (item) {
        printf("entouremm");
        QPushButton* button = qobject_cast<QPushButton*>(item->widget());
        if (button) {
            // Animação de destaque (por exemplo, mudar a cor de fundo).
            button->setStyleSheet(elementoListaEfeito3); // Altere as cores conforme necessário.
            currentChangedButton = button;
            currentButtonIndex = position -1;
            // Aguarde um curto período de tempo para desfazer o destaque.
            QTimer::singleShot(1000, this, [this, position]() {
                currentChangedButton->setStyleSheet(elementoLista3);
            });
        }
    }
}
