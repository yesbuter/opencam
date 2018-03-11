#include "opencam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Opencam w;
    w.setAttribute(Qt::WA_QuitOnClose, true);
    w.show();
    return a.exec();
}
