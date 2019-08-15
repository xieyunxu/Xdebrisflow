#include "data.h"
#include "dialog_logging.h"
#include "dialog_logging_view.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QDebug>
Dialog_logging::Dialog_logging(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    this->setFixedSize(Data::instance()->log_WidgetSize());
    this->setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::FramelessWindowHint);

    _pixmap = new QPixmap(this->size());
    _logging_View = new Dialog_logging_view;//最后找出来是这一步没有初始化，(这里没有初始化导致这个类的构造器没有被调用，构造器里读取的资源文件里的图片)
    ui->lineEdit->setText(QStringLiteral("admin"));
    ui->lineEdit_2->setText(QStringLiteral("111111"));
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    drawpixmap();

}

Dialog_logging::~Dialog_logging()
{
    delete ui;
}

void Dialog_logging::on_pushButton_2_clicked()
{
    this->close();
}

void Dialog_logging::on_enter_clicked()
{
    if(ui->lineEdit->text() == "admin")
    {
        if(ui->lineEdit_2->text() == "111111")
        {
            this->close();
            emit gotoMainwindow();
        }

    }

}

void Dialog_logging::on_close_clicked()
{
    this->close();

}

void Dialog_logging::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,*_pixmap);
    painter.end();

}

void Dialog_logging::drawpixmap()
{
    QPainter painter;
    painter.begin(_pixmap);
    painter.drawPixmap(0,0,*_logging_View->pixmap());
    painter.end();

}
