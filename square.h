#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class square : public QPushButton
{
    Q_OBJECT
public:
    explicit square(int row, int column, QWidget *parent = nullptr);
    void setBomb(bool value);
    bool getBomb();
    bool eventFilter(QObject *object, QEvent *event);
private:
    bool isBomb;
    int row;
    int column;

signals:
    void onClick(QString position);

};

#endif // SQUARE_H
