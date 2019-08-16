#include <math.h>
#include "Swe_mnt/process_main.h"
#include "term.h"
#include "phase.h"
#include "data.h"
Term::Term(float miu_1,float miu_2)
    :miu_quasi(miu_1),miu_shear(miu_2)
    ,_frictionModel(Data::instance()->get_FrictionModel())
{

    for (int i=0;i<2;i++){_direction[i]=new Matrix_data;
        _gravityTerm[i]=new Matrix_data;
        _frictionTerm[i]=new Matrix_data;}
    for (int i=0;i<3;i++){_sourceTerm[i]=new Matrix_data;}
    _entrainmentTerm=new Matrix_data;
    _speed=new Matrix_data;
}
Term::~Term()
{
    for (int i=0;i<2;i++){delete  _direction[i];
        delete _gravityTerm[i];
        delete _frictionTerm[i];}
    for (int i=0;i<3;i++){delete  _sourceTerm[i];}
    delete _entrainmentTerm;
    delete _speed;
}
void Term::update_SourceTerm(const Phase& solid,const Process_main& main)
{
    update_Direction(solid);
    init_GravityTerm(solid);
    init_FrictionTerm(solid);
    init_EntrainmentTerm(solid);
    for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {
            (*_sourceTerm[0])[i][j]=-(*_entrainmentTerm)[i][j];
            (*_sourceTerm[1])[i][j]=-(*_gravityTerm[0])[i][j]
                    -(*_frictionTerm[0])[i][j];
            float stop_Flux_x=(*solid._U[1])[i][j]/main._dt;
            float stop_Flux_y=(*solid._U[2])[i][j]/main._dt;
            if(abs((*_frictionTerm[0])[i][j])>=abs(stop_Flux_x))
            {(*_sourceTerm[1])[i][j]=-(*_gravityTerm[0])[i][j]-stop_Flux_x;}

            (*_sourceTerm[2])[i][j]=-(*_gravityTerm[1])[i][j]
                    -(*_frictionTerm[1])[i][j];
            if(abs((*_frictionTerm[1])[i][j])>=abs(stop_Flux_y))
            {(*_sourceTerm[2])[i][j]=-(*_gravityTerm[1])[i][j]-stop_Flux_y;}
        }
    }
}
void Term::init_GravityTerm(const Phase& solid)
{
    float cellsize=Data::instance()->get_cellSize();
    for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {
            (*_gravityTerm[0])[i][j]=9.8*(*solid._U[0])[i][j]
                    *((*solid._Z)[i+1][j]-(*solid._Z)[i-1][j])/(2*cellsize);
            if(i==1){
                (*_gravityTerm[0])[i][j]=9.8*(*solid._U[0])[i][j]
                        *((*solid._Z)[i+1][j]-(*solid._Z)[i][j])/(cellsize);}
            else if(i==solid.get_PhaseSize().getRow_Size()-1){
                (*_gravityTerm[0])[i][j]=9.8*(*solid._U[0])[i][j]
                        *((*solid._Z)[i][j]-(*solid._Z)[i-1][j])/(cellsize);}

            (*_gravityTerm[1])[i][j]=9.8*(*solid._U[0])[i][j]
                    *((*solid._Z)[i][j+1]-(*solid._Z)[i][j-1])/(2*cellsize);
            if(j==1){(*_gravityTerm[1])[i][j]=9.8*(*solid._U[0])[i][j]
                        *((*solid._Z)[i][j+1]-(*solid._Z)[i][j])/(cellsize);}
            else if(j==solid.get_PhaseSize().getCol_Size()-1){
                (*_gravityTerm[1])[i][j]=9.8*(*solid._U[0])[i][j]
                        *((*solid._Z)[i][j]-(*solid._Z)[i][j-1])/(cellsize);}
        }
    }
}
void Term::init_FrictionTerm(const Phase& solid)
{
    switch(_frictionModel)
    {
    case FM::Comlomb:
    {
        for (int k=0;k<2;k++)
        {
            for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
            {
                for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
                {
                    (*_frictionTerm[k])[i][j]=9.8*miu_quasi*(*solid._U[0])[i][j]*(*_direction[k])[i][j];
                }
            }
        }
        break;
    }
    case FM::Voellmy:
    {
        break;
    }
    case FM::Rhelogic:
    {
        for (int k=0;k<2;k++)
        {
            for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
            {
                for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
                {
                    (*_frictionTerm[k])[i][j]=9.8*(miu_quasi+
                                                   (miu_shear-miu_quasi)*(*_speed)[i][j]*Data::instance()->get_D50()
                                                   /(Data::instance()->get_I0()*pow((*solid._U[0])[i][j],1.5)*sqrt(Data::instance()->get_Cs()*9.8)
                                                   +(*_speed)[i][j]*Data::instance()->get_D50()))
                            *(*solid._U[0])[i][j]*(*_direction[k])[i][j];
                }
            }
        }
        break;
    }
    case FM::miu_V:
    {
        for (int k=0;k<2;k++)
        {
            for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
            {
                for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
                {
                    (*_frictionTerm[k])[i][j]=9.8*(miu_quasi+
                                                   (miu_shear-miu_quasi)
                                                   /(1+Data::instance()->get_Uw()/(*_speed)[i][j]))
                            *(*solid._U[0])[i][j]*(*_direction[k])[i][j];
                }
            }
        }
        break;
    }
    }
}
void Term::init_EntrainmentTerm(const Phase &solid)
{
    for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for(int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {
#if 0
            float coef =0.125;
            (*_entrainmentTerm)[i][j]=coef*(1)*(*_speed)[i][j]*pow(Data::instance()->get_D50(),-0.2)
                    /(*solid._U[0])[i][j];
#endif
            (*_entrainmentTerm)[i][j]=0;
        }
    }
}
void Term::update_Direction(const Phase& solid)
{
    float eps=Data::instance()->get_Eps();
    for (int k=0;k<2;k++)
    {
        for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {
                (*_direction[k])[i][j]=(*solid._U[k+1])[i][j]
                        /(sqrt((*solid._U[1])[i][j]*(*solid._U[1])[i][j]
                        +(*solid._U[2])[i][j]*(*solid._U[2])[i][j])+eps);
                (*_speed)[i][j]=sqrt((*solid._U[1])[i][j]*(*solid._U[1])[i][j]
                        +(*solid._U[2])[i][j]*(*solid._U[2])[i][j])/(*solid._U[0])[i][j];
            }
        }
    }
}
