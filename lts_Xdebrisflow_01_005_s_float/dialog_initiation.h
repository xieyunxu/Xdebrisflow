#ifndef DIALOG_INITIATION_H
#define DIALOG_INITIATION_H

#include <QDialog>

namespace Ui {
class Dialog_initiation;
}
class Dialog_initiation_view;
class Dialog_initiation : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_initiation(QWidget *parent = nullptr);
    ~Dialog_initiation();
    void paintEvent(QPaintEvent* ev);
    void drawpixmap();
public slots:
    void receive();

private:
    Ui::Dialog_initiation *ui;
    QPixmap* _pixmap;
    Dialog_initiation_view* _init_View;
};

#endif // DIALOG_INITIATION_H
