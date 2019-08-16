#ifndef DIALOG_MOVEMENT_VIEW_H
#define DIALOG_MOVEMENT_VIEW_H

#include <QPixmap>
class Dialog_movement_view
{
public:
    Dialog_movement_view();
    ~Dialog_movement_view();
    QPixmap* pixmap(){return _pixmap;}
    QPixmap* pixmap_2(){return _pixmap_2;}
    QPixmap* pixmap_white(){return _pixmap_white;}
private:
    QPixmap* _pixmap;
    QPixmap* _pixmap_2;
    QPixmap* _pixmap_white;
};

#endif // DIALOG_MOVEMENT_VIEW_H
