#include "tcpserver.h"
#include <QDebug>

TcpServer::TcpServer(std::unique_ptr<IHandler> handler, QObject *parent)
    : QObject{parent},
      handler_(std::move(handler))
{
    server_ = std::make_unique<QTcpServer>(this);
    connect(server_.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server_->listen(QHostAddress::Any, 9999)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started";
    }
}

void TcpServer::newConnection() {
    QTcpSocket *socket = server_->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    socket->write("Hello client.\nPlease enter the message that will be processed by server..\r\n");
    socket->flush();
    socket->waitForBytesWritten();
}

void TcpServer::readyRead() {
    auto socket = static_cast<QTcpSocket*>(sender());
    QByteArray message = socket->readAll().trimmed();
    processMessage(socket, message);
}

void TcpServer::disconnected() {
    auto socket = static_cast<QTcpSocket*>(sender());
    socket->close();
    if (!socket->isOpen()) {
        qDebug() << "connection is closed";
    }
}

void TcpServer::processMessage(QTcpSocket* socket, QByteArray message) {
    std::string result = handler_->handle(message.toStdString());
    socket->write((result + "\r\n").c_str());
    socket->flush();
}
