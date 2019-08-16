#include "dialog_movement_view.h"
#include "dialog_movement_view.h"


Dialog_movement_view::Dialog_movement_view()
{
    _pixmap = new QPixmap(":/pic/5.png");
    _pixmap_2 = new QPixmap(":/pic/6.png");
    _pixmap_white = new QPixmap(":/pic/white.png");
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

Dialog_movement_view::~Dialog_movement_view()
{
    delete _pixmap;
    delete _pixmap_2;
    _pixmap = nullptr;
    _pixmap_2 = nullptr;
}
