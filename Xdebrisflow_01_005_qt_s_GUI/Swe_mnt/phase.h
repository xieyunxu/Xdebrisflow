#ifndef PHASE_H
#define PHASE_H
#include <iostream>
#include <cassert>
#include "data.h"
class Size
{
public:
    Size(){_row=0;_col=0;}
    Size(int i, int j):_row(i),_col(j){}
    ~Size(){}
    Size(const Size& p){_row=p._row;_col=p._col;}
    inline Size getSize(){return Size(_row,_col);}
    inline int getRow_Size(){return _row;}
    inline int getCol_Size(){return _col;}
protected:
    int _row;
    int _col;
};
enum DifferenceType
{
    Forward_x,
    Forward_y,
    Backward_x,
    Backward_y
};
class Matrix_data:public Size
{
public:
    Matrix_data(double defaults=0)
        :Size(Data::instance()->get_Row(),Data::instance()->get_Col())
    {
        _real_Row=_row+2;
        _real_Col=_col+2;
        _mat=new double*[_real_Row];
        for (int i=0;i<_real_Row;i++){  _mat[i]=new double[_real_Col];
            for (int j=0;j<_real_Col;j++)
            {_mat[i][j]=defaults;}}}
    ~Matrix_data(){delete []_mat;}
    Matrix_data(const Matrix_data& a);
    Matrix_data(const Matrix_data& a,DifferenceType diff);
    inline int getRow() const{return _row;}
    inline int getCol() const{return _col;}
    inline int get_RealRow() const{return _real_Row;}
    inline int get_RealCol() const{return _real_Col;}
    inline Size getSize() const{return Size(_row,_col);}
    inline Size get_RealSize() const{return Size(_real_Row,_real_Col);}
    Matrix_data& operator=(const Matrix_data& right);
    Matrix_data& operator+(const Matrix_data& right);
    Matrix_data& operator-(const Matrix_data& right);
    Matrix_data& operator*(const Matrix_data& right);
    friend Matrix_data& operator*(double n,const Matrix_data& right);
    Matrix_data& operator/(const Matrix_data& right);
    Matrix_data& operator()(const Matrix_data& right);
    Matrix_data& operator+=(const Matrix_data& right);
    Matrix_data& operator-=(const Matrix_data& right);
    Matrix_data& abs2(const Matrix_data& input);
    Matrix_data& sqrt2(const Matrix_data& input);
    double* operator[](int n) const;
    friend std::ostream& operator<<(std::ostream& out,const Matrix_data& ah)
    {out<<"("<<ah.getRow()<<"+2"<<","<<ah.getCol()<<"+2"<<")";
        return out;}
    friend class Process_main;
    friend class MidPara;
    friend class Swe_movemnt;
private:
    double **_mat;
    int _real_Row;
    int _real_Col;
};
class Phase
{
public:
    Phase(){
        _U[0]=new Matrix_data(Data::instance()->get_Eps());
        _U[1]=new Matrix_data;
        _U[2]=new Matrix_data;
        for (int i=0;i<3;i++)
        {
            _F[i]=new Matrix_data;
            _G[i]=new Matrix_data;
        }
        _Z=new Matrix_data;
    }
    ~Phase(){
        for (int i=0;i<3;i++)
        {
            delete _U[i];
            delete _F[i];
            delete _G[i];
        }
        delete _Z;
    }
    inline Size get_PhaseSize(){return _Z->get_RealSize();}
    inline Size get_PhaseSize() const{return _Z->get_RealSize();}
private:
    Matrix_data* _U[3];
    Matrix_data* _F[3];
    Matrix_data* _G[3];
    Matrix_data* _Z;
    friend class Process_pre;
    friend class Process_main;
    friend class Process_post;
    friend class MidPara;
    friend class Swe_movemnt;
    friend class Term;
    friend class Rectangle;
    friend class Circle;
};
#endif // PHASE_H
