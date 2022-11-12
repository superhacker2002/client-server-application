#include "udpclient.h"

UdpClient::UdpClient(QString IP, uint16_t port, QObject *parent)
    : QObject{parent},
      socket_(std::make_unique<QUdpSocket>(this))
{
    if (socket_->bind(QHostAddress(IP), port)) {
        qDebug() << "Connected to the server.";
    } else {
        qDebug() << "Could not connect to the server.";
        throw std::exception();
    }
    connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_.get(), SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
}

void UdpClient::sendData(QByteArray message, QString IP, uint16_t port) {
    socket_->writeDatagram(message, QHostAddress(IP), port);
}

void UdpClient::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written to the socket.";
}

void UdpClient::readyRead() {
    std::string received_message;
    QHostAddress sender;
    uint16_t senderPort;
    socket_->readDatagram(received_message.data(), socket_->pendingDatagramSize(),
                          &sender, &senderPort);
    qDebug() << received_message.data();
}


