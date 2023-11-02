#ifndef LISTASIMPLES_H
#define LISTASIMPLES_H

#include <QDialog>
#include "LSE.h"
#include "QGraphicsRectItem"
#include <QTimer>

namespace Ui {
class listaSimples;
}

class listaSimples : public QDialog
{
    Q_OBJECT

public:
    explicit listaSimples(QWidget *parent = nullptr);
    ~listaSimples();
    void addElemento();
public slots:
    void changeButtonColor();
    void restoreButtonColor();
    void clickBotaoAdd();
    void removerElemento();
    void clickBotaoRemove();

private:
    Ui::listaSimples *ui;
    LDE lista3;
    QTimer* colorChangeTimer;
    QTimer *restoreColorTimer; // novo timer
    QPushButton* currentChangedButton;
    int currentButtonIndex = 0;
    bool animationInProgress = false;
    bool removeelemento = false;
};

#endif // listaSimples_H
