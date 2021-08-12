#include "board.h"
#include <QGridLayout>
#include <iostream>
#include <QTime>
#include <QApplication>

#include <cstdlib>

Board::Board(int rowCount, int columnCount, int bombCount):rows(rowCount), columns(columnCount), countOfBombs(bombCount)
{
    for(int i = 0; i < rows*columns; i++) {
        if(i < countOfBombs)
            bombs.push_back(true);
        else
            bombs.push_back(false);
    }
    int round = rand() % 10;
    for(int i = 0; i < round; i++)
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
        calculateNeighbourNumber(row, column);
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

    getBombCountAndDisplay(row, column);
    emit onClick(value);
    return;
}

void Board::getBombCountAndDisplay(int row, int column, bool displayIfZero)
{
    if(squares[row*columns+column]->bombChecked)
        return;
    int countOfNeighbourBombs = calculateNeighbourNumber(row, column);

    if(displayIfZero) {
        if(squares[row*columns+column]->bombChecked == false) {
            squares[row*columns+column]->showNumber();
            squares[row*columns+column]->bombChecked = true;
            squares[row*columns+column]->imageIsDisplayed = true;
        }
    }
    else {
        squares[row*columns+column]->showNumber();
        squares[row*columns+column]->bombChecked = true;
        squares[row*columns+column]->imageIsDisplayed = true;
    }

    if(countOfNeighbourBombs == 0) {
        if(row > 0) {
            if(column > 0)
                getBombCountAndDisplay(row-1, column-1, true);
            if(column < columns-1)
                getBombCountAndDisplay(row-1, column+1, true);
            getBombCountAndDisplay(row-1, column, true);
        }
        if(column > 0)
            getBombCountAndDisplay(row, column-1, true);
        if(column < columns-1)
            getBombCountAndDisplay(row, column+1, true);
        if(row < rows-1) {
            if(column > 0)
                getBombCountAndDisplay(row+1, column-1, true);
            if(column < columns-1)
                getBombCountAndDisplay(row+1, column+1, true);
            getBombCountAndDisplay(row+1, column, true);

        }
    }
}

int Board::calculateNeighbourNumber(int row, int column)
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

unsigned int Board::getCountOfClickedCells()
{
    unsigned int countOfClicked = 0;
    for(unsigned int i = 0; i < squares.size(); ++i) {
        if(squares[i]->imageIsDisplayed)
            countOfClicked++;
    }
    return countOfClicked;
}

bool Board::getGameResult()
{
    if(getCountOfClickedCells() == squares.size())
        return true;
    else
        return false;
}

void Board::setAllCellDisable()
{
    for(unsigned int i = 0; i < squares.size(); ++i) {
        squares[i]->setEnabled(false);
    }
}

void Board::showAllValues()
{
    for(unsigned int i = 0; i < squares.size(); ++i) {
        squares[i]->showNumber(true);
    }
}

bool Board::isWin()
{
    for(unsigned int i = 0; i < squares.size(); ++i) {
        if(squares[i]->getBomb()) {
            if(!squares[i]->markedAsBomb)
                return false;
        } else {
            if(squares[i]->markedAsBomb)
                return false;
        }
    }
    return true;
}
