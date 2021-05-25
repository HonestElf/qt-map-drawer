#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "ui_mapwidget.h"
#include "QPainter"
#include "QDebug"

using namespace std;

namespace Ui
{
class mapWidget;

//структура объекта на карте
struct objectParams
{
    QString objName;
    QString objType;
    int objX;
    int objY;
};

}

class mapWidget : public QWidget, Ui::mapWidget
{
    Q_OBJECT
public:

    //конструктор
    explicit mapWidget(QWidget *parent = nullptr);
    //деструктор
    ~mapWidget();

//создается новый объект с переданными параметрами и закидывается в вектор
   void setNewObj(QString objName,QString objType,int objX,int objY);

   //Удаление объекта из вектора
   void objectDelete(QString objName);

   //вектор объектов
   QVector<Ui::objectParams> objectVector;

  //наш корабль
    Ui::objectParams targetShip;


    //Измение положения корабля
    void setShipCurrentCoords(int x, int y);
    void translateCoordsFromCurs(double psi, double marsh);

private:

    //переопределяем paintEvent чтобы можно было рисовать
    void paintEvent(QPaintEvent *);

    //Рисователь всего и вся
    void draw();

    //Рисователь сетки
    void drawGrid(int xStep, int yStep);

    //Подписыватель осей
    void drawAxis(int xStep, int yStep);

    //Рисователь объектов
    void drawAims();

    int gridXStep; //шаг сетки по Х
    int gridYstep;//Шаг сетки по Y

    int axisXStep;// Шаг подписей осей по Х
    int axisYstep;// Шаг подписей осей по Y

    QPainter painter;
    QBrush background;
    float dx, dy, scaleX, scaleY;
    int wid, hei, devwid,devhei;
    QImage myIm;

//вывод параметров объекта
    void showParams(Ui::objectParams myObj);
};

#endif // MAPWIDGET_H
