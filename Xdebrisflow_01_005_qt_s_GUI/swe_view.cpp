#include "swe_view.h"
#include <QObject>
#include <QDebug>
Swe_view::Swe_view(QObject* parent)
    :QObject (parent)
{
    _logging=new Dialog_logging;
    _mwindow=new MainWindow;
    _dock_dam=new Dialog_dam;
    _dock_channel=new Dialog_channel;
    _initation=new Dialog_initiation;
    _movement=new Dialog_movement;
    init_Plugin();
    connect(_logging,SIGNAL(gotoMainwindow()),_mwindow,SLOT(receive()));
    connect(_mwindow,SIGNAL(showDamsetting()),_dock_dam,SLOT(receive()));
    connect(_mwindow,SIGNAL(showChannelsetting()),_dock_channel,SLOT(receive()));
    connect(_mwindow,SIGNAL(showInitsetting()),_initation,SLOT(receive()));
    connect(_mwindow,SIGNAL(showMovemntsetting()),_movement,SLOT(receive()));
    connect(_mwindow,SIGNAL(showStartSig()),this,SIGNAL(sweMntstartSig()));
    connect(this,SIGNAL(sweMntstartSig()),_bar,SLOT(receive()));
    connect(this,SIGNAL(sweMntstartSig()),_bar2,SLOT(initForm()));
    connect(this,SIGNAL(getCurrtimeSig(double)),_bar,SLOT(getCurrtimeSlot(double)));
    connect(this,SIGNAL(getCurrtimeSig(double)),_bar2,SLOT(getCurrtimeSlot(double)));
    connect(this,SIGNAL(sweMntfinishSig()),_bar,SLOT(finish()));
    connect(this,SIGNAL(sweMntfinishSig()),_bar2,SLOT(finish()));
    _logging->show();

}
Swe_view::~Swe_view()
{
    _logging->deleteLater();
    _mwindow->deleteLater();
    _dock_dam->deleteLater();
    _dock_channel->deleteLater();
    _initation->deleteLater();
    _movement->deleteLater();
    _bar->deleteLater();
}
void Swe_view::init_Plugin()
{
    _bar=new process_bar_widget;
    _bar2=new frmRoundPlot;
}
void Swe_view::receive()
{
    init_Plugin();
}
