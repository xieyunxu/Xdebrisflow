#ifndef PROCESS_BAR_WIDGET_H
#define PROCESS_BAR_WIDGET_H

#include <QDialog>
#include <QDebug>
namespace Ui {
class process_bar_widget;
}

class process_bar_widget : public QDialog
{
    Q_OBJECT

public:
    explicit process_bar_widget(QWidget *parent = nullptr);
    ~process_bar_widget();
public slots:
    void receive();
    void finish();
    void getCurrtimeSlot(double crt);


private:
    Ui::process_bar_widget* ui;
};

#endif // PROCESS_BAR_WIDGET_H
