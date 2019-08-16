#ifndef PROCESS_PRE_H
#define PROCESS_PRE_H
#include <string>
#include "process_main.h"
class Phase;
class Process_pre
{
public:
    Process_pre(Phase& solid);
    void Read_terrain_sourceFile(Phase& solid);
    void Read_parasFile();
    void space_Arrangment();
    void space_Free();
    void Read_sourceFile();
    void Read_erosionFile();
    void setmatrixInfo();
private:
    std::string _terrain_Name;
    std::string _source_Name;
    std::string _erosion_Name;
    float _elevation_Read;
    int _matrix_col_Read;
    int _matrix_row_Read;
    float _xcorner_Read;
    float _ycorner_Read;
    float _cellsize_Read;
    int _nodata_Value;
    SM::importsource_ModelType source_Type;
    int source_Shape;
};
#endif // PROCESS_PRE_H
