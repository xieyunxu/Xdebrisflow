#include "dialog_channel_view.h"

Dialog_channel_view::Dialog_channel_view()
{
    _pixmap = new QPixmap(":/pic/5.png");
    _pixmap_2 = new QPixmap(":/pic/6.png");
    *_pixmap = _pixmap->scaled(1080,150
                               , Qt::IgnoreAspectRatio
                               , Qt::SmoothTransformation);
    *_pixmap_2 = _pixmap_2->scaled(1080,150
                                   , Qt::IgnoreAspectRatio
                                   , Qt::SmoothTransformation);

}

Dialog_channel_view::~Dialog_channel_view()
{
    delete _pixmap;
    delete _pixmap_2;
    _pixmap = nullptr;
    _pixmap_2 = nullptr;
}

