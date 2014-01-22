#include <QCoreApplication>

#include "inputreader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InputReader *in = new InputReader();

    return a.exec();
}
