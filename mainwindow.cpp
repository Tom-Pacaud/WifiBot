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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        Robot.gogogo();
    }
    if (event->key() == Qt::Key_S)
    {
        Robot.nonono();
    }
    if (event->key() == Qt::Key_Q)
    {
        Robot.gotoGauche();
    }
    if (event->key() == Qt::Key_D)
    {
        Robot.gotoDroite();
    }
}


void MainWindow::buttonConnect_clicked()
{
    Robot.doConnect();
}


void MainWindow::buttonDisconnect_clicked()
{
    Robot.disConnect();
}


void MainWindow::buttonGauche_clicked()
{
    Robot.allerGauche();
}


void MainWindow::buttonStop_clicked()
{
    Robot.stop();
}


void MainWindow::buttonDroite_clicked()
{
    Robot.allerDroite();
}


void MainWindow::buttonAvancer_clicked()
{
    Robot.avancer();
}


void MainWindow::buttonReculer_clicked()
{
    Robot.reculer();
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

