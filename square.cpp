#include "square.h"
#include "qpushbutton.h"

square::square(int row, int column, QWidget *parent) : QPushButton(parent) , isBomb(false), row(row), column(column)
{  
    installEventFilter(this);
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

bool square::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
        if (keyEvent->button() == Qt::RightButton) {
            if(text() == "B!") {
                setText("-");
                emit onClick("-B!");
                return true;
            }
            setText("B!");
            emit onClick("B!");
            return true;
        }
        if(keyEvent->button() == Qt::LeftButton) {
            QString result = isBomb? "Bomb": QString::number(row)+":"+QString::number(column);
            //setText(result);
            setEnabled(false);
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

void square::showNumber()
{
    setText(QString::number(counter));
}
