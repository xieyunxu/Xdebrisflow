#ifndef DIALOG_MOVEMENT_H
#define DIALOG_MOVEMENT_H

#include <QDialog>

namespace Ui {
class Dialog_movement;
}
class Dialog_movement_view;
class Dialog_movement : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_movement(QWidget *parent = nullptr);
    ~Dialog_movement();
    void paintEvent(QPaintEvent* ev);
    void     drawpixmap();
public slots:
    void receive();

private:
    Ui::Dialog_movement *ui;
    QPixmap* _pixmap;
    Dialog_movement_view* _movemnt_View;
};

#endif // DIALOG_MOVEMENT_H
