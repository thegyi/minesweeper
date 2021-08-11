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
    myboard = new Board(20, 20, 30);
    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(myboard);
    connect(myboard, &Board::onClick, this, &MainWindow::handleClick);
}

MainWindow::~MainWindow()
{
    delete myboard;
    delete ui;
}



void MainWindow::handleClick(QString value)
{
    //delay();
    if(myboard->checkEnd()) {
        QMessageBox msgBox;
        if(myboard->checkWin())
            msgBox.setText("WIN");
        else
            msgBox.setText("LOOSE");
        msgBox.exec();
        return;
    }
    if(value == "Bomb") {
        myboard->showAllValues();
    }
    //std::cout << value.toStdString()<<std::endl;
}

void MainWindow::on_action10x10_triggered()
{
    if(myboard)
        delete myboard;
    myboard = new Board(10,10,20);
    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(myboard);
    layout->setGeometry(QRect(0,0,300,300));
    connect(myboard, &Board::onClick, this, &MainWindow::handleClick);
}


void MainWindow::on_action20x20_triggered()
{
    if(myboard)
        delete myboard;
    myboard = new Board(20,20,70);
    QLayout *layout = ui->centralwidget->layout();
    layout->addWidget(myboard);
    layout->setGeometry(QRect(0,0,500,500));
    connect(myboard, &Board::onClick, this, &MainWindow::handleClick);
}

