#include <QApplication>
#include "swe.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Swe SWE;
    return app.exec();
}
