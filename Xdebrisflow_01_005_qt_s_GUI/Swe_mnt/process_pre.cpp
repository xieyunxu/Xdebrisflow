#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "process_pre.h"
#include "process_pre_makeshape.h"
#include "phase.h"
#include "data.h"
Process_pre::Process_pre(Phase& solid)
    :     _terrain_Name("z"),_source_Name("h"),
      _matrix_col_Read(0), _matrix_row_Read(0),
      _xcorner_Read(0), _ycorner_Read(0),
      _cellsize_Read(0),_nodata_Value(-9999),
      source_Type(Data::instance()->get_SourceMode()),
      source_Shape(Data::instance()->get_SourceShape())
{Read_terrain_sourceFile(solid);}
void Process_pre::Read_terrain_sourceFile(Phase& solid)
{
    using namespace std;

    std::ifstream Terrain_File;
    std::string ch=Data::instance()->get_char_System();
    Terrain_File.open(Data::instance()->openDir()+ch+"Input"+ch+_terrain_Name+".txt");
    if(!Terrain_File)
    {std::cout<<"Terrainfile is not existed, please check"<<std::endl;
        exit(-1);}
    else
    {
        std::string keywords;
        Terrain_File>>keywords>>_matrix_col_Read;
        Terrain_File>>keywords>>_matrix_row_Read;
        Terrain_File>>keywords>>_xcorner_Read;
        Terrain_File>>keywords>>_ycorner_Read;
        Terrain_File>>keywords>>_cellsize_Read;
        Terrain_File>>keywords>>_nodata_Value;
        setmatrixInfo();
        /********************************************/
        for (int i=1; i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1; j<solid.get_PhaseSize().getCol_Size()-1; j++)
            {
                Terrain_File>>_elevation_Read;
                if(ceil(_elevation_Read) == _nodata_Value){(*solid._Z)[i][j] =0;}
                else {(*solid._Z)[i][j]=_elevation_Read;}
            }
        }
    }
    Terrain_File.close();
    switch (source_Type)
    {
    case SM::import_Txt:
    {
        std::ifstream Source_File;
        double eps=Data::instance()->get_Eps();
        Source_File.open(Data::instance()->openDir()+ch+"Input"+ch+_source_Name+".txt");
        if(!Source_File)
        {std::cout<<"SourceFile is not existed, please check"<<std::endl;
            exit(-1);}
        else
        {
            std::string keywords;
            Source_File>>keywords>>_matrix_col_Read;
            Source_File>>keywords>>_matrix_row_Read;
            Source_File>>keywords>>_xcorner_Read;
            Source_File>>keywords>>_ycorner_Read;
            Source_File>>keywords>>_cellsize_Read;
            Source_File>>keywords>>_nodata_Value;
            for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
            {
                for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
                {
                    Source_File>>_elevation_Read;
                    if(ceil(_elevation_Read) == _nodata_Value||ceil(_elevation_Read) == 0)
                    {(*solid._U[0])[i][j]=eps;}
                    else{(*solid._U[0])[i][j]=_elevation_Read;}
                }
            }
        }
        Source_File.close();
        break;
    }
    case SM::import_Selfdefined:
    {
        switch (source_Shape){
        case 3:{Rectangle rec
                    (Point(Data::instance()->get_SourcePoint().get_pointX()
                           ,Data::instance()->get_SourcePoint().get_pointY())
                     ,Data::instance()->get_SourceLen().get_pointX()
                     ,Data::instance()->get_SourceLen().get_pointY());
            rec.insideOrnot(solid);
            std::cout<<"case 3:rec"<<std::endl;
            break;}
        case 4:{Circle circle
                    (Point(Data::instance()->get_SourcePoint().get_pointX()
                           ,Data::instance()->get_SourcePoint().get_pointY())
                     ,Data::instance()->get_SourceLen().get_pointX());
            circle.insideOrnot(solid);
            std::cout<<"case 3:cir"<<std::endl;
            break;}
        default:{std::cout<<source_Shape<<" dont right"<<std::endl;break;}}
    }
    }
}
    void Process_pre::setmatrixInfo()
    {
        Data::instance()->set_Column(_matrix_col_Read);
        Data::instance()->set_Row(_matrix_row_Read);
        Data::instance()->set_xCorner(_xcorner_Read);
        Data::instance()->set_yCorner(_ycorner_Read);
        Data::instance()->set_Dx(_cellsize_Read);
        Data::instance()->set_Dy(_cellsize_Read);
        Data::instance()->set_cellSize(_cellsize_Read);
        if(static_cast<int>(ceil(Data::instance()->get_cellSize())) == 0
                ||static_cast<int>(ceil(Data::instance()->get_Col())) == 0
                ||static_cast<int>(ceil(Data::instance()->get_Row())) == 0)
        {std::cout<<"Reading matirx info error(Process_pre)"<<std::endl;
            system("pause");}
    }
