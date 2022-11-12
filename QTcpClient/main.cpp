#include <QCoreApplication>
#include <QCommandLineParser>
#include "tcpclient.h"
#include <iostream>

bool commandLineParserSuccess( QString &IP, uint16_t &port) {
    QCommandLineParser parser;
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

void getMessages(TcpClient &client) {
    QString message;
    QTextStream instream(stdin);
    QTextStream outstream(stdout);
    while (true) {
        qDebug() << "Enter message that will be proccesd by the server.";
//        outstream.flush();
        message = instream.readLine();
        if (message.isEmpty()) {
            qDebug() << "Message is empty.";
        } else {
            client.sendData(QString(message));
        }
    }
}

void startTcpClient(QString IP, uint16_t port) {
    try {
        TcpClient client(IP, port);
        getMessages(client);
    } catch (...) {
        exit(1);
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString IP;
    uint16_t port;

    if (!commandLineParserSuccess(IP, port)) {
        return 1;
    }
    startTcpClient(IP, port);

    return a.exec();
}