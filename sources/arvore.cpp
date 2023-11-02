#include <iostream>
#include "arvore.h"
#include "ui_arvore.h"
#include "listasequencial.h"
#include <QTimer>
#include <QThread>
#include <windows.h>


Arvore::Arvore(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::Arvore),
    mainWindow(mainWindow),
    root(nullptr) // Inicializa a raiz da árvore como nula
{
    QTimer* timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(adicionarElementoAutomaticamente()));
    timer->start(100); // Define um intervalo de 1000 ms (1 segundo)

    ui->setupUi(this);
    setStyleSheet("background: #000721; max-width: 700px; width: 800px; max-height: 600px; color: #fff;");
    setGeometry(0, 0, 700, 400);
    setMinimumSize(1000, 500);

    //layout da arvore
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    QSpacerItem* spacer = new QSpacerItem(400, 200, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addItem(spacer);
    // Adicione seu conteúdo aqui, como botões, rótulos, etc.



    ui->horizontalLayout->setAlignment(Qt::AlignCenter);

    ui->pushButton->setStyleSheet(butonsL);
    ui->pushButton_2->setStyleSheet(butonsL);
    ui->pushButton_3->setStyleSheet(butonsL);
    ui->pushButton_4->setStyleSheet(butonsL);
    ui->pushButton_20->setStyleSheet(butonsL);

    ui->lineEdit->setStyleSheet("background-color: #CDCFCD; height: 35px; width: 100px; color: #000; margin: auto;");

    // Conecte os botões para adicionar e remover elementos
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(abrirJanelaMenu()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(addElemento()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(removerElemento()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(localizarElemento()));
    connect(ui->pushButton_20, SIGNAL(clicked(bool)), this, SLOT(adicionarElementoAutomaticamente()));

    ui->verticalLayout_2->setAlignment(Qt::AlignCenter);

    //layout arvore
    // Obtém as dimensões da janela principal
    int larguraJanela = this->width();
    int alturaJanela = this->height();

    // Calcula as novas dimensões para o ui->widget
    int novaLargura = larguraJanela * 0.9;  // 90% da largura
    int novaAltura = alturaJanela * 0.2;    // 20% da altura



}

Arvore::~Arvore() {
    // Libere a memória da árvore, chamando uma função de liberação
    delete ui;
}

Node* insert(Node* node, int elemento) {
    if (node == nullptr) {
        // Se o nó estiver vazio, crie um novo nó com o elemento
        return new Node(elemento);
    } else if (elemento < node->valor) {
        // Se o elemento for menor, insira na subárvore esquerda
        node->esquerda = insert(node->esquerda, elemento);
    } else if (elemento > node->valor) {
        // Se o elemento for maior, insira na subárvore direita
        node->direita = insert(node->direita, elemento);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current != nullptr && current->esquerda != nullptr) {
        current = current->esquerda;
    }
    return current;
}


Node* remove(Node* node, int elemento) {
    if (node == nullptr) {
        // A árvore está vazia ou o elemento não está presente.
        return node;
    }

    if (elemento < node->valor) {
        // O elemento a ser removido está na subárvore esquerda.
        node->esquerda = remove(node->esquerda, elemento);
    } else if (elemento > node->valor) {
        // O elemento a ser removido está na subárvore direita.
        node->direita = remove(node->direita, elemento);
    } else {
        // Encontrou o elemento a ser removido.
        if (node->esquerda == nullptr) {
            Node* temp = node->direita;
            delete node;
            return temp;
        } else if (node->direita == nullptr) {
            Node* temp = node->esquerda;
            delete node;
            return temp;
        }
        Node* temp = minValueNode(node->direita);
        node->valor = temp->valor;
        node->direita = remove(node->direita, temp->valor);
    }
    return node;
}



void Arvore::addElemento() {
    QString elementoStr = ui->lineEdit->text();
    bool ok;
    int elemento = elementoStr.toInt(&ok);

    if (ok) {
        root = insert(root, elemento);
        printf("Inserindo o elemento %d\n", elemento);

        // Crie um novo botão para representar o elemento.
        QPushButton* novoBotao = new QPushButton(QString::number(elemento), this);
        novoBotao->setStyleSheet("QPushButton {"
                                                "    width: 35px;"
                                                "    height: 35px;"
                                                "    background-color: transparent;"
                                                "    border: 2px solid #fff;"
                                                "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                "}");


        // Chame a função para posicionar o botão no layout vertical do widget.
        posicionarBotao(root, novoBotao);

        // Atualize a interface gráfica.
        this->repaint(); // Ou outra forma apropriada de atualização da interface gráfica.
    }
}
void Arvore::posicionarBotao(Node* currentNode, QPushButton* botao) {
    if (ui->verticalLayout_2->count() == 1) {
        // Se não houver botões, adicione o botão ao verticalLayout_2.
        ui->verticalLayout_2->addWidget(botao, 0, Qt::AlignHCenter);
    } else {
        // Aqui você pode fazer a lógica de comparação e adicionar o botão ao layout apropriado.
        // Por exemplo, compare o valor do botão com o valor do primeiro botão, que estará no índice 0.
        QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());

        if (primeiroBotao) {
            int valorBotao = botao->text().toInt();
            int valorPrimeiroBotao = primeiroBotao->text().toInt();
            if(valorPrimeiroBotao  == valorBotao){
                return;
            }
            if (valorBotao < valorPrimeiroBotao) {
                // Adicione o botão à esquerda.
                //verifica se existe botão aqui
                if(ui->verticalLayout_3->count() > 1){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao  == valorBotao){
                        return;
                    }
                    if(valorBotao < valorPrimeiroBotao){
                        if(ui->verticalLayout_5->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao  == valorBotao){
                                return;
                            }else
                                if(valorBotao < valorPrimeiroBotao){
                                    ui->verticalLayout_9->addWidget(botao, 0, Qt::AlignHCenter);
                                }else{
                                    ui->verticalLayout_10->addWidget(botao, 0, Qt::AlignHCenter);
                                }
                        }else{
                            ui->verticalLayout_5->addWidget(botao, 0, Qt::AlignHCenter);
                        }
                    }else
                        if(ui->verticalLayout_6->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao  == valorBotao){
                                return;
                            } else
                                if(valorBotao < valorPrimeiroBotao){
                                    if(ui->verticalLayout_11->count() > 1){
                                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_11->itemAt(1)->widget());
                                        valorPrimeiroBotao = primeiroBotao->text().toInt();
                                        if(valorPrimeiroBotao  == valorBotao){
                                            return;
                                        }
                                        ui->verticalLayout_11->addWidget(botao, 0, Qt::AlignHCenter);
                                    }else
                                        ui->verticalLayout_11->addWidget(botao, 0, Qt::AlignHCenter);
                                }else{
                                    if(ui->verticalLayout_12->count() > 1){
                                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_12->itemAt(1)->widget());
                                        valorPrimeiroBotao = primeiroBotao->text().toInt();
                                        if(valorPrimeiroBotao  == valorBotao){
                                            return;
                                        }
                                        ui->verticalLayout_12->addWidget(botao, 0, Qt::AlignHCenter);
                                    }else
                                        ui->verticalLayout_12->addWidget(botao, 0, Qt::AlignHCenter);
                                }
                        }else{
                            ui->verticalLayout_6->addWidget(botao, 0, Qt::AlignHCenter);
                        }
                }else{
                    ui->verticalLayout_3->addWidget(botao, 0, Qt::AlignHCenter);
                }
            } else {
                // Adicione o botão à direita.
                //verifica se existe botão aqui
                if(ui->verticalLayout_4->count() > 1){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao  == valorBotao){
                        return;
                    }
                    if(valorBotao < valorPrimeiroBotao){
                        if(ui->verticalLayout_7->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao  == valorBotao){
                                return;
                            }
                            if(valorBotao < valorPrimeiroBotao){
                                if(ui->verticalLayout_13->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_13->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao  == valorBotao){
                                        return;
                                    }
                                    ui->verticalLayout_13->addWidget(botao, 0, Qt::AlignHCenter);
                                }else{
                                    ui->verticalLayout_13->addWidget(botao, 0, Qt::AlignHCenter);
                                }
                            }else{
                                if(ui->verticalLayout_14->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_14->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao  == valorBotao){
                                        return;
                                    }
                                    ui->verticalLayout_14->addWidget(botao, 0, Qt::AlignHCenter);
                                }else
                                    ui->verticalLayout_14->addWidget(botao, 0, Qt::AlignHCenter);
                            }
                        }else{
                            ui->verticalLayout_7->addWidget(botao, 0, Qt::AlignHCenter);
                        }
                    }else
                        if(ui->verticalLayout_8->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao  == valorBotao){
                                return;
                            }
                            if(valorBotao < valorPrimeiroBotao){
                                if(ui->verticalLayout_15->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_15->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao  == valorBotao){
                                        return;
                                    }
                                    ui->verticalLayout_15->addWidget(botao, 0, Qt::AlignHCenter);
                                }else
                                    ui->verticalLayout_15->addWidget(botao, 0, Qt::AlignHCenter);
                            }else{
                                if(ui->verticalLayout_16->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_16->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao  == valorBotao){
                                        return;
                                    }
                                    ui->verticalLayout_16->addWidget(botao, 0, Qt::AlignHCenter);
                                }else
                                    ui->verticalLayout_16->addWidget(botao, 0, Qt::AlignHCenter);
                            }
                        }else{
                            ui->verticalLayout_8->addWidget(botao, 0, Qt::AlignHCenter);
                        }
                }else{
                    ui->verticalLayout_4->addWidget(botao, 0, Qt::AlignHCenter);
                }
            }
        }
    }
}

void Arvore::localizarElemento() {
    int tempo = 500;
    QString elementoStr = ui->lineEdit->text();
    bool ok;
    int elemento = elementoStr.toInt(&ok);
    if (ok) {
        if (ui->verticalLayout_2->count() > 1) {
            printf("Pesquisando elemento");
            QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
            int valorPrimeiroBotao = primeiroBotao->text().toInt();
            if(valorPrimeiroBotao != elemento){
                printf("elemento encontrado %d\n", elemento);
                primeiroBotao->setStyleSheet("QPushButton {"
                                             "    width: 35px;"
                                             "    height: 35px;"
                                             "    background-color: transparent;"
                                             "    border: 2px solid red;"
                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                             "}");
                trocarCorButao(primeiroBotao, tempo);
                tempo += 500;
            }
            if(valorPrimeiroBotao == elemento){
                printf("elemento encontrado %d\n", elemento);
                primeiroBotao->setStyleSheet("QPushButton {"
                                             "    width: 35px;"
                                             "    height: 35px;"
                                             "    background-color: transparent;"
                                             "    border: 2px solid yellow;"
                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                             "}");
                trocarCorButao(primeiroBotao, tempo);
                tempo += 500;
            }else if(elemento > valorPrimeiroBotao){
                if (ui->verticalLayout_4->count() > 1){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao != elemento){
                        printf("elemento encontrado %d\n", elemento);
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                       "    width: 35px;"
                                                       "    height: 35px;"
                                                       "    background-color: transparent;"
                                                       "    border: 2px solid red;"
                                                       "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                       "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }
                    if(valorPrimeiroBotao == elemento){
                        printf("elemento encontrado %d\n", elemento);
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                     "    width: 35px;"
                                                     "    height: 35px;"
                                                     "    background-color: transparent;"
                                                     "    border: 2px solid yellow;"
                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                     "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }else if(elemento > valorPrimeiroBotao){
                        if (ui->verticalLayout_8->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao != elemento){
                                printf("elemento encontrado %d\n", elemento);
                                    primeiroBotao->setStyleSheet("QPushButton {"
                                                                 "    width: 35px;"
                                                                 "    height: 35px;"
                                                                 "    background-color: transparent;"
                                                                 "    border: 2px solid red;"
                                                                 "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                 "}");trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }
                            if(valorPrimeiroBotao == elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid yellow;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;

                            }else if(elemento > valorPrimeiroBotao){
                                if (ui->verticalLayout_16->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_16->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }else if(elemento < valorPrimeiroBotao){
                                if (ui->verticalLayout_15->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_15->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }
                        }
                    }else if(elemento < valorPrimeiroBotao){
                        if (ui->verticalLayout_7->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao != elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid red;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }
                            if(valorPrimeiroBotao == elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid yellow;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");
                                trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }else if(elemento > valorPrimeiroBotao){
                                if (ui->verticalLayout_14->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_14->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }else if(elemento < valorPrimeiroBotao){
                                if (ui->verticalLayout_13->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_13->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }
                        }

                    }
                }
            }else if(elemento < valorPrimeiroBotao){
                if (ui->verticalLayout_3->count() > 1){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao != elemento){
                        printf("elemento encontrado %d\n", elemento);
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                     "    width: 35px;"
                                                     "    height: 35px;"
                                                     "    background-color: transparent;"
                                                     "    border: 2px solid red;"
                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                     "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }
                    if(valorPrimeiroBotao == elemento){
                        printf("elemento encontrado %d\n", elemento);
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                     "    width: 35px;"
                                                     "    height: 35px;"
                                                     "    background-color: transparent;"
                                                     "    border: 2px solid yellow;"
                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                     "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }else if(elemento > valorPrimeiroBotao){
                        if (ui->verticalLayout_6->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao != elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid red;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");
                                trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }
                            if(valorPrimeiroBotao == elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid yellow;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");
                                trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }else if(elemento > valorPrimeiroBotao){
                                if (ui->verticalLayout_12->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_12->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }else if(elemento < valorPrimeiroBotao){
                                if (ui->verticalLayout_11->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_11->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }
                        }
                    }else if(elemento < valorPrimeiroBotao){
                        if (ui->verticalLayout_5->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                            valorPrimeiroBotao = primeiroBotao->text().toInt();
                            if(valorPrimeiroBotao != elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid red;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");
                                trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }
                            if(valorPrimeiroBotao == elemento){
                                printf("elemento encontrado %d\n", elemento);
                                primeiroBotao->setStyleSheet("QPushButton {"
                                                             "    width: 35px;"
                                                             "    height: 35px;"
                                                             "    background-color: transparent;"
                                                             "    border: 2px solid yellow;"
                                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                             "}");
                                trocarCorButao(primeiroBotao, tempo);
                                tempo += 500;
                            }else if(elemento > valorPrimeiroBotao){
                                if (ui->verticalLayout_10->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_10->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }else if(elemento < valorPrimeiroBotao){
                                if (ui->verticalLayout_9->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_9->itemAt(1)->widget());
                                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                                    if(valorPrimeiroBotao != elemento){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid red;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }
                                    if(elemento == valorPrimeiroBotao){
                                        printf("elemento encontrado %d\n", elemento);
                                        primeiroBotao->setStyleSheet("QPushButton {"
                                                                     "    width: 35px;"
                                                                     "    height: 35px;"
                                                                     "    background-color: transparent;"
                                                                     "    border: 2px solid yellow;"
                                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                                     "}");
                                        trocarCorButao(primeiroBotao, tempo);
                                        tempo += 500;
                                    }else{
                                        printf("elemento não existe");
                                    }
                                }
                            }
                        }

                    }
                }
            }

        }
    }
}

void Arvore::trocarCorButao(QPushButton* primeiroBotao, int tempo) {
    // Crie um QTimer para o atraso de 500ms
    QTimer *timer = new QTimer(this);

    // Conecte o sinal timeout do QTimer a uma função lambda
    connect(timer, &QTimer::timeout, this, [this, primeiroBotao, timer](){
        // Restaura o estilo original do botão
        primeiroBotao->setStyleSheet("QPushButton {"
                                     "    width: 35px;"
                                     "    height: 35px;"
                                     "    background-color: transparent;"
                                     "    border: 2px solid #fff;"
                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                     "}");

        // Pare o QTimer após o atraso
        timer->stop();

        // Libere a memória do QTimer
        timer->deleteLater();
    });

    // Configure o intervalo para 500ms e inicie o QTimer
    timer->start(tempo);
}


// Implemente a função para adicionar elementos automaticamente.
void Arvore::adicionarElementoAutomaticamente() {
    static int elementoAtual = 0;
    printf("chamou aqui\n");
    if (elementoAtual < 15) {
        int elemento = elementos_inserir[elementoAtual];
        ui->lineEdit->setText(QString::number(elemento));
        addElemento();
        elementoAtual++;
    } else {
        // Todos os elementos foram adicionados, podemos parar o temporizador.
        QTimer* timer = qobject_cast<QTimer*>(sender());
        if (timer) {
            timer->stop();
            timer->deleteLater();
        }
    }
    if(elementoAtual < 15){
        // Crie um QTimer para o atraso de 500ms
        QTimer *timer = new QTimer(this);

        // Conecte o sinal timeout do QTimer a uma função lambda
        connect(timer, &QTimer::timeout, this, [this , timer](){
            adicionarElementoAutomaticamente();

            // Pare o QTimer após o atraso
            timer->stop();

            // Libere a memória do QTimer
            timer->deleteLater();
        });

        // Configure o intervalo para 500ms e inicie o QTimer
        timer->start(1500);
    }
}

void Arvore::removerElemento() {
    int tempo = 1000;
    QString elementoStr = ui->lineEdit->text();
    bool ok;
    int elemento = elementoStr.toInt(&ok);
    if (ok) {
        if (ui->verticalLayout_2->count() > 1) {
            printf("Pesquisando elemento");
            QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
            int valorPrimeiroBotao = primeiroBotao->text().toInt();
            if(valorPrimeiroBotao != elemento){
                primeiroBotao->setStyleSheet("QPushButton {"
                                             "    width: 35px;"
                                             "    height: 35px;"
                                             "    background-color: transparent;"
                                             "    border: 2px solid yellow;"
                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                             "}");
                trocarCorButao(primeiroBotao, tempo);
                tempo += 500;
            }
            if(valorPrimeiroBotao == elemento){
                primeiroBotao->setStyleSheet("QPushButton {"
                                             "    width: 35px;"
                                             "    height: 35px;"
                                             "    background-color: transparent;"
                                             "    border: 2px solid red;"
                                             "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                             "}");
                trocarCorButao(primeiroBotao, tempo);
                if(ui->verticalLayout_3->count() > 1){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                    QString valorPrimeiroBotao = primeiroBotao->text();
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                    primeiroBotao->setText(valorPrimeiroBotao);
                    if(ui->verticalLayout_6->count() > 1){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                        QString valorPrimeiroBotao = primeiroBotao->text();
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                        primeiroBotao->setText(valorPrimeiroBotao);
                        QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                        QString valorSegundoBotao = segundoBotao->text();;
                        if(valorPrimeiroBotao > valorSegundoBotao){
                            segundoBotao->setText(valorPrimeiroBotao);
                            primeiroBotao->setText(valorSegundoBotao);
                        }
                        if(ui->verticalLayout_12->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_12->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            removerBotao(primeiroBotao, ui->verticalLayout_12, 2);
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                            QString valorSegundoBotao = segundoBotao->text();;
                            if(valorPrimeiroBotao > valorSegundoBotao){
                                segundoBotao->setText(valorPrimeiroBotao);
                                primeiroBotao->setText(valorSegundoBotao);
                            }
                        }
                        else if(ui->verticalLayout_11->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_11->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            removerBotao(primeiroBotao, ui->verticalLayout_11, 2);
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                        } else{
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_6, 2);
                        }
                    }
                    else{
                        if(ui->verticalLayout_5->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            if(ui->verticalLayout_9->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_9->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_9, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                            }else if(ui->verticalLayout_10->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_10->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                                QString valorSegundoBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_10, 2);
                                if(valorPrimeiroBotao > valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                                valorPrimeiroBotao = primeiroBotao->text();
                                if(valorPrimeiroBotao < valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_5, 2);
                            }
                        }else{
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_3, 2);
                        }
                    }
                }else if(ui->verticalLayout_4->count() > 1){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                    QString valorPrimeiroBotao = primeiroBotao->text();
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                    primeiroBotao->setText(valorPrimeiroBotao);
                    if(ui->verticalLayout_7->count() > 1){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                        QString valorPrimeiroBotao = primeiroBotao->text();
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                        primeiroBotao->setText(valorPrimeiroBotao);
                        if(ui->verticalLayout_13->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_13->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            removerBotao(primeiroBotao, ui->verticalLayout_13, 2);
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                            QString valorSegundoBotao = segundoBotao->text();
                            if(valorPrimeiroBotao < valorSegundoBotao){
                                segundoBotao->setText(valorPrimeiroBotao);
                                primeiroBotao->setText(valorSegundoBotao);
                            }
                        }else if(ui->verticalLayout_14->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_14->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            QString valorSegundoBotao = primeiroBotao->text();
                            removerBotao(primeiroBotao, ui->verticalLayout_14, 2);
                            segundoBotao->setText(valorPrimeiroBotao);
                        }else{
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_7, 2);
                        }
                    }else{
                        if(ui->verticalLayout_8->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            if(ui->verticalLayout_15->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_15->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_15, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                                QString valorSegundoBotao = segundoBotao->text();
                                if(valorPrimeiroBotao < valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                            }else if(ui->verticalLayout_16->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_16->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_16, 2);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                segundoBotao->setText(valorPrimeiroBotao);

                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_8, 2);
                            }
                        }else{
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_4, 2);
                        }
                    }
                }else{
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(1)->widget());
                    removerBotao(primeiroBotao, ui->verticalLayout_2, 2);
                }

            }else if(elemento > valorPrimeiroBotao){
                QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                int valorPrimeiroBotao = primeiroBotao->text().toInt();
                if(valorPrimeiroBotao != elemento){
                    primeiroBotao->setStyleSheet("QPushButton {"
                                                 "    width: 35px;"
                                                 "    height: 35px;"
                                                 "    background-color: transparent;"
                                                 "    border: 2px solid yellow;"
                                                 "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                 "}");
                    trocarCorButao(primeiroBotao, tempo);
                    tempo += 500;
                }
                if(valorPrimeiroBotao == elemento){
                    primeiroBotao->setStyleSheet("QPushButton {"
                                                 "    width: 35px;"
                                                 "    height: 35px;"
                                                 "    background-color: transparent;"
                                                 "    border: 2px solid red;"
                                                 "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                 "}");
                    trocarCorButao(primeiroBotao, tempo);

                    if(ui->verticalLayout_7->count() > 1){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                        QString valorPrimeiroBotao = primeiroBotao->text();
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                        primeiroBotao->setText(valorPrimeiroBotao);
                        if(ui->verticalLayout_14->count() > 1){
                            printf("toAq");
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_14->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_14, 2);
                            segundoBotao->setText(valorPrimeiroBotao);
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                            QString valorSegundoBotao = primeiroBotao->text();
                            printf("1 %d\n", valorPrimeiroBotao.toInt());
                            printf("2 %d\n", valorSegundoBotao.toInt());
                            if(valorPrimeiroBotao > valorSegundoBotao){
                                segundoBotao->setText(valorSegundoBotao);
                                primeiroBotao->setText(valorPrimeiroBotao);
                            }

                        }else if(ui->verticalLayout_13->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_13->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            removerBotao(primeiroBotao, ui->verticalLayout_13, 2);
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                            QString valorSegundoBotao = segundoBotao->text();
                            if(valorPrimeiroBotao > valorSegundoBotao){
                                segundoBotao->setText(valorPrimeiroBotao);
                                primeiroBotao->setText(valorSegundoBotao);
                            }
                        }
                        else{
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_7, 2);
                        }
                    }else{
                        if(ui->verticalLayout_8->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            if(ui->verticalLayout_15->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_15->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_15, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                                QString valorSegundoBotao = segundoBotao->text();
                                if(valorPrimeiroBotao < valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                            }else if(ui->verticalLayout_16->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_16->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_16, 2);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                segundoBotao->setText(valorPrimeiroBotao);

                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_8, 2);
                            }
                        }else{
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_4->itemAt(1)->widget());
                            removerBotao(primeiroBotao, ui->verticalLayout_4, 2);
                        }
                    }
                }else if(elemento > valorPrimeiroBotao){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao != elemento){
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                     "    width: 35px;"
                                                     "    height: 35px;"
                                                     "    background-color: transparent;"
                                                     "    border: 2px solid yellow;"
                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                     "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }
                    if(valorPrimeiroBotao == elemento){
                        if(ui->verticalLayout_8->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            if(ui->verticalLayout_15->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_15->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_15, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                QString valorSegundoBotao = segundoBotao->text();
                                if(valorPrimeiroBotao < valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                            }else if(ui->verticalLayout_16->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_16->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_16, 2);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                segundoBotao->setText(valorPrimeiroBotao);

                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_8->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_8, 2);
                            }
                        }
                    }else if(elemento > valorPrimeiroBotao){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_16->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_16, 2);
                    }else if(elemento < valorPrimeiroBotao){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_15->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_15, 2);
                    }
                }else if(elemento < valorPrimeiroBotao){
                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                    valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao != elemento){
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                     "    width: 35px;"
                                                     "    height: 35px;"
                                                     "    background-color: transparent;"
                                                     "    border: 2px solid yellow;"
                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                     "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }
                    if(valorPrimeiroBotao == elemento){
                        if(ui->verticalLayout_7->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();

                            if(ui->verticalLayout_15->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_13->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_13, 2);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                                QString valorSegundoBotao = segundoBotao->text();
                                if(valorPrimeiroBotao < valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                            }else if(ui->verticalLayout_16->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_14->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_14, 2);
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                                segundoBotao->setText(valorPrimeiroBotao);

                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_7->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_7, 2);
                            }
                        }
                    }else if(elemento > valorPrimeiroBotao){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_14->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_14, 2);
                    }else if(elemento < valorPrimeiroBotao){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_13->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_13, 2);
                    }
                }
            } else if(elemento < valorPrimeiroBotao){
                QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                int valorPrimeiroBotao = primeiroBotao->text().toInt();
                if(valorPrimeiroBotao != elemento){
                    primeiroBotao->setStyleSheet("QPushButton {"
                                                 "    width: 35px;"
                                                 "    height: 35px;"
                                                 "    background-color: transparent;"
                                                 "    border: 2px solid yellow;"
                                                 "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                 "}");
                    trocarCorButao(primeiroBotao, tempo);
                    tempo += 500;
                }
                if(valorPrimeiroBotao == elemento){
                    if(ui->verticalLayout_3->count() > 1){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                        QString valorPrimeiroBotao = primeiroBotao->text();
                        if(ui->verticalLayout_5->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                            primeiroBotao->setText(valorPrimeiroBotao);
                            if(ui->verticalLayout_10->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_10->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                                QString valorSegundoBotao = segundoBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_10, 2);
                                if(valorPrimeiroBotao > valorSegundoBotao){
                                    segundoBotao->setText(valorPrimeiroBotao);
                                    primeiroBotao->setText(valorSegundoBotao);
                                }
                            }else if(ui->verticalLayout_9->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_9->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_9, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);

                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_5, 2);
                            }
                        }else{
                            if(ui->verticalLayout_6->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                                if(ui->verticalLayout_11->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_11->itemAt(1)->widget());
                                    QString valorPrimeiroBotao = primeiroBotao->text();
                                    removerBotao(primeiroBotao, ui->verticalLayout_11, 2);
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                    primeiroBotao->setText(valorPrimeiroBotao);
                                    QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                                    QString valorSegundoBotao = segundoBotao->text();;
                                    if(valorPrimeiroBotao < valorSegundoBotao){
                                        segundoBotao->setText(valorPrimeiroBotao);
                                        primeiroBotao->setText(valorSegundoBotao);
                                    }
                                }

                                else if(ui->verticalLayout_12->count() > 1){
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_12->itemAt(1)->widget());
                                    QString valorPrimeiroBotao = primeiroBotao->text();
                                    removerBotao(primeiroBotao, ui->verticalLayout_12, 2);
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                    primeiroBotao->setText(valorPrimeiroBotao);
                                    QPushButton* segundoBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                                    QString valorSegundoBotao = segundoBotao->text();;
                                    if(valorPrimeiroBotao < valorSegundoBotao){
                                        segundoBotao->setText(valorPrimeiroBotao);
                                        primeiroBotao->setText(valorSegundoBotao);
                                    }
                                } else{
                                    primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                    removerBotao(primeiroBotao, ui->verticalLayout_6, 2);
                                }
                            }else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_3->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_3, 2);
                            }
                        }
                    }
                }else if(valorPrimeiroBotao < elemento){
                    QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                    int valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao != elemento){
                        primeiroBotao->setStyleSheet("width: 35px; height: 25px; background-color: transparent; border-radius: 50%; border: 2px solid yellow;");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }
                    if(valorPrimeiroBotao == elemento){
                        if(ui->verticalLayout_6->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();

                            if(ui->verticalLayout_11->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_11->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_11, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                            }else if(ui->verticalLayout_12->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_12->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_12, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                            } else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_6->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_6, 2);
                            }
                        }
                    }else if(valorPrimeiroBotao < elemento){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_12->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_12, 2);
                    }else if(valorPrimeiroBotao > elemento){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_11->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_11, 2);
                    }
                }else if(valorPrimeiroBotao > elemento){
                    QPushButton* primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                    int valorPrimeiroBotao = primeiroBotao->text().toInt();
                    if(valorPrimeiroBotao != elemento){
                        primeiroBotao->setStyleSheet("QPushButton {"
                                                     "    width: 35px;"
                                                     "    height: 35px;"
                                                     "    background-color: transparent;"
                                                     "    border: 2px solid yellow;"
                                                     "    border-radius: 17px;"  // A metade da largura/altura para criar um círculo.
                                                     "}");
                        trocarCorButao(primeiroBotao, tempo);
                        tempo += 500;
                    }
                    if(valorPrimeiroBotao == elemento){
                        if(ui->verticalLayout_5->count() > 1){
                            primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                            QString valorPrimeiroBotao = primeiroBotao->text();

                            if(ui->verticalLayout_9->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_9->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_9, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                            }else if(ui->verticalLayout_10->count() > 1){
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_10->itemAt(1)->widget());
                                QString valorPrimeiroBotao = primeiroBotao->text();
                                removerBotao(primeiroBotao, ui->verticalLayout_10, 2);
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                primeiroBotao->setText(valorPrimeiroBotao);
                            } else{
                                primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_5->itemAt(1)->widget());
                                removerBotao(primeiroBotao, ui->verticalLayout_5, 2);
                            }
                        }
                    }else if(valorPrimeiroBotao < elemento){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_10->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_10, 2);
                    }else if(valorPrimeiroBotao > elemento){
                        primeiroBotao = qobject_cast<QPushButton*>(ui->verticalLayout_9->itemAt(1)->widget());
                        removerBotao(primeiroBotao, ui->verticalLayout_9, 2);
                    }
                }
            }
        }
    }
}

void Arvore::removerBotao(QPushButton* primeiroBotao,  QLayout* layout, int grid){
    // Crie um QTimer para o atraso de 500ms
    QTimer *timer = new QTimer(this);

    primeiroBotao->setStyleSheet("width: 25px; height: 25px; background-color: transparent; border-radius: 17px; border: 2px solid red;");
    // Conecte o sinal timeout do QTimer a uma função lambda
    connect(timer, &QTimer::timeout, this, [this, layout, primeiroBotao, timer](){
        // Restaura o estilo original do botão
        layout->removeWidget(primeiroBotao);
        delete primeiroBotao;
        // Pare o QTimer após o atraso
        timer->stop();

        // Libere a memória do QTimer
        timer->deleteLater();
    });

    // Configure o intervalo para 500ms e inicie o QTimer
    timer->start(500);
}

void Arvore::abrirJanelaMenu() {
    if (mainWindow) {
        this->hide(); // Feche a janela atual
        mainWindow->show(); // Mostre a MainWindow existente
    }
}
