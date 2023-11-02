#ifndef FILASEQUENCIAL_H
#define FILASEQUENCIAL_H

#include <QDialog>
#include "FilaSeq.h"
#include "QGraphicsRectItem"
#include <QTimer>
#include "mainwindow.h"

namespace Ui {
class filaSequencial;
}

class filaSequencial : public QDialog
{
    Q_OBJECT

public:
    explicit filaSequencial(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~filaSequencial();
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
    Ui::filaSequencial *ui;
    FilaSeq filaSequen;
    QTimer* colorChangeTimer;
    QTimer *restoreColorTimer; // novo timer
    QPushButton* currentChangedButton;
    int currentButtonIndex = 0;
    bool animationInProgress = false;
    bool removeelemento = false;
    MainWindow *mainWindow; // Declaração do membro da MainWindow
};

#endif // FILA_H
