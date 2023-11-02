#include "filasequencial.h"
#include "ui_filasequencial.h"

QString widgetStyles5 = "background: #fff; "
                        "color: #000721;"
                        "height: 500px; "
                        "border-radius: 10px;"
                        "height: 500px;"
                        "font-size: 15px;"
                        "font-weight: 400; ";

QString butonsL5 = "QPushButton {"
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

QString elementoLista5 = "QPushButton {"
                         "   background: #fff; /* Estilo padrão */"
                         "   color: #000721; /* Estilo padrão */"
                         "   padding: 10px; /* Estilo padrão */"
                         "   font-size: 15px; /* Estilo padrão */"
                         "   height: 20px;"
                         "   max-width: 40px;"
                         "   border-radius: 10px; /* Estilo padrão */"
                         "   font-weight: 400; /* Estilo padrão */"
                         "}";
QString elementoListaEfeito5 = "QPushButton {"
                               "   background: #000; /* Estilo padrão */"
                               "   color: #fff; /* Estilo padrão */"
                               "   padding: 10px; /* Estilo padrão */"
                               "   font-size: 15px; /* Estilo padrão */"
                               "   height: 25px;"
                               "   max-width: 45px;"
                               "   border-radius: 10px; /* Estilo padrão */"
                               "   font-weight: 400; /* Estilo padrão */"
                               "}";


filaSequencial::filaSequencial(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::filaSequencial),
    mainWindow(mainWindow) // Inicialize o ponteiro para a MainWindow
{

    colorChangeTimer = new QTimer(this);
    connect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(changeButtonColor()));
    colorChangeTimer->setSingleShot(true); // só queremos que ele seja disparado uma vez
    restoreColorTimer = new QTimer(this);
    connect(restoreColorTimer, SIGNAL(timeout()), this, SLOT(restoreButtonColor()));
    restoreColorTimer->setSingleShot(true); // só queremos que ele seja disparado uma vez

    ui->setupUi(this);
    setStyleSheet("background: #000721; max-width: 700px; width: 700px; max-height: 700px; color: #fff;"); //bacground da aplicação
    setGeometry(0, 0, 700, 700);
    setMinimumSize(700, 700);

    ui->pushButton1->setStyleSheet(butonsL5);
    ui->label->setStyleSheet("height: 30px;");
    ui->label->setStyleSheet("color: #fff; font-size: 25px; font-weight: 900;");
    ui->widget_2->setStyleSheet(widgetStyles5);
    ui->widget_2->setMinimumSize(170, 280);
    ui->verticalLayoutWidget_2->setMinimumSize(160, 275);
    ui->lineEdit_2->setStyleSheet("background-color: #CDCFCD; height: 35px;");
    ui->pushButton_2->setStyleSheet(butonsL5);
    ui->pushButton_4->setStyleSheet(butonsL5);
    ui->pushButton->setStyleSheet(butonsL5);
    //layout da pilha
    ui->horizontalLayout_5->setAlignment(Qt::AlignCenter);

    // Suponha que 'pilha' seja uma QList ou QVector contendo dados.
    FilaSeq filaSequen;
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(clickBotaoAdd()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(removerElemento()));
    connect(ui->pushButton1, SIGNAL(clicked(bool)), this, SLOT(abrirJanelaMenu()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(buscaElemento()));
}

filaSequencial::~filaSequencial()
{
    delete ui;
}

void filaSequencial::addElemento(){
    QString elementoStr = ui->lineEdit_2->text();

    bool ok;
    int elemento = elementoStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (elemento não é um número válido).
        return;
    }
    if (filaSequen.insere(elemento)) {
        printf("Elemento inserido com sucesso.\n");

        QPushButton* botao = new QPushButton(QString::number(elemento));
        botao->setStyleSheet(elementoLista5);
        QHBoxLayout* layout = ui->horizontalLayout_5;

        // A posição não existe, então adicione um novo botão.
        layout->addWidget(botao);
        int qtElementos = layout->count();
        QLayoutItem* item = layout->itemAt(qtElementos -1);
        QPushButton* btn = qobject_cast<QPushButton*>(item->widget());
        if(btn){
            btn->setStyleSheet("QPushButton {"
                               "   background: #0238FF; /* Estilo padrão */"
                         "   color: #000721; /* Estilo padrão */"
                         "   padding: 10px; /* Estilo padrão */"
                         "   font-size: 15px; /* Estilo padrão */"
                         "   height: 20px;"
                         "   max-width: 40px;"
                         "   border-radius: 10px; /* Estilo padrão */"
                         "   font-weight: 400; /* Estilo padrão */"
                               "}");
        }
        item = layout->itemAt(0);
        btn = qobject_cast<QPushButton*>(item->widget());
        if(btn){
            btn->setStyleSheet("QPushButton {"
                               "   background: #0238FF; /* Estilo padrão */"
                         "   color: #000721; /* Estilo padrão */"
                         "   padding: 10px; /* Estilo padrão */"
                         "   font-size: 15px; /* Estilo padrão */"
                         "   height: 20px;"
                         "   max-width: 40px;"
                         "   border-radius: 10px; /* Estilo padrão */"
                         "   font-weight: 400; /* Estilo padrão */"
                               "}");
        }
    } else {
        printf("Falha ao inserir elemento.\n");
    }
}

// Função para mudar a cor dos botões
void filaSequencial::changeButtonColor() {

    // Suponha que 'filaSequencial' seja a instância da sua classe FilaSeq.
    int numButtons = ui->horizontalLayout_5->count();
    printf("%d %d\n",numButtons, currentButtonIndex);
    if(numButtons == 0){
        addElemento();
        return;
    }
    printf("%d", currentButtonIndex);
    // Se chegarmos ao final da fila, pare o timer
    if (currentButtonIndex == 0 && removeelemento == 1) {
        printf("remove %b", removeelemento);
        removerElemento();

        colorChangeTimer->stop();
        return;
    }else if(currentButtonIndex == numButtons){
        addElemento();
    }
    if (currentButtonIndex < numButtons) {
        // Obtenha o botão atual
        QLayoutItem* item = ui->horizontalLayout_5->itemAt(currentButtonIndex);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                // Mude a cor do botão (exemplo: para vermelho)
                button->setStyleSheet(elementoListaEfeito5);
                currentChangedButton = button;
                restoreColorTimer->start(500); // espera 1 segundo para restaurar a cor
            }
        }

        // Avance para o próximo botão
        currentButtonIndex++;

    }

}

void filaSequencial::restoreButtonColor() {

    QString posStr = ui->lineEdit_2->text(); // Suponha que você tenha uma caixa de texto para inserir a posição a ser removida.

    bool ok;
    int pos = posStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (posição não é um número válido).
        return;
    }


    if(pos == 0 && removeelemento == true){
        removeelemento = false;
        return;
    }
    if (currentChangedButton) {
        currentChangedButton->setStyleSheet(elementoLista5); // supondo que "elementoLista" seja a folha de estilo original
        currentChangedButton = nullptr; // reset para null
        colorChangeTimer->start(100); // reinicie o colorChangeTimer para alterar o próximo botão
    }
}

void filaSequencial::removerElemento() {


    // Suponha que a instância de FilaSeq já foi criada no construtor.
    int elemento = filaSequen.remove();
    printf("%d", elemento);

    if (elemento >= 0) {
        printf("Elemento removido com sucesso.\n");

        // Atualize a interface gráfica para refletir a remoção.
        // Por exemplo, você pode remover o botão correspondente à posição 'pos' da interface.
        QLayoutItem* item = ui->horizontalLayout_5->itemAt(0);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                ui->horizontalLayout_5->removeWidget(button);
                delete button; // Certifique-se de liberar a memória do botão removido.
                // Depois de remover e excluir o botão, ajuste o layout para que os outros botões se reposicionem corretamente.
                ui->horizontalLayout_5->update();
            }
        }
    } else {
        printf("Falha ao remover elemento.\n");
    }
}

void filaSequencial::clickBotaoAdd(){
    currentButtonIndex = 0;
    changeButtonColor();
}

void filaSequencial::clickBotaoRemove(){
    currentButtonIndex = 0;
    removeelemento = true;
    changeButtonColor();
}

void filaSequencial::abrirJanelaMenu() {
    if (mainWindow) {
        this->hide(); // Feche a janela atual
        mainWindow->show(); // Mostre a MainWindow existente
    }
}

void filaSequencial::buscaElemento() {

    int numButtons = ui->horizontalLayout_5->count();

    // Obtenha o botão correspondente à posição.
    QLayoutItem* item = ui->horizontalLayout_5->itemAt(0);
    printf("entouremm522\n");
    if (item) {
        printf("entouremm");
        QPushButton* button = qobject_cast<QPushButton*>(item->widget());
        if (button) {
            // Animação de destaque (por exemplo, mudar a cor de fundo).
            button->setStyleSheet(elementoListaEfeito5); // Altere as cores conforme necessário.
            currentChangedButton = button;
            currentButtonIndex = 0;
            // Aguarde um curto período de tempo para desfazer o destaque.
            QTimer::singleShot(1000, this, [this, numButtons]() {
                currentChangedButton->setStyleSheet(elementoLista5);
            });
        }
    }
}
