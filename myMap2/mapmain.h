#ifndef MAPMAIN_H
#define MAPMAIN_H

#include <QWidget>
#include "ui_mapmain.h"
#include "QPainter"
#include "mapwidget.h"
#include "QDebug"
#include "QTimer"
#include "su_rov.h"

#include <cmath>
#include <QtMath>
namespace Ui {
class mapMain;
}

class mapMain : public QWidget, Ui::mapMain
{
    Q_OBJECT

public:
    //Конструктор
    explicit mapMain(QWidget *parent = 0);
    //Деструктор
    ~mapMain();

    SU_ROV rov;

private:
QTimer timer;

//для перерисовки границ виджета
    int mapWid, mapHei;

    //виджет карты
mapWidget *map = new mapWidget;

//проверяет, какое название стоит в комбобоксе и подставляет соответствующие поля
void fillLines();

public slots:
//загрузка полей в новый объект
void loadParams();

//Удаление объекта отовсюду
void btnDelete();

 //грузим новые координаты
void updateShipCoords();
};

#endif // MAPMAIN_H
