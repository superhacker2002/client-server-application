#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <memory>
#include "../../handlers/handler_interface.h"

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(std::unique_ptr<IHandler> handler, uint16_t port, QObject *parent = nullptr);

public slots:
    void readyRead();
    void processMessage(QByteArray message);

private:
    std::unique_ptr<QUdpSocket> socket_;
    std::unique_ptr<IHandler> handler_;
    QHostAddress sender_;
    quint16 senderPort_;
};
