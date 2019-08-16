#ifndef SWE_MOVEMNT_H
#define SWE_MOVEMNT_H
#include <QDebug>
#include <QObject>
class Phase;
class Term;
class Process_pre;
class Process_main;
class Process_post;
class Swe_movemnt:public QObject
{
    Q_OBJECT
public:
    explicit Swe_movemnt(QObject* parent=nullptr);
    ~Swe_movemnt();
    void preChecksize();
    void preCheckinputPara();
    void preTranslatePara(const std::vector<std::string>& vec);
    void init_SWEmnt();
signals:
    void getCurrtimeSig(float crt);
    void sweMntfinishSig();
public slots:
    void running_SWEmnt();
private:
    Phase* _solid;
    Term* _term;
    Process_pre* _pre;
    Process_main* _main;
    Process_post* _post;
    int _countNUm;
};

#endif // SWE_MOVEMNT_H
