#ifndef RCONCONNECTION_H
#define RCONCONNECTION_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include "rconpackage.h"

namespace rcon {

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QString address, int port, QObject *parent = 0);
    explicit Connection(QObject *parent = 0);

private:
    QString address;
    QString password;
    QTcpSocket *sock;
    int port;
    int ID;

    qint32 readquint32FromSock();
    void testConnectionSuccesful(Package &package);

signals:
    void response(quint32 ID, QString response);
    void rconDisconnect();

public slots:
    void sendCommand(QString command);
    void rconConnect(QString password);
    void rconReset(QString address, int port);

private slots:
    /**
     * @brief rconLogin sends SERVERDATA_AUTH and enables the connection
     */
    void rconLogin();

    /**
     * @brief rconReceivePackage receives a package and sends the command string
     * as a signal
     */
    void rconReceivePackage();

    void rconDisconnection() {
        qDebug("\nDisconnetting from RCON");
        emit rconDisconnect();
    }

};

}

#endif // RCONCONNECTION_H
