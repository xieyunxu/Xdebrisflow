#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QPixmap;
class MainWindow_View;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawpixmap();


private:
    void paintEvent(QPaintEvent* ev);
    Ui::MainWindow *ui;
    QPixmap* _pixmap;
    MainWindow_View* _mainView;
private slots:
    void receive();
    void on_treeWidget_clicked(const QModelIndex &index);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

signals:
    void showDamsetting();
    void showChannelsetting();
    void showInitsetting();
    void showMovemntsetting();
    void showStartSig();
};

#endif // MAINWINDOW_H
