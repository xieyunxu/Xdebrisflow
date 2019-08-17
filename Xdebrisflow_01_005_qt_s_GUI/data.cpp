#include <math.h>
#include <QSize>
#include "data.h"
Data* Data::_data = nullptr;
Data::Data()
    : _systemType(System::Lin),
      _status(SS::StartStatus),_guiEnable(true),
      _col(20),_row(20),
      _cellSize(0),_dx(_cellSize),_dy(_cellSize),
      _xCorner(0),_yCorner(0),
      _sourceMode(SM::import_Txt),_sourceShape(SS::rectangle),_timeTypeMode(TM::Variable_T),
      _sourceDepth(pow(10,-6)),_sourcePoint(Point(0,0)),_sourceLen(Point(0,0)),
      _miu1(0.25),_miu2(0.3),_turbulence(500), _d50(0.01),_I0(0.3),_cs(0.6),_uw(2),
      _frictionModel(FM::Comlomb),
      _totalTime(50),_dt(0.01),
      _eps(pow(10,-6)),_alfa(1.1),
      _intervalT(10)
{
    init_KeyWord();
    _courant=1/(2*_alfa)*(sqrt(4+4*_alfa-_alfa*_alfa)-2-_eps);
#if 0
    _in_path="/home/yancys/Qt/Examples/Yigong_landslide";
#endif

//    _in_path="D:\\QT\\Documents\\Yigong_landslide\\";
    _in_path="D:\\QT\\QTcode\\Examples\\Yigong_landslide\\";


}

Data* Data::instance()
{
    if(_data == nullptr)
    {
        _data = new Data;
    }
    return _data;
}

void Data::release()
{
    if(_data != nullptr)
    {
        delete _data;
        _data = nullptr;
    }
}
void Data::init_KeyWord()
{
    const int size_keyword=7;
    std::string keywords[size_keyword]{
        "System"
        ,"GUI"
        ,"Tlt"
        ,"Record"
        ,"TimeStep"
        ,"SourceMode"
        ,"Friction"
    };
    for (int i=0;i<size_keyword;i++){_KeyWords.push_back(keywords[i]);}
}
