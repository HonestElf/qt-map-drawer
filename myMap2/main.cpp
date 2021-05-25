#include "mapmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mapMain w;
    w.show();

    return a.exec();
}
