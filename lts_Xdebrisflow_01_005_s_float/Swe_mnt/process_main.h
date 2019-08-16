#ifndef PROCESS_MAIN_H
#define PROCESS_MAIN_H
#include <iostream>
#include <QObject>
#include <math.h>
#include "phase.h"
#include "data.h"
class Point;
class Phase;
class Term;
class MidPara;
class MidPara_UNS;
class Process_main:public QObject
{
    Q_OBJECT
public:
    Process_main(QObject* parent=nullptr);
    ~Process_main();
    void RunIteration(Phase& solid,Term& term);
    void staggerResult(Phase& solid);
    void NUstaggerResult(Phase& solid,Term& term);
    void LaxWendroffResult(Phase& solid,Term& term);
    void maxSpeed(const Phase& solid);
    inline float abs2(float input){return (input>0?input:-input);}
    void count_time();
    inline Point* get_Maxspeed(){return _maxSpeed;}
    inline float max(float input_1,float input_2){return (input_1>=input_2?input_1:input_2);}
    inline float currentTime(){return _crt;}
    inline void set_currentTime(float new_crt){_crt=new_crt;}
    inline float dtime(){return _dt;}
    inline float totalTime(){return _tlt;}
    inline void settotalTime(float totaltime){_tlt = totaltime;}

private:
    MidPara* _mid;
    MidPara_UNS* _mid_uns;
    Matrix_data* _stagRes[3];
    Matrix_data* _NUstagRes[3];
    Point* _maxSpeed;
    Matrix_data* _Ux[3];
    Matrix_data* _Uy[3];
    Matrix_data* _du[3];
    Matrix_data* _df[3];
    Matrix_data* _du_bx[3];
    Matrix_data* _df_bx[3];
    Matrix_data* _Fx[3];
    Matrix_data* _Gy[3];
    Matrix_data* _halfStep[3];
    int _timestepType;
    float _crt;
    float  _dt;
    float _dt_after;
    float _tlt;
    float courant;
    float cellsize;

    friend class Process_post;
    friend class MidPara;
    friend class MidPara_UNS;
    friend class Term;
};
class MidPara
{
public:
    MidPara(){}
    ~MidPara(){}
    void update_SR(Phase& solid, Process_main& _main);
    Matrix_data Xmic(const Matrix_data& input_1,const Matrix_data& input_2);
    float Xmic(float input_1,float input_2);
    inline float min(float input_1,float input_2){return (input_1>input_2?input_2:input_1);}
    inline float sign(float input){return (input>0?1:-1);}
    inline float abs2(float input){return (input>0?input:-input);}
    friend class Process_main;
private:

};

class MidPara_UNS: public MidPara
{
public:
    MidPara_UNS(){}
    ~MidPara_UNS(){}
    void update_UNSR(Phase& solid, Process_main& _main);
    friend class Process_main;
};

#endif // PROCESS_MAIN_H
