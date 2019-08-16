#include "Swe_mnt/process_pre_makeshape.h"
#include <math.h>
#include "phase.h"
#include "data.h"
std::ostream& operator<<(std::ostream& out,const Point& input)
{
    out<<"point("<<input._x<<" , "<<input._y<<") ";
    return out;
}
float Point::distance(Point input_1,Point input_2)
{return sqrt((input_1._x-input_2._x)*(input_1._x-input_2._x)
             +(input_1._y-input_2._y)*(input_1._y-input_2._y));}
void Rectangle::insideOrnot(Phase &solid)
{
    float eps=Data::instance()->get_Eps();
    float source_Dep=Data::instance()->get_SourceDepth();
    std::cout<<tl_corner.get_pointX()<<" "<<
               tl_corner.get_pointX()+len_hori<<" "
            <<tl_corner.get_pointY()<<" "<<tl_corner.get_pointY()+len_vert
           <<" "<<source_Dep<<std::endl;
    for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
    {
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {

            if(i>=tl_corner.get_pointX()
             &&i<=tl_corner.get_pointX()+len_hori
             &&j>=tl_corner.get_pointY()
             &&j<=tl_corner.get_pointY()+len_vert)
            {(*solid._U[0])[i][j]=source_Dep;
            std::cout<<" source ";}
            else{(*solid._U[0])[i][j]=eps;}
        }
    }
}
void Circle::insideOrnot(Phase &solid)
{
    {
        float eps=Data::instance()->get_Eps();
        float source_Dep=Data::instance()->get_SourceDepth();
        for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {
                if(distance(Point(i,j),center)<=len)
                {(*solid._U[0])[i][j]=source_Dep;}
                else{(*solid._U[0])[i][j]=eps;}
            }
        }
    }
}
