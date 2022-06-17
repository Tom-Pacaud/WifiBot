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
    if (event->key() == Qt::Key_Space)
    {
        Robot.stop();
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

void MainWindow::affichage(QByteArray data)
{
    // Affichage batterie
    unsigned char dataBat = (data[2] >> 2);
    float bat = float(dataBat);
    if (bat > 125){
        ui->lcdBatterie->display(100);
    }
    else{
        ui->lcdBatterie->display(int(bat)*100/128);
    }

    // Affichage Vitesse
    float vit = float(-data[1] >> 8);
    ui->lcdVitesse->display(int(vit));

    // Affichage Infrarouges
    unsigned char dataInfraDroite = data[4];
    float infraDroite = float(dataInfraDroite);
    ui->lcdInfraDroite->display(int(infraDroite));
    float infraHaut = float(data[11]);
    ui->lcdInfraHaut->display(int(infraHaut));
    float infraGauche = float(data[3]);
    ui->lcdInfraGauche->display(int(infraGauche));
    float infraBas = float(data[12]);
    ui->lcdInfraBas->display(int(infraBas));

    // Affichage Position

    float odometryL = ((((long)data[8] << 24)) + (((long)data[7] << 16)) + (((long)data[6] <<8)) + ((long)data[5]));
    ui->lcdPosL->display(int(odometryL));

    float odometryR = ((((long)data[16] << 24)) + (((long)data[15] << 16)) + (((long)data[14] << 8)) + ((long)data[13]));
    ui->lcdPosR->display(int(odometryR));


}
