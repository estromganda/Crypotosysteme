#include "playfairWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayfairWidget w;
    w.show();
    return a.exec();
}
