#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <memory>
#include "../handlers/handler_interface.h"

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(std::unique_ptr<IHandler> handler, QObject *parent = nullptr);


public slots:
    void readyRead();
private:
    std::unique_ptr<QUdpSocket> socket_;
    std::unique_ptr<IHandler> handler_;

};

#endif // UDPSERVER_H
