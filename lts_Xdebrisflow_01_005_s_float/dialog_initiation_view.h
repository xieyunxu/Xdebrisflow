#ifndef DIALOG_INITIATION_VIEW_H
#define DIALOG_INITIATION_VIEW_H

#include <QPixmap>
class Dialog_initiation_view
{
public:
    Dialog_initiation_view();
    ~Dialog_initiation_view();
    QPixmap* pixmap(){return _pixmap;}
    QPixmap* pixmap_2(){return _pixmap_2;}
    QPixmap* pixmap_white(){return _pixmap_white;}
private:
    QPixmap* _pixmap;
    QPixmap* _pixmap_2;
    QPixmap* _pixmap_white;
};

#endif // DIALOG_INITIATION_VIEW_H
