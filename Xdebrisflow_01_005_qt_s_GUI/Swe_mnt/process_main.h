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
    inline double abs2(double input){return (input>0?input:-input);}
    void count_time();
    inline Point* get_Maxspeed(){return _maxSpeed;}
    inline double max(double input_1,double input_2){return (input_1>=input_2?input_1:input_2);}
    inline double currentTime(){return _crt;}
    inline void set_currentTime(double new_crt){_crt=new_crt;}
    inline double dtime(){return _dt;}
    inline double totalTime(){return _tlt;}
    inline void settotalTime(double totaltime){_tlt = totaltime;}

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
    double _crt;
    double  _dt;
    double _dt_after;
    double _tlt;
    double courant;
    double cellsize;
    bool _warn_Flag=false;

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
    double Xmic(double input_1,double input_2);
    inline double min(double input_1,double input_2){return (input_1>input_2?input_2:input_1);}
    inline double sign(double input){return (input>0?1:-1);}
    inline double abs2(double input){return (input>0?input:-input);}
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
