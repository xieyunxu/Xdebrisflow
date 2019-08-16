#include "dialog_initiation.h"
#include "ui_dialog_initiation.h"
#include "dialog_initiation_view.h"
#include "data.h"
#include <QPixmap>
#include <QPainter>
Dialog_initiation::Dialog_initiation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_initiation)
{
    _init_View = new Dialog_initiation_view ;
    _pixmap = new QPixmap(Data::instance()->dial_WidgetSize());
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::FramelessWindowHint);
    drawpixmap();
}

Dialog_initiation::~Dialog_initiation()
{
    delete ui;
}

void Dialog_initiation::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,*_pixmap);
    painter.end();
}

void Dialog_initiation::drawpixmap()
{
    QPainter painter;
    painter.begin(_pixmap);
    painter.drawPixmap(0,0,*_init_View->pixmap());
    painter.drawPixmap(0,150,*_init_View->pixmap_white());
    painter.drawPixmap(0,570,*_init_View->pixmap_2());
    painter.end();
}

void Dialog_initiation::receive()
{
    this->exec();

}
