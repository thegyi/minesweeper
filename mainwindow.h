#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Board *mineBoard;

private:
    Ui::MainWindow *ui;

public slots:
    void handleClick(QString value);
    void on_action10x10_triggered();
    void on_action20x20_triggered();
};
#endif // MAINWINDOW_H
