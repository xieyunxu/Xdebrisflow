#include "dialog_dam.h"
#include "dialog_dam_view.h"
#include "ui_dialog_dam.h"
#include "data.h"
#include <QPainter>
Dialog_dam::Dialog_dam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_dam)
{
    _dam_View = new Dialog_dam_View ;
    _pixmap = new QPixmap(Data::instance()->dial_WidgetSize());
    this->setFixedSize(Data::instance()->dial_WidgetSize());
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::FramelessWindowHint);
    drawpixmap();

}

void Dialog_dam::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,*_pixmap);
    painter.end();
}

void Dialog_dam::drawpixmap()
{
    QPainter painter;
    painter.begin(_pixmap);
    painter.drawPixmap(0,0,*_dam_View->pixmap());
    painter.drawPixmap(0,570,*_dam_View->pixmap_2());
    painter.end();
}
Dialog_dam::~Dialog_dam()
{
    delete ui;
}

void Dialog_dam::receive()
{
    this->exec();

}
