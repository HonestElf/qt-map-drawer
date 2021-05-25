#include "udpsender.h"

udpsender::udpsender(QObject *parent): QObject(parent)
{
    //создаем сокеты
    m_socket = new QUdpSocket(this);
    //Биндим сокет и выводим результат бинда
    qDebug()<<"one: "<<m_socket->bind(QHostAddress::LocalHost,13041);
    qDebug()<<"two: "<<m_socket->errorString();

    m_receiveSocket=new QUdpSocket(this);

    qDebug()<<m_receiveSocket->bind(QHostAddress::LocalHost,13044);
    qDebug()<<m_receiveSocket->errorString();

    connect(m_receiveSocket,SIGNAL(readyRead()),this,SLOT(readData()));

}

//Отправка данных
void udpsender::send(double Upsi, double Umarsh) {
    sendData.Upsi=Upsi;
    sendData.UMarsh=Umarsh;
//    qDebug()<<"==============";
//    qDebug()<<"send to matlab: ";
//    qDebug()<<"sendData.Upsi: "<<sendData.Upsi;
//    qDebug()<<"sendData.UMarsh: "<<sendData.UMarsh;
    m_socket->writeDatagram((char*)&sendData,sizeof (sendData),QHostAddress::LocalHost,13042);
}

//Чтение данных с порта
void udpsender::readData(){
    while (m_receiveSocket->hasPendingDatagrams()){
        m_receiveSocket->readDatagram((char*)&receivedData,sizeof(receivedData));
    }
//    qDebug()<<"==============";
//    qDebug()<<"received from matlab: ";
//    qDebug()<<"receivedData.Marsh "<<receivedData.Marsh;
//    qDebug()<<"receivedData.Psi "<<receivedData.Psi;
//    qDebug()<<"sendData.dMarsh: "<<receivedData.dMarsh;
//    qDebug()<<"sendData.dPsi: "<<receivedData.dPsi;
}

//получаем структуру с данными
FromMatlab udpsender::getData() {
    return receivedData;
}
