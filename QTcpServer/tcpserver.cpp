#include "tcpserver.h"
#include <QDebug>

TcpServer::TcpServer(std::unique_ptr<IHandler> handler, uint16_t port, QObject *parent)
    : QObject{parent},
      handler_(std::move(handler))
{
    server_ = std::make_unique<QTcpServer>(this);
    connect(server_.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server_->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started";
    }
}

void TcpServer::newConnection() {
    QTcpSocket *socket = server_->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    socket->waitForBytesWritten();
}

void TcpServer::readyRead() {
    auto socket = static_cast<QTcpSocket*>(sender());
    QByteArray message = socket->readAll().trimmed();
    QTextStream outstream(stdout);
    qDebug() << "Message is received: " << message;
    processMessage(socket, message);
}

void TcpServer::disconnected() {
    auto socket = static_cast<QTcpSocket*>(sender());
    socket->close();
    if (!socket->isOpen()) {
        qDebug() << "Connection is closed";
    }
}

void TcpServer::processMessage(QTcpSocket* socket, QByteArray message) {
    std::string result = handler_->handle(message.toStdString());
    qint64 writtenBytes = socket->write((result).c_str());
    if (writtenBytes && writtenBytes != -1) {
        qDebug() << "Message was sent to the client.";
    } else {
        qDebug() << "Message could not be sent.";
    }
    socket->flush();
}
