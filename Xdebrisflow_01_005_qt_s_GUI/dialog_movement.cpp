#include "dialog_movement.h"
#include "ui_dialog_movement.h"
#include "dialog_movement_view.h"
#include "data.h"
#include <QPixmap>
#include <QPainter>

Dialog_movement::Dialog_movement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_movement)
{
    _movemnt_View = new Dialog_movement_view;
    _pixmap = new QPixmap(Data::instance()->dial_WidgetSize());
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::FramelessWindowHint);
    drawpixmap();
}

Dialog_movement::~Dialog_movement()
{
    delete ui;
}

void Dialog_movement::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,*_pixmap);
    painter.end();
}

void Dialog_movement::drawpixmap()
{
    QPainter painter;
    painter.begin(_pixmap);
    painter.drawPixmap(0,0,*_movemnt_View->pixmap());
    painter.drawPixmap(0,150,*_movemnt_View->pixmap_white());
    painter.drawPixmap(0,570,*_movemnt_View->pixmap_2());
    painter.end();
}

void Dialog_movement::receive()
{
    this->exec();

}
