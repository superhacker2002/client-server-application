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

    socket_->readDatagram(received_message.data(), received_message.size(), &sender_, &senderPort_);
    processMessage(received_message.trimmed());
    socket_->waitForBytesWritten();
}

void UdpServer::processMessage(QByteArray message) {
    auto result_message = handler_->handle(message.toStdString()) + "\r\n";
    socket_->writeDatagram(QByteArray(result_message.c_str()), sender_, senderPort_);
    socket_->flush();
}
