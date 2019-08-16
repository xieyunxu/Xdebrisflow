#ifndef DIALOG_CHANNEL_H
#define DIALOG_CHANNEL_H

#include <QDialog>

namespace Ui {
class Dialog_channel;
}
class Dialog_channel_view;
class Dialog_channel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_channel(QWidget *parent = nullptr);
    ~Dialog_channel();
    void paintEvent(QPaintEvent* ev);
    void drawpixmap();

public slots:
    void receive();

private:
    Ui::Dialog_channel *ui;
    QPixmap* _pixmap;
    Dialog_channel_view* _channel_View;
};

#endif // DIALOG_CHANNEL_H
