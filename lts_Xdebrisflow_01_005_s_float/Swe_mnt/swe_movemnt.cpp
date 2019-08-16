#include <iostream>
#include <fstream>
#include <vector>
#include "swe_movemnt.h"
#include "process_pre.h"
#include "process_main.h"
#include "process_post.h"
#include "function.h"
#include "phase.h"
#include "data.h"
#include "term.h"
Swe_movemnt::Swe_movemnt(QObject* parent)
    :QObject (parent)
{
    init_SWEmnt();
}
Swe_movemnt::~Swe_movemnt()
{
    delete _solid;
    delete _term;
    delete _pre;
    delete _main;
    delete _post;
}
void Swe_movemnt::init_SWEmnt()
{
    preChecksize();
    preCheckinputPara();
    _solid = new Phase;
    _term = new Term;
    _pre = new Process_pre(*_solid);
    _main = new Process_main;
    _post = new Process_post;
    _post->make_AnimationFile(*_solid,*_main);
    Data::instance()->set_Status(SS::RuningStatus);
    connect(_post,SIGNAL(getCurrtimeSig(float)),this,SIGNAL(getCurrtimeSig(float)));
    std::cout<<"Initiation Finish"<<std::endl;
}
void Swe_movemnt::running_SWEmnt()
{
    if(_main->currentTime()!=0)
    {init_SWEmnt();}
    while (_main->currentTime()<_main->totalTime()
           &&Data::instance()->Status()==SS::RuningStatus)
    {
        _main->RunIteration(*_solid,*_term);
        _main->count_time();
        _post->make_AnimationFile(*_solid,*_main);
    }

    std::cout<<"Simulation Finish"<<std::endl;
    emit sweMntfinishSig();
}
void Swe_movemnt::preChecksize()
{
    std::ifstream pre_Read;
    std::string c=Data::instance()->get_char_System();
    std::string in_path=Data::instance()->openDir()+c+"Input"+c+"z"+".txt";
    //std::cout<<in_path;
    pre_Read.open(in_path);
    if(!pre_Read){std::cout<<"Pre_readSize error, the input folder is not exist, please check"<<std::endl;exit(-1);}
    else
    {
        std::string keywords;
        int _matrix_col_Read;
        int _matrix_row_Read;
        pre_Read>>keywords>>_matrix_col_Read;
        pre_Read>>keywords>>_matrix_row_Read;
        Data::instance()->set_Column(_matrix_col_Read);
        Data::instance()->set_Row(_matrix_row_Read);
    }
}
void Swe_movemnt::preCheckinputPara()
{
    std::ifstream input_Para;
    std::string ch=Data::instance()->get_char_System();
    std::string path_InputPara=(Data::instance()->openDir()+ch+"Input"+ch+"Input"+".txt");
    std::cout<<path_InputPara;
    input_Para.open(path_InputPara);
    if(!input_Para){std::cout<<"Pre_readInputPara error, Input file not found"<<std::endl;exit(-1);}
    else {
        char buffer[100]=" ";
        std::vector<std::string> vec_Para;
        vec_Para.reserve(100);
        while(input_Para.getline(buffer,100))
        {FO::stringSplit(buffer,' ',vec_Para);
            if(vec_Para.size()>=2)
            {preTranslatePara(vec_Para);
                //                for (int i=0;i<vec_Para.size();i++)
                //                {std::cout<<"vec["<<i<<"]=("<<vec_Para[i]<<") ";}
                //                std::cout<<std::endl;
            }
            else if(vec_Para.size()==1)
            {std::cout<<"Value of KeyWord is not found"<<std::endl;exit(-1);}
            else{continue;}
        }
    }
}
void Swe_movemnt::preTranslatePara(const std::vector<std::string>& vec)
{
    //    "System"
    //    ,"GUI"
    //    ,"Tlt"
    //    ,"Record"
    //    ,"TimeStep"
    //    ,"SourceMode"
    //    ,"Friction"
    std::vector<std::string> kwSource=Data::instance()->get_KeyWord();
    if(vec[0]==kwSource[0]){
        std::cout<<"Found keyword "<<"SystemType"<<std::endl;
        Data::instance()->set_OSType(vec[1]);
        std::cout<<"System is "<<Data::instance()->get_OSType()<<std::endl;
    }
    if(vec[0]==kwSource[1]){
        std::cout<<"Found keyword "<<"GUI"<<std::endl;
        if(vec[1]!=" "&&vec.size()>=2)
        {
            Data::instance()->set_GUIStatus(FO::stringToBool(vec[1]));
            std::cout<<"GUI is "<<vec[1]<<std::endl;
        }
        else{std::cout<<"Miss self-set value of GUI Status"<<std::endl;}
    }
    if(vec[0]==kwSource[2]){
        std::cout<<"Found keyword "<<"Tlt"<<std::endl;
        if(vec[1]!=" "&&vec.size()>=2)
        {
            Data::instance()->set_TotalTime(FO::stringToFloat(vec[1]));
            std::cout<<"Now Totaltime="<<vec[1]<<std::endl;
        }
        else{std::cout<<"Miss self-set value of Tlt"<<std::endl;}
    }
    if (vec[0]==kwSource[3]){
        std::cout<<"Found keyword "<<"Record"<<std::endl;
        if(vec[1]!=" "&&vec.size()>=2)
        {
            Data::instance()->set_IntervalTime(FO::stringToFloat(vec[1]));
            std::cout<<"Now Interval time="<<vec[1]<<std::endl;
        }
        else{std::cout<<"Miss self-set value of interval time"<<std::endl;}

    }
    if (vec[0]==kwSource[4]){
        std::cout<<"Found keyword "<<"TimeStep"<<std::endl;
        if(vec[1]!=" "&&vec.size()>=2)
        {
            Data::instance()->set_TimeStepMode(vec[1]);
            std::cout<<"Now TimeStep Mode="<<vec[1]<<std::endl;
            if(FO::stringToInt(vec[1])==2
                    &&vec.size()==3)
            {Data::instance()->set_DtInitial(FO::stringToFloat(vec[2]));}
        }
        else{std::cout<<"Miss self-set value of TimeStep Mode"<<std::endl;}

    }
    if(vec[0]==kwSource[5]){
        std::cout<<"Found keyword "<<"SourceMode"<<std::endl;
        if(vec[1]!=" "&&vec.size()>=2)
        {
            Data::instance()->set_SourceMode(FO::stringToInt(vec[1]));
            std::cout<<"Now SourceMode Mode="<<vec[1]<<std::endl;
            if(FO::stringToInt(vec[1])==2){
                Data::instance()->set_SourceShape(vec[2]);//sourceShape KW
                if(vec.size()>=7&&vec.size()<=8){
                    if(FO::stringToInt(vec[4])>0){Data::instance()->set_SourceDepth(FO::stringToFloat(vec[3]));}
                    if(FO::stringToInt(vec[4])>=0&&FO::stringToInt(vec[4])<Data::instance()->get_Row()){Data::instance()->set_SourcePoint_X(FO::stringToInt(vec[4]));}
                    if(FO::stringToInt(vec[5])>=0){Data::instance()->set_SourcePoint_Y(FO::stringToInt(vec[5]));}
                    if(FO::stringToInt(vec[6])>=0){Data::instance()->set_SourceLen_X(FO::stringToInt(vec[6]));}
                    if(FO::stringToInt(vec[7])>0){Data::instance()->set_SourceLen_Y(FO::stringToInt(vec[7]));}
                    else{Data::instance()->set_SourceLen_Y(FO::stringToInt(vec[6]));}}
                else{std::cout<<"Variable nums error of keyword SourceMode"<<vec.size()<<std::endl;
                    std::cout<<vec.size()<<std::endl;
                    exit(-1);}}
        }
    }
    if(vec[0]==kwSource[6]){
        std::cout<<"Found keyword "<<"Friction"<<std::endl;
        if(vec[1]!=" "&&vec.size()>=2)
        {
            Data::instance()->set_FrictionModel(FO::stringToInt(vec[1]));
            std::cout<<"Now Friction Mode="<<vec[1]<<std::endl;
            if(vec[1]!=" "&&vec.size()>=2){
                Data::instance()->set_Miu1(FO::stringToFloat(vec[2]));
                if(FO::stringToInt(vec[1])==2){}
                if(FO::stringToInt(vec[1])==3){}
            }
            else{std::cout<<"Variable nums error of keyword Friction"<<std::endl;}
        }
    }
}


