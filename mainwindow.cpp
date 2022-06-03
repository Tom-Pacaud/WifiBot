#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyRobot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Robot.doConnect();
}


void MainWindow::on_pushButton_2_clicked()
{
    Robot.disConnect();
}


void MainWindow::on_pushButton_3_clicked()
{
    Robot.gotoGauche();
}


void MainWindow::on_pushButton_4_clicked()
{
    Robot.stop();
}


void MainWindow::on_pushButton_5_clicked()
{
    Robot.gotoDroite();
}


void MainWindow::on_pushButton_6_clicked()
{
    Robot.gogogo();
}


void MainWindow::on_pushButton_7_clicked()
{
    Robot.nonono();
}

