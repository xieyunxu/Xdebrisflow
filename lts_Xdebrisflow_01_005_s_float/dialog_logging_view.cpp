#include <QPixmap>
#include "dialog_logging_view.h"
#include "data.h"
Dialog_logging_view::Dialog_logging_view()
{
    _pixmap = new QPixmap(":/pic/log_1.png");
    *_pixmap = _pixmap->scaled(Data::instance()->log_WidgetSize()
                               ,Qt::IgnoreAspectRatio
                               ,Qt::SmoothTransformation);
}
Dialog_logging_view::~Dialog_logging_view()
{
    delete _pixmap;
    _pixmap = nullptr;
}
