#include "mapwidget.h"

mapWidget::mapWidget(QWidget *parent) : QWidget(parent)
{
    //устанавливаем форму
    setupUi(this);

    //всякая косметика
    background.setStyle(Qt::SolidPattern);
    background.setColor(Qt::white);

    myIm.load("/home/niism/projects/qtProj/myMap/p.png");

    gridXStep = 50;
    gridYstep = 50;

    axisXStep = 100;
    axisYstep = 100;


    //Заполняем наш объект параметрами
    targetShip.objName = "targetShip";
    targetShip.objType = "targetShip";
    targetShip.objX = 0;
    targetShip.objY = 0;

}
//деструктор
mapWidget::~mapWidget()
{
    delete this;
}

//для отрисовки
void mapWidget::paintEvent(QPaintEvent * )
{
    devwid = width();//Ширина окна
    devhei = height();//Высота окна
    wid = devwid / 2;
    hei = devhei / 2;

    //начинаем рисовать
    painter.begin(this);
    //разрешаем трансформировать вид
    painter.setViewTransformEnabled(true);
    //настройки рендера
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //вызываем метод рисования
    draw();
    //убираем кисти в портфель
    painter.end();
}

//сам метод рисования
void mapWidget::draw()
{
    painter.setPen(QPen(Qt::black,1));
    painter.resetTransform();
    painter.setRenderHint(QPainter::Antialiasing, false);
    //переносим начало в середину окна
    painter.translate(wid, hei);

    //Заполняем все окно фоном
    painter.fillRect(-wid, -hei, devwid, devhei, background);
    //рисуем сетку
    drawGrid(gridXStep,gridYstep);
    //Подписываем сетку
    drawAxis(axisXStep,axisYstep);
    //рисуем цели
    drawAims();
}

//Отрисовка сетки
void mapWidget::drawGrid(int gridXStep, int gridYStep)
{
    int numberX = wid/gridXStep; //кол-во вертикальных линий сетки
    int numberY = hei/gridYStep; //кол-во горизонтальных линий сетки
    for (int i = -numberX; i <= numberX; i++)
    { painter.drawLine(i * gridXStep, -hei, i * gridXStep, hei);}
    for (int i = -numberY; i <= numberY; i++)
    { painter.drawLine(-wid, i * gridYStep, wid, i * gridYStep);}
}

//отрисовка осей
void mapWidget::drawAxis(int axisXStep, int axisYStep)
{
    int tmp;
    float num;

    int numberX = wid/axisXStep; //кол-во вертикальных подписей сетки
    int numberY = hei/axisYStep; //кол-во горизонтальных подписей сетки

    painter.setPen(QPen(Qt::black,4));
    for (int i = -numberX; i <= numberX; i++)
    {
        tmp = i * axisXStep;    //пискель на вертикальной линии
        num = i * axisXStep;    //значение подписи
        int horSl = 5;  //горизонтальное смещение, положит - вправо
        int verSl = 10; //вертикальное смещение, положит - вниз
        int notch = 6;  //длина рисок
        painter.drawText(tmp + horSl, verSl, QString::number(num));
        painter.drawLine(tmp, -notch/2, tmp, notch/2); //рисочки
    }

    for (int i = -numberY; i <= numberY; i++)
    {
        if (i != 0)
        {
            tmp = i * axisYStep;//пискель на горизонтальной линии
            num = i * axisXStep;//значение подписи
            int horSl = 5; //горизонтальное смещение, положит - вправо
            int verSl = 5; //вертикальное смещение, положит - вниз
            int notch = 6; //длина рисок
            painter.drawText(horSl,tmp + verSl, QString::number(num));
            painter.drawLine(-notch/2, tmp,notch/2, tmp);
        }
    }
}

//отрисовка объектов
void mapWidget::drawAims()
{
    QRectF shipPlace;
    painter.setPen(QPen(Qt::black,5));
    shipPlace.setRect(50,50,10,10);

    int xTmp = targetShip.objX;
    int yTmp = targetShip.objY;
    QPoint point1(xTmp,yTmp);
    shipPlace.moveCenter(point1);
    painter.drawRect(shipPlace);

    auto iter = objectVector.begin();
    while (iter != objectVector.end())
    {
        QRectF objPlace;
        if (iter->objType == "Буй")
        {
            painter.setPen(QPen(Qt::red,5));
            objPlace.setRect(50,50,5,5);
        }
        else if (iter->objType == "Корабль")
        {
            painter.setPen(QPen(Qt::blue,5));
            objPlace.setRect(50,50,10,10);
        }
        else if (iter->objType == "Подводный объект")
        {
            painter.setPen(QPen(Qt::green,5));
            objPlace.setRect(50,50,10,5);
        }
        else if (iter->objType == "targetShip")
        {
            painter.setPen(QPen(Qt::black,5));
            objPlace.setRect(50,50,10,10);
        } else if (iter->objType == "base")
        {
            painter.setPen(QPen(Qt::darkRed,5));
            objPlace.setRect(50,50,10,10);
        }
        else
        {
            painter.setPen(QPen(Qt::yellow,5));
            objPlace.setRect(50,50,5,10);
        }
        int xTmp = iter->objX;
        int yTmp = iter->objY;
        QPoint point1(xTmp,yTmp);
        objPlace.moveCenter(point1);
        painter.drawRect(objPlace);
        ++iter;
    }

}

//создается новый объект с переданными параметрами и закидывается в вектор
void mapWidget::setNewObj(QString objName, QString objType, int objX, int objY)
{
    Ui::objectParams myNewObj;
    myNewObj.objName = objName;
    myNewObj.objType = objType;
    myNewObj.objX = objX;
    myNewObj.objY = -objY;

    objectVector.push_back(myNewObj);

    repaint();
}


//Удаление объекта из вектора
void mapWidget::objectDelete(QString objName)
{
    int pos = 0;
    auto iter = objectVector.begin();

    while (iter < objectVector.end())
    {
        if (iter->objName == objName)
        {
            objectVector.remove(pos);
        }
        ++pos;
        ++iter;
    }
    repaint();
}

//вывод параметров объекта
void mapWidget::showParams(Ui::objectParams myObj)
{
    qDebug()<<"==========";
    qDebug()<<"Заданное имя: "<<myObj.objName;
    qDebug()<<"Заданный тип: "<<myObj.objType;
    qDebug()<<"Заданный X: "<<myObj.objX;
    qDebug()<<"Заданный Y: "<<myObj.objY;

}

void mapWidget::translateCoordsFromCurs(double psi, double marsh){
       qDebug()<<"translateCoordsFromCurs: ";
    int coordX = marsh*cos(psi);
    int coordY = marsh*sin(psi);

    setShipCurrentCoords(coordX, coordY);
}

void mapWidget::setShipCurrentCoords(int x, int y){
        qDebug()<<"setShipCurrentCoords";
        qDebug()<<"objX = "<<targetShip.objX;
        qDebug()<<"objY = "<<targetShip.objY;
    targetShip.objX += x;
    targetShip.objY += y;

    repaint();
}
