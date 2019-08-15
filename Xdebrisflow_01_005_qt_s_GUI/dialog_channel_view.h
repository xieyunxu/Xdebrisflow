#ifndef DIALOG_CHANNEL_VIEW_H
#define DIALOG_CHANNEL_VIEW_H

#include <QPixmap>
class Dialog_channel_view
{
public:
    Dialog_channel_view();
    ~Dialog_channel_view();
    QPixmap* pixmap(){return _pixmap;}
    QPixmap* pixmap_2(){return _pixmap_2;}
private:
    QPixmap* _pixmap;
    QPixmap* _pixmap_2;
};

#endif // DIALOG_CHANNEL_VIEW_H
