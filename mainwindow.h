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

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    MyRobot Robot;
};
#endif // MAINWINDOW_H
