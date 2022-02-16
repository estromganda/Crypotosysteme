#include "cryptoflotwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CryptoFlotWidget w;
    w.show();
    return a.exec();
}
