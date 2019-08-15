#ifndef DIALOG_DAM_VIEW_H
#define DIALOG_DAM_VIEW_H

class QPixmap;
class Dialog_dam_View
{
public:
    Dialog_dam_View();
    ~Dialog_dam_View();
    QPixmap* pixmap(){return _pixmap;}
    QPixmap* pixmap_2(){return _pixmap_2;}
private:
    QPixmap* _pixmap;
    QPixmap* _pixmap_2;

};

#endif // DIALOG_DAM_VIEW_H
