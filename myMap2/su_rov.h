#ifndef SU_ROV_H
#define SU_ROV_H

#include <QObject>
#include <QTimer>
#include "udpsender.h"

class SU_ROV : public QObject
{
    Q_OBJECT

public:
    explicit SU_ROV(QObject *parent = nullptr);
    ~SU_ROV();

   //Установка требуемого угла
    void setPsiDesired(double input);
    //Установка требуемой скорости
    void setMarshDesired(double input);

    //получение текущего угла
    double getPsiCurrent();
        double getdPsiCurrent();
    //получение текущей скорости
    double getMarshCurrent();
    double getdMarshCurrent();

//применение регуляторов
   void Regulyator();
signals:

private:
    QTimer timer;
    //класс под прием и отправку
    udpsender udp;
    //заданный и текущий курс, угловая скорость по курсу
    double psiDesired,psiCurrent,dPsi;

    //заданное и текущее положение по маршу и скорость по маршу
    double marshDesired,marshCurrent,dMarsh;

    //коэффициенты K1m,K2m - для марша
    double K1m,K2m;
    //коэффициенты K1psi,K2psi - для угла
    double K1psi,K2psi;

    //управляющие сигнал
    double Upsi;
    double UMarsh;



};
#endif // SU_ROV_H
