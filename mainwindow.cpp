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
    connect(&Robot, SIGNAL(updateUI(QByteArray)),this, SLOT(affichage(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        Robot.avancer();
    }
    if (event->key() == Qt::Key_S)
    {
        Robot.reculer();
    }
    if (event->key() == Qt::Key_Q)
    {
        Robot.allerGauche();
    }
    if (event->key() == Qt::Key_D)
    {
        Robot.allerDroite();
    }
    if (event->key() == Qt::Key_O)
    {
        Robot.camHaut();
    }
    if (event->key() == Qt::Key_L)
    {
        Robot.camBas();
    }
    if (event->key() == Qt::Key_K)
    {
        Robot.camGauche();
    }
    if (event->key() == Qt::Key_M)
    {
        Robot.camDroite();
    }
}

void MainWindow::on_buttonConnect_clicked()
{
    Robot.doConnect();
}


void MainWindow::on_buttonDisconnect_clicked()
{
    Robot.disConnect();
}


void MainWindow::on_buttonGauche_clicked()
{
    Robot.allerGauche();
}


void MainWindow::on_buttonStop_clicked()
{
    Robot.stop();
}


void MainWindow::on_buttonDroite_clicked()
{
    Robot.allerDroite();
}


void MainWindow::on_buttonAvancer_clicked()
{
    Robot.avancer();
}


void MainWindow::on_buttonReculer_clicked()
{
    Robot.reculer();
}


void MainWindow::affichage(QByteArray data)
{
    // Affichage batterie
    float bat = float(data[2] << 2);
    qDebug() << bat;
    bat = bat/4;
    ui->lcdBatterie->display(int(bat));
}


void MainWindow::on_Hautcam_clicked()
{
    Robot.camHaut();
}

void MainWindow::on_Bascam_clicked()
{
    Robot.camBas();
}

void MainWindow::on_Gauchecam_clicked()
{
    Robot.camGauche();
}

void MainWindow::on_Droitecam_clicked()
{
   Robot.camDroite();
}

