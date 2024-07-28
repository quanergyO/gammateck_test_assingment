#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class DataReceiver : public QObject
{
    Q_OBJECT

public:
    DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

    void startReceiving();
    void stopReceiving();

signals:
    void figureReceived(const QByteArray &data);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
};

#endif // DATARECEIVER_H
