/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#include <QtWidgets/QApplication>
#include "mainwindow.h"

static const char* DEFAULTLEXFILENAME = "boglex.txt";
static unsigned int DEFAULTMINWORDLENGTH = 4;
static unsigned int DEFAULTROWS = 4;
static unsigned int DEFAULTCOLS = 4;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const char* lexfilename = DEFAULTLEXFILENAME;
    unsigned int rows = DEFAULTROWS;
    unsigned int cols = DEFAULTCOLS;
    unsigned int minwordlength = DEFAULTMINWORDLENGTH;
    if(argc > 1) lexfilename = argv[1];
    if(argc > 2) minwordlength = atoi(argv[4]);
    if(argc > 3) rows = atoi(argv[2]);
    if(argc > 4) cols = atoi(argv[3]);

    MainWindow w(lexfilename,rows,cols,minwordlength);
    w.show();

    return a.exec();
}
