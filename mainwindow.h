/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boggleboard.h"
#include "boggleplayer.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel ***gridLabels;
    BoggleBoard *boggle_board;
    BogglePlayer *comp_boggle_player;
    int minWordLength;
    void createNewGrid(int rows, int cols);
    void destroyGrid();
    void sleepMillisec(long int msec);
    void popMsgBox(const char* msg);
    void clearGrid();
    void highlightCell(int r, int c);
    void deHighlightCell(int r, int c);
    void highlightLocations(std::vector<int> locations, int delay = 50);
    void deHighlightLocations(std::vector<int> locations);
    void updateScores();
    void resizeEvent(QResizeEvent *evt);

public:
    explicit MainWindow(const char* lexfilename,
			unsigned int rows, unsigned int cols,
			unsigned int minwordlength,
			QWidget *parent = 0);
    void clearAllHighlights();
    void checkAndAddWord(std::string word);
    ~MainWindow();

private slots:
    void on_actionNew_Random_triggered();

    void on_humanInput_returnPressed();

    void on_actionNew_Custom_triggered();

    void on_computerPlayButton_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
