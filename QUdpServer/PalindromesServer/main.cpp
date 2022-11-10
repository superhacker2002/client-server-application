#include <QCoreApplication>
#include <QCommandLineParser>
#include "../udpserver.h"
#include "../../handlers/handler_factory.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption portNumber(QStringList() << "p", QCoreApplication::translate("main", "Port number of the server"), "port");
    portNumber.setDefaultValue("9999");
    parser.addOption(portNumber);
    parser.process(a);
    uint16_t port = parser.value(portNumber).toUInt();

    UdpServer server(HandlerFactory::getHandler(HandlerFactory::handlerType::duplications), port);
    return a.exec();
}
