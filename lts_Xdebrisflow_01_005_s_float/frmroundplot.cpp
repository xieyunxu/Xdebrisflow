#include<QThread>
#include "frmroundplot.h"
#include "ui_frmroundplot2.h"
#include "data.h"
frmRoundPlot::frmRoundPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmRoundPlot)
{
    ui->setupUi(this);
    this->move(Data::instance()->upperRight_Position());
}

frmRoundPlot::~frmRoundPlot()
{delete ui;}

void frmRoundPlot::initForm()
{
    this->show();
    int total=static_cast<int>(Data::instance()->get_TotalTime());
    ui->widget1->setRange(0,total);
    ui->widget1->setValue(0);
    ui->widget1->update();
}

void frmRoundPlot::on_pushButton_clicked()
{}
void frmRoundPlot::getCurrtimeSlot(double crt)
{
//    int setValue=static_cast<int>(100*crt
//            /Data::instance()->get_TotalTime());
    ui->widget1->setValue(crt);
//    if(setValue>=100)
//    {ui->widget1->setValue(100);}
    ui->widget1->update();
}
void frmRoundPlot::finish()
{
    ui->widget1->setValue(static_cast<int>(Data::instance()->get_TotalTime()));
    //std::cout<<"get iteration finish sig"<<std::endl;
    QThread::sleep(1);
    this->deleteLater();
}
