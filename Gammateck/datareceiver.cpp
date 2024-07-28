#include "datareceiver.h"
#include <iostream>

namespace {
namespace Config {
static constexpr int port = 10002;
} // namespace Config
}

DataReceiver::DataReceiver(QObject *parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

DataReceiver::~DataReceiver()
{
}

void DataReceiver::startReceiving()
{
    if (udpSocket->bind(QHostAddress::LocalHost, Config::port)) {
        connect(udpSocket, &QUdpSocket::readyRead, this, &DataReceiver::readPendingDatagrams);
        std::cout << "Listening port: " << Config::port << std::endl;
    }
}

void DataReceiver::stopReceiving()
{
    disconnect(udpSocket, &QUdpSocket::readyRead, this, &DataReceiver::readPendingDatagrams);
    udpSocket->close();
    std::cout << "Close connection port: " << Config::port;
}

void DataReceiver::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagramData;
        datagramData.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagramData.data(), datagramData.size(), &sender, &senderPort);
        emit figureReceived(datagramData);
    }
}
