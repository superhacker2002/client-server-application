#include "udpserver.h"
#include <QDebug>

UdpServer::UdpServer(std::unique_ptr<IHandler> handler, QObject *parent)
    : QObject{parent},
      socket_(std::make_unique<QUdpSocket>(this)),
      handler_(std::move(handler))
{
    if (socket_->bind(QHostAddress::Any, 9999)) {
        qDebug() << "Server started";
    } else {
        qDebug() << "Server could not start";
    }
    connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));

}

void UdpServer::readyRead() {
    QByteArray received_message;
    received_message.resize(socket_->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    QByteArray welcome_message("Hello client.\nPlease enter the message that will be processed by server..\r\n");
    socket_->writeDatagram(welcome_message, sender, senderPort);
    socket_->readDatagram(received_message.data(), received_message.size(), &sender, &senderPort);
    processMessage(received_message.trimmed(), sender, senderPort);
    socket_->waitForBytesWritten();
}

void UdpServer::processMessage(QByteArray message, QHostAddress sender, quint16 senderPort) {
    auto result_message = handler_->handle(message.toStdString()) + "\r\n";
    socket_->writeDatagram(QByteArray(result_message.c_str()), sender, senderPort);
    socket_->flush();
}

