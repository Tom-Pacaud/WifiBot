#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include "MyRobot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->load(QUrl(QString("http://192.168.1.106:8080/?action=stream")));
    connect(&Robot, SIGNAL(updateUI(QByteArray)),this, SLOT(updateUI(QByteArray)));
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


void MainWindow::updateUI(const QString &iconText)
{
    Robot.readyRead();
    if(int (Robot.DataReceived[2]) >= 0){
        ui->batterie->setText(QString(int(Robot.DataReceived[2])));

    }
    if(int (Robot.DataReceived[2]) < 0){
        ui->batterie->setText(QString((256 + int (Robot.DataReceived[2]))*100/256));
    }
}

