#include "square.h"
#include "qpushbutton.h"
#include <iostream>

square::square(int row, int column, QWidget *parent) : QPushButton(parent) , isBomb(false), row(row), column(column)
{  
    connect(this, &QPushButton::released, this, &square::handleButtonClick);
    std::cout << row << "," << column <<std::endl;
    setFixedSize(QSize(40,40));
}

void square::setBomb(bool value)
{
    isBomb = value;
}

bool square::getBomb()
{
    return isBomb;
}

void square::handleButtonClick()
{
    QString result = isBomb? "Bomb": QString::number(row)+":"+QString::number(column);
    setText(result);
    setEnabled(false);
    emit onClick(result);
}
