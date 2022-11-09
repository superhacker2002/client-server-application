#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "../handlers/handler_interface.h"
#include <memory>


class TcpServer : public QObject
{
    Q_OBJECT
 public:
    explicit TcpServer(std::unique_ptr<IHandler> handler, QObject *parent = nullptr);

 public slots:
    void newConnection();
    void readyRead();
    void disconnected();

 private:
    std::unique_ptr<IHandler> handler_;
    std::unique_ptr<QTcpServer> server_;
    void processMessage(QTcpSocket* socket, QByteArray message);
};
