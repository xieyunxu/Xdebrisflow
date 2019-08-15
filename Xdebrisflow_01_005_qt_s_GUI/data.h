#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <QSize>
#include <QPoint>
#include <vector>
#include <string>
#include "Swe_mnt/process_pre_makeshape.h"
#include "Swe_mnt/function.h"
namespace System{
enum SystemType{
    Lin=1,
    Win=2
};
}
namespace SS{
enum SystemStatus{
    StartStatus = 1,
    RuningStatus = 2,
    PauseStatus = 3,
    OverStatus = 4
};
}
namespace FM {
enum FrictionModel
{
    Comlomb=1,
    Voellmy=2,
    Rhelogic=3
};
}
namespace SM {
enum importsource_ModelType
{
    import_Txt=1,
    import_Selfdefined=2

};
}
namespace SS {
enum sourceShape
{
    rectangle=3,
    circle=4};
}
namespace TM {
enum TimeStepMode
{
    Variable_T=1,
    Constant_T=2
};
}
class Point;
class Data
{
private:
    Data();
    static Data* _data;
public:
    static Data* instance();
    static void release();

private:
    //SystemType
    System::SystemType _systemType;
    //GUI_Widgets
    QPoint _upperLeft= QPoint(150,200);
    QPoint _upperRight= QPoint(1200,200);

    QSize _log_widget_size= QSize(850,480);
    int _mainWindow_width= 1820;
    int _mainWindow_height= 980;
    QSize _mainWindow_size= QSize(1820,980);
    int _dialog_width= 1080;
    int _dialog_height= 720;
    QSize _dialog_size= QSize(1080, 720);
    QSize _progressBar_size= QSize(650,240);


    //Running status
    SS::SystemStatus _status;
    bool _guiEnable;
    //Matrix info
    int _col;
    int _row;
    double _cellSize;
    double _dx;
    double _dy;
    double _xCorner;
    double _yCorner;
    //Keyword_IO
    std::vector<std::string> _KeyWords;
    void init_KeyWord();
    SM::importsource_ModelType _sourceMode;
    SS::sourceShape _sourceShape;
    TM::TimeStepMode _timeTypeMode;
    double _sourceDepth;
    Point _sourcePoint;
    Point _sourceLen;
    //Constutitive model
    double _miu1;
    double _miu2;
    double _d50;
    double _I0;
    double _cs;
    FM::FrictionModel _frictionModel;
    //Time
    double _totalTime;
    //Scheme info
    double _eps;
    double _alfa;
    double _courant;
    /*Root File*/
    std::string _in_path;
    /*Animation*/
    double _intervalT;

public:
    //SystemType
    inline std::string get_char_System(){
        switch (_systemType){
        case System::Lin:{return "/";}
        case System::Win:{return "\\";}}}
    inline std::string get_OSType(){
        switch (_systemType){
        case System::Lin:{return "Linux";}
        case System::Win:{return "Windows";}}}
    inline void set_OSType(std::string sys){
        int new_sys;
        if(sys=="Linux"){new_sys=1;}
        else if (sys=="Windows"){new_sys=2;}
        else {new_sys=-1;}
        switch(new_sys){
        case 1:{_systemType=System::Lin;break;}
        case 2:{_systemType=System::Win;break;}}}
    //GUI_Widgets
    inline QPoint upperLeft_Position(){return _upperLeft;}
    inline QPoint upperRight_Position(){return _upperRight;}

    inline QSize log_WidgetSize(){return _log_widget_size;}
    inline int main_WidgetWidth(){return _mainWindow_width;}
    inline int main_WidgetHeight(){return _mainWindow_height;}
    inline QSize main_WidgetSize(){return _mainWindow_size;}
    inline int dial_WidgetWidth(){return _dialog_width;}
    inline int dial_WidgetHeight(){return _dialog_height;}
    inline QSize dial_WidgetSize(){return _dialog_size;}
    inline QSize progressBar_WidgetSize(){return _progressBar_size;}

    //Status
    inline SS::SystemStatus Status(){return _status;}
    inline void set_Status(SS::SystemStatus new_sta){_status = new_sta;}
    inline bool get_GUIStatus(){return _guiEnable;}
    inline void set_GUIStatus(bool new_sta){_guiEnable=new_sta;}
    //Keyword_IO
    inline std::vector<std::string>& get_KeyWord(){return _KeyWords;}
    inline SM::importsource_ModelType get_SourceMode(){return _sourceMode;}
    inline void set_SourceMode(int new_mode){
        switch (new_mode){
        case 1:{_sourceMode=SM::import_Txt;break;}
        case 2:{_sourceMode=SM::import_Selfdefined;break;}
        default:{break;}}}
    inline SS::sourceShape get_SourceShape(){return _sourceShape;}
    inline void set_SourceShape(std::string new_mode_string){
        int new_mode;
        if(new_mode_string=="Rectangle"
                ||new_mode_string=="rectangle"
                ||new_mode_string=="rec"
                ||new_mode_string=="Rec"){new_mode=3;}
        else if(new_mode_string=="circle"
                ||new_mode_string=="Circle"
                ||new_mode_string=="cir"
                ||new_mode_string=="Cir"){new_mode=4;}
        else{new_mode=-1;}
        switch (new_mode){
        case 3:{_sourceShape=SS::rectangle;break;}
        case 4:{_sourceShape=SS::circle;break;}
        case -1:{std::cout<<"SourceShape KW error"<<std::endl;exit(-1);}
        default:{break;}}}
    inline int get_TimeStepMode(){return _timeTypeMode;}
    inline void set_TimeStepMode(std::string new_mode){
        switch (FO::stringToInt(new_mode)){
        case 1:{_timeTypeMode=TM::Variable_T;break;}
        case 2:{_timeTypeMode=TM::Constant_T;break;}
        default:{break;}}}
    inline double get_SourceDepth(){return _sourceDepth;}
    inline void set_SourceDepth(double source__h){_sourceDepth=source__h;}
    inline Point get_SourcePoint(){return _sourcePoint;}
    inline void set_SourcePoint_X(int x){_sourcePoint.set_pointX(x);}
    inline void set_SourcePoint_Y(int y){_sourcePoint.set_pointY(y);}
    inline Point get_SourceLen(){return _sourceLen;}
    inline void set_SourceLen_X(int len_x){_sourceLen.set_pointX(len_x);}
    inline void set_SourceLen_Y(int len_y){_sourceLen.set_pointY(len_y);}
    //Matrix info
    inline void set_Dx(double new_dx){_dx = new_dx;}
    inline void set_Dy(double new_dy){_dy = new_dy;}
    inline void set_cellSize(double new_cellsize){_cellSize = new_cellsize;}
    inline void set_xCorner(double new_xcorner){_xCorner = new_xcorner;}
    inline void set_yCorner(double new_ycorner){_yCorner = new_ycorner;}
    inline void set_Column(int new_column){_col = new_column;}
    inline void set_Row(int new_row){_row = new_row;}
    inline double get_Dx(){return _dx;}
    inline double get_Dy(){return _dy;}
    inline double get_cellSize(){return _cellSize;}
    inline double get_xCorner(){return _xCorner;}
    inline double get_yCorner(){return _yCorner;}
    inline int get_Col()const{return _col;}
    inline int get_Row(){return _row;}
    //Constutitive models
    inline void set_Miu1(double new_miu1){_miu1=new_miu1;}
    inline void set_Miu2(double new_miu2){_miu2=new_miu2;}
    inline double get_Miu1(){return _miu1;}
    inline double get_Miu2(){return _miu2;}
    inline void set_D50(double new_d50){_d50=new_d50;}
    inline double get_D50(){return _d50;}
    inline double get_I0(){return _I0;}
    inline double get_Cs(){return _cs;}
    inline FM::FrictionModel get_FrictionModel(){return _frictionModel;}
    inline void set_FrictionModel(int new_model){
        switch (new_model) {
        case 1:{_frictionModel=FM::Comlomb;break;}
        case 2:{_frictionModel=FM::Voellmy;break;}
        case 3:{_frictionModel=FM::Rhelogic;break;}
        default:{break;}}}
    //Time
    inline double get_TotalTime(){return _totalTime;}
    inline void set_TotalTime(double new_tlt){_totalTime=new_tlt;}
    //Scheme info
    inline void set_Eps(double new_eps){_eps = new_eps;}
    inline double get_Eps(){return _eps;}
    inline double get_Alfa(){return _alfa;}
    inline double get_Courant(){return _courant;}
    /*Root File*/
    inline std::string openDir(){return _in_path;}
    inline void setOpenDir(std::string dir){_in_path = dir;}
    /*Animation*/
    inline double get_IntervalTime(){return _intervalT;}
    inline void set_IntervalTime(double new_intervalT){_intervalT = new_intervalT;}

};

#endif // DATA_H
