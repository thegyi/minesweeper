#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>
#include <QRect>
#include <QTime>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mineBoard = new Board(20, 20, 40);
    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(mineBoard);
    connect(mineBoard, &Board::onClick, this, &MainWindow::handleClick);
}

MainWindow::~MainWindow()
{
    delete mineBoard;
    delete ui;
}

void MainWindow::handleClick(QString value)
{
    std::cout << "MainWindow::handleClick" << std::endl;
    if(mineBoard->getGameResult()) {
        QMessageBox msgBox;
        if(mineBoard->isWin())
            msgBox.setText("WIN");
        else
            msgBox.setText("LOOSE");
        mineBoard->setAllCellDisable();
        msgBox.exec();
        return;
    }
    if(value == "Bomb") {
        mineBoard->showAllValues();
    }
}

void MainWindow::on_action10x10_triggered()
{
    if(mineBoard)
        delete mineBoard;
    mineBoard = new Board(10,10,50);
    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(mineBoard);
    layout->setGeometry(QRect(0,0,300,300));
    connect(mineBoard, &Board::onClick, this, &MainWindow::handleClick);
}

void MainWindow::on_action20x20_triggered()
{
    if(mineBoard)
        delete mineBoard;
    mineBoard = new Board(20,20,70);
    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(mineBoard);
    layout->setGeometry(QRect(0,0,500,500));
    connect(mineBoard, &Board::onClick, this, &MainWindow::handleClick);
}
