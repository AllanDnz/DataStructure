#ifndef LISTADEMCADEADA_H
#define LISTADEMCADEADA_H

#include <QDialog>
#include "LDE.h"
#include "QGraphicsRectItem"
#include <QTimer>
#include "mainwindow.h"



namespace Ui {
class listaDEmcadeada;
}

class listaDEmcadeada : public QDialog
{
    Q_OBJECT

public:
    explicit listaDEmcadeada(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~listaDEmcadeada();
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
    Ui::listaDEmcadeada *ui;
    LDE lista2;
    QTimer* colorChangeTimer;
    QTimer *restoreColorTimer; // novo timer
    QPushButton* currentChangedButton;
    int currentButtonIndex = 0;
    bool animationInProgress = false;
    bool removeelemento = false;
    MainWindow *mainWindow; // Declaração do membro da MainWindow

};

#endif // LISTADEMCADEADA_H
