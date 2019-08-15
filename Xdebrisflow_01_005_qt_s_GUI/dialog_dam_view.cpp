#include "dialog_dam_view.h"

#include <QPixmap>

Dialog_dam_View::Dialog_dam_View()
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

Dialog_dam_View::~Dialog_dam_View()
{
    delete _pixmap;
    delete _pixmap_2;
    _pixmap = nullptr;
    _pixmap_2 = nullptr;
}

