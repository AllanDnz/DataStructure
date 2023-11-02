#ifndef LISTASEMCADEADA_H
#define LISTASEMCADEADA_H

#include <QDialog>
#include "LSE.h"
#include "QGraphicsRectItem"
#include <QTimer>
#include "mainwindow.h"



namespace Ui {
class listaSEmcadeada;
}

class listaSEmcadeada : public QDialog
{
    Q_OBJECT

public:
    explicit listaSEmcadeada(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~listaSEmcadeada();
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
    Ui::listaSEmcadeada *ui;
    LSE lista2;
    QTimer* colorChangeTimer;
    QTimer *restoreColorTimer; // novo timer
    QPushButton* currentChangedButton;
    int currentButtonIndex = 0;
    bool animationInProgress = false;
    bool removeelemento = false;
    MainWindow *mainWindow; // Declaração do membro da MainWindow

};

#endif // LISTASEMCADEADA_H
