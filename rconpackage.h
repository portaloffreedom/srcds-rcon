#ifndef RCONPACKAGE_H
#define RCONPACKAGE_H

#include <QString>

namespace rcon {

class Package
{
public:
    enum Type {
        SERVERDATA_AUTH = 3,
        SERVERDATA_AUTH_RESPONSE = 2,
        SERVERDATA_EXECCOMMAND = 2,
        SERVERDATA_RESPONSE_VALUE = 0
    };

    //Contructors
    Package(QString command, Type dataType, qint32 ID);
    Package(const qint32 size, const QByteArray &data);
    static Package LoginPackage(QString password, quint32 ID);

    //Getters
    QString getMessage() const {
        return this->command;
    }
    Type getType() const {
        return this->dataType;
    }
    quint32 getID() const {
        return this->ID;
    }
    const QByteArray &data();

private:
    QString command;
    Type dataType;
    quint32 ID;

    QByteArray package;

    void constructPackage();
    void deconstructPackage(const qint32 size, const QByteArray &qData);
    void appendPackage32Byte(qint32 data);

};

}

#endif // RCONPACKAGE_H
