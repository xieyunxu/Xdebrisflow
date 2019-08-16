#ifndef TERM_H
#define TERM_H
#include "phase.h"
class Process_main;
class Term
{
public:
    Term(float miu_1=Data::instance()->get_Miu1()
            ,float miu_2=Data::instance()->get_Miu2());
    ~Term();
    void update_SourceTerm(const Phase& solid,const Process_main& main);
    void update_Direction(const Phase& solid);
    void init_FrictionTerm(const Phase& solid);
    void init_GravityTerm(const Phase& solid);
    void init_EntrainmentTerm(const Phase& solid);
    inline float get_Miu1(){return miu_quasi;}
    inline float get_Miu2(){return miu_shear;}
    inline void set_Miu1(float new_miu1){miu_quasi=new_miu1;}
    inline void set_Miu2(float new_miu2){miu_shear=new_miu2;}

private:
    float miu_quasi;
    float miu_shear;
    Matrix_data* _sourceTerm[3];
    Matrix_data* _gravityTerm[2];
    Matrix_data* _frictionTerm[2];
    Matrix_data* _entrainmentTerm;
    Matrix_data* _direction[2];
    Matrix_data* _speed;
    FM::FrictionModel _frictionModel;

    friend class Process_main;
};

#endif // TERM_H
