#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <QObject>
#include <QSocketNotifier>
#include <QCoreApplication>
#include <QTextStream>
#include "rconconnection.h"

class InputReader : public QObject
{
    Q_OBJECT
public:
    explicit InputReader(QObject *parent = 0);

public slots:
    void read();
    void receive(quint32 ID, QString message);
    void disconnect(){
        QCoreApplication::exit(0);
    }

private:
    QSocketNotifier *notifier;
    QTextStream stream;
    rcon::Connection con;
};

#endif // INPUTREADER_H
