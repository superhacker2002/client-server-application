#include <QCoreApplication>
#include "tcpserver.h"
#include "../../handlers/handler_factory.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer server(HandlerFactory::getHandler(HandlerFactory::handlerType::duplications));
    return a.exec();
}
