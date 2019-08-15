#include "dialog_initiation_view.h"

#include <QPixmap>

Dialog_initiation_view::Dialog_initiation_view()
{
    _pixmap = new QPixmap(":/pic/5.png");
    _pixmap_2 = new QPixmap(":/pic/6.png");
    _pixmap_white= new QPixmap(":/pic/white.png");
    *_pixmap = _pixmap->scaled(1080,150
                               , Qt::IgnoreAspectRatio
                               , Qt::SmoothTransformation);
    *_pixmap_2 = _pixmap_2->scaled(1080,150
                                   , Qt::IgnoreAspectRatio
                                   , Qt::SmoothTransformation);
    *_pixmap_white =_pixmap_white->scaled(1080,420
                                          , Qt::IgnoreAspectRatio
                                          , Qt::SmoothTransformation);

}

Dialog_initiation_view::~Dialog_initiation_view()
{
    delete _pixmap;
    delete _pixmap_2;
    delete  _pixmap_white;
    _pixmap = nullptr;
    _pixmap_2 = nullptr;
    _pixmap_white =nullptr;
}
