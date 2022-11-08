#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <memory>
#include "../handler_interface.h"
#include "../handler_factory.h"


class TcpServer : public QObject
{
    Q_OBJECT
 public:
    explicit TcpServer(QObject *parent = nullptr);

 public slots:
    void newConnection();
    void readyRead(QTcpSocket *socket);

 private:
    std::unique_ptr<QTcpServer> server;

};

#endif // TCPSERVER_H
