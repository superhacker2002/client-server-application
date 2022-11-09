#include "udpserver.h"

UdpServer::UdpServer(std::unique_ptr<IHandler> handler, QObject *parent)
    : QObject{parent},
      socket_(std::make_unique<QUdpSocket>(this)),
      handler_(std::move(handler))
{

}
