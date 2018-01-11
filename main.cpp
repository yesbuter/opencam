#include "opencam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    opencam w;
    w.show();

    return a.exec();
}
