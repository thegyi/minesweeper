#include "board.h"
#include <QGridLayout>
#include <iostream>
#include <QTime>
#include <QApplication>

Board::Board(int rowCount, int columnCount, int bombCount):rows(rowCount), columns(columnCount), countOfBombs(bombCount)
{
    for(int i = 0; i < rows*columns; i++) {
        bombChecked.push_back(false);
        if(i < countOfBombs)
            bombs.push_back(true);
        else
            bombs.push_back(false);
    }
    std::random_shuffle(bombs.begin(), bombs.end());

    QGridLayout *layout = new QGridLayout(this);
    int row = 0;
    int column = 0;
    for(int i = 0; i < rows*columns; ++i) {
        if(column >= columns) {
            row++;
            column = 0;
        }
        square *tmp = new square(row, column, this);
        QImage image(":/images/default.png");
        QPixmap pixmap = QPixmap::fromImage(image);
        QIcon ButtonIcon(pixmap);
        tmp->setIcon(ButtonIcon);
        tmp->setIconSize(QSize(40,40));
        if(bombs[i])
            tmp->setBomb(true);
        squares.push_back(tmp);
        layout->addWidget(tmp, row, column);
        connect(tmp, &square::onClick, this, &Board::handleClick);
        ++column;

    }

    row = 0;
    column = 0;
    for(int i = 0; i < rows*columns; ++i) {
        if(column >= columns) {
            row++;
            column = 0;
        }
        calculateNumber(row, column);
        ++column;
    }

    this->setLayout(layout);
}

Board::~Board()
{
    for(unsigned int i = 0; i < squares.size(); i++) {
        delete squares[i];
        squares[i] = nullptr;
    }
    squares.clear();
}

void Board::handleClick(QString value)
{
    if(value == "B!") {
        emit onClick(value);
        return;
    }
    if(value == "-B!") {
        emit onClick("B!");
        return;
    }
    if(value == "Bomb") {
        emit onClick(value);
        return;
    }

    QStringList values = value.split(":");
    int row = values[0].toInt();
    int column = values[1].toInt();

    checkBombCountAndDisplay(row, column);
}

void Board::checkBombCountAndDisplay(int row, int column, bool displayIfZero)
{
    if(bombChecked[row*columns+column])
        return;
    int countOfNeighbourBombs = calculateNumber(row, column);

    if(displayIfZero) {
        if(/*countOfNeighbourBombs == 0 &&*/ bombChecked[row*columns+column] == false) {
            squares[row*columns+column]->showNumber();//setText(QString::number(countOfNeighbourBombs));
            //squares[row*columns+column]->setEnabled(false);
            bombChecked[row*columns+column] = true;
            squares[row*columns+column]->isClicked = true;
        }
    }
    else {
        squares[row*columns+column]->showNumber();//setText(QString::number(countOfNeighbourBombs));
        bombChecked[row*columns+column] = true;
        squares[row*columns+column]->isClicked = true;
    }

    if(countOfNeighbourBombs == 0) {
        if(row > 0) {
            if(column > 0)
                checkBombCountAndDisplay(row-1, column-1, true);
            if(column < columns-1)
                checkBombCountAndDisplay(row-1, column+1, true);
            checkBombCountAndDisplay(row-1, column, true);
        }
        if(column > 0)
            checkBombCountAndDisplay(row, column-1, true);
        if(column < columns-1)
            checkBombCountAndDisplay(row, column+1, true);
        if(row < rows-1) {
            if(column > 0)
                checkBombCountAndDisplay(row+1, column-1, true);
            if(column < columns-1)
                checkBombCountAndDisplay(row+1, column+1, true);
            checkBombCountAndDisplay(row+1, column, true);

        }
    }
}

int Board::calculateNumber(int row, int column)
{
    int countOfNeighbourBombs = 0;
    if(row >=1) {
        if(squares[(row-1)*columns+column]->getBomb())
            countOfNeighbourBombs++;
        if(column >= 1 && squares[(row-1)*columns+column-1]->getBomb())
            countOfNeighbourBombs++;
        if(column < columns-1 && squares[(row-1)*columns+column+1]->getBomb())
            countOfNeighbourBombs++;
    }
    if(row < rows-1) {
        if(squares[(row+1)*columns+column]->getBomb())
            countOfNeighbourBombs++;
        if(column >= 1 && squares[(row+1)*columns+column-1]->getBomb())
            countOfNeighbourBombs++;
        if(column < columns-1 && squares[(row+1)*columns+column+1]->getBomb())
            countOfNeighbourBombs++;
    }
    if(column >= 1 && squares[row*columns+column-1]->getBomb())
        countOfNeighbourBombs++;
    if(column < columns-1 && squares[row*columns+column+1]->getBomb())
        countOfNeighbourBombs++;

    squares[row*columns+column]->setCounter(countOfNeighbourBombs);
    return countOfNeighbourBombs;
}

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool Board::checkEnd()
{
    int countOfClicked = 0;
    for(unsigned int i = 0; i < squares.size(); ++i) {
        if(squares[i]->isClicked)
            countOfClicked++;
    }
    if( (rows*columns) - countOfClicked < 2)
        delay();
    countOfClicked = 0;
    for(unsigned int i = 0; i < squares.size(); ++i) {
            if(squares[i]->isClicked)
                countOfClicked++;
        }
    if(countOfClicked == rows*columns)
        return true;
    else
        return false;
}

bool Board::checkWin()
{
    for(unsigned int i = 0; i < squares.size(); ++i) {
        if(squares[i]->markedAsBomb) {
            if(bombs[i] == false) {
                return false;
            }
        } else {
            if(bombs[i] == true){
                return false;
            }
        }
    }
    return true;
}

void Board::showAllValues()
{
    for(unsigned int i = 0; i < squares.size(); ++i) {
        squares[i]->showNumber(true);
    }
}
