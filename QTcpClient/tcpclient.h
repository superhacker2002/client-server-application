#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <memory>


class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QString IP="localhost", uint16_t port=9999, QObject *parent = 0);
    ~TcpClient();
    void sendData(QString data);
    bool connectToHost(QString host, uint16_t port);
private:
    std::unique_ptr<QTcpSocket> socket_;
public slots:
    void readyRead();
    void bytesWritten(qint64 bytes);
    void disconnected();
};

#endif // TCPCLIENT_H
