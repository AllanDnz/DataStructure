#ifndef PILHA_H
#define PILHA_H

#include <QDialog>
#include "PilhaSeq.h"
#include "QGraphicsRectItem"
#include <QTimer>
#include "mainwindow.h"

namespace Ui {
class pilha;
}

class pilha : public QDialog
{
    Q_OBJECT

public:
    explicit pilha(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~pilha();
    void addElemento();

public slots:
    void changeButtonColor();
    void restoreButtonColor();
    void clickBotaoAdd();
    void removerElemento();
    void clickBotaoRemove();
    void abrirJanelaMenu();
    void buscaElemento();

private:
    Ui::pilha *ui;
    PilhaSeq pilhaSequencial;
    QTimer* colorChangeTimer;
    QTimer *restoreColorTimer; // novo timer
    QPushButton* currentChangedButton;
    int currentButtonIndex = 0;
    bool animationInProgress = false;
    bool removeelemento = false;
    MainWindow *mainWindow; // Declaração do membro da MainWindow
};

#endif // PILHA_H
