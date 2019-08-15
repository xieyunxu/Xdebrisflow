#include "mainwindow.h"
#include "mainwindowview.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <QDebug>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(Data::instance()->main_WidgetSize());
    _mainView = new MainWindow_View;
    _pixmap = new QPixmap(this->size());
    drawpixmap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0,0,*_pixmap);
    painter.end();
}

void MainWindow::drawpixmap()
{
    QPainter painter;
    painter.begin(_pixmap);
    painter.drawPixmap(0,0,*_mainView->pixmap());
    painter.drawPixmap(0,150,*_mainView->pixmap_2());
    painter.drawPixmap(500,150,*_mainView->pixmap_3());
    painter.end();
}

void MainWindow::receive()
{
    this->show();
}

void MainWindow::on_treeWidget_clicked(const QModelIndex &)
{
    qDebug()<<__FUNCTION__<<endl;
}

void MainWindow::on_pushButton_clicked()
{
    emit showDamsetting();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit showChannelsetting();

}

void MainWindow::on_pushButton_3_clicked()
{
    emit showInitsetting();

}

void MainWindow::on_pushButton_4_clicked()
{
    emit showMovemntsetting();
}

void MainWindow::on_pushButton_5_clicked()
{
    emit showStartSig();

}
