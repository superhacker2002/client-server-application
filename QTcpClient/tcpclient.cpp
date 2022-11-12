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
        qDebug() << "no Connected to server.";
    }
    connect(socket_.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_.get(), SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
}

bool TcpClient::connectToHost(QString host, uint16_t port) {
   socket_->connectToHost(QHostAddress(host), port);
   return socket_->waitForConnected();
}

TcpClient::~TcpClient() {
//    socket_->close();
}

void TcpClient::sendData(QString data) {
    socket_->write(data.toStdString().c_str());
    socket_->flush();
    socket_->waitForReadyRead();
}

void TcpClient::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void TcpClient::readyRead() {
    qDebug() << "Ready to read message";
    QByteArray message = socket_->readAll();
    qDebug() << message;
}
