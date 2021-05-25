#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QUdpSocket>

//структура данных, отправляемая в модель
struct ToMatlab{
    ToMatlab(){Upsi=0;UMarsh=0;}
    double Upsi; //управляющий сигнал по курсу
    double UMarsh;//управляющий сигнал по маршу
};

//структура данных, принятых от модели
struct FromMatlab{
    FromMatlab(){Psi=0;dPsi=0;Marsh=0;dMarsh=0;}
    double Psi;//курс
    double dPsi;//угловая скорость по курсу
    double Marsh;//марш
    double dMarsh;//линейная скорость по маршу
};

class udpsender: public QObject
{
    Q_OBJECT

public:
    udpsender(QObject *parent = nullptr);

    //метод, возвращает принятые значения
    FromMatlab getData();
private:
    //отправленные данные
    ToMatlab sendData;
    //принятые данные
    FromMatlab receivedData;

    //сокет под отправку
    QUdpSocket *m_socket;
    //сокет под прием
    QUdpSocket *m_receiveSocket;

public slots:
    //метод, который отправляет сообщение с новым управляющим сигналом
    void send(double Upsi, double Umarsh);

    //слот, который считывает принятые по udp сообщения и заполняет ими структуру receivedData
    void readData();
};

#endif // UDPSENDER_H
