#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
	
	void keyPressEvent(QKeyEvent *event);

    void updateUI(const QString &iconText);

private:
    Ui::MainWindow *ui;
    MyRobot Robot;
};
#endif // MAINWINDOW_H
