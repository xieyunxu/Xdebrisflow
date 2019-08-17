#include <math.h>
#include "Swe_mnt/process_pre_makeshape.h"
#include "process_main.h"
#include "phase.h"
#include "term.h"
#include "data.h"
Process_main::Process_main(QObject* parent)
    :QObject (parent),
      _timestepType(Data::instance()->get_TimeStepMode())
    ,_crt(0),_dt(0.001),_dt_after(Data::instance()->get_DtInitial())
    ,_tlt(Data::instance()->get_TotalTime())
    ,courant(Data::instance()->get_Courant())
    ,cellsize(Data::instance()->get_cellSize())
{
    _mid=new MidPara;
    _mid_uns=new MidPara_UNS;
    _maxSpeed=new Point;
    for (int i=0;i<3;i++)
    {

        _Ux[i]       =new Matrix_data;
        _Uy[i]       =new Matrix_data;
        _du[i]       =new Matrix_data;
        _df[i]       =new Matrix_data;
        _Fx[i]       =new Matrix_data;
        _Gy[i]       =new Matrix_data;
        _halfStep[i] =new Matrix_data;
        _stagRes[i]=new Matrix_data;
        _NUstagRes[i]=new Matrix_data;
    }
}
Process_main::~Process_main()
{
    delete _mid;
    delete _mid_uns;
    delete _maxSpeed;
    for (int i=0;i<3;i++)
    {
        delete  _Ux[i]       ;
        delete  _Uy[i]       ;
        delete  _du[i]       ;
        delete  _df[i]       ;
        delete  _Fx[i]       ;
        delete  _Gy[i]       ;
        delete  _halfStep[i] ;
        delete _stagRes[i];
        delete _NUstagRes[i];
    }
}
void Process_main::RunIteration(Phase& solid,Term& term)
{
    double eps=Data::instance()->get_Eps();
    for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {
            if((*solid._U[0])[i][j]<0)
            {(*solid._U[0])[i][j]=eps;_warn_Flag=true;}
            (*solid._F[0])[i][j]=(*solid._U[1])[i][j];
            (*solid._F[1])[i][j]=(*solid._U[1])[i][j] * (*solid._U[1])[i][j]/((*solid._U[0])[i][j]+eps)+9.8/2*(*solid._U[0])[i][j]*(*solid._U[0])[i][j];
            (*solid._F[2])[i][j]=(*solid._U[1])[i][j] * (*solid._U[2])[i][j]/((*solid._U[0])[i][j]+eps);
            (*solid._G[0])[i][j]=(*solid._U[2])[i][j];
            (*solid._G[1])[i][j]=(*solid._U[1])[i][j] * (*solid._U[2])[i][j]/((*solid._U[0])[i][j]+eps);
            (*solid._G[2])[i][j]=(*solid._U[2])[i][j] * (*solid._U[2])[i][j]/((*solid._U[0])[i][j]+eps)+9.8/2*(*solid._U[0])[i][j]*(*solid._U[0])[i][j];

        }

    }
    if(_warn_Flag){std::cout<<"Fatal Warning(h<0)!!!!"<<std::endl;_warn_Flag=false;}
    /*Scheme ENO(WENO)*/
#if 1
    this->maxSpeed(solid);
    _mid->update_SR(solid,*this);
    this->staggerResult(solid);
    _mid_uns->update_UNSR(solid,*this);
    term.update_SourceTerm(solid,*this);
    this->NUstaggerResult(solid,term);
#endif
    /*Scheme ENO(WENO)*/
    /*Scheme CLF(CF)*/
#if 0
    LaxWendroffResult(solid,term);
#endif
    /*Scheme CLF(CF)*/
}
void Process_main::LaxWendroffResult(Phase &solid, Term &term)
{
    double eps=Data::instance()->get_Eps();
    double cellsize=Data::instance()->get_cellSize();
    std::cout<<cellsize<<std::endl;
    for(int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for(int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {/*U(i+1,j+1/2)->F(i+1,j+1/2)*/
                (*_Uy[k])[i][j]=0.5*((*solid._U[k])[i+1][j+1]+(*solid._U[k])[i+1][j])
                        +0.25*(_dt/cellsize)*((*solid._G[k])[i+1][j+1]-(*solid._G[k])[i+1][j]);
                /*U(i+1/2,j+1)->G(i+1/2,j+1)*/
                (*_Ux[k])[i][j] =0.5*((*solid._U[k])[i+1][j+1]+(*solid._U[k])[i][j+1])
                        +0.25*(_dt/cellsize)*((*solid._F[k])[i+1][j+1]-(*solid._F[k])[i][j+1]);
            }
        }
    }
    for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for(int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {/*F(i+1,j+1/2) G(i+1/2,j+1)*/
            (*solid._F[0])[i][j]=(*_Uy[1])[i][j];
            (*solid._F[1])[i][j]=(*_Uy[1])[i][j] * (*_Uy[1])[i][j]/((*_Uy[0])[i][j]+eps)+9.8/2*(*_Uy[0])[i][j]*(*_Uy[0])[i][j];
            (*solid._F[2])[i][j]=(*_Uy[1])[i][j] * (*_Uy[2])[i][j]/((*_Uy[0])[i][j]+eps);
            (*solid._G[0])[i][j]=(*_Ux[2])[i][j];
            (*solid._G[1])[i][j]=(*_Ux[1])[i][j] * (*_Ux[2])[i][j]/((*_Ux[0])[i][j]+eps);
            (*solid._G[2])[i][j]=(*_Ux[2])[i][j] * (*_Ux[2])[i][j]/((*_Ux[0])[i][j]+eps)+9.8/2*(*_Ux[0])[i][j]*(*_Ux[0])[i][j];
        }
    }

    for(int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for(int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {/*U(i+1/2,j+1/2)t=n+1/2*/
                (*_stagRes[k])[i][j]=0.25*((*solid._U[k])[i][j]+(*solid._U[k])[i+1][j]+(*solid._U[k])[i][j+1]+(*solid._U[k])[i+1][j+1])
                        +0.5*(_dt/cellsize)*((*solid._F[k])[i][j]-(*solid._F[k])[i-1][j])
                        +0.5*(_dt/cellsize)*((*solid._G[k])[i][j]-(*solid._G[k])[i][j-1]);
            }
        }
    }
    for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for(int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {/*F(i+1/2,j+1/2) G(i+1/2,j+1/2)t=n+1/2*/
            (*solid._F[0])[i][j]=(*_stagRes[1])[i][j];
            (*solid._F[1])[i][j]=(*_stagRes[1])[i][j] * (*_stagRes[1])[i][j]/((*_stagRes[0])[i][j]+eps)+9.8/2*(*_stagRes[0])[i][j]*(*_stagRes[0])[i][j];
            (*solid._F[2])[i][j]=(*_stagRes[1])[i][j] * (*_stagRes[2])[i][j]/((*_stagRes[0])[i][j]+eps);
            (*solid._G[0])[i][j]=(*_stagRes[2])[i][j];
            (*solid._G[1])[i][j]=(*_stagRes[1])[i][j] * (*_stagRes[2])[i][j]/((*_stagRes[0])[i][j]+eps);
            (*solid._G[2])[i][j]=(*_stagRes[2])[i][j] * (*_stagRes[2])[i][j]/((*_stagRes[0])[i][j]+eps)+9.8/2*(*_stagRes[0])[i][j]*(*_stagRes[0])[i][j];
        }
    }
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {/*U(i,j)t=n+1*/
                (*_NUstagRes[k])[i][j]=(*solid._U[k])[i][j]
                        +0.5*(_dt/cellsize)*((*solid._F[k])[i][j]+(*solid._F[k])[i][j-1]-(*solid._F[k])[i-1][j]-(*solid._F[k])[i-1][j-1])
                        +0.5*(_dt/cellsize)*((*solid._G[k])[i][j]+(*solid._G[k])[i-1][j]-(*solid._G[k])[i][j-1]-(*solid._G[k])[i-1][j-1]);
            }
        }
    }

    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {
                (*solid._U[k])[i][j]=(*_NUstagRes[k])[i][j]
                +_dt*(*term._sourceTerm[k])[i][j];
            }
        }
    }
}
void Process_main::staggerResult(Phase& solid)
{
    for (int k=0;k<3;k++)
    {
        double dx=Data::instance()->get_Dx();
        double dy=Data::instance()->get_Dy();
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {

                (*_stagRes[k])[i][j]=((*solid._U[k])[i][j]+(*solid._U[k])[i+1][j]+(*solid._U[k])[i][j+1]+(*solid._U[k])[i+1][j+1])/4
                        +(((*_Ux[k])[i][j]-(*_Ux[k])[i+1][j])+((*_Ux[k])[i][j+1]-(*_Ux[k])[i+1][j+1])
                        + ((*_Uy[k])[i][j]-(*_Uy[k])[i][j+1])+((*_Uy[k])[i+1][j]-(*_Uy[k])[i+1][j+1]))/16
                        -_dt/(2*dx)*((*solid._F[k])[i+1][j]-(*solid._F[k])[i][j]+(*solid._F[k])[i+1][j+1]-(*solid._F[k])[i][j+1])
                        -_dt/(2*dy)*((*solid._G[k])[i][j+1]-(*solid._G[k])[i][j]+(*solid._G[k])[i+1][j+1]-(*solid._G[k])[i+1][j]);
            }
        }
    }
}
void Process_main::NUstaggerResult(Phase& solid,Term& term)
{
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {

                (*_NUstagRes[k])[i][j]=((*_stagRes[k])[i][j]+(*_stagRes[k])[i-1][j]+(*_stagRes[k])[i][j-1]+(*_stagRes[k])[i-1][j-1])/4
                        -((*_Ux[k])[i][j-1]-(*_Ux[k])[i-1][j-1]+(*_Ux[k])[i][j]-(*_Ux[k])[i-1][j]
                        +(*_Fx[k])[i-1][j]-(*_Fx[k])[i-1][j-1]+(*_Fx[k])[i][j]-(*_Fx[k])[i][j-1])/16;
            }
        }
    }
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {

                (*solid._U[k])[i][j]=(*_NUstagRes[k])[i][j]
                        +_dt*(*term._sourceTerm[k])[i][j];
            }
        }
    }
}
Matrix_data& Matrix_data::abs2(const Matrix_data& input)
{
    for (int i=0;i<input.getRow();i++)
    {
        for (int j=0;j<input.getCol();j++)
        {_mat[i][j]=input._mat[i][j]>0?input._mat[i][j]:-input._mat[i][j];}
    }
    return *this;
}

Matrix_data& Matrix_data::sqrt2(const Matrix_data& input)
{
    for (int i=0;i<input.getRow();i++)
    {
        for (int j=0;j<input.getCol();j++)
        {_mat[i][j]=sqrt(input._mat[i][j]);}
    }
    return *this;
}
void Process_main::maxSpeed(const Phase& solid)
{
    *_maxSpeed=Point(0,0);
    double input_x;
    double input_y;
    for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {

            input_x=abs2((*solid._U[1])[i][j]/(*solid._U[0])[i][j])+sqrt(9.8*(*solid._U[0])[i][j]);
            input_y=abs2((*solid._U[2])[i][j]/(*solid._U[0])[i][j])+sqrt(9.8*(*solid._U[0])[i][j]);
            // std::cout<<input_x<<" ";
            _maxSpeed->_x=(_maxSpeed->_x>=input_x?_maxSpeed->_x:input_x);
            _maxSpeed->_y=(_maxSpeed->_y>=input_y?_maxSpeed->_y:input_y);
        }
    }
}
void Process_main::count_time()
{
    _crt+=_dt;
    double maxVelo=max(_maxSpeed->_x,_maxSpeed->_y);
    if (_timestepType == 1){_dt= courant*cellsize/maxVelo;}
    else if(_timestepType == 2){_dt=_dt_after;}
    if(_dt+_crt>ceil(_crt)&&_crt!=ceil(_crt))
    {_dt=ceil(_crt)-_crt;}
    std::cout<<" crt = "<<_crt<<"   dt = "
    <<_dt<<" MaxSpeed "<<maxVelo<<std::endl;
}
void MidPara::update_SR(Phase& solid, Process_main& _main)
{
    for (int k=0;k<3;k++)
    {
        for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {
                (*_main._du[k])[i][j]=(*solid._U[k])[i+1][j]-(*solid._U[k])[i][j];
                (*_main._df[k])[i][j]=(*solid._F[k])[i+1][j]-(*solid._F[k])[i][j];
                //正确写法(*solid._U[k])[i][j];
                //正确写法(*_main._du[k])[i][j];
            }
        }
    }
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {

                (*_main._Ux[k])[i][j]=
                        Xmic((*_main._du[k])[i-1][j],(*_main._du[k])[i][j]);
                (*_main._Fx[k])[i][j]=
                        Xmic((*_main._df[k])[i-1][j],(*_main._df[k])[i][j]);
            }
        }
    }
    for (int k=0;k<3;k++)
    {
        for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {
                (*_main._du[k])[i][j]=(*solid._U[k])[i][j+1]-(*solid._U[k])[i][j];
                (*_main._df[k])[i][j]=(*solid._F[k])[i][j+1]-(*solid._F[k])[i][j];
            }
        }
    }
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {

                (*_main._Uy[k])[i][j]=
                        Xmic((*_main._du[k])[i][j-1],(*_main._du[k])[i][j]);
                (*_main._Gy[k])[i][j]=
                        Xmic((*_main._df[k])[i][j-1],(*_main._df[k])[i][j]);
            }
        }
    }
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {
                (*_main._halfStep[k])[i][j]=(*solid._U[k])[i][j]
                        -_main._dt/(2*Data::instance()->get_Dx())*(*_main._Fx[k])[i][j]
                        -_main._dt/(2*Data::instance()->get_Dy())*(*_main._Gy[k])[i][j];
            }
        }
    }
    for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {
            (*solid._F[0])[i][j]=(*_main._halfStep[1])[i][j];
            (*solid._F[1])[i][j]=(*_main._halfStep[1])[i][j] * (*_main._halfStep[1])[i][j]/(*_main._halfStep[0])[i][j]+(9.8/2)* (*_main._halfStep[0])[i][j]* (*_main._halfStep[0])[i][j];
            (*solid._F[2])[i][j]=(*_main._halfStep[1])[i][j] * (*_main._halfStep[2])[i][j]/(*_main._halfStep[0])[i][j];
            (*solid._G[0])[i][j]=(*_main._halfStep[2])[i][j];
            (*solid._G[1])[i][j]=(*_main._halfStep[1])[i][j] * (*_main._halfStep[2])[i][j]/(*_main._halfStep[0])[i][j];
            (*solid._G[2])[i][j]=(*_main._halfStep[2])[i][j] * (*_main._halfStep[2])[i][j]/(*_main._halfStep[0])[i][j]+(9.8/2)* (*_main._halfStep[0])[i][j]* (*_main._halfStep[0])[i][j];
        }
    }
}
Matrix_data MidPara::Xmic(const Matrix_data& input_1,const Matrix_data& input_2)
{
    Matrix_data re;
    double alfa=Data::instance()->get_Alfa();
    for (int i=0;i<re.getRow();i++)
    {
        for (int j=0;j<re.getCol();j++)
        {
            double mid_1=alfa/2*(sign(input_1._mat[i][j])+sign(input_2._mat[i][j]))
                    *min(abs2(input_1._mat[i][j]),abs2(input_2._mat[i][j]));
            double mid_2=(input_1._mat[i][j]+input_2._mat[i][j])/2;
            re._mat[i][j]=0.5*(sign(mid_1)+sign(mid_2))*min(abs2(mid_1),abs2(mid_2));
        }
    }
    return re;
}
double MidPara::Xmic(double input_1,double input_2)
{
    double alfa=Data::instance()->get_Alfa();
    double mid_1=alfa/2*(sign(input_1)+sign(input_2))
            *min(abs2(input_1),abs2(input_2));
    double mid_2=(input_1+input_2)/2;
    return (0.5*(sign(mid_1)+sign(mid_2))*min(abs2(mid_1),abs2(mid_2)));
}
void MidPara_UNS::update_UNSR(Phase& solid, Process_main& _main)
{
    for (int k=0;k<3;k++)
    {
        for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {


                (*_main._du[k])[i][j]=(*_main._stagRes[k])[i+1][j]-(*_main._stagRes[k])[i][j];
                (*_main._df[k])[i][j]=(*_main._stagRes[k])[i][j+1]-(*_main._stagRes[k])[i][j];
                //正确写法(*solid._U[k])[i][j];
                //正确写法(*_main._du[k])[i][j];
            }
            //std::cout<<std::endl;
        }

    }
    for (int k=0;k<3;k++)
    {
        for(int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {

                (*_main._Ux[k])[i][j]=
                        Xmic((*_main._du[k])[i-1][j],(*_main._du[k])[i][j]);
                (*_main._Fx[k])[i][j]=
                        Xmic((*_main._df[k])[i][j-1],(*_main._df[k])[i][j]);
            }
        }

    }
}

