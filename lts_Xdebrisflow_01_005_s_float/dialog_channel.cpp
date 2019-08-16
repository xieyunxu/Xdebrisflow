#include "dialog_channel.h"
#include "ui_dialog_channel.h"
#include "dialog_channel_view.h"
#include "data.h"
#include <QPixmap>
#include <QPainter>

Dialog_channel::Dialog_channel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_channel)
{
    _channel_View = new Dialog_channel_view;
    _pixmap = new QPixmap(Data::instance()->dial_WidgetSize());
    ui->setupUi(this);
    this->setFixedSize(Data::instance()->dial_WidgetSize());
    this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::FramelessWindowHint);
    drawpixmap();

}

Dialog_channel::~Dialog_channel()
{
    delete ui;
}

void Dialog_channel::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,*_pixmap);
    painter.end();
}

void Dialog_channel::drawpixmap()
{
    QPainter painter;
    painter.begin(_pixmap);
    painter.drawPixmap(0,0,*_channel_View->pixmap());
    painter.drawPixmap(0,570,*_channel_View->pixmap_2());
    painter.end();
}

void Dialog_channel::receive()
{
    this->exec();

}
