#include "square.h"
#include "qpushbutton.h"
#include <iostream>

square::square(int row, int column, QWidget *parent) : QPushButton(parent) , isBomb(false), row(row), column(column)
{  
    installEventFilter(this);
    setFixedSize(QSize(40,40));
    markedAsBomb = false;
    isClicked = false;
}

void square::setBomb(bool value)
{
    isBomb = value;
}

bool square::getBomb()
{
    return isBomb;
}

bool square::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
        if (keyEvent->button() == Qt::RightButton) {
            if(markedAsBomb) {
                //setText("-");
                QImage image(":/images/default.png");
                QPixmap pixmap = QPixmap::fromImage(image);
                QIcon ButtonIcon(pixmap);
                setIcon(ButtonIcon);
                setIconSize(QSize(50,50));
                markedAsBomb = false;
                isClicked = false;
                emit onClick("-B!");
                return true;
            }
            if(!markedAsBomb) {
                QImage image(":/images/bomb_mark.png");
                QPixmap pixmap = QPixmap::fromImage(image);
                QIcon ButtonIcon(pixmap);
                setIcon(ButtonIcon);
                setIconSize(QSize(50,50));
                markedAsBomb = true;
                isClicked = true;
                //setText("B!");
                emit onClick("B!");
                return true;
            }
        }
        if(keyEvent->button() == Qt::LeftButton) {
            isClicked = true;
            QString result = isBomb? "Bomb": QString::number(row)+":"+QString::number(column);
            if(result == "Bomb") {
                QImage image(":/images/bomb.png");
                QPixmap pixmap = QPixmap::fromImage(image);
                QIcon ButtonIcon(pixmap);
                setIcon(ButtonIcon);
                setIconSize(QSize(50,50));
            }
            emit onClick(result);
        }
    }
    return false;
}

void square::setCounter(int value)
{
    counter = value;
}

int square::getCounter()
{
    return counter;
}

void square::showNumber(bool showBombs)
{
    if(counter >= 0 && counter <= 8) {
        QImage image(":/images/"+QString::number(counter)+".png");
        QPixmap pixmap = QPixmap::fromImage(image);
        QIcon ButtonIcon(pixmap);
        setIcon(ButtonIcon);
        setIconSize(QSize(50,50));
    }
    if(showBombs && isBomb) {
        QImage image(":/images/bomb.png");
        QPixmap pixmap = QPixmap::fromImage(image);
        QIcon ButtonIcon(pixmap);
        setIcon(ButtonIcon);
        setIconSize(QSize(50,50));
    }
    //std::cout << counter << std::endl;
    //setText(QString::number(counter));
}
