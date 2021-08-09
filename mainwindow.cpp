#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myboard = new Board(20, 20, 10);
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
    if(myboard->checkEnd()) {
        QMessageBox msgBox;
        if(myboard->checkWin())
            msgBox.setText("WIN");
        else
            msgBox.setText("END");
        msgBox.exec();
        return;
    }
    if(value == "B!") {
        setWindowTitle(QString::number(myboard->markedAsBomb));
        return;
    }
    QMessageBox msgBox;
    msgBox.setText(value);
    msgBox.exec();
}
