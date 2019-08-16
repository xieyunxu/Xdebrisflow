#ifndef PROCESS_POST_H
#define PROCESS_POST_H
#include <QObject>
#include "phase.h"
class Process_main;
class Process_post:public QObject
{
    Q_OBJECT
private:
    float _recordtime;
public:
    Process_post(QObject* parent=nullptr);
    /*Computation Time*/
    void make_AnimationFile(const Phase& solid,const Process_main& _main);
    inline float get_RecordT(){return _recordtime;}
signals:
    void getCurrtimeSig(float crt);
};

#endif // PROCESS_POST_H
