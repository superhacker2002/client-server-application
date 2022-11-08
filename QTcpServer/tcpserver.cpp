#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QObject{parent}
{
    server = std::make_unique<QTcpServer>(this);
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started";
    }
}


void TcpServer::newConnection() {
    auto socket = server->nextPendingConnection();
    socket->write("Write text \r\n");
    socket->flush();
    socket->waitForBytesWritten();
    socket->close();
}

class Interface {
    virtual void handle() = 0;
};

class A : Interface {
    void handle() override;
};
