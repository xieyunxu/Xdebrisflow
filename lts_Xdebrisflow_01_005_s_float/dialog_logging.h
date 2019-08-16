#ifndef DIALOG_H
#define DIALOG_H
#include "dialog_logging_view.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog_logging : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_logging(QWidget *parent = nullptr);
    ~Dialog_logging();

private slots:
    void on_pushButton_2_clicked();

    void on_enter_clicked();

    void on_close_clicked();

    void paintEvent(QPaintEvent* event);

    void drawpixmap();

private:
    Ui::Dialog *ui;
    Dialog_logging_view* _logging_View;
    QPixmap* _pixmap;
signals:
    void gotoMainwindow();
};

#endif // DIALOG_H
