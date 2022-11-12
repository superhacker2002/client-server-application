#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <memory>

class UdpClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpClient(QString IP, uint16_t port, QObject *parent = nullptr);
    void sendData(QByteArray message, QString IP, uint16_t port);

public slots:
    void readyRead();
    void bytesWritten(qint64 bytes);

private:
    std::unique_ptr<QUdpSocket> socket_;
};

#endif // UDPCLIENT_H
