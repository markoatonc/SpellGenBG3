#include "gen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gen w;
    w.show();
    return a.exec();
}
