#include "adfgvxWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdfgvxWidget w;
    w.show();
    return a.exec();
}
