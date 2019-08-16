#ifndef LONGFIGURE_H
#define LONGFIGURE_H

#include <QPixmap>
#include <QDebug>
class Dialog_logging_view
{
private:
    QPixmap* _pixmap;
public:
    Dialog_logging_view();
    ~Dialog_logging_view();
    QPixmap* pixmap()
    {
        //qDebug()<<__FUNCTION__<<endl;
        return _pixmap;}
};

#endif // LONGFIGURE_H
