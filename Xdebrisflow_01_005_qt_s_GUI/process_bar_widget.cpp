#include <QThread>
#include <QDebug>
#include "process_bar_widget.h"
#include "ui_process_bar_widget.h"
#include "data.h"
process_bar_widget::process_bar_widget(QWidget *parent)
    :QDialog(parent),
     ui(new Ui::process_bar_widget)
{
    ui->setupUi(this);
    this->setFixedSize(Data::instance()->progressBar_WidgetSize());
    this->move(Data::instance()->upperLeft_Position());
    this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::FramelessWindowHint);
}

process_bar_widget::~process_bar_widget()
{
    delete ui;
}
void process_bar_widget::receive()
{
    std::cout<<"get sig"<<std::endl;
    this->show();
    int total=static_cast<int>(Data::instance()->get_TotalTime());
    ui->progressBar->setRange(0,total);
    ui->progressBar->setValue(0);
    ui->progressBar->update();
}
void process_bar_widget::getCurrtimeSlot(double crt)
{
    //qDebug()<<crt<<endl;
    ui->progressBar->setValue(static_cast<int>(crt));
    ui->progressBar->update();
}
void process_bar_widget::finish()
{
    ui->progressBar->setValue(static_cast<int>(Data::instance()->get_TotalTime()));
    //std::cout<<"get iteration finish sig"<<std::endl;
    QThread::sleep(1);
    this->deleteLater();
}
