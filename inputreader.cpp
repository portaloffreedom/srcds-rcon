#include "inputreader.h"
#include <iostream>

InputReader::InputReader(QObject *parent) :
    QObject(parent),
    stream(stdin, QIODevice::ReadOnly)
{
    std::cout<<"Inserire l'indirizzo del server: "<<std::flush;
    QString addr;
    stream>>addr;

    std::cout<<"Inserire la porta del server: "<<std::flush;
    int port;
    stream>>port;

    if (port == 0)     port = 27015; //default value

    con.rconReset(addr,port);

    std::cout<<"Inserire la password: "<<std::flush;
    QString passwd;
    stream>>passwd;

    con.rconConnect(passwd);

    notifier = new QSocketNotifier(fileno(stdin),QSocketNotifier::Read);
    connect(notifier,SIGNAL(activated(int)),this,SLOT(read()));
    connect(&con,SIGNAL(response(quint32,QString)),this,SLOT(receive(quint32,QString)));
    connect(&con,SIGNAL(rconDisconnect()),this,SLOT(disconnect()));
}

void InputReader::read()
{
    QString cmd = stream.readLine();
    con.sendCommand(cmd);
}

void InputReader::receive(quint32 ID, QString message)
{
//    if (message.isEmpty())
//        return;

    std::cout<<message.toUtf8().data();
    std::cout<<">>"<<std::flush;
}
