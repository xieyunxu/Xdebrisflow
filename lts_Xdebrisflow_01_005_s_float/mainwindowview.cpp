#include "mainwindowview.h"
#include <QPixmap>

MainWindow_View::MainWindow_View()
{
    _pixmap = new QPixmap(":/pic/56.png");
    *_pixmap = _pixmap->scaled(1820,150
                               , Qt::IgnoreAspectRatio
                               , Qt::SmoothTransformation);
    _pixmap_2 = new QPixmap(":/pic/2.png");
    *_pixmap_2 = _pixmap_2->scaled(500,830
                                   , Qt::IgnoreAspectRatio
                                   , Qt::SmoothTransformation);
    _pixmap_3 = new QPixmap(":/pic/7.jpg");
    *_pixmap_3 = _pixmap_3->scaled(1320,830
                                   , Qt::IgnoreAspectRatio
                                   , Qt::SmoothTransformation);


}

MainWindow_View::~MainWindow_View()
{
    delete _pixmap;
    delete _pixmap_2;
    delete _pixmap_3;
    _pixmap = nullptr;
    _pixmap_2 = nullptr;
    _pixmap_3 = nullptr;
}
