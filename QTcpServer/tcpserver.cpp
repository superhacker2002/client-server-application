#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QObject{parent}
{
    server = std::make_unique<QTcpServer>(this);
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server->listen(QHostAddress::Any, 9999)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started";
    }
}


void TcpServer::newConnection() {
    QTcpSocket * socket = server->nextPendingConnection();
    qDebug() << "new connection";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead(socket)));

//    qDebug() << socketBuffer;
//    HandlerFactory factory;
//    auto handler = factory.getHandler(FUNCTION);
//    auto handle_result = handler->handle(socketBuffer.toStdString());
//    qDebug() << handle_result.c_str();
    socket->write("Hello\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
//    socket->close();
}

void TcpServer::readyRead(QTcpSocket *socket) {
    auto socketBuffer = socket->readAll();
    HandlerFactory factory;
    auto handler = factory.getHandler(FUNCTION);
    auto handle_result = handler->handle(socketBuffer.toStdString());
    qDebug() << handle_result.c_str();
    socket->write(handle_result.c_str());
    socket->flush();
}
