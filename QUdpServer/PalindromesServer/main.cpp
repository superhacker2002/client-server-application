#include <QCoreApplication>
#include "udpserver.h"
#include "../../handlers/handler_factory.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdpServer server(HandlerFactory::getHandler(HandlerFactory::handlerType::palindromes));
    return a.exec();
}
