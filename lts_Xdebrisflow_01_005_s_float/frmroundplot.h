#ifndef FRMROUNDPLOT_H
#define FRMROUNDPLOT_H

#include <QWidget>

namespace Ui {
class frmRoundPlot;
}

class frmRoundPlot : public QWidget
{
    Q_OBJECT
public:
    explicit frmRoundPlot(QWidget *parent = 0);
    ~frmRoundPlot();

private:
    Ui::frmRoundPlot *ui;
private slots:
    void initForm();
    void getCurrtimeSlot(double crt);
    void on_pushButton_clicked();
    void finish();
};

#endif // FRMROUNDPLOT_H
