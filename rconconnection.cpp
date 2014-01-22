#include "rconconnection.h"
#include "rconpackage.h"
#include <QDebug>
#include <iostream>

using namespace rcon;

Connection::Connection(QString address, int port, QObject *parent) :
    Connection(parent)
{
    this->rconReset(address,port);
}


Connection::Connection(QObject *parent) :
    QObject(parent),
    sock(nullptr)
{
}

void Connection::rconReset(QString address, int port)
{
    this->address = address;
    this->port = port;
    this->ID = 43;

    delete this->sock;
    this->sock = new QTcpSocket(this);
    connect(sock,SIGNAL(connected()),this,SLOT(rconLogin()));
    connect(sock,SIGNAL(readyRead()),this,SLOT(rconReceivePackage()));
    connect(sock,SIGNAL(disconnected()),this,SLOT(rconDisconnection()));
}

void Connection::rconConnect(QString password)
{
    sock->connectToHost(address,port);
    this->password = password;
}

void Connection::rconLogin()
{
    Package login = Package::LoginPackage(password,42);
    sock->write(login.data());
    sock->flush();
    this->password = "";
}

void Connection::sendCommand(QString command)
{
    Package commandP = Package(command,Package::SERVERDATA_EXECCOMMAND,this->ID++);
    sock->write(commandP.data());
    sock->flush();
}

qint32 Connection::readquint32FromSock()
{
    qint32 data;
    int status = sock->read(reinterpret_cast<char*>(&data),sizeof(qint32));
    if (status == -1)
        qFatal("error reading package!");
    return data;
}

void Connection::rconReceivePackage()
{
    qDebug("##Receiving data");

    if (sock->bytesAvailable() < sizeof(qint32)) {
        qDebug("received partial package (for size)");
        return;
    }

    qint32 size = readquint32FromSock();

    if (size < 10) {
        qFatal("Error, package received shorter of 10 bytes");
        return;
    }

    if (sock->bytesAvailable() < size) {
        qDebug("received partial package (for real data)");
        //TODO return back in the sock of sizeof(qint32)
        return;
    }

    QByteArray data = sock->read(size);

    Package received(size,data);
    QString message = received.getMessage();
//    if (message.isEmpty())
//        message = '\n';


    static int counter = 0;
    counter++;

    switch(counter) {
    case 2:
        this->testConnectionSuccesful(received);
        break;
    default:
    {
        QString response(message);
        emit this->response(ID, response);
    }
    case 1:
        break;
    }
    //qDebug(QString().setNum(ID).append(response).toUtf8());

//    if (sock->bytesAvailable() != 0)
//        this->rconReceivePackage();
}

void Connection::testConnectionSuccesful(Package &package)
{
    if (package.getID() == 42) {
        emit this->response(ID, "Connection succesfull\n");
    }
    else
        qFatal("connection failed - probably a password error");
}
