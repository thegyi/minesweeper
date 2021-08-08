#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class square : public QPushButton
{
    Q_OBJECT
public:
    explicit square(int row, int column, QWidget *parent = nullptr);
    void setBomb(bool value);
    bool getBomb();
private:
    bool isBomb;
    int row;
    int column;

signals:
    void onClick(QString position);

private slots:
    void handleButtonClick();
};

#endif // SQUARE_H
