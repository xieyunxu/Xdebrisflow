#include <string>
#include <fstream>
#include "phase.h"
Matrix_data::Matrix_data(const Matrix_data& a)
    :Size(a)
{
    _row=a._row;
    _col=a._col;
    _real_Row=a._real_Row;
    _real_Col=a._real_Col;
    _mat=new float*[_real_Row];
    for (int i=0;i<_real_Row;i++)
    {  _mat[i]=new float[_real_Col];}
    for (int i=0;i<_real_Row;i++)
    {
        for (int j=0;j<_real_Col;j++){
            _mat[i][j]=a._mat[i][j];}
    }
}
Matrix_data::Matrix_data(const Matrix_data& a,DifferenceType diff)
{
    _row=a._row;
    _col=a._col;
    _real_Row=a._real_Row;
    _real_Col=a._real_Col;
    _mat=new float*[_real_Row];
    for (int i=0;i<_real_Row;i++)
    {  _mat[i]=new float[_real_Col];}
    switch (diff)
    {
    case Forward_x:
    {
        for (int i=1;i<_real_Row-1;i++)
        {
            for (int j=1;j<_real_Col-1;j++)
            {
                _mat[i][j]=a._mat[i+1][j];
            }
        }
        break;
    }
    case Forward_y:
    {
        for (int i=1;i<_real_Row-1;i++)
        {
            for (int j=1;j<_real_Col-1;j++)
            {
                _mat[i][j]=a._mat[i][j+1];
            }
        }
        break;
    }
    case Backward_x:
    {
        for (int i=1;i<_real_Row-1;i++)
        {
            for (int j=1;j<_real_Col-1;j++)
            {
                _mat[i][j]=a._mat[i-1][j];
            }
        }
        break;
    }
    case Backward_y:
    {
        for (int i=1;i<_real_Row-1;i++)
        {
            for (int j=1;j<_real_Col-1;j++)
            {
                _mat[i][j]=a._mat[i][j-1];
            }
        }
        break;
    }
    }
}
Matrix_data& Matrix_data::operator=(const Matrix_data& right)
{
    _row=right._row;
    _col=right._col;
    _real_Row=right._real_Row;
    _real_Col=right._real_Col;
     std::cout<<*this<<" "<<right<<std::endl;
    // std::cout<<this->_row<<" "<<this->_col<<std::endl;
    //std::cout<<this->getRow()<<std::endl;
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {this->_mat[i][j]=right._mat[i][j];}
    }
    // std::cout<<__FUNCTION__<<" over"<<std::endl;
    return *this;
}
Matrix_data& Matrix_data::operator+(const Matrix_data& right)
{
    // std::cout<<right._row<<" "<<right._col<<" right"<<std::endl;
    //  std::cout<<this->_row<<" "<<this->_col<<std::endl;
    std::cout<<__FUNCTION__<<std::endl;
    Matrix_data* _re=new Matrix_data;
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {*_re[i][j]=this->_mat[i][j]+right._mat[i][j];}
    }
    std::cout<<__FUNCTION__<<" over"<<std::endl;
    return *_re;
}
Matrix_data& Matrix_data::operator-(const Matrix_data& right)
{
        Matrix_data* _re=new Matrix_data;
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {*_re[i][j]=this->_mat[i][j]-right._mat[i][j];}
    }
    return *_re;
}
Matrix_data& Matrix_data::operator*(const Matrix_data& right)
{
        Matrix_data* _re=new Matrix_data;
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {*_re[i][j]=this->_mat[i][j]*right._mat[i][j];}
    }
    return *_re;
}
Matrix_data& operator*(float n,const Matrix_data& right)
{
    Matrix_data* _re=new Matrix_data;
    for (int i=0;i<right._row;i++)
    {
        for (int j=0;j<right._col;j++)
        {*_re[i][j]=n*right._mat[i][j];}
    }
    return *_re;
}
Matrix_data& Matrix_data::operator/(const Matrix_data& right)
{
        Matrix_data* _re=new Matrix_data;
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {*_re[i][j]=this->_mat[i][j]/right._mat[i][j];}
    }
    return *_re;
}
Matrix_data& Matrix_data::operator+=(const Matrix_data& right)
{
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {_mat[i][j]+=right._mat[i][j];}
    }
    return *this;
}
Matrix_data& Matrix_data::operator-=(const Matrix_data& right)
{
    for (int i=1;i<_real_Row-1;i++)
    {
        for (int j=1;j<_real_Col-1;j++)
        {_mat[i][j]-=right._mat[i][j];}
    }
    return *this;
}
float* Matrix_data::operator[](int n) const
{
    return _mat[n];
}




