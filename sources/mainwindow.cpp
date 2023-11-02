#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listasequencial.h"
#include "listaSEmcadeada.h"
#include "listaDEmcadeada.h"
#include "pilha.h"
#include "filasequencial.h"
#include "arvore.h"

QString butons = "QPushButton {"
                 "   background: #fff; /* Estilo padrão */"
                 "   color: #000; /* Estilo padrão */"
                 "   padding: 10px; /* Estilo padrão */"
                 "   font-size: 20px; /* Estilo padrão */"
                 "   width: 550px; /* Estilo padrão */"
                 "   height: 30px;"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    listaSeq = new listaSequencial(this, this);
    listaSeq->hide();

    //abrindo janela simples encadeada
    listSEncad = new listaSEmcadeada(this, this);
    listSEncad->hide();

    //abrindo janela DE
    listDEncad = new listaDEmcadeada(this, this);
    listDEncad->hide();

    //abrindo janela pilha
    pilhaSequencial = new pilha(this, this);
    pilhaSequencial->hide();

    filaSequen = new filaSequencial(this, this);
    filaSequen->hide();

    arvoreTela = new Arvore(this, this);
    arvoreTela->hide();


    setStyleSheet("background: #000721; max-width: 700px; width: 700px; max-height: 500px; border: 10px; border-radius: 10px;"); //bacground da aplicação
    setGeometry(0, 0, 700, 500);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->verticalLayout->setSpacing(10);
    ui->label->setStyleSheet("color: #fff; font-size: 20px; font-weight: 900; margin-bottom: 100px; margin-top: 100px;");
    ui->pushButton->setStyleSheet(butons);
    ui->pushButton_2 ->setStyleSheet(butons);
    ui->pushButton_3->setStyleSheet(butons);
    ui->pushButton_4->setStyleSheet(butons);
    ui->pushButton_5->setStyleSheet(butons);
    ui->pushButton_6->setStyleSheet(butons);


    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaListaSequencial()) );
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaListaSimplesmenteEncadeada()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaListaDuplamenteEncadeada()) );
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaPilha()) );
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaFila()) );
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(AbrirJanelaArvore()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AbrirJanelaListaSequencial() {
    this->hide();
    listaSeq->show();
}

void MainWindow::AbrirJanelaListaDuplamenteEncadeada() {
    this->hide();
    listDEncad->show();
}

void MainWindow::AbrirJanelaListaSimplesmenteEncadeada() {
    this->hide();
    listSEncad->show();
}

void MainWindow::AbrirJanelaPilha(){
    this->hide();
    pilhaSequencial->show();
}

void MainWindow::AbrirJanelaFila(){
    this->hide();
    filaSequen->show();
}

void MainWindow::AbrirJanelaArvore() {
    this->hide();
    arvoreTela->show();
}
