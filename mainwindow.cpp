/**
 *  CSE 100 C++ Boggle
 *  Authors: Vivek Ramavajjala, Paul Kube
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
#include <QtGui/QResizeEvent>
#include <time.h>
#include <iostream>

static int MSECDELAY = 400; // when highlighting dice 

static std::string toLowerCase(std::string strToConvert){
  std::string res;
  for (std::string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
    res += tolower(*p);
  return res;
}


MainWindow::MainWindow(const char* lexfilename,
		       unsigned int rows, unsigned int cols,
		       unsigned int minwordlength,
		       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->boggle_board = new BoggleBoard(lexfilename, rows, cols);
  this->comp_boggle_player = new BogglePlayer();
  this->comp_boggle_player->buildLexicon(this->boggle_board->lexicon_words);
  this->minWordLength = minwordlength;  

  /*  
  clearGrid();
  */
  ui->centralLayout->setRowMinimumHeight(1, 200);
  ui->centralLayout->setColumnMinimumWidth(1, 200);
  ui->centralWidget->setLayout(ui->centralLayout);
  ui->comp_words_box->setLayout(ui->comp_words_grid);
  ui->human_words_box->setLayout(ui->human_words_grid);
  this->resizeEvent(NULL);

  createNewGrid(rows, cols);
  on_actionNew_Random_triggered(); // start with a random board

}

MainWindow::~MainWindow() {
  destroyGrid();
  delete ui;
  delete boggle_board;
  delete comp_boggle_player;
  delete ui->gridLayout;
}

void MainWindow::createNewGrid(int rows, int cols) {
  /* Won't call destroyGrid() - that is the caller's responsibility!
     Assumes the board is not defined when this function is called. */

  // get a Qfont so we can use a nice font size and style
  // for displaying die faces in our labels
  QFont ourFont;
  ourFont.setPointSize(16);
  ourFont.setBold(true);
  QPalette pal;

  //Initialize the grid
  this->gridLabels = new QLabel**[rows];
  for(int r=0; r<rows; r++)     {
    this->gridLabels[r] = new QLabel*[cols];
    ui->gridLayout->setRowMinimumHeight(r, 40);
    ui->gridLayout->setColumnMinimumWidth(r, 40);
    for(int c=0; c<cols; c++)       {
      this->gridLabels[r][c] = new QLabel();
      this->gridLabels[r][c]->setFixedSize(40, 40);
      this->gridLabels[r][c]->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

      // tell all the labels to use that font, and
      // tell all the labels to center their text horizontally and vertically
      this->gridLabels[r][c]->setFont(ourFont);
      this->gridLabels[r][c]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      ui->gridLayout->addWidget(this->gridLabels[r][c], r, c, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);
    }
  }
  //this->resize(boggle_board->COLS*50 + 300, boggle_board->ROWS*50 + 100);
  //this->resize(0, 0);
}

void MainWindow::destroyGrid() {
  for(unsigned int r=0; r < this->boggle_board->ROWS; r++)     {
    for(unsigned int c=0; c < this->boggle_board->COLS; c++)      {
      delete this->gridLabels[r][c];
    }
    delete[] this->gridLabels[r];
  }
  delete[] this->gridLabels;
  ui->centralLayout->removeItem(ui->centralLayout->itemAtPosition(1, 1));
  delete ui->gridLayout;
  ui->gridLayout = new QGridLayout();
  ui->gridLayout->setContentsMargins(5,5,5,5);
  ui->centralLayout->addLayout(ui->gridLayout,1, 1, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);

}


void MainWindow::clearGrid() {
  for(unsigned int r=0; r < this->boggle_board->ROWS; r++)
    for(unsigned int c=0; c < this->boggle_board->COLS; c++)       {
      this->gridLabels[r][c]->setText("");
      deHighlightCell(r,c);
    }
}


void MainWindow::highlightCell(int r, int c) {
  this->gridLabels[r][c]->setStyleSheet("border-radius:8px;background-color:#ffff00");
}

void MainWindow::deHighlightCell(int r, int c) {
  this->gridLabels[r][c]->setStyleSheet("border-radius:8px;background-color:#eee5aa");
}


void MainWindow::on_actionNew_Random_triggered() {
  /*
    To create a new random game:
    1. Clear all scores, boxes etc.
    2. Destroy old grid (we're not sure what size it is)
    3. Get boggle_board to create new random board
    4. Create new grid
    5. Specify new grid to the comp_player.
  */
  this->ui->humanInput->clear();
  this->ui->humanWords->clear();
  this->ui->computerWords->clear();
  this->ui->computerScore->setText("0");
  this->ui->humanScore->setText("0");
  this->destroyGrid();
  this->boggle_board->initRandomBoard();
  this->createNewGrid(boggle_board->ROWS, boggle_board->COLS);

  this->clearAllHighlights();
  for(unsigned int r=0; r < this->boggle_board->ROWS; r++)
    for(unsigned int c=0; c < this->boggle_board->COLS; c++)
      this->gridLabels[r][c]->setText(this->boggle_board->board[r][c].c_str());

  this->comp_boggle_player->setBoard(this->boggle_board->ROWS, this->boggle_board->COLS,
				     this->boggle_board->board);
  ui->humanInput->setFocus();
  qApp->processEvents();
}


void MainWindow::highlightLocations(std::vector<int> locations, int delay) {
  clearAllHighlights();
  for(unsigned int i=0; i<locations.size(); i++)    {
    std::vector<int> pos =
      this->boggle_board->returnGridLocation(locations[i]);
    qApp->processEvents();
    highlightCell(pos[0], pos[1]);
    qApp->processEvents();
    if(delay>0) {
      sleepMillisec(delay);
    }
  }
}


void MainWindow::clearAllHighlights() {
  for(unsigned int r=0; r < this->boggle_board->ROWS; r++)
    for(unsigned int c=0; c < this->boggle_board->COLS; c++)
      deHighlightCell(r,c);
  qApp->processEvents();
}

void MainWindow::deHighlightLocations(std::vector<int> locations) {
  for(unsigned int i=0;i<locations.size();i++)     {
    std::vector<int> pos = this->boggle_board->returnGridLocation(locations[i]);
    deHighlightCell(pos[0], pos[1]);
  }
  qApp->processEvents();
}

void MainWindow::popMsgBox(const char* msg) {
  QMessageBox msgBox;
  msgBox.setText(msg);
  msgBox.exec();
  ui->humanInput->setFocus();
  qApp->processEvents();
}

void MainWindow::checkAndAddWord(std::string word) {


  /*
  //Not worrying about min word length for humans
  if(word.length()<minWordLength)
  {
  msgBox.setText("Word is too short.");
  msgBox.exec();
  return;
  }
  */
  bool in_lexicon = this->comp_boggle_player->isInLexicon(word);
  if(!in_lexicon)    {
    popMsgBox("Word not in lexicon");
    return;
  }

  for(int i=0; i < ui->humanWords->count(); i++)    {
    if(ui->humanWords->item(i)->text().toStdString().compare(word)==0)   {
      popMsgBox("Word already added.");
      return;
    }
  }

  std::vector<int> pos = this->comp_boggle_player->isOnBoard(word);
  if(pos.size()==0)    {
    popMsgBox("Word does not exist on board.");
    return;
  }

  ui->humanWords->addItem(QString(word.c_str()));
  this->updateScores();
  this->highlightLocations(pos,MSECDELAY);
}

void MainWindow::on_humanInput_returnPressed() {
  std::string word = ui->humanInput->text().toStdString();
  checkAndAddWord(toLowerCase(word));
  ui->humanInput->clear();
  qApp->processEvents();
  sleepMillisec(MSECDELAY);
  this->clearAllHighlights();
}

void MainWindow::on_actionNew_Custom_triggered() {
  this->ui->humanInput->clear();
  this->ui->humanWords->clear();
  this->ui->computerWords->clear();
  this->ui->computerScore->setText("0");
  this->ui->humanScore->setText("0");

  std::string** board_setup;
  unsigned int rows, cols;
  this->comp_boggle_player->getCustomBoard(board_setup, &rows, &cols);
  //  std::cerr << "Custom dims " << rows<<","<<cols<<std::endl;

  if(board_setup!=NULL) {
    this->destroyGrid();
    this->createNewGrid(rows, cols);
    this->boggle_board->setBoard(rows, cols, board_setup);
  }
  else {
    this->destroyGrid();
    this->boggle_board->initRandomBoard();
    this->createNewGrid(this->boggle_board->ROWS, this->boggle_board->COLS);
    this->comp_boggle_player->setBoard(this->boggle_board->ROWS, this->boggle_board->COLS,
				       this->boggle_board->board);
  }

  this->clearAllHighlights();

  for(unsigned int r=0; r < this->boggle_board->ROWS; r++) {
    for(unsigned int c=0; c < this->boggle_board->COLS; c++) {
      this->gridLabels[r][c]->setText(this->boggle_board->board[r][c].c_str());
    }
  }

  this->comp_boggle_player->setBoard(this->boggle_board->ROWS, this->boggle_board->COLS,
				     this->boggle_board->board);

  ui->humanInput->setFocus();
  qApp->processEvents();
}

void MainWindow::updateScores() {
  ui->humanScore->setNum(ui->humanWords->count());
  ui->computerScore->setNum(ui->computerWords->count());
  qApp->processEvents();
}

void MainWindow::sleepMillisec(long int msec)
{
  struct timespec req = {0,0};
  req.tv_sec = 0;
  req.tv_nsec = msec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);
}

void MainWindow::on_computerPlayButton_released() {
  std::set<std::string> validWords;
  // change text in button to "Thinking..."
  this->ui->computerPlayButton->setText("Thinking...");
  this->ui->computerPlayButton->repaint();
  qApp->processEvents();

  this->comp_boggle_player->getAllValidWords(minWordLength, &validWords);
  std::set<std::string>::iterator iter;
  for(iter = validWords.begin(); iter != validWords.end(); iter++)    {
    //    std::vector<int> pos = this->comp_boggle_player->isOnBoard(*iter);
    //    this->highlightLocations(pos, 0); // too slow
    ui->computerWords->addItem(QString(iter->c_str()));
  }
  this->updateScores();
  this->clearAllHighlights();
  // change text back to "Computer Play!"
  this->ui->computerPlayButton->setText("Computer Play!");
  this->ui->computerPlayButton->repaint();
  qApp->processEvents();
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{
  evt = evt;  // to avoid unused var warning
/*
    int w = ui->human_words_box->width();
    int h = ui->human_words_box->height();
    int w1 = ui->comp_words_box->width();
    int h1 = ui->comp_words_box->height();

    int w = (this->width() - boggle_board->COLS*40 - 40)/2;
    int w1 = w;
    int h = (this->height() - 100);
    int h1 = h;
*/

    //ui->humanWords->resize(w - 25, h - 35);
    //ui->computerWords->resize(w1 - 25, h1 - 35);

}
