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

private:
    int rows;
    int columns;
    int countOfBombs;

public slots:
    void handleClick(QString value);

signals:
    void onClick(QString value);
};

#endif // BOARD_H
