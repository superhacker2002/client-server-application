#include <QCoreApplication>
#include <QCommandLineParser>
#include "tcpclient.h"
#include <iostream>

bool commandLineParserSuccess(QCommandLineParser &parser, QString &IP, uint16_t &port) {
    parser.addHelpOption();
    parser.addPositionalArgument("IP", "server address");
    parser.addPositionalArgument("port", "port number");

    parser.parse(QCoreApplication::arguments());

    const QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.size() == 2) {
       IP = positionalArguments[0];
       port = positionalArguments[1].toUInt();
       return true;
    } else {
       return false;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString IP;
    uint16_t port;
    QCommandLineParser parser;

    if (!commandLineParserSuccess(parser, IP, port)) {
        return 1;
    }

    QString message;
    QTextStream instream(stdin);
    TcpClient client(IP, port);
    while (true) {
        instream.flush();
        message = instream.readLine();
        client.sendData(QString(message));
    }
    return a.exec();
}
