#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <vector>
#include "square.h"


class Board : public QWidget
{
    Q_OBJECT
public:
    Board(int rowCount, int columnCount, int bombs);
    ~Board();

    std::vector<square*> squares;
    std::vector<bool> bombs;

    void getBombCountAndDisplay(int row, int column, bool displayIfZero = false);
    bool getGameResult();
    void showAllValues();
    unsigned int getCountOfClickedCells();
    void setAllCellDisable();
    bool isWin();

private:
    int rows;
    int columns;
    int countOfBombs;

    int calculateNeighbourNumber(int row, int column);


public slots:
    void handleClick(QString value);

signals:
    void onClick(QString value);
};

#endif // BOARD_H
