#ifndef SWE_VIEW_H
#define SWE_VIEW_H
#include <QDebug>
#include "dialog_logging.h"
#include "mainwindow.h"
#include "dialog_channel.h"
#include "dialog_dam.h"
#include "dialog_channel.h"
#include "dialog_initiation.h"
#include "dialog_movement.h"
#include "process_bar_widget.h"
#include "frmroundplot.h"
class Swe_view:public QObject
{
    Q_OBJECT
public:
    explicit Swe_view(QObject* parent=nullptr);
    ~Swe_view();
signals:
    void getCurrtimeSig(double crt);
    void sweMntfinishSig();
public slots:
    void receive();
    void sweMntfinishSlot(){qDebug()<<"receive";}
    void show(double crt){qDebug()<<crt<<endl;}
    void init_Plugin();
private:
    Dialog_logging* _logging;
    MainWindow* _mwindow;
    Dialog_dam* _dock_dam;
    Dialog_channel* _dock_channel;
    Dialog_initiation* _initation;
    Dialog_movement* _movement;
    process_bar_widget* _bar;
    frmRoundPlot* _bar2;

signals:
    void sweMntstartSig();
};

#endif // SWE_VIEW_H
