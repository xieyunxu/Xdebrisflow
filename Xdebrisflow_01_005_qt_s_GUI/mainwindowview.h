#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

class QPixmap;

class MainWindow_View
{
public:
    MainWindow_View();
    ~MainWindow_View();
    QPixmap* pixmap(){return _pixmap;}
    QPixmap* pixmap_2(){return _pixmap_2;}
    QPixmap* pixmap_3(){return _pixmap_3;}
private:
    QPixmap* _pixmap;
    QPixmap* _pixmap_2;
    QPixmap* _pixmap_3;

};

#endif // MAINWINDOWVIEW_H
