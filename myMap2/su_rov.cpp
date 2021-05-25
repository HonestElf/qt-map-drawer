#include "su_rov.h"

SU_ROV::SU_ROV(QObject *parent)
    : QObject(parent)
{
//    начальные значения
    //курс
    psiDesired = 0;
    psiCurrent =0;
    K1psi=0.05;
    K2psi=0.1;
    dPsi = 0;
    Upsi = 0;
    //марш
    marshDesired = 0;
    marshCurrent = 0;
    K1m=31;
    K2m=21.65;
    dMarsh =0;
    UMarsh =0;
}

SU_ROV::~SU_ROV()
{
}

//Установка требуемого угла
void SU_ROV::setPsiDesired(double input){
    psiDesired = input;
};

 //Установка требуемой скорости
void SU_ROV::setMarshDesired(double input){
 marshDesired=input;
};

double SU_ROV::getPsiCurrent()
{
    return udp.getData().Psi;
}

double SU_ROV::getMarshCurrent()
{
    return udp.getData().Marsh;;
}

double SU_ROV::getdMarshCurrent()
{
    return udp.getData().dMarsh;
}

double SU_ROV::getdPsiCurrent()
{
    return udp.getData().dPsi;
}


void SU_ROV::Regulyator() {
  //получаем данные
    marshCurrent = getMarshCurrent();
    psiCurrent =fmod(getPsiCurrent(),360);
    dMarsh = getdMarshCurrent();
    dPsi=fmod(getdPsiCurrent(),360);

    qDebug()<<"==============";
    qDebug()<<"marshCurrent"<<marshCurrent;
    qDebug()<<"marshDesired"<<marshDesired;

    qDebug()<<"psiCurrent"<<psiCurrent;
    qDebug()<<"psiDesired"<<psiDesired;

    qDebug()<<"dMarsh"<<dMarsh;
    qDebug()<<"dPsi"<<dPsi;

    //формируем управляющие напряжения
    Upsi = (psiDesired-psiCurrent)*K1psi-(K2psi*dPsi);
    UMarsh = (marshDesired-marshCurrent)*K1m-(K2m*dMarsh);

    qDebug()<<"Upsi"<<Upsi;
    qDebug()<<"UMarsh"<<UMarsh;

    //Отправляем управляющие напряжения
      udp.send(Upsi,UMarsh);
}
