#ifndef DIALOG_DAM_H
#define DIALOG_DAM_H

#include <QDialog>
#include <QPixmap>
namespace Ui {
class Dialog_dam;
}
class Dialog_dam_View;
class Dialog_dam : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_dam(QWidget *parent = nullptr);
    ~Dialog_dam();
    void paintEvent(QPaintEvent* ev);
    void drawpixmap();

public slots:
    void receive();

private:
    Ui::Dialog_dam *ui;
    QPixmap* _pixmap;
    Dialog_dam_View* _dam_View;
};

#endif // DIALOG_DAM_H
