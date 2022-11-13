#include "udpclient.h"

UdpClient::UdpClient(QObject *parent)
    : QObject{parent},
      socket_(std::make_unique<QUdpSocket>(this))
{
    connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_.get(), SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
}

void UdpClient::sendData(QByteArray message, QString IP, uint16_t port) {
    socket_->writeDatagram(message, QHostAddress(IP), port);
}

void UdpClient::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written to the socket.";
    socket_->waitForReadyRead();
}

void UdpClient::readyRead() {
    QByteArray received_message;
    received_message.resize(socket_->pendingDatagramSize());
    socket_->readDatagram(received_message.data(), received_message.size());
    QTextStream out(stdout);
    out << received_message << "\n";
}


