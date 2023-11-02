#ifndef ARVORE_H
#define ARVORE_H

#include <QDialog>
#include "mainwindow.h"
#include <QVBoxLayout>

struct Node {
    int valor;
    Node* esquerda;
    Node* direita;
    Node(int v) : valor(v), esquerda(nullptr), direita(nullptr) {}
};

namespace Ui {
class Arvore;
}

class Arvore : public QDialog
{
    Q_OBJECT

public:
    explicit Arvore(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~Arvore();
    // Adicione os métodos públicos necessários para manipular a árvore e a interface gráfica.
    void posicionarBotao(Node* currentNode, QPushButton* botao);
    void trocarCorButao(QPushButton* primeiroBotao, int tempo = 2000);
public slots:
    void removerElemento();
    void addElemento();
    void adicionarElementoAutomaticamente();
    void localizarElemento();
    void abrirJanelaMenu();


private:
    Ui::Arvore *ui;
    MainWindow *mainWindow;
    Node* root;
    void removerBotao(QPushButton* primeiroBotao,  QLayout* layout, int grid);
    int elementos_inserir[15] = {10, 5, 20, 3, 7, 23, 18, 15, 1, 4, 6, 8, 19, 24, 21};
};

#endif // ARVORE_H
