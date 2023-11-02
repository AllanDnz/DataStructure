#include "pilha.h"
#include "ui_pilha.h"

QString widgetStyles4 = "background: #fff; "
                        "color: #000721;"
                        "height: 500px; "
                        "border-radius: 10px;"
                        "height: 500px;"
                        "font-size: 15px;"
                        "font-weight: 400; ";

QString butonsL4 = "QPushButton {"
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

QString elementoLista4 = "QPushButton {"
                         "   background: #0238FF; /* Estilo padrão */"
                         "   color: #000721; /* Estilo padrão */"
                         "   padding: 10px; /* Estilo padrão */"
                         "   font-size: 15px; /* Estilo padrão */"
                         "   height: 20px;"
                         "   max-width: 40px;"
                         "   border-radius: 10px; /* Estilo padrão */"
                         "   font-weight: 400; /* Estilo padrão */"
                         "}";
QString elementoListaEfeito4 = "QPushButton {"
                               "   background: #000; /* Estilo padrão */"
                               "   color: #fff; /* Estilo padrão */"
                               "   padding: 10px; /* Estilo padrão */"
                               "   font-size: 15px; /* Estilo padrão */"
                               "   height: 25px;"
                               "   max-width: 45px;"
                               "   border-radius: 10px; /* Estilo padrão */"
                               "   font-weight: 400; /* Estilo padrão */"
                               "}";


pilha::pilha(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::pilha),
    mainWindow(mainWindow) // Inicialize o ponteiro para a MainWindow
{

    colorChangeTimer = new QTimer(this);
    connect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(changeButtonColor()));
    colorChangeTimer->setSingleShot(true); // só queremos que ele seja disparado uma vez
    restoreColorTimer = new QTimer(this);
    connect(restoreColorTimer, SIGNAL(timeout()), this, SLOT(restoreButtonColor()));
    restoreColorTimer->setSingleShot(true); // só queremos que ele seja disparado uma vez

    ui->setupUi(this);
    setStyleSheet("background: #000721; max-width: 700px; width: 700px; max-height: 600px; color: #fff;"); //bacground da aplicação
    setGeometry(0, 0, 700, 600);
    setMinimumSize(1000, 600);

    ui->pushButton1->setStyleSheet(butonsL4);
    ui->label->setStyleSheet("height: 30px;");
    ui->label->setStyleSheet("color: #fff; font-size: 25px; font-weight: 900;");
    ui->widget_2->setStyleSheet(widgetStyles4);
    ui->widget_2->setMinimumSize(170, 280);
    ui->verticalLayoutWidget_2->setMinimumSize(160, 275);
    ui->lineEdit_1->setStyleSheet("background-color: #CDCFCD; height: 35px;");
    ui->pushButton_2->setStyleSheet(butonsL4);
    ui->pushButton_4->setStyleSheet(butonsL4);
    ui->pushButton->setStyleSheet(butonsL4);
    //layout da pilha
    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    // Suponha que 'pilha' seja uma QList ou QVector contendo dados.
    PilhaSeq pilhaSequencial;
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(clickBotaoAdd()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(removerElemento()));
    connect(ui->pushButton1, SIGNAL(clicked(bool)), this, SLOT(abrirJanelaMenu()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(buscaElemento()));
}

pilha::~pilha()
{
    delete ui;
}

void pilha::addElemento(){
    QString elementoStr = ui->lineEdit_1->text();

    bool ok;
    int elemento = elementoStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (elemento não é um número válido).
        return;
    }
    // Suponha que a instância de PilhaSeq já foi criada no construtor.
    if (pilhaSequencial.push(elemento)) {
        printf("Elemento inserido com sucesso.\n");

        QPushButton* botao = new QPushButton(QString::number(elemento));
        botao->setStyleSheet(elementoLista4);
        QVBoxLayout* layout = ui->verticalLayout; // Substitua 'ui' pelo nome da sua classe UI.

        layout->insertWidget(0, botao);
        int qtdElementos = layout->count();

        QLayoutItem* item = layout->itemAt(0);
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
        for( int i = 1; i < qtdElementos; i++ ){
            item = layout->itemAt(i);
            btn = qobject_cast<QPushButton*>(item->widget());
            if(btn){
                btn->setStyleSheet("QPushButton {"
                                   "   background: #fff; /* Estilo padrão */"
                                   "   color: #000721; /* Estilo padrão */"
                                   "   padding: 10px; /* Estilo padrão */"
                                   "   font-size: 15px; /* Estilo padrão */"
                                   "   height: 20px;"
                                   "   max-width: 40px;"
                                   "   border-radius: 10px; /* Estilo padrão */"
                                   "   font-weight: 400; /* Estilo padrão */"
                                   "}");
            }

        }

    } else {
        printf("Falha ao inserir elemento.\n");
    }
}

// Função para mudar a cor dos botões
void pilha::changeButtonColor() {

    // Suponha que 'pilhaSequencial' seja a instância da sua classe PilhaSeq.
    int numButtons = ui->verticalLayout->count();
    printf("%d %d\n",numButtons, currentButtonIndex);
    if(numButtons == 0){
        addElemento();
        return;
    }
    printf("%d", currentButtonIndex);
    // Se chegarmos ao final da lista, pare o timer
    //if (currentButtonIndex == 1) {
    printf("remove %b", removeelemento);
    if(removeelemento){
        removerElemento();
    }else{
        addElemento();
    }
    colorChangeTimer->stop();
    return;
    //}
    if (currentButtonIndex > 1) {
        // Obtenha o botão atual
        QLayoutItem* item = ui->verticalLayout->itemAt(currentButtonIndex);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                // Mude a cor do botão (exemplo: para vermelho)
                button->setStyleSheet(elementoListaEfeito4);
                currentChangedButton = button;
                restoreColorTimer->start(500); // espera 1 segundo para restaurar a cor
            }
        }

        // Avance para o próximo botão
        currentButtonIndex--;

    }

}

void pilha::restoreButtonColor() {
    if(removeelemento == true){
        removeelemento = false;
        return;
    }
    if (currentChangedButton) {
        currentChangedButton->setStyleSheet(elementoLista4); // supondo que "elementoLista" seja a folha de estilo original
        currentChangedButton = nullptr; // reset para null
        colorChangeTimer->start(100); // reinicie o colorChangeTimer para alterar o próximo botão
    }
}

void pilha::removerElemento() {

    // Suponha que a instância de PilhaSeq já foi criada no construtor.
    int elemento = pilhaSequencial.pop();
    printf("%d", elemento);

    if (elemento >= 0) {
        printf("Elemento removido com sucesso.\n");

        // Atualize a interface gráfica para refletir a remoção.
        // Por exemplo, você pode remover o botão correspondente à posição 'pos' da interface.
        QLayoutItem* item = ui->verticalLayout->itemAt(0);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                ui->verticalLayout->removeWidget(button);
                delete button; // Certifique-se de liberar a memória do botão removido.
                // Depois de remover e excluir o botão, ajuste o layout para que os outros botões se reposicionem corretamente.
                ui->verticalLayout->update();
            }
            item = ui->verticalLayout->itemAt(0);
            if(item){
                button = qobject_cast<QPushButton*>(item->widget());
                button->setStyleSheet(elementoLista4);
            }
        }
    } else {
        printf("Falha ao remover elemento.\n");
    }
}

void pilha::clickBotaoAdd(){
    int numButtons = ui->verticalLayout->count();
    currentButtonIndex = numButtons;
    changeButtonColor();
}

void pilha::clickBotaoRemove(){
    int numButtons = ui->verticalLayout->count();
    currentButtonIndex = numButtons;
    removeelemento = true;
    changeButtonColor();
}

void pilha::abrirJanelaMenu() {
    if (mainWindow) {
        this->hide(); // Feche a janela atual
        mainWindow->show(); // Mostre a MainWindow existente
    }
}

void pilha::buscaElemento() {

    int pos = 1;

    // Obtenha o botão correspondente à posição.
    QLayoutItem* item = ui->verticalLayout->itemAt(0);
    printf("entouremm522\n");
    if (item) {
        printf("entouremm");
        QPushButton* button = qobject_cast<QPushButton*>(item->widget());
        if (button) {
            // Animação de destaque (por exemplo, mudar a cor de fundo).
            button->setStyleSheet(elementoListaEfeito4); // Altere as cores conforme necessário.
            currentChangedButton = button;
            currentButtonIndex = 0;
            // Aguarde um curto período de tempo para desfazer o destaque.
            QTimer::singleShot(1000, this, [this, pos]() {
                currentChangedButton->setStyleSheet(elementoLista4);
            });
        }
    }
}

