#include <QObject>
#include "swe.h"
#include "Swe_mnt/swe_movemnt.h"
#include "Swe_mnt/process_main.h"
#include "swe_view.h"
Swe::Swe(QObject* parent)
    :QObject (parent)
{
    _swe_mnt =new Swe_movemnt;
    if(Data::instance()->get_GUIStatus()==false)
    {_swe_mnt->running_SWEmnt();}
    else{
        _swe_view =new Swe_view;
        _thread_Mnt=new QThread(this);
        _swe_mnt->moveToThread(_thread_Mnt);
        connect(_swe_view,SIGNAL(sweMntstartSig()),_swe_mnt,SLOT(running_SWEmnt()));
        connect(_swe_mnt,SIGNAL(sweMntfinishSig()),_swe_view,SIGNAL(sweMntfinishSig()));
        connect(_swe_mnt,SIGNAL(getCurrtimeSig(double)),this,SIGNAL(getCurrtimeSig(double)));
        connect(this,SIGNAL(getCurrtimeSig(double)),_swe_view,SIGNAL(getCurrtimeSig(double)));
        connect(_thread_Mnt,SIGNAL(finished()),_swe_mnt,SLOT(deleteLater()));
        _thread_Mnt->start();
    }
}
Swe::~Swe()
{

    delete _swe_view;
    _thread_Mnt->quit();
    _thread_Mnt->wait();
}
