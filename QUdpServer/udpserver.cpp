#include "udpserver.h"
#include <QDebug>

UdpServer::UdpServer(std::unique_ptr<IHandler> handler, uint16_t port, QObject *parent)
    : QObject{parent},
      socket_(std::make_unique<QUdpSocket>(this)),
      handler_(std::move(handler))
{
    if (socket_->bind(QHostAddress::Any, port)) {
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
    qDebug() << "Server received message from client:" << received_message;
    processMessage(received_message.trimmed());
    socket_->waitForBytesWritten();
}

void UdpServer::processMessage(QByteArray message) {
    auto result_message = handler_->handle(message.toStdString());
    quint64 writtenBytes = socket_->writeDatagram(QByteArray(result_message.c_str()), sender_, senderPort_);
    if (writtenBytes) {
        qDebug() << "Message was processed and sent to the client.";
    } else {
        qDebug() << "Message could not be sent.";
    }
    socket_->flush();
}
