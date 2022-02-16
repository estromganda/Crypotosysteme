#include "vigenereWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VigenereWidget w;
    w.resize(700, 580);
    w.show();
    return a.exec();
}
