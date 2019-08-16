#ifndef SWE_H
#define SWE_H
#include <QObject>
#include <QThread>
#include <QDebug>
class Swe_movemnt;
class Swe_view;
class Swe:public QObject
{
       Q_OBJECT
public:
    explicit Swe(QObject* parent=nullptr);
    ~Swe();
signals:
    void getCurrtimeSig(double crt);
private:
    Swe_movemnt* _swe_mnt;
    Swe_view* _swe_view;
    QThread* _thread_Mnt;
};

#endif // SWE_H
