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
    std::vector<bool> Bombs;
    std::vector<bool> bombChecked;
    void checkBombCountAndDisplay(int row, int column, bool displayIfZero = false);
    int markedAsBomb;
    bool checkEnd();
    bool checkWin();

private:
    int rows;
    int columns;
    int countOfBombs;
    int calculateNumber(int row, int column);

public slots:
    void handleClick(QString value);

signals:
    void onClick(QString value);
};

#endif // BOARD_H
