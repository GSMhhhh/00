#include "JCMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //qputenv("QT_SCALE_FACTOR", "2.0");
    QApplication a(argc, argv);
    JCMainWindow w;
    w.show();

    return a.exec();
}
