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
    void buttonConnect_clicked();

    void buttonDisconnect_clicked();

    void buttonGauche_clicked();

    void buttonStop_clicked();

    void buttonDroite_clicked();

    void buttonAvancer_clicked();

    void buttonReculer_clicked();
	
	void keyPressEvent(QKeyEvent *event);

    void updateUI(const QString &iconText);

private:
    Ui::MainWindow *ui;
    MyRobot Robot;
};
#endif // MAINWINDOW_H
