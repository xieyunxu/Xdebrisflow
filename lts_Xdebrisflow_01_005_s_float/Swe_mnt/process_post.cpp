#include <fstream>
#include "process_post.h"
#include "process_main.h"
Process_post::Process_post(QObject* parent)
 :QObject(parent), _recordtime(0)
{
}
void Process_post::make_AnimationFile(const Phase& solid,const Process_main& _main)
{
    using namespace std;
    float interval=Data::instance()->get_IntervalTime();
    string opendir=Data::instance()->openDir();
    if (_main._crt<=_recordtime && _main._crt+_main._dt>=_recordtime)
    {
        ofstream outFile;
        std::string ch=Data::instance()->get_char_System();
        outFile.open(opendir+ch+"Output"+ch+"result.dat", ios::app);
        outFile << fixed;
        outFile.precision(3);
        outFile << "Title=\"results_Animation\"" << endl;
        outFile << "VARIABLES = \"X\"  \"Y\"  \"Surface\"  \"Base\" \"Height\"" << endl;
        outFile << "ZONE T= " << "\"" <<_main._crt<< "\"" << " i= " << Data::instance()->get_Row() << " , " << " j= " << Data::instance()->get_Col() << endl;
        for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
        {
            for (int i=1;i<solid.get_PhaseSize().getRow_Size()-1;i++)
            {

                float ix = i * Data::instance()->get_cellSize();
                float iy = j * Data::instance()->get_cellSize();
                outFile << ix << " " << iy << " " << (*solid._Z)[i][j] + (*solid._U[0])[i][j] << " "<< (*solid._Z)[i][j] <<" "<< (*solid._U[0])[i][j] << endl;
            }

        }
        ofstream outFile_snap;
        outFile_snap.open(opendir+ch+"Output"+ch+"snap_crt= "+std::to_string(_main._crt)+" .txt", ios::app);
        outFile_snap<<fixed;
        outFile_snap.precision(3);
        outFile_snap<<"ncols  "<<Data::instance()->get_Col()<<endl;
        outFile_snap<<"nrows  "<<Data::instance()->get_Row()<<endl;
        outFile_snap<<"xllcorner  "<<Data::instance()->get_xCorner()<<endl;
        outFile_snap<<"yllcorner  "<<Data::instance()->get_yCorner()<<endl;
        outFile_snap<<"cellsize  "<<Data::instance()->get_cellSize()<<endl;
        for (int i=1; i<solid.get_PhaseSize().getRow_Size()-1;i++)
        {
            for (int j=1;j<solid.get_PhaseSize().getCol_Size()-1;j++)
            {outFile_snap <<(*solid._U[0])[i][j]<<" ";}
            outFile_snap<<endl;
        }
        emit getCurrtimeSig(_main._crt);
        _recordtime+=interval;
    }
}


