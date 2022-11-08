#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <memory>

class TcpServer : public QObject
{
    Q_OBJECT
 public:
    explicit TcpServer(QObject *parent = nullptr);
 signals:

 public slots:
    void newConnection();
 private:
    std::unique_ptr<QTcpServer> server;

};

#endif // TCPSERVER_H
