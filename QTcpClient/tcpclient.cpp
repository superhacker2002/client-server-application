#include "tcpclient.h"
#include <QHostAddress>
#include <iostream>


TcpClient::TcpClient(QString IP, uint16_t port, QObject *parent)
    : QObject{parent},
      socket_{std::make_unique<QTcpSocket>(this)}
{
    if (connectToHost(IP, port)) {
        qDebug() << "Connected to server.";
    } else {
        qDebug() << "Could not connect to the server.";
        throw std::exception();

    }
    connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_.get(), SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket_.get(), SIGNAL(disconnected()), this, SLOT(disconnected()));
}

bool TcpClient::connectToHost(QString host, uint16_t port) {
   socket_->connectToHost(QHostAddress(host), port);
   return socket_->waitForConnected();
}

TcpClient::~TcpClient() {
    if (socket_->isOpen()) {
        socket_->close();
    }
}

void TcpClient::sendData(QString data) {
    socket_->write(data.toStdString().c_str());
    socket_->flush();
    socket_->waitForReadyRead();
}

void TcpClient::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written to the socket.";
}

void TcpClient::readyRead() {
    qDebug() << "Message from server is received:";
    QByteArray message = socket_->readAll();
    qDebug() << message;
}

void TcpClient::disconnected() {
    qDebug() << "Connection to the server was closed.";
    exit(1);
}
