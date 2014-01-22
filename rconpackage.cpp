#include "rconpackage.h"
#include <QtEndian>
#include <QDebug>

using namespace rcon;

void Package::constructPackage()
{
    this->appendPackage32Byte(command.size()+10);
    this->appendPackage32Byte(ID);
    this->appendPackage32Byte(dataType);
    package += command += static_cast<char>(0);
    package += static_cast<char>(0);

}

qint32 readQuint32FromData(const char* data, int pos)
{
    const qint32 *pint = reinterpret_cast<const qint32*>(data+pos*sizeof(qint32));
    return *pint;
}

void Package::deconstructPackage(const qint32 size, const QByteArray &qData)
{
    const char *data = qData.data();

    this->ID = readQuint32FromData(data,0);
    qint32 typeInt = readQuint32FromData(data,1);
    this->dataType = static_cast<Package::Type>(typeInt);

    int messageOffset = sizeof(qint32)*2;
    QString message(data+messageOffset);
    this->command = message;

    char end = data[size-1];
    if (end != 0)
        qFatal("error response package not ending with 0");
}

Package Package::LoginPackage(QString password, quint32 ID)
{
    return Package(password, Package::SERVERDATA_AUTH, ID);
}

void Package::appendPackage32Byte(qint32 data)
{
    quint32 littleData = qToLittleEndian(data);
    package.append(reinterpret_cast<char*>(&littleData),sizeof(qint32));
}

Package::Package(QString command, Type dataType, qint32 ID):
    package()
{
    this->command = command;
    this->dataType = dataType;
    this->ID = ID;
}

Package::Package(const qint32 size,const QByteArray &data)
{
    this->deconstructPackage(size,data);
}

const QByteArray &Package::data()
{
    this->constructPackage();
    return package;
}
