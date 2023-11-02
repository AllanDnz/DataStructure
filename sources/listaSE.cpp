#include "listaSE.h"
#include "ui_listaSE.h"

QString widgetStyles2 = "background: #fff; "
                       "color: #000721;"
                       "height: 500px; "
                       "border-radius: 10px;"
                       "height: 500px;"
                       "font-size: 15px;"
                       "font-weight: 400; ";

QString butonsL2 = "QPushButton {"
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

QString elementoLista2 = "QPushButton {"
                        "   background: #fff; /* Estilo padrão */"
                        "   color: #000721; /* Estilo padrão */"
                        "   padding: 10px; /* Estilo padrão */"
                        "   font-size: 15px; /* Estilo padrão */"
                        "   height: 20px;"
                        "   max-width: 40px;"
                        "   border-radius: 10px; /* Estilo padrão */"
                        "   font-weight: 400; /* Estilo padrão */"
                        "}";
QString elementoLista2Efeito = "QPushButton {"
                              "   background: #000; /* Estilo padrão */"
                              "   color: #fff; /* Estilo padrão */"
                              "   padding: 10px; /* Estilo padrão */"
                              "   font-size: 15px; /* Estilo padrão */"
                              "   height: 25px;"
                              "   max-width: 45px;"
                              "   border-radius: 10px; /* Estilo padrão */"
                              "   font-weight: 400; /* Estilo padrão */"
                              "}";


listaSE::listaSE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listaSE)
{
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
    ui->pushButton->setStyleSheet(butonsL2);
    ui->label->setStyleSheet("height: 30px;");
    ui->label->setStyleSheet("color: #fff; font-size: 25px; font-weight: 900;");
    ui->widget_2->setStyleSheet(widgetStyles2);
    ui->widget_2->setMinimumSize(170, 280);
    ui->verticalLayoutWidget_2->setMinimumSize(160, 275);
    ui->lineEdit_1->setStyleSheet("background-color: #CDCFCD; height: 35px;");
    ui->lineEdit_2->setStyleSheet("background-color: #CDCFCD; height: 35px;");
    ui->pushButton_2->setStyleSheet(butonsL2);
    ui->pushButton_4->setStyleSheet(butonsL2);
    //layout da lista
    ui->horizontalLayout_5->setAlignment(Qt::AlignCenter);

    LDE lista3;
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(clickBotaoAdd()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(removerElemento()));
}

listaSE::~listaSE()
{
    delete ui;
}

void listaSE::addElemento(){
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
    if (lista3.insere(pos, elemento)) {
        printf("Elemento inserido com sucesso.\n");

        QPushButton* botao = new QPushButton(QString::number(elemento));
        botao->setStyleSheet(elementoLista2);
        //botao->setFixedSize(elemento * 280 / 100, 30); // Ajuste o tamanho conforme necessário.
        QHBoxLayout* layout = ui->horizontalLayout_5; // Substitua 'ui' pelo nome da sua classe UI.

        // Verifique se já existe um botão na posição especificada.
        if ((pos - 1) < layout->count()) {
            QLayoutItem* item = layout->itemAt(pos-1);
            // if (item) {
            //     // Substitua o texto do botão existente.
            //     QPushButton* existingButton = qobject_cast<QPushButton*>(item->widget());
            //     if (existingButton) {
            //         existingButton->setText(QString::number(elemento));
            //     }
            // }
        } else {
            // A posição não existe, então adicione um novo botão.
            layout->addWidget(botao);
        }
    } else {
        printf("Falha ao inserir elemento.\n");
    }
}

// Função para mudar a cor dos botões
void listaSE::changeButtonColor() {
    // Suponha que 'lista2' seja a instância da sua classe ListaSeq.
    int numButtons = ui->horizontalLayout_5->count();
    printf("%d %d\n",numButtons, currentButtonIndex);
    if(numButtons == 0){
        addElemento();
    }
    if (currentButtonIndex < numButtons) {
        // Obtenha o botão atual
        QLayoutItem* item = ui->horizontalLayout_5->itemAt(currentButtonIndex);
        if (item) {
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                // Mude a cor do botão (exemplo: para vermelho)
                button->setStyleSheet(elementoLista2Efeito);
                currentChangedButton = button;
                restoreColorTimer->start(500); // espera 1 segundo para restaurar a cor
            }
        }

        // Avance para o próximo botão
        currentButtonIndex++;

    }
    // Se chegarmos ao final da lista, pare o timer
    if (currentButtonIndex == numButtons) {
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

}

void listaSE::restoreButtonColor() {
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
        currentChangedButton->setStyleSheet(elementoLista2); // supondo que "elementoLista2" seja a folha de estilo original
        currentChangedButton = nullptr; // reset para null
        colorChangeTimer->start(100); // reinicie o colorChangeTimer para alterar o próximo botão
    }
}

void listaSE::removerElemento() {
    printf("removendo");
    QString posStr = ui->lineEdit_2->text(); // Suponha que você tenha uma caixa de texto para inserir a posição a ser removida.

    bool ok;
    int pos = posStr.toInt(&ok);
    if (!ok) {
        // Lidar com erro de conversão (posição não é um número válido).
        return;
    }

    // Suponha que a instância de ListaSeq já foi criada no construtor.
    int elemento = lista3.remove(pos);
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
                delete button; // Certifique-se de liberar a memória do botão removido.
                // Depois de remover e excluir o botão, ajuste o layout para que os outros botões se reposicionem corretamente.
                ui->horizontalLayout_5->update();
            }
        }
    } else {
        printf("Falha ao remover elemento.\n");
    }
}

void listaSE::clickBotaoAdd(){
    currentButtonIndex = 0;
    changeButtonColor();
}

void listaSE::clickBotaoRemove(){
    currentButtonIndex = 0;
    removeelemento = true;
    changeButtonColor();
}
