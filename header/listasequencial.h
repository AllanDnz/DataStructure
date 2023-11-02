#ifndef LISTASEQUENCIAL_H
#define LISTASEQUENCIAL_H

#include <QDialog>
#include "ListaSeq.h"
#include "QGraphicsRectItem"
#include <QTimer>
#include "mainwindow.h"



namespace Ui {
class listaSequencial;
}

extern const QString butonsL;

class listaSequencial : public QDialog
{
    Q_OBJECT

public:
    explicit listaSequencial(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr);
    ~listaSequencial();
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
    Ui::listaSequencial *ui;
    ListaSeq lista2;
    QTimer* colorChangeTimer;
    QTimer *restoreColorTimer; // novo timer
    QPushButton* currentChangedButton;
    int currentButtonIndex = 0;
    bool animationInProgress = false;
    bool removeelemento = false;
    MainWindow *mainWindow; // Declaração do membro da MainWindow

};

#endif // LISTASEQUENCIAL_H
