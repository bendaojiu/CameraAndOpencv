#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QImage>("QImage");
    Widget w;
    w.show();

    return a.exec();
}
