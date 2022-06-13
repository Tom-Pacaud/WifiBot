#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "MyRobot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonConnect_clicked();

    void on_buttonDisconnect_clicked();

    void on_buttonGauche_clicked();

    void on_buttonStop_clicked();

    void on_buttonDroite_clicked();

    void on_buttonAvancer_clicked();

    void on_buttonReculer_clicked();

    void affichage(QByteArray data);

    void keyPressEvent(QKeyEvent *event);

    void on_Hautcam_clicked();

    void on_Bascam_clicked();

    void on_Gauchecam_clicked();

    void on_Droitecam_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot Robot;
};
#endif // MAINWINDOW_H
