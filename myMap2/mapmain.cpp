#include "mapmain.h"

mapMain::mapMain(QWidget *parent) :  QWidget(parent)
{
    //устанавливаем
    setupUi(this);

    //даем название окошку
    setWindowTitle("Карта");

    //Задаем высоту Gui
    frameComp->setMaximumSize(250,300);
    frameParams->setMaximumSize(250, 300);
    frameEdit->setMaximumSize(250, 300);

    //Добавляем виджет карты
    frameMap->layout()->addWidget(map);

    //Кликнули на делит - удалили объект
    connect(pbDelete, &QPushButton::clicked, this, &mapMain::btnDelete);

    //смена объекта в комбобоксе - меняем поля
    connect(comboObj, &QComboBox::currentTextChanged, this, &mapMain::fillLines);

    //кликнули на кнопку - загрузили поля в новый объект
    connect(pbAdd, &QPushButton::clicked, this,&mapMain::loadParams);

    //таймаут - перерисовка границ виджета + загрузка нвоых координат корабля
    connect(&timer, &QTimer::timeout,[&]()
    {
        mapWid = frameMap->width();
        mapHei = frameMap->height();

        dsbXEdit->setRange(-(mapWid/2-20),(mapWid/2-20));
        dsbYEdit->setRange(-(mapHei/2-20),(mapHei/2-20));

        dsbX->setRange(-(mapWid/2-20),(mapWid/2-20));
        dsbY->setRange(-(mapHei/2-20),(mapHei/2-20));

        //грузим новые координаты
        updateShipCoords();
    });
    timer.start(100);

    //Ставим количество знаков после запятой
    dsbX->setDecimals(0);
    dsbY->setDecimals(0);
    dsbXEdit->setDecimals(0);
    dsbYEdit->setDecimals(0);

    //делаем неизменныйми
    dsbX->setReadOnly(true);
    dsbY->setReadOnly(true);

    //Ставим названия
    comboTypeEdit->addItem("Буй");
    comboTypeEdit->addItem("Корабль");
    comboTypeEdit->addItem("Подводный объект");
    comboTypeEdit->addItem("Другое");

    //всякая всячина
    frameComp->layout()->setAlignment(Qt::AlignCenter);
    QPixmap pix(":/images/compass.jpg");
    pix=pix.scaled(QSize(200,200),Qt::KeepAspectRatio);
    lblComp->setAlignment(Qt::AlignCenter);
    lblComp->setPixmap(pix);
}

mapMain::~mapMain()
{
    delete this;
}

//загрузка полей в новый объект
void mapMain::loadParams()
{
    qDebug()<<"loadParams called";
    QString typeTmp = comboTypeEdit->currentText();
    QString nameTmp = leNameEdit->text();

    int xTmp = (int)dsbXEdit->value();
    int yTmp = (int)dsbYEdit->value();

    map->setNewObj(nameTmp,typeTmp,xTmp,yTmp);

    comboObj->addItem(nameTmp);

    fillLines();
}

//Удаление объекта отовсюду
void mapMain::btnDelete()
{
    QString objName = comboObj->currentText();

    //удаляем объект из вектора
    map->objectDelete(objName);
    //и из комбобокса
    comboObj->removeItem(comboObj->currentIndex());
    fillLines();
}

//проверяет, какое название стоит в комбобоксе и подставляет соответствующие поля
void mapMain::fillLines()
{
    auto iter = map->objectVector.begin();
    while (iter < map->objectVector.end())
    {
        if (iter->objName == comboObj->currentText())
        {
            leType->setText(iter->objType);
            dsbX->setValue(iter->objX);
            dsbY->setValue(-iter->objY);
        }
        ++iter;
    }
}

void mapMain::updateShipCoords(){

    leMarsh->setText(QString::number((dialMarsh->value())/10));
    lePsi->setText(QString::number(dialPsi->value()));

    rov.setPsiDesired(dialPsi->value());
    rov.setMarshDesired((dialMarsh->value())/10);

    rov.Regulyator();

    double marshCurrent = rov.getMarshCurrent();
    double psiCurrent = rov.getPsiCurrent();
    map->translateCoordsFromCurs(psiCurrent,marshCurrent);

}
