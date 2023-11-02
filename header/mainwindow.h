#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declaration da classe listaSequencial
class listaSequencial;
class listaSEmcadeada;
class listaDEmcadeada;
class pilha;
class filaSequencial;
class Arvore;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void AbrirJanelaListaSequencial();
    void AbrirJanelaListaDuplamenteEncadeada();
    void AbrirJanelaListaSimplesmenteEncadeada();
    void AbrirJanelaPilha();
    void AbrirJanelaFila();
    void AbrirJanelaArvore();

private:
    Ui::MainWindow *ui;
    listaSequencial *listaSeq; // Declarando a instância da listaSequencial
    listaSEmcadeada *listSEncad;
    listaDEmcadeada *listDEncad;
    pilha *pilhaSequencial;
    filaSequencial *filaSequen;
    Arvore *arvoreTela;

};
#endif // MAINWINDOW_H
