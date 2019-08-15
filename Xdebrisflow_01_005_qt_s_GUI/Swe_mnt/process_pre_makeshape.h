#ifndef PROCESS_PRE_MAKESHAPE_H
#define PROCESS_PRE_MAKESHAPE_H
#include <QPoint>
#include <ostream>
class Phase;
class Point
{
public:
    Point(){_x=0;_y=0;}
    Point(double i, double j):_x(i),_y(j){}
    ~Point(){}
    Point(const Point& p){_x=p._x;_y=p._y;}
    Point getSize(){return Point(_x,_y);}

    Point operator+(Point& right)
    {
        Point re;
        re._x=this->_x+right._x;
        re._y=this->_y+right._y;
        return re;
    }
    inline double get_pointX(){return _x;}
    inline double get_pointY(){return _y;}
    inline double distance(Point input_1,Point input_2);
    inline void set_pointX(double new_x){_x=new_x;}
    inline void set_pointY(double new_y){_y=new_y;}
    friend std::ostream& operator<<(std::ostream& out,const Point& input);
private:
    double _x;
    double _y;
    friend class Process_main;
};
class Rectangle:public Point
{
public:
    Rectangle(Point input_cor,double len1=0,double len2=0)
        :tl_corner(input_cor),len_vert(len1),len_hori(len2)
    {
        tl_corner.set_pointX(input_cor.get_pointX()+1);
        tl_corner.set_pointY(input_cor.get_pointY()+1);
    }
    void insideOrnot(Phase& solid);
private:
    Point tl_corner;
    double len_vert;
    double len_hori;
};
class Circle:public Point
{
public:
    Circle(Point input_center,double input_radius)
        :center(input_center),len(input_radius)
    {
        center.set_pointX(input_center.get_pointX()+1);
        center.set_pointY(input_center.get_pointY()+1);
    }
    void insideOrnot(Phase& solid);
    inline Point get_Center(){return center;}
private:
    Point center;
    double len;
};
#endif // PROCESS_PRE_MAKESHAPE_H
